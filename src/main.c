/*******************************************************************************
                  			3V3 Tecnologia LTDA ME

	Projeto: 

	main.c
	3V3 Tecnologia, 2012

  	Descrição:

  	Versão: v1.00
  	Início: 11/03/2013

	Histórico de alterações
	-----------------------

*******************************************************************************/
#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hardware_profile.h"
#include "main.h"
#include "uart.h"
#include "pwm_ir.h"
#include "main.h"
#include "ir.h"
#include "msd_sd_file.h"
#include "touch.h"
#include "timer.h"
#include "register.h"
#include "tcpip.h"
#include "extint.h"

/*****************************************************************************

*****************************************************************************/
void verify_last_reset(void)
{
//	if(LPC_SC->RSID & (1<<0))
//		printf("[POR]\r");

	if(LPC_SC->RSID & (1<<1))
		printf("[EXTR][Reset Extern]\r");
	if(LPC_SC->RSID & (1<<2))
		printf("[WDTR][Reset WDT]\r");
	if(LPC_SC->RSID & (1<<3))
		printf("[BODR][Reset Brown-Out Detector]\r\r");
	fflush(stdout);
	/*Limpa flags que indicam reset*/
	LPC_SC->RSID &= ~(1<<0) | (1<<1) | (1<<2) | (1<<3);	
}

/*****************************************************************************

*****************************************************************************/
int main (void)
{		
	SystemInit();
	init_gpio();
	init_uart();
	verify_last_reset();
	init_register();
	init_msd();	
	init_file();
	init_TcpNet(); //printf("[exit InitTcpNet]\r");fflush(stdout);							
	user_init(); //printf("[exit UserInit]\r");fflush(stdout);
	init_touch();//printf("[exit InitTouch]\r");fflush(stdout);			
	init_scene(0xFF); //printf("[exit InitScene]\r");fflush(stdout);
	init_timer(); //printf("[exit InitTimer]\r");fflush(stdout);
	Init_EINT();  //printf("[exit InitExtern]\r");fflush(stdout);
	#if USE_IR
	PWM_Init();	//printf("[exit InitPwm]\r");fflush(stdout);
	#endif

	show_all_scene();

	printf("[Start]\r");						
	fflush(stdout);

	for(;;)
	{
		timer_poll();
		cmd_task();
		touch_task();
		led_task();
		key_task();
		file_task();
		main_TcpNet();
		tcp_task();
		wdt_feed();
		#if USE_IR
		control_ir_task();
		#endif
		ext_task();
	}
}


		
