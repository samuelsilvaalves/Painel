/****************************************Copyright (c)****************************************************
**								   http://www.OpenMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        The main() function example template
**
**--------------------------------------------------------------------------------------------------------
** Created by:          OpenMCU
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        ±àÐ´Ê¾Àý´úÂë
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#ifndef __TIMER_H 
#define __TIMER_H

#include <RTL.H>
	
#define TIME_INTERVAL	25000000/1000-1 //(9000000/100 - 1)

#define tick(time) {time = timer0_counter;}
#define time_dif(time)	(timer0_counter-(time))

extern U8 tick;
extern U8 tick_10ms;
extern U8 tick_50ms;
extern U8 tick_30ms;
extern U64 timer1_counter;
extern U64 timer0_counter;

void timer_poll (void);
void delayMs(uint8_t timer_num, uint32_t delayInMs);
void init_timer(void); 

void enable_timer( uint8_t timer_num );
void disable_timer( uint8_t timer_num );
void reset_timer( uint8_t timer_num );
void TIMER0_IRQHandler (void);
void TIMER1_IRQHandler (void);

#endif /* end __TIMER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
