/****************************************************************************
 *   $Id:: extint.c 5670 2010-11-19 01:33:16Z usb00423                      $
 *   Project: NXP LPC17xx EINT example
 *
 *   Description:
 *     This file contains EINT code example which include EINT 
 *     initialization, EINT interrupt handler, and APIs for EINT.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hardware_profile.h"
#include "extint.h"
#include "timer.h"
#include "ir.h"
#include "generic_type_defs.h"
#include "touch.h"
#include "pwm_ir.h"
#include "tcpip.h"
#include "msd_sd_file.h"

U8  flag_new_cmdir = __FALSE;

int contEnableExtIr = 0;

/***************************************************************************

****************************************************************************/
char get_new_ir(void)
{
	FILE *f;
	U32 i=0, j=0, x=0, n=0, id=0, pulse = 0, n_acertos=0;
	char str[30], strId[30], logic = 0, status = 1, erro = 0;
	int ch=0;
		
	memset(ir,0xffff,sizeof(ir));
	wdt_feed();
	disable_timer(0);	/*Disabilita o timer 0*/
	
	ir_counter = 0;		/*Reseta contador do IR*/
	LPC_TIM1->IR = 1;	/*Limpa flag da interrupção do timer 1*/
	LPC_TIM1->TCR = 2;	/*Reseta contador do timer 1*/
	LPC_TIM1->TCR = 1;	/*Inicia a contagem do timer 1*/
	while(1)	
	{	 			
		if(LPC_TIM1->IR & (1<<0))
		{
			LPC_TIM1->IR = 1;
			ir_counter++;
		}

		wdt_feed();
		if(status)	/*Ainda está acontecendo a leitura do IR?*/
		{
			if(!RECEIVE_IR())	/*IR está em low?*/	
			{
				LED3_BOARD(1); 	
				if(logic)	
				{
					logic = __FALSE;
					pulse++;  
				}
			}else
			{
				LED3_BOARD(0); 	
				if(!logic)
				{
					logic = __TRUE;
					pulse++;  
				}
			}
			if(pulse >= MAX_QTD_PULSOS-1)
			{
				/*Overflow dos pulsos no IR*/	
				memset(ir,0xFFFF,sizeof(ir));
				ir_counter = 0;
				pulse = 0;
				status = __FALSE;		/*Sinaliza que a leitura do IR já terminou*/
				erro = __TRUE;			/*Sinaliza erro (Overflow de pulsos)*/	
			}
					 		 
			ir[pulse] = ((ir[pulse] == 0xFFFF) ? 0 : ir[pulse]) + ir_counter;	/*Vai incrementando os pulsos do IR*/
			ir_counter = 0;											/*Reseta para um novo incremento*/
			if(ir[pulse] * 4 >= 120000) /*Maior que 120ms?*/
			{	
				ir[pulse] = 0xFFFF; /*Reseta o ultimo pulso (timeout)*/
				status = __FALSE;	/*Sinaliza que a leitura do IR já terminou*/	
			}
		}
		
		/*Sai do laço se o IR foi armazenado*/
		if(!status)
			break;
	}
	LPC_TIM1->TCR = 0;	/*Desabilita Timer 1*/

	if(pulse > 10 && erro == __FALSE)
	{		
		printf("*****\r[IR Receiver...All Pulses:%u]\r",pulse);
		fflush(stdout);
		memcpy(ir_cmp,ir,sizeof(ir_cmp));

		/*Loop para eliminar os pulsos de repetição do IR recebido*/
		for(j=4;j<MAX_QTD_PULSOS;j++)
		{
			if(ir_cmp[j] == 0xFFFF || ir_cmp[j] <= 0x10)
				break;
			if(j < 70)
				continue;
			
			printf("[Limited to 70 pulses]\r");
			fflush(stdout);
			for(n=j;n<MAX_QTD_PULSOS;n++)
				ir_cmp[n] = 0xFFFF;	
			break;		
		}
		pulse = j-4;

		for(x=0;x<NUM_SCENE;x++)	/*Loop para comparar o IR recebido com apenas os IRs previamente cadastrados*/
		{
			wdt_feed();
			memset(ir,0xFFFF,sizeof(ir));
			memset(strId,0,sizeof(strId));
			sprintf(strId,"%s%u.TXT\0",FILE_CMDIR,x);

			f = fopen(strId,"r");

			if(f == NULL)
			{
				/*Ocorreu erro na abertura do IR em questão (addr: i)mas continua no loop para abrir o restante dos IRs*/
				continue;	
			}
			
			id=0;
			i=0;
			memset(str,0,sizeof(str));
			/*Laço para ler todo o IR no SD*/
			while((ch = fgetc (f)) != EOF)
			{
				if(ch == '#')
				{
					ir[id] = atoi(str);
					if(ir[id] <= 16)
						break;
					id++;		
				}else
				{
					if(ch != '\r' && ch != '\n')
					{
						str[i] = ch;
						i++;
					}else
					{
						memset(str,0,sizeof(str));
						i=0;
					}
				}
			}
			fclose(f);

			/*Loop para eliminar os pulsos de repetição do IR que está gravado no sd*/
			for(j=4;j<MAX_QTD_PULSOS;j++)
			{
				if(ir[j] == 0xFFFF || ir[j] <= 0x10)
					break;
				if(j < 70)
					continue;
				for(n=j;n<MAX_QTD_PULSOS;n++)
					ir[n] = 0xFFFF;	
				break;		
			}

			/*Comparação do IR recebido (ir_cmp) com o IR de endereço 'x' (ir) previamente armazenado no SD*/
			if(ir[0] != 0xFFFF && ir[1] != 0xFFFF && ir[2] != 0xFFFF)	
			{	
				for(j=4,n_acertos=0;j<MAX_QTD_PULSOS;j++)
				{
					if(ir[j] != 0xffff && ir[j] >= 0x10)
					{
						if(ir_cmp[j] >= (ir[j] - (float)ir[j] * 0.3) && ir_cmp[j] <= (ir[j] + (float)ir[j] * 0.3))	/*Cada pulso está dentro do range de 30%?*/
							n_acertos++;
						else
							break;	
					}else
						break;
				}
	
				printf("[IR %u (SD)...Acertos:%u...Pulsos:%u]\r",x,n_acertos,pulse);
				fflush(stdout);
				
				if(n_acertos >= pulse - 5 && n_acertos <= pulse + 5)
				{
					printf("[IR Scene found...Scene %u Run]\r*****\r\r",x);
					fflush(stdout);
					enable_timer(0);
					
					exe_scene(x);	/*Executa a cena referente ao endereço do IR recebido (reconhecido)*/
					debounce_press = DEBOUNCE_PRESS_KEY;
					debounce_release = DEBOUNCE_RELEASE_KEY;
					return 1;
				}
			}else
			{
				/*Não encontrou o IR de endereço i*/
				printf("[IR %u (SD) not found]\r",x);
				fflush(stdout);
			}
		}
		printf("[IR Scene not found]\r*****\r\r");
		fflush(stdout);	
			
	}else	/*Falha na recepção de IR*/
	if(pulse > 5)
	{
		printf("[Error CMD IR Scene]\r");
		fflush(stdout);	
	}

	enable_timer(0);	
	return 0;
	
}

/*****************************************************************************

*****************************************************************************/
void ext_task(void)
{
	static char cnt_ext = 0;

	/*LED para debug IR Receiver*/
	if(!RECEIVE_IR())
	{	
		LED3_BOARD(1);
	}else 
	   	LED3_BOARD(0);

	if(!atoi(cfg.file.func_ir_scene))	/*Função IR Scene desabilitada?*/
	{
		/*Desabilita interrupção e contadores auxiliares*/
		NVIC_DisableIRQ(EINT3_IRQn);
		cnt_ext = 0;
		contEnableExtIr = 0;
	 	return;
	}

	if(!flag_new_cmdir)	/*Ainda sem receber IR?*/
	{
		if(contEnableExtIr >= 100)
			NVIC_EnableIRQ(EINT3_IRQn);
		cnt_ext = 0;	
		return;
	}

	if(++cnt_ext >= 20)	
	{
		if(!RECEIVE_IR())
		{ 	
			NVIC_DisableIRQ(EINT3_IRQn);	/*Desabilita a interrupção responsavel por detectar que um IR xegou no pino*/
			get_new_ir();					/*Chama função para lê o IR e verificar se ele de fato é um comando de cena*/
			contEnableExtIr = 45;			/*Temporização para habilitar interrupção novamente*/
		}else
			NVIC_EnableIRQ(EINT3_IRQn);		/*Habilita novamente a interrupção*/
		/*Reseta contador e flag para receber um novo IR como comando de cena*/
		cnt_ext = 0;
		flag_new_cmdir = __FALSE;					
	}			
}	
/*****************************************************************************
** Function name:		EINT0_Handler
**
** Descriptions:		external INT handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void EINT0_IRQHandler (void) 
{
#if USE_EXT0
	static U32 eint0_counter=0;
  	LPC_SC->EXTINT = EINT0;			/* clear interrupt */

    if(++eint0_counter & 0x01) 
        flag_new_ir = __TRUE;
#endif
}
/*****************************************************************************
** Function name:		EINT1_Handler
**
** Descriptions:		external INT handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void EINT1_IRQHandler (void) 
{
#if USE_EXT1
  	LPC_SC->EXTINT |= EINT1;		/* clear interrupt */
#endif
}
/*****************************************************************************
** Function name:		EINT2_Handler
**
** Descriptions:		external INT handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void EINT2_IRQHandler (void) 
{
#if USE_EXT2
  	LPC_SC->EXTINT |= EINT2;		/* clear interrupt */
#endif
}

/*----------------------------------------------------------------------------
 *   External Interrupt PORT 2 Service Routine:  Digital Channel
 *---------------------------------------------------------------------------*/
void EINT3_IRQHandler (void) 
{
#if USE_EXT_ANY_GPIO2			
	LPC_GPIOINT->IO2IntClr |= (1 << PIN_EXT_ANY_GPIO2);    /* Clear pending interrupt */
	flag_new_cmdir = __TRUE;
#endif

#if USE_EXT_ANY_GPIO0 
   	LPC_GPIOINT->IO0IntClr |= (1 << PIN_EXT_ANY_GPIO0);    /* Clear pending interrupt */
#endif
	flag_new_cmdir = __TRUE;
}
/*****************************************************************************
** Function name:		EINTInit
**
** Descriptions:		Initialize external interrupt pin and
**						install interrupt handler
**
** parameters:			None
** Returned value:		true or false, return false if the interrupt
**						handler can't be installed to the VIC table.
** 
*****************************************************************************/
uint32_t Init_EINT (void)
{
#if USE_EXT0

	LPC_PINCON->PINSEL4 	|= 0x00100000;	/* set P2.10 as EINT0 */										 
  	LPC_GPIOINT->IO2IntEnF 	|= 0x200;		/* Port2.10 is falling edge. */
  	LPC_SC->EXTMODE 		|= EINT0_EDGE;	/* INT0 edge trigger */
  	LPC_SC->EXTPOLAR = 0;					/* INT0 is falling edge by default */
  	NVIC_EnableIRQ(EINT0_IRQn);

#endif
#if USE_EXT1
	
	LPC_PINCON->PINSEL4 	|= 0x00400000;	/* set P2.11 as EINT1 */
	LPC_GPIOINT->IO2IntEnF 	|= 0x400;		/* Port2.11 is falling edge. */
	LPC_SC->EXTMODE 		|= EINT1_EDGE;	/* INT1 edge trigger */
  	LPC_SC->EXTPOLAR = 0;					/* INT1 is falling edge by default */
  	NVIC_EnableIRQ(EINT1_IRQn);				/* INT1 edge trigger */

#endif
#if USE_EXT2

	LPC_PINCON->PINSEL4 	|= 0x01000000;	/* set P2.12 as EINT2 */
	LPC_GPIOINT->IO2IntEnF 	|= 0x800;		/* Port2.12 is falling edge. */
	LPC_SC->EXTMODE 		|= EINT2_EDGE;	/* INT2 edge trigger */
  	LPC_SC->EXTPOLAR = 0;					/* INT2 is falling edge by default */
  	NVIC_EnableIRQ(EINT2_IRQn);				/* INT2 edge trigger */

#endif
#if USE_EXT_ANY_GPIO2 

   /*Seta o pino qualquer da porta 2 que funcionará como interrupção EINT3*/
	LPC_GPIO2->FIODIR &= ~(1<<PIN_EXT_ANY_GPIO2);        	/* Pin as input */
	LPC_GPIOINT->IO2IntEnF |= (1<<PIN_EXT_ANY_GPIO2);      /* Enable falling edge IRQ pin chosen */
	NVIC_EnableIRQ(EINT3_IRQn);             /* enable irq in nvic */
#endif 
#if USE_EXT_ANY_GPIO0 

   /*Seta o pino qualquer da porta 0 que funcionará como interrupção EINT3*/
	LPC_GPIO0->FIODIR &= ~(1<<PIN_EXT_ANY_GPIO0);        	/* Pin as input */
	LPC_GPIOINT->IO0IntEnF |= (1<<PIN_EXT_ANY_GPIO0);      /* Enable falling edge IRQ pin chosen */
	NVIC_EnableIRQ(EINT3_IRQn);             /* enable irq in nvic */

#endif
  	return 1;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

