#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hardware_profile.h"
#include "register.h"
#include "timer.h"
#include "touch.h"

IR_STATE ir_state; 

unsigned int out_leds;		 				/*Variavel que contém as configurações de todas as saídas*/

/*****************************************************************************
Função destinada para inicializar todas as saídas(leds) 
*****************************************************************************/
void init_register(void)
{
	U64 j;
	int i,y,num_rand=0;
	char seq[24] = {16,17,0,1,2,3,7,6,5,4,19,18,20,21,8,9,10,11,15,14,13,12,23,22}; //Efeito serpente descendo  

	for(i=0,y=0;i<48;i++)
	{
		if(i%2)	
			out_leds &= ~(1<<num_rand);		
		else
		{
			num_rand = seq[y];
			y++;
			out_leds |= (1<<num_rand);
			atualiza_saidas();
			for(j=0;j<1000000;j++);
			wdt_feed();	
		}
	}
	

	out_leds = 0xFFFFFFFF;		/*Todos os leds ligados*/
	atualiza_saidas();
	LED_ATEND(1);
	LED_LOGO(1);
	for(j=0;j<6000000;j++);			
	out_leds = 0;				/*Todos os leds desligados*/
	atualiza_saidas();
	LED_ATEND(0);
	LED_LOGO(0);	
}

#define LEDS_PAINEL		1		
/*****************************************************************************
Função destinada a configurar (On/Off) todas as saidas
*****************************************************************************/
void atualiza_saidas(void)
{
	signed int i; 				/*Variavel local*/
    
	#if	REGISTER_START_SEND_MSB 
	for(i=QTD_OUTS-1;i>=0;i--)	/*Inclui na compilação loop para enviar todos os bits do MSB ao LSB*/
	#endif 

	#if	REGISTER_START_SEND_LSB 
	for(i=0;i<QTD_OUTS;i++)		/*Inclui na compilação loop para enviar todos os bits do LSB ao MSB*/
	#endif   
   	{
       	SH(0); 							/*Descida do clock*/
		#if	LEDS_PAINEL 
		if(ir_state.bit.PwrPainel)		/*Função (leds do painel) ativada?*/
		{
			//DS((out_leds & (1<<i)));
			/*Liga led apenas se o touch estiver habilitado*/
			if(touchEnaDis & (1<<i))
			{
				DS((out_leds & (1<<i)));
			}else
				DS(1);	/*Desliga*/
		}else
		#endif
			DS(!(out_leds & (1<<i)));	
		SH(1);   				/*Subida do clock.Armazena bit serialmente*/
	}
	/*Pulso de clock para colocar os todos os bits (enviados serialmente) 
	  nas saídas paralelas*/
	ST(0);   
	ST(1);
	MR(1); 	/*Mantém o reset dos registradores em nivel normal(1)*/

}
/*****************************************************************************

*****************************************************************************/
void led_task(void)
{
	if(!ir_state.bit.PwrPainel)
	{
		LED_LOGO(0); 
	}else
		LED_LOGO(1);

	/*Deixa apenas o led do touch 'power painel' ligado se os leds estiverem desabilitados*/
	if(!ir_state.bit.PwrPainel)
		out_leds |= (1<<TOUCH_11);

	atualiza_saidas();
}

