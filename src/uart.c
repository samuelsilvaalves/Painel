/*----------------------------------------------------------------------------
 * Name:    Serial.c
 * Purpose: MCB1700 Low level serial functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <RTL.H>
#include <LPC17xx.H>					/* LPC17xx definitions */
#include <stdio.h>
#include <ctype.h>                    	/* character functions */
#include <string.h>                   	/* string and memory functions */
#include <stdlib.h> 
#include "hardware_profile.h"
#include "uart.h"
#include "cmds_ir.h"
#include "control_ir.h"
#include "register.h"
#include "touch.h"
#include "timer.h"
#include "tcpip.h"
#include "MSD_SD_File.h"
#include "ir.h"

#define FOSC          12000000
#define FCCLK         (FOSC  * 8)
#define FCCO          (FCCLK * 3)
#define FPCLK         (FCCLK / 4)
#define UART2_BPS     115200
#define UART0_BPS     115200

char buf_tx[160];
char buf_rx[160];
char *lp;
int cntUART2;
int cntUART0;

char rcv_cmd = __FALSE;	/*Flag que sinaliza quando um comando é recebido pela uart*/
char rcv =  __FALSE;

char send_ir(unsigned short addr, int index_file, short PosStart, short PosStop);

/*Estrutura de comandos*/
static const SCMD cmd[] = 
{

/*
** Não alterar as posições dos comandos (a seguir) destinados a função IR
*/

#if USE_IR	/*Inclui na compilação a função IR da placa?*/

  	"IRL",	cmd_ir_learn,			//0				
	"IRS",  cmd_ir_send,			//1
	"IRE",  cmd_ir_erase,			//2
	"IREA", cmd_ir_erase_all,		//3
	"IRR",  cmd_ir_read,			//4

#endif

	"RST", 	cmd_reset_board,		//5

	"TOU", 	cmd_rcv_touch,			//6
	"SCE",  cmd_scene,				//7
	"RSC",  cmd_run_scene,			//8
	"MSG",  cmd_msg_dimmer, 		//9
	"SWI", 	cmd_ar_swing,			//10
	"SET",  cmd_set_real_time,		//11
	"LSC",  cmd_irl_scene,			//12
	"LIA",  cmd_ir_learn_app,		//13
	"SIA",  cmd_ir_send_app,		//14
	"REL",  cmd_rel,				//15
	"FUN",  cmd_ena_dis_func,		//16
	"DTS",  cmd_detect_swing,		//17
	"TDI",  cmd_type_dim,			//18
	"ENT",  cmd_enable_touch,		//19
	"DIT",  cmd_disable_touch		//20
};

#define CMD_COUNT   (sizeof (cmd) / sizeof (cmd[0]))


/*----------------------------------------------------------------------------
 *        Process input string for long or short name entry
 *---------------------------------------------------------------------------*/
char *get_entry (char *cp, char **pNext) 
{
	char *sp, lfn = 0, sep_ch = ' ';

  	if(cp == NULL) 
	{                           
		/* skip NULL pointers */
   		*pNext = cp;
   		return (cp);
  	}
  	for ( ; *cp == ' ' || *cp == '\"'; cp++) 
	{  
		/* skip blanks and starting  " */
   		if (*cp == '\"') 
		{ 
			sep_ch = '\"'; 
			lfn = 1; 
		}
   		*cp = 0;
  	}
  	for (sp = cp; *sp != CR && *sp != LF; sp++) 
  	{
   		if ( lfn && *sp == '\"') 
			break;
   		if (!lfn && *sp == ' ' ) 
			break;
  	}
  	for ( ; *sp == sep_ch || *sp == CR || *sp == LF || *sp == '!'; sp++) 
	{
   		*sp = 0;
   		if ( lfn && *sp == sep_ch) 
		{ 
			sp ++; 
			break; 
		}
  }
  *pNext = (*sp) ? sp : NULL;     /* next entry */
  return (cp);
}
/*****************************************************************************

*****************************************************************************/
void UART0_IRQHandler(void)
{	
	char c;

	NVIC_ClearPendingIRQ(UART0_IRQn);
	c = LPC_UART0->RBR;
	switch (c)
	{
		case CNTLQ:         /*ignore Control S/Q*/             
		case CNTLS:
			break;;

		case BACKSPACE:
		case DEL:
			if (cntUART0 == 0) 
				break;	
			cntUART0--;     /*decrement count*/                
			lp--;           /*and line pointer*/               
			break;

		case ESC:
			*lp = 0;        /*ESC - stop editing line*/        
			lp = buf_rx;
			return;

		case '!': 
		case CR:            /*CR - done, stop editing line*/   
			*lp = c;
			lp++;           /*increment line pointer*/         
			cntUART0++;     /*and count*/                      
			c = LF;

		default:
			*lp = c;
			lp++;           /*increment line pointer*/      
			cntUART0++; 	/*and count*/                   
			break;
  	}
	if((cntUART0 < (sizeof(buf_rx) - 2)  &&  c != LF))  	/*check limit and CR*/           
		return;

	*lp = 0;								/*mark end of string*/        
	rcv = rcv_cmd = RCV_CMD_UART_0;
//	NVIC_DisableIRQ(UART2_IRQn);
//	NVIC_DisableIRQ(UART0_IRQn);
	lp = buf_rx;
	cntUART0 = 0;
}
/*****************************************************************************

*****************************************************************************/
void UART2_IRQHandler(void)
{	
	char c;

	NVIC_ClearPendingIRQ(UART2_IRQn);
	c = LPC_UART2->RBR;
	switch (c)
	{
		case CNTLQ:         /*ignore Control S/Q*/             
		case CNTLS:
			break;;

		case BACKSPACE:
		case DEL:
			if (cntUART2 == 0) 
				break;	
			cntUART2--;     /*decrement count*/                
			lp--;           /*and line pointer*/               
			break;

		case ESC:
			*lp = 0;        /*ESC - stop editing line*/        
			lp = buf_rx;
			return;

		case '!': 
		case CR:            /*CR - done, stop editing line*/   
			*lp = c;
			lp++;           /*increment line pointer*/         
			cntUART2++;     /*and count*/                      
			c = LF;

		default:
			*lp = c;
			lp++;           /*increment line pointer*/      
			cntUART2++; 	/*and count*/                   
			break;
  	}
	if((cntUART2 < (sizeof(buf_rx) - 2)  &&  c != LF))  	/*check limit and CR*/           
		return;

	*lp = 0;								/*mark end of string*/    
	rcv = rcv_cmd = RCV_CMD_UART_2;
	
//	NVIC_DisableIRQ(UART2_IRQn);
//	NVIC_DisableIRQ(UART0_IRQn);
	lp = buf_rx;
	cntUART2 = 0;
}
/*****************************************************************************

*****************************************************************************/
void init_uart (void)
{
	uint16_t usFdiv;

	/* UART0 */
	LPC_PINCON->PINSEL0 |= (1 << 4);
	LPC_PINCON->PINSEL0 |= (1 << 6);	
	LPC_SC->PCONP = LPC_SC->PCONP|(1<<3);	
	LPC_UART0->LCR  = 0x83;
	usFdiv = (FPCLK / 16) / UART0_BPS;
	LPC_UART0->DLM  = usFdiv / 256;
	LPC_UART0->DLL  = usFdiv % 256;
	LPC_UART0->LCR  = 0x03;
	LPC_UART0->IER  = 0x01;		
	LPC_UART0->FCR  = 0x06;

	/* UART2 */
	LPC_PINCON->PINSEL0 |= (1 << 20);
	LPC_PINCON->PINSEL0 |= (1 << 22);	
	LPC_SC->PCONP = LPC_SC->PCONP|(1<<24);
	LPC_UART2->LCR  = 0x83;
	usFdiv = (FPCLK / 16) / UART2_BPS;
	LPC_UART2->DLM  = usFdiv / 256;
	LPC_UART2->DLL  = usFdiv % 256;
	LPC_UART2->LCR  = 0x03;
	LPC_UART2->IER  = 0x01;		
	LPC_UART2->FCR  = 0x06;
	
	lp = buf_rx;
	cntUART2 = 0;
	cntUART0 = 0;
	NVIC_EnableIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
}
/*****************************************************************************

******************************************************************************/
int uart_putChar (int uart, int c) 
{
  	LPC_UART_TypeDef *pUart;

	if(uart == 0 || uart == 1)
		pUart = (uart == 0) ? (LPC_UART_TypeDef *)LPC_UART0 : (LPC_UART_TypeDef *)LPC_UART1;
	else					  
		pUart = (uart == 2) ? (LPC_UART_TypeDef *)LPC_UART2 : (LPC_UART_TypeDef *)LPC_UART3;
	while (!(pUart->LSR & 0x20));
  	return (pUart->THR = c);
}
/*****************************************************************************

******************************************************************************/
int uart_getChar (int uart) 
{
  	LPC_UART_TypeDef *pUart;

	if(uart == 0 || uart == 1)
		pUart = (uart == 0) ? (LPC_UART_TypeDef *)LPC_UART0 : (LPC_UART_TypeDef *)LPC_UART1;
	else					  
		pUart = (uart == 2) ? (LPC_UART_TypeDef *)LPC_UART2 : (LPC_UART_TypeDef *)LPC_UART3;
  	while (!(pUart->LSR & 0x01));
  	return (pUart->RBR);
}
/*****************************************************************************

******************************************************************************/
int uart_getChar_nb (int uart) 
{
  	LPC_UART_TypeDef *pUart;

	if(uart == 0 || uart == 1)
		pUart = (uart == 0) ? (LPC_UART_TypeDef *)LPC_UART0 : (LPC_UART_TypeDef *)LPC_UART1;
	else					  
		pUart = (uart == 2) ? (LPC_UART_TypeDef *)LPC_UART2 : (LPC_UART_TypeDef *)LPC_UART3;
  	if (pUart->LSR & 0x01)
		return (pUart->RBR);	
  	else				  
		return 0;  	
}
/*****************************************************************************

******************************************************************************/
void uart_putString (int uart, char *s) 
{
  	while (*s != 0)
	{
		uart_putChar(uart,*s++); 
	}
}

/*****************************************************************************
Reinicia placa
exemplo: RST!
******************************************************************************/
void cmd_reset_board (char *par) 
{
	LPC_WDT->WDTC = 0x003FFFF;	/*0.5s*/
	wdt_feed();
	while(1);
} 
/*****************************************************************************

*****************************************************************************/
void cmd_ar_swing (char *par) 
{
	char currentCfg = atoi(cfg.file.mode_func_ar); 

	if(par[0] == '1')
	{
		ir_state.bit.ArSwing = __TRUE;
		sprintf(buf_tx,"SWI %u",ir_state.bit.ArSwing);

	}else 
	if(par[0] == '0')
	{
		ir_state.bit.ArSwing = __FALSE;
		sprintf(buf_tx,"SWI %u",ir_state.bit.ArSwing);

	}else 
	if(par[0] == '2')
	{
		memset(buf_tx,0,sizeof(buf_tx));
		if(par[1] == '0')
			strcpy(cfg.file.mode_func_ar,"0\0");
		else 
		if(par[1] == '1')
			strcpy(cfg.file.mode_func_ar,"1\0");	 
		else 
		if(par[1] == '?')
			sprintf(buf_tx,"SWI 2%u",atoi(cfg.file.mode_func_ar));
		else
			sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);

		if(currentCfg != atoi(cfg.file.mode_func_ar)) 
			fwrite_line(cfg.file.mode_func_ar, FILE_CFG_CFG, LINE_MODE_FUNC_AR);
		
		if(!buf_tx[0])	
			sprintf(buf_tx,"SWI 2%u",atoi(cfg.file.mode_func_ar));
	}else
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);		
}

/*****************************************************************************

*****************************************************************************/
void cmd_detect_swing(char *par)
{
	U16 j,n_acertos,n_pulse;

	memset(ir_cmp,0xffff,sizeof(ir_cmp));
	memcpy(ir_cmp,ir,sizeof(ir_cmp));

	cmd_ir_learn_app("0");	
	if(buf_tx[0] == 'E')
		return;

	for(j=0, n_acertos=0, n_pulse=0;j<MAX_QTD_PULSOS;j++)
	{
		if(ir_cmp[j] == 0xffff || ir_cmp[j] < 0x10)
			break;

		n_pulse++;
		if(ir_cmp[j] >= (ir[j] - ((float)ir[j] * 0.3)) && ir_cmp[j] <= (ir[j] + ((float)ir[j] * 0.3)))	/*Cada pulso está dentro do range de 30%?*/
			n_acertos++;		
	}

	printf("[SWING %s...Acertos:%u...All pulse:%u]\r\r",(n_acertos == n_pulse) ? "OUT" : "IN", n_acertos,n_pulse);
	fflush(stdout);

	if(n_acertos == n_pulse)
		sprintf(buf_tx,"OK 1");	/*Ar condicionado do tipo swing out*/	
	else
		sprintf(buf_tx,"OK 0");	/*Ar condicionado do tipo swing in*/	
}

/*****************************************************************************

*****************************************************************************/
//void cmd_type_dim(char *par)
//{
//	char str[20], cfg = __FALSE;
//
//	switch(par[0])
//	{
//		case '0':	strcpy(str, par[1] == '1' ? "TDI 01" : "TDI 00"); 
//					type_dim[0] = (par[1] == '1') ? 1 : 0;	/*1:Dimmer 0:On/Off*/
//					cfg = __TRUE; 
//					break;
//
//		case '1':	strcpy(str, par[1] == '1' ? "TDI 11" : "TDI 10"); 
//					type_dim[1] = (par[1] == '1') ? 1 : 0;	/*1:Dimmer 0:On/Off*/
//					cfg = __TRUE; 
//					break;
//
//		case '2':	strcpy(str, par[1] == '1' ? "TDI 21" : "TDI 20"); 
//					type_dim[2] = (par[1] == '1') ? 1 : 0;	/*1:Dimmer 0:On/Off*/
//					cfg = __TRUE; 
//					break;
//
//		case '>':	type_dim[0] = (par[2] == '1') ? 1 : 0;
//					type_dim[1] = (par[3] == '1') ? 1 : 0;
//					type_dim[2] = (par[4] == '1') ? 1 : 0;
//					sprintf(buf_tx,"OK");
//					break;
//		
//		case '?':	sprintf(buf_tx,"TDI %u %u %u", type_dim[0], type_dim[1], type_dim[2]); 	
//					break;
//		
//		default:	sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);
//					return;
//	}
//
//	if(cfg)
//	{
//		uart_putString(UART_LINK_LPC,str);
//		uart_putString(UART_LINK_LPC,"!\0");
//		sprintf(buf_tx,"OK"); 
//	}
//
//	printf("\r[Type Dimmer's: 0:%s..1:%s..2:%s]\r",type_dim[0] ? "DIMMER":"ONOFF",type_dim[1] ? "DIMMER":"ONOFF",type_dim[2] ? "DIMMER":"ONOFF");
//	fflush(stdout);
//}

/*****************************************************************************

*****************************************************************************/
void cmd_type_dim(char *par)
{
	char str[20], cfg = __FALSE;

	memset(str,0,sizeof(str));
	switch(par[0])
	{	/*TDI 00 (Dimmer 0 On/Off) ou TDI 01 (Dimmer 0 Dimerizável)*/
		case '0':	strcpy(str, par[1] == '1' ? "1\0" : "0\0"); 
					fwrite_line(str, FILE_CFG_CFG, LINE_TYPE_DIM0);
					strcpy(type_dim0,str);
					strcpy(str, par[1] == '1' ? "TDI 01\0" : "TDI 00\0"); 
					cfg = __TRUE; 
					break;

		/*TDI 10 (Dimmer 1 On/Off) ou TDI 11 (Dimmer 1 Dimerizável)*/
		case '1':	strcpy(str, par[1] == '1' ? "1\0" : "0\0"); 
					fwrite_line(str, FILE_CFG_CFG, LINE_TYPE_DIM1);
					strcpy(type_dim1,str);
					strcpy(str, par[1] == '1' ? "TDI 11\0" : "TDI 10\0");
					cfg = __TRUE; 
					break;

		/*TDI 20 (Dimmer 2 On/Off) ou TDI 21 (Dimmer 2 Dimerizável)*/
		case '2':	strcpy(str, par[1] == '1' ? "1\0" : "0\0"); 
					fwrite_line(str, FILE_CFG_CFG, LINE_TYPE_DIM2);
					strcpy(type_dim2,str);
					strcpy(str, par[1] == '1' ? "TDI 21\0" : "TDI 20\0");
					cfg = __TRUE; 
					break;

		case '?':	sprintf(buf_tx,"TDI %u %u %u", atoi(type_dim0), atoi(type_dim1), atoi(type_dim2)); 
					if(rcv_cmd == RCV_CMD_UART_2)
					{
						uart_putString(UART_LINK_LPC,buf_tx);
						uart_putString(UART_LINK_LPC,"!\0");
					}		
					break;
		
		default:	sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);
					return;
	}

	if(cfg)
	{
		uart_putString(UART_LINK_LPC,str);
		uart_putString(UART_LINK_LPC,"!\0");
		sprintf(buf_tx,"OK"); 
	}

	printf("[Type Dimmer's config: 0:%s..1:%s..2:%s]\r",atoi(type_dim0) ? "DIMMER":"ONOFF", 
		atoi(type_dim1) ? "DIMMER":"ONOFF", 
		atoi(type_dim2) ? "DIMMER":"ONOFF");

	fflush(stdout);
}

/*****************************************************************************

*****************************************************************************/
void ena_dis_touch(void)
{
	char str[20];

	sprintf(str,"%u\0",touchEnaDis);
	fwrite_line(str, FILE_CFG_CFG, LINE_ENA_DIS_TOUCH);
	sprintf(buf_tx,"OK");
}
 
/*****************************************************************************

*****************************************************************************/
void cmd_enable_touch(char *par)
{
	if(atoi(par) < QTD_OUTS && par[0])
	{
		if(par[0] == '?')
		{
			sprintf(buf_tx,"ENT %u\0",touchEnaDis);	
			return;
		}
		touchEnaDis |= (1 << atoi(par));
		ena_dis_touch();
	}else
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);	
}

/*****************************************************************************

*****************************************************************************/
void cmd_disable_touch(char *par)
{
	if(atoi(par) < QTD_OUTS && par[0])
	{
		touchEnaDis &= ~(1 << atoi(par));
		ena_dis_touch();
	}else
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);	
}

/*****************************************************************************

*****************************************************************************/
void cmd_set_real_time(char *par) 
{
/*
	exemplo "SET 100.........!"	 //Configura apenas a porcentagem do dimmer 0
	exemplo "SET ...100......!"	 //Configura apenas a porcentagem do dimmer 1
	exemplo "SET ......100...!"	 //Configura apenas a porcentagem do dimmer 2

	exemplo "SET .........1..!"	 //Configura apenas o rele 0 (Liga)
	exemplo "SET .........0..!"	 //Configura apenas o rele 0 (Desliga)
	exemplo "SET ..........1.!"	 //Configura apenas o rele 1 (Liga)
	exemplo "SET ..........0.!"	 //Configura apenas o rele 1 (Desliga)
	exemplo "SET ...........1!"	 //Configura apenas o rele 2 (Liga)
	exemplo "SET ...........0!"	 //Configura apenas o rele 2 (Desliga)
*/

	char str[30],i;

	memset(str,0,sizeof(str));
	strcat(str,"SET ");
	strcat(str,par);

	for(i=0;i<sizeof(str);i++)
		if(str[i] == '\r' || str[i] == '\n' || str[i] == '!')
			str[i] = 0;

	uart_putString(UART_LINK_LPC,str);
	uart_putString(UART_LINK_LPC,"!\0");

	sprintf(buf_tx,"OK"); 
}

/*****************************************************************************

*****************************************************************************/
//void verify_ir_repeat(char *str_IdIr)
//{
//	short i, end=0, lead_in_on, lead_in_off, pos0 = 0, pos1 = 0;
//
//	if(!read_ir(atoi(str_IdIr), FILE_INDEX_INFRARED))	
//		return;
//
//	lead_in_on = ir[0];
//	lead_in_off = ir[1];
//
//	for(i=0; i<MAX_QTD_PULSOS; i++)
//	{
//		if(ir[i] == 0xffff || ir[i] < 0x10)
//		{
//			end = i;
//			break;
//		}
//
//		if(ir[i] < 2 * lead_in_on && ir[i] < 2 * lead_in_off)
//			continue;	
//
//		if(!pos0)
//			pos0 = i;				 /*Armazena a posição inicial*/
//		else 
//		if(!pos1)
//		{
//			pos1 = i-1;				 /*Armazena a posição final*/
//			interval = ir[i] * 4;	/*Intervalo (us) entre os pulsos de repetição*/
//			break;
//		}			
//	}
//	
//	if(pos0 && !pos1)
//		pos1 = end - 1;	
//	
//	for(i=pos0; i<=pos1; i++)
//		printf("ir[%u]:%u\r",i,ir[i]);		
//	fflush(stdout);
//
//	printf("Pos0:%u...Pos1:%u..interval:%u\r",pos0, pos1, interval);
//	fflush(stdout);		
//}


/*****************************************************************************
Envia o mesmo IR repetidamente
*****************************************************************************/
void repeat_IR(char *str_IdIr, char qtd_interval_100ms, char time_start_100ms)
{
	char i, cont=0, start=0;

	memset(buf_rx,0,sizeof(buf_rx));
	NVIC_EnableIRQ(UART2_IRQn);		/*Habilita a interrupção serial para receber a tecla despressionada (TOU 000)*/
	while(1)
	{
		/*Sai do laço caso a tecla deixe de ser pressionada ou aconteça algum erro ao enviar o IR*/	
		if(strstr(buf_rx,"TOU 000") || buf_tx[0] == 'E')
			break;
		else
			cmd_ir_send(str_IdIr);  /*Envia o IR localizado no endereço recebido pela função*/	

		wdt_feed();
		if(!start)	/*Apenas na inicialização*/
		{
			if(time_start_100ms)	/*Existe tempo de start para o IR*/
			{
				while(1)	/*Loop para da um tempo minimo para o primeiro IR enviado*/
				{
					/*Contagem de tempo para comparação com o tempo de Start*/
					timer_poll();
					if(tick)
						if(++cont >= time_start_100ms)break;
				}
			}
			start = 1;	
		}
		/*Continua no laço caso não tenha intervalo de repetição*/
		if(!qtd_interval_100ms)	
			continue;
		/*Contagem de tempo para comparação com o intervalo de repetição*/
		cont=0;
		while(1)
		{
			wdt_feed();
			timer_poll();
			if(tick)
				if(++cont >= qtd_interval_100ms)	/*No primeiro IR demora um pouco mais*/
					break;
		}	
	}
	NVIC_DisableIRQ(UART2_IRQn);		/*Desabilita novamente a interrupção serial*/
	memset(buf_rx,0,sizeof(buf_rx));	
	for(i=TOUCH_0;i<=TOUCH_15;i++)		/*Loop para desligar todos os leds 4x4*/
		out_leds &= ~(1<<i);
	touch_led_press = TOUCH_NONE;

	if(buf_tx[0] == 'E')    /*Houve algum erro ao enviar o IR?*/
	{
		beep(BEEP_ERROR);
		strcat(buf_tx,"\r\r\0");
		uart_putString(0,buf_tx);	/*String de erro*/
	}
}

/*****************************************************************************
Função que recebe o touch pressionado do capacitivo 4x4
*****************************************************************************/
void cmd_rcv_touch(char *par) 
{
	char i,touch,str_IdIr[4],str_aux[50],flag_send_ir = __TRUE;	 

	memset(str_IdIr,0,sizeof(str_IdIr));
	memset(str_aux,0,sizeof(str_aux));
	str_IdIr[0] = par[1];
	str_IdIr[1] = par[2];
	touch = atoi(str_IdIr);	
    
	if(!(touchEnaDis & (1<<touch)))
		return;

	NVIC_DisableIRQ(UART2_IRQn);
	NVIC_DisableIRQ(UART0_IRQn);
	
	if(touch > 23 && (par[0]-48))
	{
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);
		return;
	}

	if(par[0] - 48)	/*Transforma em inteiro*/
	{
		/*Desliga led anterior (IRs) caso ainda esteja ligado*/
		for(i=TOUCH_0;i<=TOUCH_23;i++)
		{
			if(i == TOUCH_11 && !ir_state.bit.PwrPainel)
				out_leds |= (1<<TOUCH_11);
			else
				out_leds &= ~(1 << i);
		}
			
		touch_led_press = touch;
		out_leds |= (1 << touch_led_press);
		atualiza_saidas();

		if(rcv_cmd != RCV_CMD_TCP_CLIENT && rcv_cmd != RCV_CMD_TCP_SERVER)
			beep(BEEP_PULSO);

		/*(TV)->ID0:Source...ID1:CH-...ID2:CH+...ID3:ON...ID4:OFF...ID5:Vol-...ID6:Vol+*/
		
		/*(HOME)->ID7:Source...ID8:VOL-...ID9:VOL+...ID10:ON...ID11:OFF...ID12:PLAY...ID13:PAUSE...ID14:BACK...ID15:NEXT*/
			/*ID16: Cursor Left...ID17: Cursor Righ...ID18: Cursor Down*/
		
		/*(AR)->ID19:16°...ID20:17°............ID33:30°...ID34:ON...ID35:OFF..ID36:SWING ON..ID37:SWING OFF*/

		if(touch == TOUCH_0)	/*Touch referente ao Power da TV*/
		{
			if(!ir_state.bit.PwrTv)strcpy(str_IdIr,ADDR_TV_ON);		/*IR power tv on*/
			else				   strcpy(str_IdIr,ADDR_TV_OFF);	/*IR power tv off*/

			ir_state.bit.PwrTv = !ir_state.bit.PwrTv;
			sprintf(str_aux,"[Touch (%u) POWER %s TV]\r",touch,(ir_state.bit.PwrTv) ? "ON":"OFF");	/*String para debug*/

		}else
		if(touch == TOUCH_1)	/*Touch referente ao Source da TV*/
		{
			strcpy(str_IdIr,ADDR_TV_SCR);		/*IR source tv*/
			sprintf(str_aux,"[SOURCE TV]\r");	/*String para debug*/
				
		}else
		if(touch == TOUCH_2)	/*Touch referente ao CH- da TV*/
		{
			strcpy(str_IdIr,ADDR_TV_CH_DOWN);	/*IR ch- tv*/
			sprintf(str_aux,"[CH- TV]\r");		/*String para debug*/	
			
		}else
		if(touch == TOUCH_3)	/*Touch referente ao CH+ da TV*/									
		{
			strcpy(str_IdIr,ADDR_TV_CH_UP);		/*IR ch+ tv*/
			sprintf(str_aux,"[CH+ TV]\r");		/*String para debug*/	

		}else 
		if(touch == TOUCH_4)	/*Touch referente ao Power Home*/
		{
			if(!ir_state.bit.PwrHome)strcpy(str_IdIr,ADDR_HOME_ON); 	/*IR Power home on*/
			else				     strcpy(str_IdIr,ADDR_HOME_OFF); 	/*IR Power home off*/

			ir_state.bit.PwrHome = !ir_state.bit.PwrHome;
			sprintf(str_aux,"[POWER %s HOME]\r",(ir_state.bit.PwrHome) ? "ON":"OFF");	/*String para debug*/

		}else
		if(touch == TOUCH_5)	/*Touch referente ao Source do Home*/
		{
			strcpy(str_IdIr,ADDR_HOME_SCR);		/*IR source home*/
			sprintf(str_aux,"[SOURCE HOME]\r");	/*String para debug*/

		}else
		if(touch == TOUCH_6)	/*Touch referente ao Volume- da Tv*/
		{
			strcpy(str_IdIr,ADDR_TV_VOL_DOWN);	/*IR vol- tv*/
			sprintf(str_aux,"[VOL- TV]\r");		/*String para debug*/
			
			/*Envia repetidamente o IR apenas se pressionar no teclado. Pelo software executa o IR apenas uma vez*/
			if(rcv_cmd == RCV_CMD_UART_2)		
			{
				repeat_IR(str_IdIr,0,5);		/*ID, Intervalo de repetição(n*100ms) e Intervalo start(ms)*/
				flag_send_ir = __FALSE;
			}	

		}else
		if(touch == TOUCH_7)	/*Touch referente ao Volume+ da Tv*/
		{
			strcpy(str_IdIr,ADDR_TV_VOL_UP);	/*IR vol+ tv*/
			sprintf(str_aux,"[VOL+ TV]\r");		/*String para debug*/
			
			/*Envia repetidamente o IR apenas se pressionar no teclado. Pelo software executa o IR apenas uma vez*/
			if(rcv_cmd == RCV_CMD_UART_2)		
			{
				repeat_IR(str_IdIr,0,5);		/*ID, Intervalo de repetição(n*100ms) e Intervalo start(ms)*/
				flag_send_ir = __FALSE;
			}

		}else
		if(touch == TOUCH_8)	/*Touch referente ao cursor Left do Home*/	
		{
			strcpy(str_IdIr,ADDR_HOME_LEFT);	/*IR left home*/
			sprintf(str_aux,"[LEFT HOME]\r");	/*String para debug*/
			
			/*Envia repetidamente o IR apenas se pressionar no teclado. Pelo software executa o IR apenas uma vez*/
			if(rcv_cmd == RCV_CMD_UART_2)		
			{
				repeat_IR(str_IdIr,0,5);		/*ID, Intervalo de repetição(n*100ms) e Intervalo start(ms)*/
				flag_send_ir = __FALSE;	
			}
			ir_state.bit.PlayPause = __FALSE;	/*Deixa a tecla Play/Pause preparada para enviar o play caso pressionada*/

		}else
		if(touch == TOUCH_9)	/*Touch referente ao cursor Righ do Home*/
		{
			strcpy(str_IdIr,ADDR_HOME_RIGH);	/*IR righ home*/
			sprintf(str_aux,"[RIGH HOME]\r");	/*String para debug*/
			
			/*Envia repetidamente o IR apenas se pressionar no teclado. Pelo software executa o IR apenas uma vez*/
			if(rcv_cmd == RCV_CMD_UART_2)		
			{
				repeat_IR(str_IdIr,0,5);		/*ID, Intervalo de repetição(n*100ms) e Intervalo start(ms)*/
				flag_send_ir = __FALSE;	
			}
			ir_state.bit.PlayPause = __FALSE;	/*Deixa a tecla Play/Pause preparada para enviar o play caso pressionada*/	

		}else
		if(touch == TOUCH_10)	/*Touch referente ao Volume- do Home*/
		{
			strcpy(str_IdIr,ADDR_HOME_VOL_DOWN);	/*IR vol- home*/
			sprintf(str_aux,"[VOL- HOME]\r");		/*String para debug*/
			
			/*Envia repetidamente o IR apenas se pressionar no teclado. Pelo software executa o IR apenas uma vez*/
			if(rcv_cmd == RCV_CMD_UART_2)		
			{
				repeat_IR(str_IdIr,0,5);			/*ID, Intervalo de repetição(n*100ms) e Intervalo start(ms)*/
				flag_send_ir = __FALSE;
			}

		}else
		if(touch == TOUCH_11)	/*Touch referente ao Volume+ do Home*/
		{
			strcpy(str_IdIr,ADDR_HOME_VOL_UP);		/*IR vol+ home*/
			sprintf(str_aux,"[VOL+ HOME]\r");		/*String para debug*/

			/*Envia repetidamente o IR apenas se pressionar no teclado. Pelo software executa o IR apenas uma vez*/
			if(rcv_cmd == RCV_CMD_UART_2)		
			{
				repeat_IR(str_IdIr,0,5);			/*ID, Intervalo de repetição(n*100ms) e Intervalo start(ms)*/
				flag_send_ir = __FALSE;
			}

		}else
		if(touch == TOUCH_12)	/*Touch referente ao cursor Down do home*/	
		{
			strcpy(str_IdIr,ADDR_HOME_DOWN);		/*IR down home*/
			sprintf(str_aux,"[DOWN HOME]\r");		/*String para debug*/
			
			/*Envia repetidamente o IR apenas se pressionar no teclado. Pelo software executa o IR apenas uma vez*/
			if(rcv_cmd == RCV_CMD_UART_2)		
			{
				repeat_IR(str_IdIr,0,5);			/*ID, Intervalo de repetição(n*100ms) e Intervalo start(ms)*/
				flag_send_ir = __FALSE;	
			}
			ir_state.bit.PlayPause = __FALSE;	/*Deixa a tecla Play/Pause preparada para enviar o play caso pressionada*/

		}else
		if(touch == TOUCH_13)	/*Touch referente ao Play/Pause do Home*/	
		{
			if(!ir_state.bit.PlayPause)strcpy(str_IdIr,ADDR_HOME_PLAY); 	/*IR play*/
			else				       strcpy(str_IdIr,ADDR_HOME_PAUSE); 	/*IR pause*/

			ir_state.bit.PlayPause = !ir_state.bit.PlayPause;
			sprintf(str_aux,"[%s HOME]\r",(ir_state.bit.PlayPause)? "PLAY":"PAUSE");	/*String para debug*/

		}else
		if(touch == TOUCH_14)	/*Touch referente ao Back do home*/	
		{
			strcpy(str_IdIr,ADDR_HOME_BACK);	/*IR back home*/
			sprintf(str_aux,"[BACK HOME]\r");	/*String para debug*/

		}else
		if(touch == TOUCH_15)	/*Touch referente ao Next do Home*/	
		{
			strcpy(str_IdIr,ADDR_HOME_NEXT);	/*IR next home*/
			sprintf(str_aux,"[NEXT HOME]\r");	/*String para debug*/

		}else
		if(touch == TOUCH_17)	/*Touch referente ao Power do AR*/	
		{
			if(!ir_state.bit.PwrAr)strcpy(str_IdIr,ADDR_AR_PWR_ON);  /*IR power ar on*/
			else				   strcpy(str_IdIr,ADDR_AR_PWR_OFF); /*IR power ar off*/
						
			ir_state.bit.PwrAr = !ir_state.bit.PwrAr;
			sprintf(str_aux,"[%s] [SWING %s] [IR ID:%s] [POWER %s AR]\r",(atoi(cfg.file.mode_func_ar))? "IN":"OUT", 
				(ir_state.bit.ArSwing)? "ON":"OFF", str_IdIr, (ir_state.bit.PwrAr) ? "ON":"OFF");	/*String para debug*/
		}else
		if(touch == TOUCH_19 || touch == TOUCH_21 || touch == TOUCH_23)
		{
			if(touch == TOUCH_19)
			{
				if(temp_ar < TEMPERATURA_MAX) 
					temp_ar++;
				sprintf(str_IdIr,"%u\0",temp_ar + 3); 	/*IR temp*/

			}else
			if(touch == TOUCH_21)
			{
				if(temp_ar > TEMPERATURA_MIN) 
					temp_ar--;
				sprintf(str_IdIr,"%u\0",temp_ar + 3); 	/*IR temp*/

			}else
			if(touch == TOUCH_23)
			{
				ir_state.bit.ArSwing = !ir_state.bit.ArSwing;			/*IR swing ar*/
				if(atoi(cfg.file.mode_func_ar)) 	/*Swing In (Função swing embutida na temperatura)?*/
					sprintf(str_IdIr,"%u\0",temp_ar + 3);  
				else
				{
					if(!ir_state.bit.ArSwing)strcpy(str_IdIr,ADDR_AR_SWING_ON); 	/*Endereço Swing On*/
					else					 strcpy(str_IdIr,ADDR_AR_SWING_OFF); 	/*Endereço Swing Off*/		 
				}
			}

			sprintf(str_aux,"[%s] [SWING %s] [IR ID:%s] [TEMP %u°]\r",(atoi(cfg.file.mode_func_ar))? "IN":"OUT", 
			   (ir_state.bit.ArSwing)? "ON":"OFF", str_IdIr, temp_ar);	/*String para debug*/

		}else
		{
			/*nenhuma função para o touch recebido*/
			return;
		}

		if(flag_send_ir)		/*Precisa enviar IR?*/
		{
			cmd_ir_send(str_IdIr);	/*Chama função que envia o ir cujo id do ir é pasado como parâmetro*/
			if(buf_tx[0] == 'E')    /*Houve algum erro ao enviar o IR?*/
			{
				beep(BEEP_ERROR);
				strcat(buf_tx,"\r\r\0");
				uart_putString(0,buf_tx);

			}else
			{							 	/*Sem erros*/
				//strcat(str_aux,"\r\0");
				//uart_putString(0,str_aux);
				//printf("[Touch:%u] [IR ID:%s] %s\r",touch, str_IdIr, str_aux);
				//fflush(stdout);
				sprintf(buf_tx,"OK %u",touch);	
			}
			printf("[Touch:%u] [IR ID:%s] %s\r",touch, str_IdIr, str_aux);
			fflush(stdout);
		}else
		{
//			strcat(str_aux,"\r\0");
//			uart_putString(0,str_aux);
			printf("[Touch:%u] [IR ID:%s] %s\r",touch, str_IdIr, str_aux);
			fflush(stdout);	
		}		
	}else
	{ 
		for(i=TOUCH_0;i<=TOUCH_23;i++)			/*Loop para desligar todos os leds 4x4*/
			out_leds &= ~(1<<i);
		touch_led_press = TOUCH_NONE;
	}
}

/*****************************************************************************
Função que configura as cenas contidas no cartão sd
*****************************************************************************/
void cmd_scene(char *par) 
{
	char i,addr,erro = __FALSE, str[30];
	
	if(par[0] == '?')	/*Solicitando a alguma cena?*/	
	{
		if(par[1] >= '0' && par[1] <= '3')	/*Cenas de 0 a 3?*/
		{
			if(read_scene(par[1]-48,FILE_DIMMER_SCENE))
				sprintf(buf_tx,"%s%u",aux_scene,par[1]-48);
			else
				sprintf(buf_tx,"ERROR %u",ERROR_SD); 
		}else
		{
			sprintf(buf_tx,"%s%u", (current_scene[0]==0) ? "SET 0000000000007" : current_scene, current_id_scene);
			if(strcmp(current_scene,scene[current_id_scene])/*strlen(current_scene) < 15*/)
				sprintf(current_scene,"%s%u",scene[current_id_scene], current_id_scene);
		}	
		return;
	}

	memset(str,0,sizeof(str));

	strncpy(str,par,17);	/*Cena ex: 0SET 020020020000*/

	addr = str[0]-48;
	for(i=0;i<20;i++)		/*Loop para eliminar o id da cena da string...Ex: SET 020020020000*/
		str[i] = str[i+1];

	for(i=4;i<16;i++)		/*Loop para verificar possiveis erros de parâmetro*/
	{
		if(str[i] < '0' || str[i] > '9' || addr > 7)	
			erro = __TRUE;	

		if(str[i] == '\r' || str[i] == '\n')	/*Elimina caracteres indesejados da cena*/
			str[i] = 0;
	}

	//printf("str:%s\r",str);
	//fflush(stdout);

	if(strlen(str) != 16 || !strstr(str,"SET") || erro)	/*Há erro?*/
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);
	else
	{
		if(save_scene(str,addr))		/*A cena foi salva no cartão sd?*/
		{
			init_scene(addr);			/*Lê a cena para se certificar que foi escrita no sd*/

			sprintf(buf_tx,"%s%u",scene[addr],addr);
			if(rcv_cmd == RCV_CMD_UART_0)
			{	
				/*Envia imediatamente para o LPC1113 a alteração da cena 'addr' */
				uart_putString(UART_LINK_LPC,scene[addr]);
				uart_putString(UART_LINK_LPC,"!\0");
				strcpy(current_scene,scene[addr]);		/*Copia para a cena atual*/	
				current_id_scene = addr;
			}else
			{
				printf("Cena %u configurada: %s\r",addr,str);
				fflush(stdout);
			}
		}else
			sprintf(buf_tx,"ERROR %u",ERROR_SD);	/*Error permitido para cartão SD*/		
	}
}

/*****************************************************************************
Função que arma a cena recebida pela função
*****************************************************************************/
void cmd_run_scene(char *par) 
{
	char addr;

	addr = atoi(par);
	if(addr >= NUM_SCENE)	/*Endereço da cena incorreto?*/
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);
	else
	{
		/*Envia imediatamente para o LPC1113 a cena de endereço 'addr' */
		uart_putString(UART_LINK_LPC,scene[addr]);
		uart_putString(UART_LINK_LPC,"!\0");
		
		strcpy(current_scene,scene[addr]); 			/*Copia para a cena atual*/
		current_id_scene = addr;

		sprintf(buf_tx,"%s%u",scene[addr],current_id_scene);		
	}
}

/*****************************************************************************
Função que habilita ou desabilita funções
*****************************************************************************/
void cmd_ena_dis_func(char *par) 
{
	if(par[0] == '0')	/*Função IR Scene*/
	{
	  	if(par[1] == '1' && !atoi(cfg.file.func_ir_scene))
		{
			strcpy(cfg.file.func_ir_scene,"1\0");
			fwrite_line(cfg.file.func_ir_scene, FILE_CFG_CFG, LINE_FUNC_IR_SCENE);
		}else
		if(par[1] == '0' && atoi(cfg.file.func_ir_scene))
		{
			strcpy(cfg.file.func_ir_scene,"0\0");
			fwrite_line(cfg.file.func_ir_scene, FILE_CFG_CFG, LINE_FUNC_IR_SCENE);
		}
		sprintf(buf_tx,"FUN 0%s",cfg.file.func_ir_scene);

	}else
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);		
}

/*****************************************************************************
Função que ativa manualmente os rele´s da placa do dimmer
*****************************************************************************/
void cmd_rel(char *par) 
{
/*
	exemplo "SET .........1..!"	 //Configura apenas o rele 0 (Liga)
	exemplo "SET .........0..!"	 //Configura apenas o rele 0 (Desliga)
	exemplo "SET ..........1.!"	 //Configura apenas o rele 1 (Liga)
	exemplo "SET ..........0.!"	 //Configura apenas o rele 1 (Desliga)
	exemplo "SET ...........1!"	 //Configura apenas o rele 2 (Liga)
	exemplo "SET ...........0!"	 //Configura apenas o rele 2 (Desliga)
*/

	switch(par[0])
	{
		case '0':	/*Rele 0*/
			sprintf(buf_tx,"SET .........%c..!",(par[1] == '0') ? '0':'1');
			break;

		case '1':	/*Rele 1*/
			sprintf(buf_tx,"SET ..........%c.!",(par[1] == '0') ? '0':'1');
			break;

		case '2':	/*Rele 2*/
			sprintf(buf_tx,"SET ...........%c!",(par[1] == '0') ? '0':'1');
			break;

		default:
			sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);
			return;
	}
	printf("%s\r",buf_tx);
	fflush(stdout);
	uart_putString(UART_LINK_LPC,buf_tx);
	sprintf(buf_tx,"OK");
}

/*****************************************************************************
Função que envia mensagens provenientes do DIMMER
*****************************************************************************/
void cmd_msg_dimmer(char *par) 
{
	sprintf(buf_tx,"OK"); 	
}
/*****************************************************************************

*****************************************************************************/
void cmd_task(void)
{
	static char rst = 0;
	char *sp,*cp,*next; //,str[4];
	long i=0;

	if(rcv_cmd)
	{
		rcv = 0;
		wdt_feed();
  		sp = get_entry (&buf_rx[0], &next);
  		if(*sp == 0)
		{
			if(rst++ >= 10)
			{
				printf ("[FAIL CMD..restart now]\r");
				fflush(stdout);
				LPC_WDT->WDTC = 0x003FFFF;	/*0.5s*/
				wdt_feed();
				while(1);			
			}
			sprintf(buf_tx,"ERROR %u",ERROR_COMMAND);
    	}else
		{
    		for (cp = sp; *cp && *cp != ' '; cp++)
				*cp = toupper (*cp);
		
    		for (i = 0; i < CMD_COUNT; i++)
			{
      			if (strcmp (sp, (const char *)&cmd[i].val))
        			continue;
      			cmd[i].func (next);		
				rst = 0;
				break;
    		}
		}

		if(i == CMD_COUNT)
			sprintf(buf_tx,"ERROR %u",ERROR_COMMAND);
			  

		if(i!=6 && rcv_cmd == RCV_CMD_UART_0)	/*i=6 (Rcv Touch lpc1113)*/
		{
			if(buf_tx[0] == 'E')
				beep(BEEP_ERROR);
			else
				beep(BEEP_CFG);
		}else
			/*Função IR learn, IR learn Scene, Detect Swing e IR learn app via TCP?*/
		if((i == 0 || i == 12 || i == 13 || i == 17) && (rcv_cmd == RCV_CMD_TCP_SERVER || rcv_cmd == RCV_CMD_TCP_CLIENT)) 
		{
			if(buf_tx[0] == 'E')
				beep(BEEP_ERROR);
			else
				beep(BEEP_CFG);
		}
		
		strcat(buf_tx,"\r\n\0");

		if(rcv_cmd == RCV_CMD_UART_2)	
		{
//			uart_putString(2,buf_tx);
		}else
		if(rcv_cmd == RCV_CMD_UART_0)
			uart_putString(0,buf_tx);
			
#if USE_TCP_CLIENT	/*Comunicação TCP CLIENT será usada?*/
		else
		if((rcv_cmd == RCV_CMD_TCP_CLIENT))
		{
			tcpSend (buf_tx, strlen(buf_tx), last_soc_client,CMD_SEND_TO_CLIENT);
			uart_putString(0,buf_tx);
		}
#endif

#if USE_TCP_SERVER	/*Comunicação TCP SERVER será usada?*/
		else
		if((rcv_cmd == RCV_CMD_TCP_SERVER))
		{
			tcpSend (buf_tx, strlen(buf_tx), tcp_server_soc,CMD_SEND_TO_SERVER);
			uart_putString(0,buf_tx);
		}
#endif			
	
		memset(buf_rx,0,sizeof(buf_rx));
		memset(buf_tx,0,sizeof(buf_tx));
		if(!rcv)
			rcv_cmd = __FALSE;
		cntUART2 = 0;
		cntUART0 = 0;
		NVIC_EnableIRQ(UART2_IRQn);
		NVIC_EnableIRQ(UART0_IRQn);
	}
}


//	if(strstr(sp,"SET") || strstr(sp,"REL"))	/*Recebeu algum cmd referente ao LPC1113?*/
//				{											/*Sim.Então repassa o cmd para o LPC1113*/
//					sprintf(buf_tx,"%s %s\0",sp,next);
//					uart_putString(UART_LINK_LPC,buf_tx);
//					printf("buf:%s\r",buf_tx);
//					fflush(stdout);
//					sprintf(buf_tx,"OK");
//				}else
//					sprintf(buf_tx,"ERROR<%u>",ERROR_COMMAND);


//
///*****************************************************************************
//
//*****************************************************************************/
//void cmd_cfg_tcp(char *par) 
//{
//	char str[20],name[200],mac[20],lin=0,i=0,j=0;
//	U8  _ip_static[4],_ip_server[4],interval=0;
//	U16 _port_udp=0,_port_serv_loc=0,_port_serv_rem=0;
//
//	memset(str,0,sizeof(str));
//	memset(name,0,sizeof(name));
//	while(par[i] != '\n')
//	{
//		if(par[i] == ':' || par[i] == '\r')
//		{
//			if     (lin == 0)	inet_aton((U8*)str, _ip_static);	
//			else if(lin == 1)   inet_aton((U8*)str, _ip_server);
//			else if(lin == 2)	_port_serv_rem = atoi(str);
//			else if(lin == 3)	interval = atoi(str);
//			else if(lin == 4)	strcpy(name,str);
//			else if(lin == 5) 	_port_serv_loc = atoi(str);
//			else if(lin == 6)	_port_udp = atoi(str);
//			else if(lin == 7)
//			{
//				strcpy(mac,str);
//				break;
//			}
//			lin++;
//			i++;	/*Incrementa para pular o ':' */
//			j=0;
//			memset(str,0,sizeof(str));	
//		}else
//		{
//			str[j] = par[i];
//			j++;
//			i++;
//		}
//	}
//	/*Todos os parâmetros estão corretos?*/
//	if(_port_udp >= 5000 && _port_serv_loc >= 5000 && _port_serv_rem >= 5000 && interval && interval < 250 && name[0] && strlen(mac) == 12)
//	{
//		printf("IP static: %u.%u.%u.%u\r",_ip_static[0],_ip_static[1],_ip_static[2],_ip_static[3]);
//		printf("IP server: %u.%u.%u.%u\r",_ip_server[0],_ip_server[1],_ip_server[2],_ip_server[3]);
//		printf("Port server rem: %u\r",_port_serv_rem);
//		printf("Interval pck serv: %u\r",interval);
//		printf("Host name: %s\r",name);
//		printf("Port server loc: %u\r",_port_serv_loc);
//		printf("Port udp: %u\r",_port_udp);
//		printf("MAC: %s\r",mac);
//		fflush(stdout);
//		sprintf(buf_tx,"OK");
//		
//		printf ("[TCP Config via UART..Reiniciando]\r\r");
//		fflush(stdout);
//		LPC_WDT->WDTC = 0x003FFFF;	/*0.5s*/
//		wdt_feed();
//		while(1);
//	}else
//		sprintf(buf_tx,"ERROR<%u>",ERROR_PARAMETER);
//
//
//		strcpy(str[0],cfg.tcp.static_ip);
//		strcpy(str[1],cfg.tcp.ip_serv_rem);
//		strcpy(str[2],cfg.tcp.port_serv_rem);
//		strcpy(str[3],cfg.tcp.interval_packet_serv);
//		strcpy(str[4],cfg.tcp.host_name);
//		strcpy(str[5],cfg.tcp.port_serv_loc);
//		strcpy(str[6],cfg.tcp.port_udp);
//		strcpy(str[7],cfg.tcp.mac);
//
//		read_cfg_tcp();	/*O cartão foi inserido novamente, então lê a configuração tcp*/
//
//		/*Houve diferença da configuração antiga pra atual?*/
//		if(strcmp(str[0],cfg.tcp.static_ip)            || strcmp(str[1],cfg.tcp.ip_serv_rem) || strcmp(str[2],cfg.tcp.port_serv_rem) || 
//		   strcmp(str[3],cfg.tcp.interval_packet_serv) || strcmp(str[4],cfg.tcp.host_name)   || strcmp(str[5],cfg.tcp.port_serv_loc) || 
//		   strcmp(str[6],cfg.tcp.port_udp)             || strcmp(str[7],cfg.tcp.mac))
//		{
//			printf ("[TCP Config via SD..Reiniciando]\r\r");
//			fflush(stdout);
//			LPC_WDT->WDTC = 0x003FFFF;	/*0.5s*/
//			wdt_feed();
//			while(1);
//		}
//}

