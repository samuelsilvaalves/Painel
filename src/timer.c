/*****************************************************************************
 *   timer.c:  Timer C file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <RTL.H>
#include <lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware_profile.h"
#include "timer.h"
#include "control_ir.h"
#include "ir.h"
#include "touch.h"
#include "register.h"
#include "extint.h"
#include "msd_sd_file.h"

U8 tick;
U8 tick_10ms;
U8 tick_50ms;
U8 tick_30ms;
U64 timer1_counter = 0;
U64 timer0_counter = 0;

/*****************************************************************************
** Function name:		timer_poll(void)
**
** Descriptions:		temporiza a execução das funções no loop principal
**
** parameters:			None
**
** Returned value:	None
** 
*****************************************************************************/
void timer_poll (void)
{
	static U8 cnt_100ms = 0,  cnt_30ms = 0, cnt_50ms = 0;
	if (tick)
		tick = __FALSE;				/* Every 100 ms */

	if (tick_10ms)
		tick_10ms = __FALSE;		/* Every 10 ms */

	if (tick_30ms)
		tick_30ms = __FALSE;		/* Every 30 ms */

	if (tick_50ms)
		tick_50ms = __FALSE;		/* Every 50 ms */
	
	/* System tick timer running in poll mode */
	if (SysTick->CTRL & 0x10000) 
	{
		/* Timer tick every 10 ms */
		tick_10ms = __TRUE;
		if(++cnt_30ms >= 3)
		{
			cnt_30ms = 0;
			tick_30ms = __TRUE;
		}
		if(++cnt_50ms >= 5)
		{
			cnt_50ms = 0;
			tick_50ms = __TRUE;
		}
		if(++cnt_100ms >= 10)
		{
			cnt_100ms = 0;
			tick = __TRUE;
			LED_PWR_TOG();
			timer_tick ();
		}	
	}
}


/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  	if ( timer_num == 0 )
  	{
		LPC_TIM0->TCR = 0x02;		/* reset timer */
		LPC_TIM0->PR  = 0x00;		/* set prescaler to zero */
		LPC_TIM0->MR0 = delayInMs * (9000000 / 1000-1);
		LPC_TIM0->IR  = 0xff;		/* reset all interrrupts */
		LPC_TIM0->MCR = 0x04;		/* stop timer on match */
		LPC_TIM0->TCR = 0x01;		/* start timer */
  
		/* wait until delay time has elapsed */
		while (LPC_TIM0->TCR & 0x01);
  	}else 
	if ( timer_num == 1 )
  	{
		LPC_TIM1->TCR = 0x02;		/* reset timer */
		LPC_TIM1->PR  = 0x00;		/* set prescaler to zero */
		LPC_TIM1->MR0 = delayInMs * (9000000 / 1000-1);
		LPC_TIM1->IR  = 0xff;		/* reset all interrrupts */
		LPC_TIM1->MCR = 0x04;		/* stop timer on match */
		LPC_TIM1->TCR = 0x01;		/* start timer */
  
		/* wait until delay time has elapsed */
		while (LPC_TIM1->TCR & 0x01);
  	}
  	return;
}
//
//void delayUs(uint8_t timer_num, uint32_t delayInMs)
//{
//  	if ( timer_num == 0 )
//  	{
//		LPC_TIM0->TCR = 0x02;		/* reset timer */
//		LPC_TIM0->PR  = 0x00;		/* set prescaler to zero */
//		LPC_TIM0->MR0 = delayInMs * (9000000 / 1000-1);
//		LPC_TIM0->IR  = 0xff;		/* reset all interrrupts */
//		LPC_TIM0->MCR = 0x04;		/* stop timer on match */
//		LPC_TIM0->TCR = 0x01;		/* start timer */
//  
//		/* wait until delay time has elapsed */
//		while (LPC_TIM0->TCR & 0x01);
//  	}else 
//	if ( timer_num == 1 )
//  	{
//		LPC_TIM1->TCR = 0x02;		/* reset timer */
//		LPC_TIM1->PR  = 0x00;		/* set prescaler to zero */
//		LPC_TIM1->MR0 = delayInMs * (9000000 / 340000-1);
//		LPC_TIM1->IR  = 0xff;		/* reset all interrrupts */
//		LPC_TIM1->MCR = 0x04;		/* stop timer on match */
//		LPC_TIM1->TCR = 0x01;		/* start timer */
//  
//		/* wait until delay time has elapsed */
//		while (LPC_TIM1->TCR & 0x01);
//  	}
//  	return;
//}



/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER0_IRQHandler (void) 
{  
 	LPC_TIM0->IR = 1;			/* clear interrupt flag */
  	timer0_counter++;

//	if(touch_led_press != TOUCH_NONE)
//	{
//		if(!(timer0_counter%2))	out_leds |=  (1 << touch_led_press);
//		else      				out_leds &= ~(1 << touch_led_press);
//		atualiza_saidas();
//	}

	if(touch_led_press != TOUCH_NONE)
	{
		if(ir_state.bit.PwrPainel)
		{
			if(!(timer0_counter%2))	out_leds |=  (1 << touch_led_press);
			else      				out_leds &= ~(1 << touch_led_press);
		}else
			out_leds |= (1 << touch_led_press);

		atualiza_saidas();
	}
	
	if(atoi(cfg.file.func_ir_scene))	/*Função IR Scene habilitada?*/
	{
		if(++contEnableExtIr == 50)
		{
			NVIC_EnableIRQ(EINT3_IRQn);		/*Habilita novamente a interrupção*/
			contEnableExtIr = 100;
			printf("Enable EINT3...RCV IR\r");
			fflush(stdout);
		}
	}	
  	return;
}
/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER1_IRQHandler (void)  
{  
  	LPC_TIM1->IR = 1;			/* clear interrupt flag */
  	timer1_counter++;
  	return;
}
/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  	if ( timer_num == 0 )
  	{
		//timer0_counter	= 0;
		reset_timer(0);
		LPC_TIM0->TCR 	= 1;
		NVIC_EnableIRQ(TIMER0_IRQn);
  	}else
  	{
		timer1_counter	= 0;
		reset_timer(1);
		LPC_TIM1->TCR 	= 1;
		NVIC_EnableIRQ(TIMER1_IRQn);
  	}
  	return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  	if ( timer_num == 0 )
  	{
		LPC_TIM0->TCR = 0;
		NVIC_DisableIRQ(TIMER0_IRQn);
  	}else
  	{
		LPC_TIM1->TCR = 0;
		NVIC_DisableIRQ(TIMER1_IRQn);
  	}
  	return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
	uint32_t regVal;

  	if ( timer_num == 0 )
  	{
		regVal = LPC_TIM0->TCR;
		regVal |= 0x02;
		LPC_TIM0->TCR = regVal;
  	}else
  	{
		regVal = LPC_TIM1->TCR;
		regVal |= 0x02;
		LPC_TIM1->TCR = regVal;
  	}
  	return;
}
/****************************************Copyright (c)****************************************************
**								   http://www.OpenMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.c
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          OpenMCU
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        ±àÐ´Ê¾Àý´úÂë
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
void init_timer(void) 
{
	/*time_interval(ns) = (800ns * LPC_TIM0->MR )/20*/
	/*LPC_TIM0->MR      = (20*time_interval(ns))/800ns*/
	/*LPC_TIM0->MR      = (20*time_interval(ms))/0.0008ms*/

	NVIC_SetPriority(TIMER1_IRQn, 0);

	/* Timer 1 destinado as funçoes do IR */
	//LPC_TIM1->MR0  = 20;			/*TimerInterval ~= 800ns*/
	//LPC_TIM1->MR0  = 150;			/*TimerInterval ~= 6us*/
	//LPC_TIM1->MR0  = 200;			/*TimerInterval ~= 8us*/
	LPC_TIM1->MR0  = 100;			/*TimerInterval ~= 4us*/
	//LPC_TIM1->MR0  = 50;		   	/*TimerInterval ~= 2us*/
	LPC_TIM1->MCR  = 3;			         
    LPC_TIM1->TCR  = 1;  
	timer1_counter = 0;
	NVIC_DisableIRQ(TIMER1_IRQn);	

	//LPC_TIM0->MR0  = 2500000;		/*TimerInterval ~= 100ms*/

#if BLINK_LED_30ms
	LPC_TIM0->MR0  = 750000;		/*TimerInterval ~= 30ms*/

#elif BLINK_LED_50ms
	LPC_TIM0->MR0  = 1250000;		/*TimerInterval ~= 50ms*/

#else
	LPC_TIM0->MR0  = 1250000;		/*TimerInterval ~= 50ms*/
#endif

	//LPC_TIM0->MR0  = 100000;		/*TimerInterval ~= 4ms*/
	//LPC_TIM0->MR0  =  250000;		/*TimerInterval ~= 10ms*/
	//LPC_TIM0->MR0  = 1250000;		/*TimerInterval ~= 50ms*/
	//LPC_TIM0->MR0  = 750000;		/*TimerInterval ~= 30ms*/
	//LPC_TIM0->MR0  =  TIME_INTERVAL;

	LPC_TIM0->MCR  = 3;				
	LPC_TIM0->TCR  = 1; 
	timer0_counter = 0;
	//NVIC_DisableIRQ(TIMER0_IRQn);
	
	enable_timer(0);
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
