/****************************************Copyright (c)****************************************************
**								SAPIEN SOLUÇÕES INTELIGENTES
**--------------File Info---------------------------------------------------------------------------------
** File name:           tcpip.c
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:		Sapien S.I.
** Created date:  
** Version:       V1.00
** Descriptions:  
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <RTL.h>
#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tcpip.h"
#include "net_config.h"
#include "generic_type_defs.h"
#include "uart.h"
#include "msd_sd_file.h"
#include "hardware_profile.h"
#include "timer.h"
#include "touch.h"

#define TASK_1S		(1000/TIMER_TICK)		/* TCP timeout 1 seconds  */
#define TASK_5S		(5000/TIMER_TICK)		/* TCP timeout 5 seconds  */
#define TASK_10S	(10000/TIMER_TICK)		/* TCP timeout 10 seconds */
#define TASK_30S	(30000/TIMER_TICK)		/* TCP timeout 10 seconds */


#if USE_TCP_CLIENT				/*Comunicação TCP CLIENT será usada?*/
U8 last_soc_client;				
U8 tcp_client_soc[MAX_NUM_SOC];
#endif

#if USE_TCP_SERVER		/*Comunicação TCP SERVER será usada?*/
U8 tcp_server_soc;
#endif

#if USE_UDP				/*Comunicação UDP será usada?*/
U8 udp_buf[LEN_UDP_BUF];
U8 udp_soc;
#endif

U8   tcp_buf[LEN_TCP_BUF];
U32  dhcp_tout;

TCP_STATE 	tcp_state;
FTP_STATE 	ftp_state;
TCP_CNT 	tcp_cnt;
CFG_TCP		cfg_tcp;

//U8 IP_SERV_REMOTE[4] = {192,168,1,32};


/*****************************************************************************
** Function name:		void dhcp_check (void)
**
** Descriptions:		verifica se há servidor DHCP na rede, se não houver então
**									configuramos com ip estático
**
** parameters:			None
**
** Returned value:		None
** 
*****************************************************************************/
void dhcp_check (void)
{
	U8 ip[4], mask[4], gateway[4],i;
	
	if (dhcp_tout == 0)
		return; 
	
	if (mem_test (&MY_IP, 0, IP_ADRLEN) == __FALSE  && !(dhcp_tout & 0x80000000)) 
	{
		dhcp_tout = 0;
		tcp_state.bit.dhcp = __TRUE;
		printf("\r[IP (DHCP): %d.%d.%d.%d]\r", MY_IP[0], MY_IP[1], MY_IP[2], MY_IP[3]);
		printf("[MASK: %d.%d.%d.%d]\r", MY_MASK[0], MY_MASK[1], MY_MASK[2], MY_MASK[3]);
		printf("[GATEWAY: %d.%d.%d.%d]\r", MY_GATEWAY[0], MY_GATEWAY[1], MY_GATEWAY[2], MY_GATEWAY[3]);
		fflush (stdout);
		return;
	}

	if (--dhcp_tout == 0) 
	{
		dhcp_disable ();
		dhcp_tout = 30 | 0x80000000;
		printf("\r[DHCP failed]\r" );
		fflush (stdout);
   		return;
  	}

	if (dhcp_tout == 0x80000000)
	{
		inet_aton((U8*)cfg.tcp.static_ip,ip);
		inet_aton((U8*)cfg.tcp.mask,mask);
		inet_aton((U8*)cfg.tcp.gateway,gateway);
		dhcp_tout = 0;
		tcp_state.bit.dhcp = __FALSE;
		for(i=0;i<4;i++)
		{
			MY_IP[i] = ip[i];
			MY_MASK[i] = mask[i];
			MY_GATEWAY[i] = gateway[i];
		}
		
		printf("\r[IP (STATIC): %d.%d.%d.%d]\r", MY_IP[0], MY_IP[1], MY_IP[2], MY_IP[3]);
		printf("[MASK: %d.%d.%d.%d]\r", MY_MASK[0], MY_MASK[1], MY_MASK[2], MY_MASK[3]);
		printf("[GATEWAY: %d.%d.%d.%d]\r", MY_GATEWAY[0], MY_GATEWAY[1], MY_GATEWAY[2], MY_GATEWAY[3]);
		fflush (stdout);
		return;
	}
}

/*****************************************************************************
** Function name:		void user_init (void)
**
** Descriptions:		armazenamos socket's livre para o servidor (tcp), clientes (tcp) e conexão udp
**
** parameters:			None
**
** Returned value:		None
** 
****************************************************************************/
void user_init (void)
{
#if USE_TCP_CLIENT	/*Comunicação TCP CLIENT será usada?*/
	
	char i=0;
																									                                  
	/*Armazena socket's onde estes serão servidores e se comunicarão com clientes(app's)*/
	for(i=0;i<MAX_NUM_SOC;i++)
	{
		tcp_client_soc[i] = tcp_get_socket(TCP_TYPE_SERVER, 0, 120, tcp_callback_server);	
		tcp_listen(tcp_client_soc[i],atoi(cfg.tcp.port_serv_loc));	/*Cada socket ouvirá somente a porta 'LOCAL_PORT_SERVER' */
	}
#endif			/*Fim das declarações para a comunicação via TCP CLIENT*/

#if USE_TCP_SERVER	/*Comunicação TCP SERVER será usada?*/

	/*Armazena socket onde este será cliente e se comunicará com um servidor*/
	tcp_server_soc = tcp_get_socket(TCP_TYPE_CLIENT, 0, 60000, tcp_callback_client);

#endif			/*Fim das declarações para a comunicação via TCP SERVER*/

#if USE_UDP		/*Comunicação UDP será usada?*/

	/*Inicia socket udp*/
	udp_soc = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS,udp_callback); 
	udp_open(udp_soc, atoi(cfg.tcp.port_udp));
	
#endif			/*Fim das declarações para a comunicação via UDP*/

	/*Reseta flags tcp*/
	dhcp_tout = DHCP_TOUT;
	tcp_state.all = 0;

	strcpy((char * )lhost_name,cfg.tcp.host_name);
}

#if USE_TCP_SERVER || USE_TCP_CLIENT	/*Comunicação TCP SERVER ou TCP CLIENT será usada?*/

/*****************************************************************************
** Function name:		U16 tcp_callback (U8 socket, U8 event, U8 *ptr, U16 par, U8 modo)
**
** Descriptions:		Verificamos os eventos TCP cliente ou servidor
*****************************************************************************/
U16 tcp_callback (U8 socket, U8 event, U8 *ptr, U16 par, U8 modo)
{
	static U8 last_event = TCP_EVT_DATA;
	int i = 0;
	
	last_event = last_event;
	switch (event)
	{
		case TCP_EVT_CONREQ:
			return (__TRUE);

		case TCP_EVT_ABORT:
			if(modo == CMD_TCP_CALL_SERVER)
				printf("\r[Client socket(%u) ABORTED]\r",socket);
			else
			{
				if(event != last_event)
					printf("\r[Server ABORTED]\r");
				last_event = event;
				tcp_state.bit.serverConnected = __FALSE;
			}
			fflush(stdout);
			return (__TRUE);

		case TCP_EVT_CONNECT:
			if(modo == CMD_TCP_CALL_SERVER)
				printf("\r[Client socket(%u) CONNECTED]\r",socket);
			else
			{	
				if(event != last_event)
					printf("\r[Server CONNECTED]\r");
				last_event = event;
				tcp_state.bit.serverConnected = __TRUE;
			}
			fflush(stdout);
			return (__TRUE);

		case TCP_EVT_CLOSE:
			if(modo == CMD_TCP_CALL_SERVER)
				printf("\r[Client socket(%u) CLOSED]\r",socket);
			else
			{
				if(event != last_event)
					printf("\r[Server CLOSED]\r");
				last_event = event;
				tcp_state.bit.serverConnected = __FALSE;
			}
			fflush(stdout);
			return (__TRUE);

		case TCP_EVT_ACK:
			return (__TRUE);

		case TCP_EVT_DATA:
			if(rcv_cmd)
				break;
			i = 0;
			memset(buf_rx,0,sizeof(buf_rx));
			while(*ptr && (i<100))
			{
				buf_rx[i++] = *ptr;
				if((*ptr == '\r') || (*ptr == '\n') || (*ptr == '!'))
				{
					buf_rx[i] = 0;
					break;
				}
				ptr++;
			}
			//NVIC_DisableIRQ(UART2_IRQn);
			//NVIC_DisableIRQ(UART0_IRQn);
			if(modo == CMD_TCP_CALL_SERVER)
			{
				rcv = rcv_cmd = RCV_CMD_TCP_CLIENT;

#if USE_TCP_CLIENT	/*Comunicação TCP CLIENT será usada?*/	
				last_soc_client = socket;
#endif
				printf("\r*** Receiver packet TCP client socket(%u): %s",socket,buf_rx);		/*Informações do pacote*/ 
			}else
			{
				rcv = rcv_cmd = RCV_CMD_TCP_SERVER;
				printf("\r*** Receiver packet TCP server: %s",buf_rx);
			}
			fflush(stdout);
			return (__TRUE);
	}
	return (__FALSE);
}

/*****************************************************************************
** Function name:		U16 tcp_callback_server (U8 socket, U8 event, U8 *ptr, U16 par)
**
** Descriptions:		Verificamos os eventos do TCP servidor
*****************************************************************************/
U16 tcp_callback_server (U8 socket, U8 event, U8 *ptr, U16 par)
{
	return (tcp_callback (socket, event, ptr, par, CMD_TCP_CALL_SERVER));
}

/*****************************************************************************
** Function name:		U16 tcp_callback_client (U8 socket, U8 event, U8 *ptr, U16 par)
**
** Descriptions:		Verificamos os eventos do TCP cliente
*****************************************************************************/
U16 tcp_callback_client (U8 socket, U8 event, U8 *ptr, U16 par)
{
	return (tcp_callback (socket, event, ptr, par, CMD_TCP_CALL_CLIENT));
}

#endif

#if USE_UDP		/*Comunicação UDP será usada?*/

/*****************************************************************************
** Function name:		U16 udp_callback (U8 socket, U8 *remip, U16 port, U8 *buf, U16 len)
**
** Descriptions:		verificamos os eventos do UDP
*****************************************************************************/
U16 udp_callback (U8 socket, U8 *remip, U16 port, U8 *buf, U16 len)
{
	U16 sz;
	U8 *sndbuf;
	char str[50],aux[8][20];
	int i,z,j;

  	/* This function is called when UDP data has been received. */
	if(len >= LEN_UDP_BUF)	/*Erro do tamanho do pacote recebido?*/
	{
		printf("[Overflow error in the UDP packet size]\r");
		printf("\r[buf:%s]\r",buf);
		fflush(stdout);
		return 0;
	}
	memset(udp_buf,0,sizeof(udp_buf));
	strncpy((char*)udp_buf,(const char*)buf,len);
	
	/*Informações do pacote*/
	printf("\r***[IP: %u.%u.%u.%u] Receiver Packet UDP:%s\r",remip[0],remip[1],remip[2],remip[3],udp_buf);
//	printf("\r*** Receiver Packet UDP: %s\r",udp_buf);
//	printf("*** IP: %u.%u.%u.%u\r",remip[0],remip[1],remip[2],remip[3]);	  		
	fflush(stdout);	

	/*Se receber a mensagem 'motel' via udp retorna para o IP do remetente as informações locais, como host name, IP e MAC*/
	if(strstr((const char *)udp_buf,"motel_all") != NULL)
	{
		sprintf(str,"%s : %u.%u.%u.%u : %02X.%02X.%02X.%02X.%02X.%02X\r\n\0",lhost_name,MY_IP[0],MY_IP[1],MY_IP[2],MY_IP[3],
		                                  own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);
		sz = strlen(str);
		sndbuf = udp_get_buf (sz);
		str_copy(sndbuf, (U8 *)str);
		udp_send (udp_soc, remip, port, sndbuf, sz);

	}else
	if((strstr((const char *)udp_buf,"SET") != NULL))
	{
		if(strlen((const char*)udp_buf) > 20)
		{
			memset(aux,0,sizeof(aux));
			for(i=0,j=0,z=0;i<strlen((const char*)udp_buf);i++)
			{
			    /*Exemplo: 6SET 040045047101:6SET 040045047101:6SET 040045047101*/ 
				if(udp_buf[i] == ':' || udp_buf[i] == '\r')
				{
					z++;
					j=0;
				}else		  
				{
					aux[z][j] = udp_buf[i];	/*Armazena scene z*/
					j++;
				}
			}
			for(i=0;i<NUM_SCENE;i++)
			{
				if((strstr(aux[i], scene[i]) != NULL))
				{ 
					printf("%s já existente na cena %u\r",aux[i],i); 
				}
				else
				{
					cmd_scene(aux[i]); 
					printf("%s...%s\r\n",buf_tx,aux[i]);
				}
				fflush(stdout);
			}
		}else
		{
			if((strstr((const char *)udp_buf,scene[udp_buf[0]]) != NULL))
			{  
				printf("%s já existente na cena %c\r",udp_buf,udp_buf[0]); 
			}
			else
			{
				cmd_scene((char*)udp_buf); 
				printf("%s\r\n",buf_tx);
			}
			fflush(stdout);
			memset(buf_tx,0,sizeof(buf_tx));
		}
	}else
	if(strstr((const char *)udp_buf,"PORT") != NULL)
	{
		for(i=0;i<8;i++)
			memset(aux[i],0,sizeof(aux[i]));
		
		for(i=0,j=0,z=0;i<strlen((const char*)udp_buf);i++)
		{
			/*Exemplo:PORT:5000:7000:6000:192.168.0.15:192.168.0.1<CR>*/
			if(udp_buf[i] == ':' || udp_buf[i] == '\r')
			{
				if(strstr(aux[0],"PORT") != NULL) //Tem "PORT" escrito?
					z=0;
				else
					z++;
				j=0;
				if(udp_buf[i] == '\r')
					break;
			}else		  
			{
				aux[z][j] = udp_buf[i];
				j++;
			}
		}

		j=0;
		if(atoi(cfg.tcp.port_udp) != atoi(aux[0]) && atoi(aux[0]) >= 5000 && atoi(aux[0]) <= 5050)
		{
			j = j + fwrite_line(aux[0], FILE_TCP_CFG, LINE_PORT_UDP);	/*Reinicia*/
			printf("Update Port Udp: %s\r",aux[0]);
			fflush(stdout);	  
		}	 
		
		if(atoi(cfg.tcp.port_serv_loc) != atoi(aux[1]) && atoi(aux[1]) >= 5000 && atoi(aux[1]) <= 5050)
		{
			j = j + fwrite_line(aux[1], FILE_TCP_CFG, LINE_PORT_SERV_LOC);	/*Reinicia*/
			printf("Update Port Tcp Local: %s\r",aux[1]);
			fflush(stdout);
		}
		
		if(atoi(cfg.tcp.port_serv_rem) != atoi(aux[2]) && atoi(aux[2]) >= 5000 && atoi(aux[2]) <= 5050)
		{
			/*j = j +*/  fwrite_line(aux[2], FILE_TCP_CFG, LINE_PORT_SERV_REM);	/*Não precisa reiniciar*/
			strcpy(cfg.tcp.port_serv_rem,aux[2]);
			printf("Update Port Server Remoto: %s\r",cfg.tcp.port_serv_rem);
			fflush(stdout);
		}

		if(strcmp(cfg.tcp.ip_serv_rem,aux[3]) && strlen(aux[3]) > 8)
		{
			/*j = j +*/  fwrite_line(aux[3], FILE_TCP_CFG, LINE_IP_SERV_REM);	/*Não precisa reiniciar*/
			strcpy(cfg.tcp.ip_serv_rem,aux[3]);
			printf("Update IP Server Remoto: %s\r",cfg.tcp.ip_serv_rem);
			fflush(stdout);
		}
		
		if(strcmp(cfg.tcp.ip_app,aux[4]) && strlen(aux[4]) > 8)
		{
			/*j = j +*/  fwrite_line(aux[4], FILE_TCP_CFG, LINE_IP_APP); 	/*Não precisa reiniciar*/
			strcpy(cfg.tcp.ip_app,aux[4]);
			printf("Update IP App: %s\r",cfg.tcp.ip_app);
			fflush(stdout);
		}

		if(j)
		{
			printf ("[TCP Config via UDP..Reiniciando]\r\r");
			fflush(stdout);
			#if USE_TCP_CLIENT	
			for(i=0;i<MAX_NUM_SOC;i++)
				tcp_close (tcp_client_soc[i]);
			#endif
			#if USE_TCP_SERVER	
				tcp_close (tcp_server_soc);
			#endif
			wdt_feed();
			for(i=0;i<5000000;i++)
				for(j=0;j<5000000;j++);
			LPC_WDT->WDTC = 0x3FFFF;	/*0.5s*/
			wdt_feed();
		}

	}else
	if(strstr((const char *)udp_buf,"RST") != NULL)
	{
		printf ("[Reset Solicitado..Reiniciando]\r\r");
		fflush(stdout);
		#if USE_TCP_CLIENT	
		for(i=0;i<MAX_NUM_SOC;i++)
			tcp_close (tcp_client_soc[i]);
		#endif
		#if USE_TCP_SERVER	
			tcp_close (tcp_server_soc);
		#endif
		LPC_WDT->WDTC = 0x003FFFF;	/*0.5s*/
		wdt_feed();
		while(1);
	}

  	return 0;
}

/*****************************************************************************
** Function name:		void udPSendBroadcast (void)
**
** Descriptions:		Envia dados udp para todos os IPs
*****************************************************************************/
void udpSendBroadcast(U8 *udp_msg) 
{
	U8 ip[4];
  	U8 *sendbuf;
  	U16 len;

  	len = strlen ((const char*)udp_msg);
  	sendbuf = udp_get_buf (len);
  	str_copy (sendbuf, udp_msg);

	/*O pacote UDP será broadcast quando o ultimo parâmetro do IP for 255*/
	memcpy(ip,MY_IP,4);
	ip[3] = 255;
	udp_send (udp_soc, ip, atoi(cfg.tcp.port_udp), sendbuf, len);
}

/*****************************************************************************
** Function name:		void udPSendUnicast (void)
**
** Descriptions:		Envia dados udp para um unico IP 
*****************************************************************************/
void udpSendUnicast(U8 *udp_msg,char *strIp) 
{
	U8 ip[4];
  	U8 *sendbuf;
  	U16 len;

  	len = strlen ((const char*)udp_msg);
  	sendbuf = udp_get_buf (len);
  	str_copy (sendbuf, udp_msg);
	inet_aton((U8*)strIp,ip);
	udp_send (udp_soc, ip, atoi(cfg.tcp.port_udp), sendbuf, len);
}
#endif

#if USE_TCP_SERVER || USE_TCP_CLIENT	/*Comunicação TCP SERVER ou TCP CLIENT será usada?*/

/*****************************************************************************
** Function name:		U16 tcpSend (void)
**
** Descriptions:		Envia dados TCP
*****************************************************************************/
U16 tcpSend (char *p, U8 sz,U8 soc,U8 send)
{
	U8 *sendbuf,ip[4];

	switch (tcp_get_state (soc))
	{
		case TCP_STATE_FREE:
		case TCP_STATE_CLOSED:
			if(send == CMD_SEND_TO_SERVER)
			{
				inet_aton((U8*)cfg.tcp.ip_serv_rem,ip);
				tcp_connect(soc,ip,atoi(cfg.tcp.port_serv_rem),atoi(cfg.tcp.port_serv_loc));
			}
			break;

		case TCP_STATE_CONNECT:			
			/* We are connected, send command to remote peer. */
			if(tcp_check_send (soc))
			{
				sendbuf = tcp_get_buf (sz);
				strncpy((char *)sendbuf,(const char *)p,sz);
				if(tcp_send (soc, sendbuf, sz))
					return __TRUE; 	/*Packet Sent*/
				else
					return __FALSE;	/*Send Error*/
			}
		break;
	}
	return __TRUE;
}
#endif

/*****************************************************************************
** Function name:		U16 tcp_task (void)
**
** Descriptions:		envia dados para o servidor TCP
*****************************************************************************/
void tcp_task(void)
{
	static U32 tcp_timer 	= 0u;
	U8 buf_udp[100],i;
			
	/****************** instantâneo ********************************/

#if USE_TCP_SERVER 	/*Comunicação TCP SERVER será usada?*/

	U8 ip[4];

	#if USE_PCK_SERV 
	static U32 cnt_tcp_serv = 0u;

	if(tcp_state.bit.dataToSend)
 	{						
		tcp_state.bit.dataToSend = __FALSE;
		cnt_tcp_serv = 0;

		//if(tcp_buf[0] == 0)		
	 		//sprintf((char*)tcp_buf,"%02X.%02X.%02X.%02X.%02X.%02X\r\n\0",own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);
		
		//tcpSend((char*)tcp_buf, strlen((const char*)tcp_buf), tcp_server_soc, CMD_SEND_TO_SERVER);
		//memset(tcp_buf,0,sizeof(tcp_buf));
	}
	#endif

#endif

	/****************** a cada 100ms *******************************/

	if(!tick)
		return;
	++tcp_timer;
	dhcp_check();

	/****************** a cada 1s **********************************/

	if((tcp_timer%TASK_1S))
		return;

#if USE_TCP_CLIENT
	
	if(!(tcp_timer%TASK_5S)) 
	{
		/*Pacote UDP de identificação*/
		sprintf((char*)buf_udp,"%s %u.%u.%u.%u %02X.%02X.%02X.%02X.%02X.%02X %s %s %u.%u.%u.%u %u.%u.%u.%u\r\n\0",lhost_name,MY_IP[0],MY_IP[1],MY_IP[2],MY_IP[3],
		own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5], cfg.tcp.port_serv_rem, cfg.tcp.ip_serv_rem,
		MY_MASK[0], MY_MASK[1], MY_MASK[2], MY_MASK[3],  MY_GATEWAY[0], MY_GATEWAY[1], MY_GATEWAY[2], MY_GATEWAY[3]);	
										   

		if(!ftp_state.bit.UpdateTcp)
			udpSendBroadcast(buf_udp);
			//udpSendUnicast(buf_udp,cfg.tcp.ip_app);
	}

	if(!(tcp_timer%TASK_30S))	/*A cada 30s*/
	{ 
		/*Mantém o link ativo*/
		//if(tcp_get_state (tcp_client_soc[0]) == TCP_STATE_CONNECT)
		//{
			sprintf(buf_tx,"LOK OK\r\n\0");
			for(i=0;i<MAX_NUM_SOC;i++)
				tcpSend (buf_tx, strlen(buf_tx), tcp_client_soc[i], CMD_SEND_TO_CLIENT);
			//tcpSend (buf_tx, strlen(buf_tx), tcp_client_soc[0], CMD_SEND_TO_CLIENT);
		//}
	}

#endif


#if USE_TCP_SERVER && USE_PCK_SERV 	/*Comunicação TCP SERVER será usada?*/
		
	if(!(++cnt_tcp_serv % atoi(cfg.tcp.interval_packet_serv)))
		tcp_state.bit.dataToSend = __TRUE;

#endif

#if USE_TCP_SERVER	/*Comunicação TCP SERVER será usada?*/

	/*Analisa estado de comunicação com o servidor externo*/
	if(tcp_get_state (tcp_server_soc) != TCP_STATE_CONNECT)
	{
		tcp_state.bit.serverConnected = __FALSE; 
		inet_aton((U8*)cfg.tcp.ip_serv_rem,ip);
		tcp_connect(tcp_server_soc,ip,atoi(cfg.tcp.port_serv_rem),atoi(cfg.tcp.port_serv_loc));
		
	}else
		tcp_state.bit.serverConnected = __TRUE; 
	
#endif	

	/*Houve alteração das cenas via FTP?*/
	if(ftp_state.bit.UpdateScene)	
	{
		printf ("[Scene config via FTP]\r\r");
		fflush(stdout);
		ftp_state.bit.UpdateScene = __FALSE;
		init_scene(0xFF);
	}

	if(ftp_state.bit.UpdateFileCfg)
	{
		printf ("[CFG.CFG configurado via FTP]\r\r");
		fflush(stdout);
		ftp_state.bit.UpdateFileCfg = __FALSE;
		read_file_cfg();
	}
	
	/*Houve alteração das configurações TCP via FTP?*/
	if(ftp_state.bit.UpdateTcp)
	{
		printf ("[TCP Config via FTP..Reiniciando]\r\r");
		fflush(stdout);
				
#if USE_TCP_CLIENT	
		for(i=0;i<MAX_NUM_SOC;i++)
			tcp_close (tcp_client_soc[i]);
#endif
#if USE_TCP_SERVER	
		tcp_close (tcp_server_soc);
#endif
		LPC_WDT->WDTC = 0x003FFFF;	/*0.5s*/
		wdt_feed();
		while(1);
	}			
}


/*****************************************************************************
** Function name:		void inet_aton(U8 *strp, U8 *np)
**
** Descriptions:		passa o endereço IP no formato string para inteiro[4]
**
** parameters:			None
**
** Returned value:	None
** 
*****************************************************************************/
void inet_aton(U8 *strp, U8 *np)
{
	U8 i, j;
	U8 buf[4];

	for(j=0;j<4;j++)
	{
		for(i=0; (*strp!='.') && *strp && (i<4); strp++,i++)
		{
			buf[i] = *strp;
		}
		buf[i] = '\0';
		*np = atoi((const char *)buf);
		np++;
		strp++;
	}
}


//U16 udp_callback (U8 socket, U8 *remip, U16 port, U8 *buf, U16 len)
//{
//	U16 sz;
//	U8 *sndbuf;
//	char str[50];
//
//  	/* This function is called when UDP data has been received. */
//	if(len >= LEN_UDP_BUF)	/*Erro do tamanho do pacote recebido?*/
//	{
//		printf("\r[Overflow error in the UDP packet size]\r");
//		fflush(stdout);
//		return 0;
//	}
//	memset(udp_buf,0,sizeof(udp_buf));
//	strncpy((char*)udp_buf,(const char*)buf,len);
//	
//	/*Informações do pacote*/
//	printf("\r*** Receiver Packet UDP: %s\r",udp_buf);
//	printf("*** IP: %u.%u.%u.%u\r",remip[0],remip[1],remip[2],remip[3]);	  		
//	fflush(stdout);	
//
//	//if(strstr((const char *)udp_buf,(const char*)lhost_name) != NULL)
//	/*Se receber a mensagem 'motel' via udp retorna para o IP do remetente as informações locais, como host name, IP e MAC*/
//	if(strstr((const char *)udp_buf,"motel") != NULL)
//	{
////		sz = strlen ((const char*)lhost_name);
////		sndbuf = udp_get_buf (sz);
////		str_copy (sndbuf, (U8 *)lhost_name);
////		udp_send (udp_soc, remip, port, sndbuf, sz);
//
//		sprintf(str,"%s : %u.%u.%u.%u : %02X.%02X.%02X.%02X.%02X.%02X\r\n\0",lhost_name,MY_IP[0],MY_IP[1],MY_IP[2],MY_IP[3],
//		                                  own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);
//		sz = strlen(str);
//		sndbuf = udp_get_buf (sz);
//		str_copy(sndbuf, (U8 *)str);
//		udp_send (udp_soc, remip, port, sndbuf, sz);
//	}
//  	return 0;
//}


