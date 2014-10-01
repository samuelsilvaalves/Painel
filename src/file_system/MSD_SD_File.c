/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    MSD_SD_FILE.C
 *      Purpose: File manipulation example program
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>                      /* RTL kernel functions & defines      */
#include <LPC17xx.h>
#include <stdio.h>                    /* standard I/O .h-file                */
#include <string.h>   
#include <stdlib.h> 
#include <ctype.h> 
#include "MSD_SD_File.h"
#include "touch.h"
#include "timer.h"
#include "Hardware_Profile.h"
#include "uart.h"

ST_FILES cfg;

WORD_VAL word_val;


char type_dim0[3u];
char type_dim1[3u];
char type_dim2[3u];

/*****************************************************************************
       Initialize a Flash Mass Storage Device         
*****************************************************************************/
char init_msd (void) 
{
  	U32 retv;

	printf("[Iniciando sd card]");
  	while ((retv = finit (NULL)) != 0) 
	{           /* Wait until the MSD is ready*/
    	if (retv == 1) 
		{
      		printf ("...[erro]\r\r");
			return 0x01;
    	}else 
		{
      		printf ("...[nao formatado]\r\r");
			return 0x02;
    	}
  	}
	printf("...[ok]\r\r");
	fflush(stdout);
	return 0x00;
}

/*****************************************************************************
         
*****************************************************************************/
void read_file_cfg(void)
{
	FILE *f;
	/*
		ARQUIVO DE CONFIGURAÇÃO GERAL	
	*/
	printf("[Open file %s]...",FILE_CFG_CFG);
	fflush(stdout);
	f = fopen(FILE_CFG_CFG,"r");
	if(f == NULL)
	{	/*Carrega todas as configurações default*/
		printf("[not found]\r");
		fflush(stdout);
		strcpy(cfg.file.mode_func_ar,DEFAULT_MODE_AR);	
		strcpy(cfg.file.func_ir_scene,DEFAULT_FUNC_IR_SCENE);

		strcpy(type_dim0,DEFAULT_TYPE_DIM0);
		strcpy(type_dim0,DEFAULT_TYPE_DIM1);
		strcpy(type_dim0,DEFAULT_TYPE_DIM2);

		strcpy(strTouchEnaDis,DEFAULT_ENA_DIS_TOUCH);		
	
	}else
	{
		fclose(f);
		printf("[ok]\r");
		fflush(stdout);
		fread_line(cfg.file.mode_func_ar, FILE_CFG_CFG, LINE_MODE_FUNC_AR);
		fread_line(cfg.file.func_ir_scene, FILE_CFG_CFG, LINE_FUNC_IR_SCENE);

		fread_line(type_dim0, FILE_CFG_CFG, LINE_TYPE_DIM0);
		fread_line(type_dim1, FILE_CFG_CFG, LINE_TYPE_DIM1);
		fread_line(type_dim2, FILE_CFG_CFG, LINE_TYPE_DIM2);

		fread_line(strTouchEnaDis, FILE_CFG_CFG, LINE_ENA_DIS_TOUCH);
		
		/*Carrega as configurações default de cada caso, caso aconteça erro */
		if(!cfg.file.mode_func_ar[0])
			strcpy(cfg.file.mode_func_ar,DEFAULT_MODE_AR); 

		if(!cfg.file.func_ir_scene[0])
			strcpy(cfg.file.func_ir_scene,DEFAULT_FUNC_IR_SCENE); 

		if(!type_dim0[0])
			strcpy(type_dim0,DEFAULT_TYPE_DIM0); 

		if(!type_dim1[0])
			strcpy(type_dim1,DEFAULT_TYPE_DIM1);

		if(!type_dim2[0])
			strcpy(type_dim2,DEFAULT_TYPE_DIM2);
			 
		if(!strTouchEnaDis[0])
			strcpy(strTouchEnaDis,DEFAULT_ENA_DIS_TOUCH);	
	}
	
	touchEnaDis = atoi(strTouchEnaDis);	
}
/*****************************************************************************
         
*****************************************************************************/
void read_cfg_tcp(void)
{
	char nibble_lsb=0,nibble_msb=0,i,x,j;//,static_ip[4],car[3],num_rand;
	FILE *f;

	/*
		ARQUIVO DE CONFIGURAÇÃO TCP	
	*/
	printf("[Open file %s]...",FILE_TCP_CFG);
	fflush(stdout);
	f = fopen(FILE_TCP_CFG,"r");
	if(f == NULL)
	{	/*Carrega todas as configurações default*/
		printf("[not found]\r");
		fflush(stdout);
//		srand(own_hw_adr[0]+own_hw_adr[1]+own_hw_adr[2]+own_hw_adr[3]+own_hw_adr[4]+own_hw_adr[5]);
//		inet_aton(DEFAULT_LOC_IP,(U8*)static_ip);
//		while(1)
//		{
//			num_rand = 10 + (rand() % 250);	/*Gera numero aleatorio de 10 - 249. Será o ultimo digito do IP estático*/		
//			if(num_rand<250)
//				break;		
//		}
//		
//		if(num_rand > 99)
//		{
//			car[0] = (num_rand / 100); 		
//			car[1] = (num_rand % 100)/10;
//			car[2] = (num_rand % 100)%10; 
//			sprintf(cfg.tcp.static_ip,"%u.%u.%u.%u%u%u\0",static_ip[0],static_ip[1],static_ip[2],car[0],car[1],car[2]);
//		}else
//		{
//			car[0] = num_rand / 10; 		
//			car[1] = num_rand % 10;
//			sprintf(cfg.tcp.static_ip,"%u.%u.%u.%u%u\0",static_ip[0],static_ip[1],static_ip[2],car[0],car[1]);
//		}
		
		//printf("rand: %u..ip estatico: %s\r\r",num_rand,cfg.tcp.static_ip);
		//fflush(stdout);
		
		strcpy(cfg.tcp.static_ip,DEFAULT_LOC_IP);
		strcpy(cfg.tcp.ip_serv_rem,DEFAULT_REM_IP_SERV);
		strcpy(cfg.tcp.port_serv_rem,DEFAULT_REM_PORT_SERV);
		strcpy(cfg.tcp.interval_packet_serv,DEFAULT_INTERVAL_PAC_SERV);
		strcpy(cfg.tcp.host_name,DEFAULT_HOST_NAME);
		strcpy(cfg.tcp.port_serv_loc,DEFAULT_LOC_PORT_SERV);
		strcpy(cfg.tcp.port_udp,DEFAULT_PORT_UDP);
		//strcpy((char*)cfg.tcp.mac,(const char*)own_hw_adr);
		sprintf(cfg.tcp.mac,"%02X.%02X.%02X.%02X.%02X.%02X\0",own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);
		strcpy(cfg.tcp.ip_app,DEFAULT_IP_APP);
		strcpy(cfg.tcp.mask,DEFAULT_MASK);
		strcpy(cfg.tcp.gateway,DEFAULT_GATEWAY);

		/*O MAC default será o configurado no Net_Config.c*/
	}else
	{
		fclose(f);
		printf("[ok]\r");
		fflush(stdout);
		fread_line(cfg.tcp.static_ip, FILE_TCP_CFG, LINE_STATIC_IP);
		fread_line(cfg.tcp.ip_serv_rem, FILE_TCP_CFG, LINE_IP_SERV_REM);
		fread_line(cfg.tcp.port_serv_rem, FILE_TCP_CFG, LINE_PORT_SERV_REM);
		fread_line(cfg.tcp.interval_packet_serv, FILE_TCP_CFG, LINE_INTERVAL_PACKET_SERV);
		fread_line(cfg.tcp.host_name, FILE_TCP_CFG, LINE_HOST_NAME);
		fread_line(cfg.tcp.port_serv_loc, FILE_TCP_CFG, LINE_PORT_SERV_LOC);
		fread_line(cfg.tcp.port_udp, FILE_TCP_CFG, LINE_PORT_UDP);
		fread_line(cfg.tcp.mac, FILE_TCP_CFG, LINE_MAC);
		fread_line(cfg.tcp.ip_app, FILE_TCP_CFG, LINE_IP_APP);
		fread_line(cfg.tcp.mask, FILE_TCP_CFG, LINE_MASK);
		fread_line(cfg.tcp.gateway, FILE_TCP_CFG, LINE_GATEWAY);

		/*Loop para transformar o MAC (contido no sd) em hexadecimal*/
		for(i=0,x=0;x<6;i+=2,x++)
		{
			cfg.tcp.mac[i]   = tolower(cfg.tcp.mac[i]);
			cfg.tcp.mac[i+1] = tolower(cfg.tcp.mac[i+1]);

			nibble_msb = (cfg.tcp.mac[i]   >= 'a' && cfg.tcp.mac[i]   <= 'f') ? cfg.tcp.mac[i]   - 87 : cfg.tcp.mac[i]   - 48;
			nibble_lsb = (cfg.tcp.mac[i+1] >= 'a' && cfg.tcp.mac[i+1] <= 'f') ? cfg.tcp.mac[i+1] - 87 : cfg.tcp.mac[i+1] - 48;

			own_hw_adr[x] = 0;
			for(j=0;j<4;j++)	
				if(nibble_lsb & (1<<j))
					own_hw_adr[x] |= (1<<j);

			for(j=4;j<8;j++)	
				if(nibble_msb & (1<<j-4))
					own_hw_adr[x] |= (1<<j);

//			for(j=0;j<sizeof(cfg.tcp.mac);j++)
//				if((cfg.tcp.mac[j] < 'a' || cfg.tcp.mac[j] > 'f') && (cfg.tcp.mac[j] < '0' || cfg.tcp.mac[j] > '9'))
//					cfg.tcp.mac[j] = 0;

		}

		/*Carrega as configurações default de cada caso, caso aconteça erro */
		if(!cfg.tcp.static_ip[0]){ printf("[Static IP empty. Loading default]\r");
			strcpy(cfg.tcp.static_ip,DEFAULT_LOC_IP); }
			
		if(!cfg.tcp.ip_serv_rem[0]){ printf("[IP server remote empty. Loading default]\r");			
			strcpy(cfg.tcp.ip_serv_rem,DEFAULT_REM_IP_SERV); }

		if(!cfg.tcp.port_serv_rem[0]){ printf("[Port server remote empty. Loading default]\r");
			strcpy(cfg.tcp.port_serv_rem,DEFAULT_REM_PORT_SERV); }

		if(!cfg.tcp.interval_packet_serv[0]){ printf("[Interval packet empty. Loading default]\r");
			strcpy(cfg.tcp.interval_packet_serv,DEFAULT_INTERVAL_PAC_SERV); }

		if(!cfg.tcp.host_name[0]){ printf("[Host Name empty. Loading default]\r");
			strcpy(cfg.tcp.host_name,DEFAULT_HOST_NAME); }

		if(!cfg.tcp.port_serv_loc[0]) { printf("[Port server local empty. Loading default]\r");
			strcpy(cfg.tcp.port_serv_loc,DEFAULT_LOC_PORT_SERV); }

		if(!cfg.tcp.port_udp[0]){ printf("[Port udp empty. Loading default]\r");
			strcpy(cfg.tcp.port_udp,DEFAULT_PORT_UDP); }

		if(!cfg.tcp.mac[0]){ printf("[Mac empty. Loading default]\r");
			strcpy(cfg.tcp.mac,(const char*)own_hw_adr); }

		if(!cfg.tcp.ip_app[0]){ printf("[IP app empty. Loading default]\r");
			strcpy(cfg.tcp.ip_app,DEFAULT_IP_APP); }

		if(!cfg.tcp.mask[0]){ printf("[Mask empty. Loading default]\r");
			strcpy(cfg.tcp.mask,DEFAULT_MASK); }

		if(!cfg.tcp.gateway[0]){ printf("[Gateway empty. Loading default]\r");
			strcpy(cfg.tcp.gateway,DEFAULT_GATEWAY); }

		fflush(stdout);
	}
}
/*****************************************************************************
         
*****************************************************************************/
void init_file(void)
{	
	read_cfg_tcp();

	read_file_cfg();

#if USE_TCP_CLIENT	/*Comunicação TCP CLIENT será usada?*/
	printf("[Server Port Local: %s]\r",cfg.tcp.port_serv_loc);
#endif

#if USE_TCP_SERVER	/*Comunicação TCP SERVER será usada?*/
	printf("[Server IP: %s]\r",cfg.tcp.ip_serv_rem);
	printf("[Server Port Remoto: %s]\r",cfg.tcp.port_serv_rem);
	#if USE_PCK_SERV
	printf("[Interval Packet: %ss]\r",cfg.tcp.interval_packet_serv);
	#endif
#endif

#if USE_UDP			/*Comunicação TCP SERVER será usada?*/
	printf("[Port UDP: %s]\r",cfg.tcp.port_udp);
#endif
	
	printf("[Static IP: %s]\r",cfg.tcp.static_ip);
	printf("[Static Mask: %s]\r",cfg.tcp.mask);
	printf("[Static Gateway: %s]\r",cfg.tcp.gateway); 
	printf("[Host name: %s]\r",cfg.tcp.host_name);
	printf("[MAC: %s..%02X.%02X.%02X.%02X.%02X.%02X]\r",cfg.tcp.mac,own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);	
	printf("[IP Aplicação: %s]\r",cfg.tcp.ip_app);	
	printf("[Enable/Disable Touch: 0x%X]\r",touchEnaDis);
	printf("[Mode Ar: Swing %s]\r\r",(atoi(cfg.file.mode_func_ar)) ? "In" : "Out");
	
	printf("[Func IR Scene: %s]\r",(atoi(cfg.file.func_ir_scene)) ? "Enable" : "Disable");

	printf("[Type Out Dimmer: 0:%s..1:%s..2:%s]\r\r",atoi(type_dim0) ? "DIMMER":"ONOFF", 
		atoi(type_dim1) ? "DIMMER":"ONOFF", 
		atoi(type_dim2) ? "DIMMER":"ONOFF");
	
	fflush(stdout);
}

/*****************************************************************************
         
*****************************************************************************/
void file_task (void) 
{
	static U8 flag_sd_inserido = __TRUE,flag_read_sd = __FALSE, cnt_init_sd=0;
	static U16 cnt_type_dim=0; 
	char str[15][20],i,j;	

	if(!tick)
		return;

	if(!(++cnt_type_dim % 300))
	{
		sprintf(buf_tx,"TDI %u %u %u!\0", atoi(type_dim0), atoi(type_dim1), atoi(type_dim2)); 
		uart_putString(UART_LINK_LPC,buf_tx);
	}

	if(flag_read_sd)
	{
		flag_read_sd = __FALSE;
		init_scene(0xFF);					/*Realiza a leitura das cenas novamente já que o SD foi inserido*/
	
		for(i=0;i<15;i++)
			memset(str[i],0,sizeof(str[i]));
		/*Copia para ram a configuração (TCP) atual*/
	
		strcpy(str[0],cfg.tcp.static_ip);
		strcpy(str[1],cfg.tcp.ip_serv_rem);
		strcpy(str[2],cfg.tcp.port_serv_rem);
		strcpy(str[3],cfg.tcp.interval_packet_serv);
		strcpy(str[4],cfg.tcp.host_name);
		strcpy(str[5],cfg.tcp.port_serv_loc);
		strcpy(str[6],cfg.tcp.port_udp);
		strcpy(str[7],cfg.tcp.mac);
		strcpy(str[8],cfg.tcp.ip_app);
		strcpy(str[9],cfg.tcp.mask);
		strcpy(str[10],cfg.tcp.gateway);

		for(i=0;i<15;i++)
			for(j=0;j<20;j++)
				if(str[i][j] == '\r' || str[i][j] == '\n')
					str[i][j] = 0;	

//		printf("\r\rAntes...\r");
//		printf("str[0]:%s...%s...\r",str[0],cfg.tcp.static_ip);
//		printf("str[1]:%s...%s...\r",str[1],cfg.tcp.ip_serv_rem);
//		printf("str[2]:%s...%s...\r",str[2],cfg.tcp.port_serv_rem);
//		printf("str[3]:%s...%s...\r",str[3],cfg.tcp.interval_packet_serv);
//		printf("str[4]:%s...%s...\r",str[4],cfg.tcp.host_name);
//		printf("str[5]:%s...%s...\r",str[5],cfg.tcp.port_serv_loc);
//		printf("str[6]:%s...%s...\r",str[6],cfg.tcp.port_udp);
//		printf("str[7]:%s...%s...\r",str[7],cfg.tcp.mac);
//		printf("str[8]:%s...%s...\r",str[8],cfg.tcp.ip_app);
//		printf("str[9]:%s...%s...\r",str[9],cfg.tcp.mask);
//		printf("str[10]:%s...%s...\r",str[10],cfg.tcp.gateway);
//		fflush(stdout); 


		read_cfg_tcp();	/*O cartão foi inserido novamente, então lê a configuração tcp*/

//		printf("\r\rDepois...\r");
//		printf("str[0]:%s...%s...\r",str[0],cfg.tcp.static_ip);
//		printf("str[1]:%s...%s...\r",str[1],cfg.tcp.ip_serv_rem);
//		printf("str[2]:%s...%s...\r",str[2],cfg.tcp.port_serv_rem);
//		printf("str[3]:%s...%s...\r",str[3],cfg.tcp.interval_packet_serv);
//		printf("str[4]:%s...%s...\r",str[4],cfg.tcp.host_name);
//		printf("str[5]:%s...%s...\r",str[5],cfg.tcp.port_serv_loc);
//		printf("str[6]:%s...%s...\r",str[6],cfg.tcp.port_udp);
//		printf("str[7]:%s...%s...\r",str[7],cfg.tcp.mac);
//		printf("str[8]:%s...%s...\r",str[8],cfg.tcp.ip_app);
//		printf("str[9]:%s...%s...\r",str[9],cfg.tcp.mask);
//		printf("str[10]:%s...%s...\r",str[10],cfg.tcp.gateway);
//		fflush(stdout);

		/*Houve diferença da configuração antiga pra atual?*/
		if(strcmp(str[0],cfg.tcp.static_ip)            || strcmp(str[1],cfg.tcp.ip_serv_rem) || strcmp(str[2],cfg.tcp.port_serv_rem) || 
		   strcmp(str[3],cfg.tcp.interval_packet_serv) || strcmp(str[4],cfg.tcp.host_name)   || strcmp(str[5],cfg.tcp.port_serv_loc) || 
		   strcmp(str[6],cfg.tcp.port_udp)             || strcmp(str[7],cfg.tcp.mac)         || strcmp(str[8],cfg.tcp.ip_app)        ||
		   strcmp(str[9],cfg.tcp.mask)                 || strcmp(str[10],cfg.tcp.gateway))
		{
			printf ("[TCP Config via SD..Reiniciando]\r\r");
			fflush(stdout);
			LPC_WDT->WDTC = 0x003FFFF;	/*0.5s*/
			wdt_feed();
			while(1);
		}

		read_file_cfg();	
	}else
	{
		if(!(LPC_GPIO1->FIOPIN & (1 << 25)))	/*SD inserido?*/
		{
			if(!flag_sd_inserido)
			{
				if(++cnt_init_sd >= 20)			/*Tempo para estabilização*/
				{
					flag_sd_inserido = __TRUE;
					cnt_init_sd = 0;			  
					printf("[SD Card Inserido]\r");
					beep(BEEP_CFG);
					fflush(stdout); 
					init_msd();					/*Start again the SD card Inicia novamente o sd*/
					flag_read_sd = __TRUE;
				}	
			}
		}else
		{
			if(flag_sd_inserido)
			{ 
				flag_sd_inserido = __FALSE;
				printf("[SD Card Retirado]\r");
				fflush(stdout);
				beep(BEEP_ERROR); 
			}
		}
	}
}
/*****************************************************************************
** Function name:		BYTE fread_line(BYTE *ptr, (const char*)file, BYTE num_line)
**
** Descriptions:		executa tarefas respectivas ao sd card
**
** parameters:			- ponteiro do buffer para armazenar linha
**									- ponteiro para nome do arquivo
**									- número da linha (linha 0, linha 1,...)
**
** Returned value:	- 0 (ok)
**									- 1 (erro)
**
*****************************************************************************/
/*__inline */char fread_line(char *ptr, const char *file, char num_line)
{
	FILE *f;
	char cur_line = 0;
 	int ch;

	f = fopen(file,"r");
	if(f == NULL)	
		return 1;
	else
	{
		for(;;)
		{
			ch = fgetc(f);

			if(ch == EOF)
			{
				fclose(f);
				return 1;
			}

			if((cur_line == num_line) && (ch != '\r') && (ch != '\n'))
			{
				*ptr = ch;
				ptr++;
			}

			if(ch == '\n')
			{
				*ptr = '\0';
				cur_line++;
				if(cur_line > num_line)
					break;
			}
		}
		fclose(f);
	}
	return 0;
}
/*****************************************************************************
         
*****************************************************************************/
char fwrite_line(char *buf_write, const char *file, char num_line)
{
	FILE *f;
	char cur_line = 0,ptr[100],i;
 	int ch,j=0;
	char lines[50][100],buf[50];

	wdt_feed();

	for(i=0;i<50;i++)
		memset(lines[i],0,sizeof(lines[i]));
	memset(ptr,0,sizeof(ptr));
	memset(buf,0,sizeof(buf));

	strcpy(buf,buf_write);

	f = fopen(file,"r");
	if(f == NULL)	
		return 0;
	else
	{
		for(;;)
		{
			ch = fgetc(f);

			if(ch == EOF || cur_line >= 50)
				break;
			else
			{
				ptr[j] = ch;
				j++;

				if(ch == '\n')
				{
					j=0;
					strcpy(lines[cur_line],ptr);
					memset(ptr,0,sizeof(ptr));
					cur_line++;	
				}
			}
			wdt_feed();
		}
		fclose(f);
	}

	for(i=0;i<strlen(buf);i++)
		if(buf[i] == '\r' || buf[i] == '\n')
			buf[i] = 0;

	memset(lines[num_line],0,sizeof(lines[num_line]));
	strcpy(lines[num_line],buf);
	strcat(lines[num_line],"\r\n\0");

	f = fopen(file,"w");
	if(f == NULL)
		return 0;

	for(j=0;j<cur_line;j++)
	{
		fprintf(f,"%s",lines[j]);
		if(strcmp(file,FILE_CFG_CFG))	//Imprime para debug se não for o arquivo cfg.cfg
		{
			printf("Write...Linha %u: %s",j,lines[j]);
			fflush(stdout);
		}
	}
	fclose(f);

	return 1;
}
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

 //char fwrite_line(char *buf_write, const char *file, char num_line)
//{
//	FILE *f;
//	char cur_line = 0,ptr[100];
// 	int ch,j=0;
//	char lines[50][100];
//
//	memset(lines,0,sizeof(lines));
//	memset(ptr,0,sizeof(ptr));
//
//	f = fopen(file,"r");
//	if(f == NULL)	
//		return 0;
//	else
//	{
//		for(;;)
//		{
//			ch = fgetc(f);
//
//			if(ch == EOF || cur_line >= 50)
//				break;
//			else
//			{
//				ptr[j] = ch;
//				j++;
//
//				if(ch == '\n')
//				{
//					j=0;
//					strcpy(lines[cur_line],ptr);
//					memset(ptr,0,sizeof(ptr));
//					cur_line++;	
//				}
//			}
//		}
//		fclose(f);
//	}
//	
//	strcpy(lines[num_line],buf_write);
//	strcat(lines[num_line],"\r\n\0");
//
//	f = fopen(file,"w");
//	if(f == NULL)
//		return 0;
//
//	for(j=0;j<cur_line;j++)
//		fprintf(f,"%s",lines[j]);
//	fclose(f);
//
//	return 1;
//}
