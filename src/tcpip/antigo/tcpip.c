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
#include "control_ir.h"
#include "ir.h"
#include "hardware_profile.h"
#include "touch.h"
#include "timer.h"

#define TASK_1S		(1000/TIMER_TICK)		/* TCP timeout 1 seconds  */
#define TASK_5S		(5000/TIMER_TICK)		/* TCP timeout 5 seconds  */
#define TASK_10S	(10000/TIMER_TICK)	/* TCP timeout 10 seconds */

U8  tcp_soc;
U32 dhcp_tout;

#if USE_UDP		/*Comunicação UDP será usada?*/

U8 udp_soc;
U8 udp_buf[LEN_UDP_BUF];

#endif			/*Fim das declarações para a comunicação via UDP*/

U8 tcp_buf[LEN_TCP_BUF];

FTP_STATE   ftp_state;
TCP_STATE 	tcp_state;
TCP_CNT 	tcp_cnt;
CFG_TCP		cfg_tcp;

//U8 IP_SERV_REMOTE[4] = {192,168,0,32};

/*****************************************************************************
** Function name:		void dhcp_check (void)
**
** Descriptions:		verifica se há servidor DHCP na rede, se não houver então
**									configuramos com ip estático
**
** parameters:			None
**
** Returned value:	None
** 
*****************************************************************************/
void dhcp_check (void)
{
	U8 static_ip[4];
		
	if (dhcp_tout == 0)
		return; 
	
	if (mem_test (&MY_IP, 0, IP_ADRLEN) == __FALSE  && !(dhcp_tout & 0x80000000)) 
	{
		dhcp_tout = 0;
		tcp_state.bit.dhcp = __TRUE;
		printf("\r[IP address (DHCP): %d.%d.%d.%d]\r", MY_IP[0], MY_IP[1], MY_IP[2], MY_IP[3]);
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
		inet_aton((U8*)cfg.tcp.static_ip,static_ip);
		dhcp_tout = 0;
		tcp_state.bit.dhcp = __FALSE;
		MY_IP[0] = static_ip[0];
		MY_IP[1] = static_ip[1];
		MY_IP[2] = static_ip[2];
		MY_IP[3] = static_ip[3];
		printf("\r[IP address (static): %d.%d.%d.%d]\r", MY_IP[0], MY_IP[1], MY_IP[2], MY_IP[3]);
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

#if USE_TCP_SERVER	/*Comunicação TCP SERVER será usada?*/

	char i;
	/*Armazena socket's onde estes serão servidores e se comunicarão com clientes(app's)*/
	for(i=0;i<MAX_NUM_SOC;i++)
	{
		tcp_client_soc[i] = tcp_get_socket(TCP_TYPE_SERVER, 0, 120, tcp_callback_server);	
		tcp_listen(tcp_client_soc[i],atoi((const char*)config.tcp.port_serv_loc));	/*Cada socket ouvirá somente a porta 'LOCAL_PORT_SERVER' */
	}

#endif			/*Fim das declarações para a comunicação via TCP SERVER*/


#if USE_TCP_CLIENT	/*Comunicação TCP CLIENT será usada?*/
	
	/*Armazena socket onde este será cliente e se comunicará com um servidor*/
	tcp_soc = tcp_get_socket(TCP_TYPE_CLIENT, 0, 60000, tcp_callback);
	dhcp_tout = DHCP_TOUT;
	tcp_state.all = 0u;

#endif			/*Fim das declarações para a comunicação via TCP CLIENT*/

#if USE_UDP		/*Comunicação UDP será usada?*/

	/*Inicia socket udp*/
	udp_soc = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS,udp_callback); 
	udp_open(udp_soc, atoi((const char*)cfg.tcp.port_udp));

#endif			/*Fim das declarações para a comunicação via UDP*/

	strcpy((char * )lhost_name,(const char *)cfg.tcp.host_name);
}
/*****************************************************************************
** Function name:		U16 tcp_callback (U8 socket, U8 event, U8 *ptr, U16 par)
**
** Descriptions:		Verificamos os eventos TCP cliente ou servidor
*****************************************************************************/
U16 tcp_callback (U8 socket, U8 event, U8 *ptr, U16 par)
{
	static U8 last_event = TCP_EVT_DATA;
	int i = 0;
	
	switch (event)
	{
		case TCP_EVT_CONREQ:
			return (__TRUE);

		case TCP_EVT_ABORT:
			if(event != last_event)
				printf("\r[Server ABORTED]\r");
			
			last_event = event;
			tcp_state.bit.serverConnected = __FALSE;
			fflush(stdout);
			return (__TRUE);

		case TCP_EVT_CONNECT:
			if(event != last_event)
				printf("\r[Server CONNECTED]\r");
			
			tcp_state.bit.serverConnected = __TRUE;
			last_event = event;
			fflush(stdout);
			return (__TRUE);

		case TCP_EVT_CLOSE:
			if(event != last_event)
				printf("\r[Server CLOSED]\r");
			
			last_event = event;
			tcp_state.bit.serverConnected = __FALSE;
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
			NVIC_DisableIRQ(UART2_IRQn);
			NVIC_DisableIRQ(UART0_IRQn);
			rcv_cmd = RCV_CMD_TCP_SERVER;
			printf("\r*** Receiver packet TCP server: %s",buf_rx);
			fflush(stdout);
			return (__TRUE);
	}
	return (__FALSE);
}
/*****************************************************************************
** Comunicação UDP será usada?
*****************************************************************************/
#if USE_UDP
/*****************************************************************************
** Function name:		U16 udp_callback (U8 socket, U8 *remip, U16 port, U8 *buf, U16 len)
**
** Descriptions:		verificamos os eventos do UDP
*****************************************************************************/
U16 udp_callback (U8 socket, U8 *remip, U16 port, U8 *buf, U16 len)
{
	U16 sz;
	U8 *sndbuf;

  	/* This function is called when UDP data has been received. */
	if(len >= LEN_UDP_BUF)	/*Erro do tamanho do pacote recebido?*/
	{
		printf("\r[Overflow error in the UDP packet size]\r");
		fflush(stdout);
		return 0;
	}
	memset(udp_buf,0,sizeof(udp_buf));
	strncpy((char*)udp_buf,(const char*)buf,len);
	
	/*Informações do pacote*/
	printf("\r*** Receiver Packet UDP: %s\r",udp_buf);
	printf("*** IP: %u.%u.%u.%u\r",remip[0],remip[1],remip[2],remip[3]);	  		
	fflush(stdout);	

	if(strstr((const char *)udp_buf,"H3V3!\0") != NULL)
	{
		sz = strlen ((const char*)lhost_name);
		sndbuf = udp_get_buf (sz);
		str_copy (sndbuf, (U8 *)lhost_name);
		udp_send (udp_soc, remip, port, sndbuf, sz);
	}
  	return 0;
}
/*****************************************************************************
** Function name:		void udPSend (void)
**
** Descriptions:		Envia dados udp 
*****************************************************************************/
void udpSend(U8 *udp_msg) 
{
  	U8 ip[4] = {192,168,1,255};
  	U8 *sendbuf;
  	U16 len;

  	len = strlen ((const char*)udp_msg);
  	sendbuf = udp_get_buf (len);
  	str_copy (sendbuf, udp_msg);

	/*O pacote UDP será broadcast quando o ultimo parâmetro do IP for 255*/
	memcpy(ip,MY_IP,3);
	udp_send (udp_soc, ip, atoi((const char*)cfg.tcp.port_udp), sendbuf, len);
}
#endif
/*****************************************************************************
** Fim das rotinas de comunicação via UDP (quando usada)
*****************************************************************************/

/*****************************************************************************
** Function name:		U16 tcpSend (void)
**
** Descriptions:		Envia dados TCP
*****************************************************************************/
U16 tcpSend (char *p, U8 sz,U8 soc)
{
	U8 *sendbuf,ip[4];

	switch (tcp_get_state (soc))
	{
		case TCP_STATE_FREE:
		case TCP_STATE_CLOSED:

			inet_aton((U8*)cfg.tcp.ip_serv_rem,ip);
			tcp_connect(soc,ip,atoi((const char*)cfg.tcp.port_serv_rem),6000);
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
/*****************************************************************************
** Function name:		U16 tcp_task (void)
**
** Descriptions:		envia dados para o servidor TCP
*****************************************************************************/
void tcp_task(void)
{
	static U32 tcp_timer = 0u, tcp_pck = 0u;

	/****************** instantâneo ********************************/
	if(tcp_state.bit.dataToSend)
	{
		sprintf((char*)tcp_buf,"[%02X.%02X.%02X.%02X.%02X.%02X]\r\n\0",own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);
 		tcpSend((char*)tcp_buf, strlen((const char*)tcp_buf),tcp_soc);
		memset(tcp_buf,0,sizeof(tcp_buf));
		tcp_state.bit.dataToSend = __FALSE;
	}

	/****************** a cada 100ms *******************************/
	if(!tick)
		return;
	++tcp_timer;
	dhcp_check();

	/****************** a cada 1s **********************************/
	if((tcp_timer%TASK_1S))
		return;

	if(!(++tcp_pck % atoi((const char*)cfg.tcp.interval_packet_serv)))
		tcp_state.bit.dataToSend = __TRUE;

		
	/*Houve alteração das cenas via FTP?*/
	if(ftp_state.bit.UpdateScene)	
	{
		printf ("[Scene config via FTP]\r\r");
		fflush(stdout);
		ftp_state.bit.UpdateScene = __FALSE;
		init_scene(0xFF);
	}
	
	/*Houve alteração das configurações TCP via FTP?*/
	if(ftp_state.bit.UpdateTcp)
	{
		printf ("[TCP Config via FTP..Reiniciando]\r\r");
		fflush(stdout);
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


