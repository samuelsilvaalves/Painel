/****************************************Copyright (c)****************************************************
**								SAPIEN SOLUÇÕES INTELIGENTES
**--------------File Info---------------------------------------------------------------------------------
** File name:           HardwareProfile.h
** Last modified Date:  25-01-2013 (Régis)
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          Sapien S.I.
** Created date:        24-04-2012 (Régis)
** Version:             V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#ifndef __HARDWARE_PROFILE_H__
#define __HARDWARE_PROFILE_H__

#include <LPC17XX.H>

								/* GERAL */
/* Porta 0 */
#define read0(x)		(LPC_GPIO0->FIOPIN &  (1<<x))
#define set0(x)			LPC_GPIO0->FIOSET |= (1<<x)
#define clr0(x)			LPC_GPIO0->FIOCLR |= (1<<x)
#define output0(x)		LPC_GPIO0->FIODIR |= (1<<x)
#define input0(x)		LPC_GPIO0->FIODIR &=~(1<<x)
#define toggle0(x)		if(read0(x)) clr0(x); else  set0(x)

/* Porta 1 */
#define read1(x)		(LPC_GPIO1->FIOPIN &  (1<<x))
#define set1(x)			LPC_GPIO1->FIOSET |= (1<<x)
#define clr1(x)			LPC_GPIO1->FIOCLR |= (1<<x)
#define output1(x)		LPC_GPIO1->FIODIR |= (1<<x)
#define input1(x)		LPC_GPIO1->FIODIR &=~(1<<x)
#define toggle1(x)		if(read1(x)) clr1(x); else  set1(x)

/* Porta 2 */
#define read2(x)		(LPC_GPIO2->FIOPIN &  (1<<x))
#define set2(x)			LPC_GPIO2->FIOSET |= (1<<x)
#define clr2(x)			LPC_GPIO2->FIOCLR |= (1<<x)
#define output2(x)		LPC_GPIO2->FIODIR |= (1<<x)
#define input2(x)		LPC_GPIO2->FIODIR &=~(1<<x)
#define toggle2(x)		if(read2(x)) clr2(x); else  set2(x)

/* Porta 3 */
#define read3(x)		(LPC_GPIO3->FIOPIN &  (1<<x))
#define set3(x)			LPC_GPIO3->FIOSET |= (1<<x)
#define clr3(x)			LPC_GPIO3->FIOCLR |= (1<<x)
#define output3(x)		LPC_GPIO3->FIODIR |= (1<<x)
#define input3(x)		LPC_GPIO3->FIODIR &=~(1<<x)
#define toggle3(x)		if(read3(x)) clr3(x); else  set3(x)

/* Porta 4 */
#define read4(x)		(LPC_GPIO4->FIOPIN &  (1<<x))
#define set4(x)			LPC_GPIO4->FIOSET |= (1<<x)
#define clr4(x)			LPC_GPIO4->FIOCLR |= (1<<x)
#define output4(x)		LPC_GPIO4->FIODIR |= (1<<x)
#define input4(x)		LPC_GPIO4->FIODIR &=~(1<<x)
#define toggle4(x)		if(read4(x)) clr4(x); else  set4(x)

/*********Definiçoes de hardware para a função IR*********/

#define USE_IR				1		/*Define se a função IR da placa será usada ou não*/

#define USE_IR_OUT_ON_HIGH	1		/*Define se o IR acenderá com pulso high saindo do pino do micro*/	

#define PIN_RCV_IR			3		/*P2.3 correto */ 
//#define PIN_RCV_IR			7		/*P0.7*/


#define PIN_IR_OUT_0		0		/*P2.0*/
#define PIN_IR_OUT_1	 	1		/*P2.1*/
#define PIN_IR_OUT_2	 	2		/*P2.2*/
//#define PIN_IR_OUT_3	 	3		/*P2.3*/
//#define PIN_IR_OUT_4	 	4		/*P2.4*/

#define RECEIVE_IR()  		(read2(PIN_RCV_IR))
//#define RECEIVE_IR()  		(read0(PIN_RCV_IR))

#define READ_IROUT_0() 		(read2(PIN_IR_OUT_0))
#define READ_IROUT_1() 		(read2(PIN_IR_OUT_1))
#define READ_IROUT_2() 		(read2(PIN_IR_OUT_2))
//#define READ_IROUT_3() 		(read2(PIN_IR_OUT_3))
//#define READ_IROUT_4() 		(read2(PIN_IR_OUT_4))

#define READ_KEY_LEARN()	READ_KEY1_BOARD()

#define LED_LEARN_TOG()		LED_PWR_TOG()	


#if USE_IR_OUT_ON_HIGH	
#define dir_ir()			input2(PIN_RCV_IR);		\
							output2(PIN_IR_OUT_0); 	\
							output2(PIN_IR_OUT_1); 	\
							output2(PIN_IR_OUT_2); 	\
							clr2(PIN_IR_OUT_0);    	\
							clr2(PIN_IR_OUT_1);    	\
							clr2(PIN_IR_OUT_2);    							
#else  					
#define dir_ir()			input2(PIN_RCV_IR);		\
							output2(PIN_IR_OUT_0); 	\
							output2(PIN_IR_OUT_1); 	\
							output2(PIN_IR_OUT_2); 	\
							set2(PIN_IR_OUT_0);    	\
							set2(PIN_IR_OUT_1);    	\
							set2(PIN_IR_OUT_2);    										
#endif


#if USE_IR
#define dir_funcao_ir()		dir_ir(); 
#else
#define dir_funcao_ir()		{} 
#endif

/*********Definiçoes de hardware para a função Shift Register*********/

#define PINO_MR			4		/* P0.4 */
#define PINO_DS			5		/* P0.5 */
#define PINO_ST			6		/* P0.6 */
#define PINO_SH			15		/* P0.15 */

#define dir_mr()		output0(PINO_MR)   	/*Pino MR  como saida*/
#define dir_ds()		output0(PINO_DS)   	/*Pino DS  como saida*/
#define dir_st()		output0(PINO_ST)  	/*Pino ST como saida*/
#define dir_sh()		output0(PINO_SH)  	/*Pino SH como saida*/

#define MR(x)	    	if(x)set0(PINO_MR);  else clr0(PINO_MR);	/*Config MR(Reset)*/	
#define DS(x)	    	if(x)set0(PINO_DS);  else clr0(PINO_DS);	/*Config DS(Dado) */
#define ST(x)	    	if(x)set0(PINO_ST);  else clr0(PINO_ST);	/*Config ST(Latch)*/
#define SH(x)	    	if(x)set0(PINO_SH);  else clr0(PINO_SH);	/*Config SH(Clock)*/		

#define dir_reg()	    dir_st(); \
						dir_sh(); \
						dir_ds(); \
						dir_mr(); \
						MR(1); \
						DS(1); \
						SH(1); \
						ST(1); 


/*********Definiçoes para o Teclado Matricial 4x2*********/


/*******************
**	KEY_LIN1	p0.25
**	KEY_LIN2	p0.23
**	KEY_LIN3	p0.26
**	KEY_LIN4	p0.24
**	KEY_COL1	p1.31
**	KEY_COL2	p1.30
*******************/

/* Linhas */
#define key_lin1	25
#define key_lin2	23
#define key_lin3	26
#define key_lin4	24

/* Colunas */
#define key_col1	31ul
#define key_col2	30ul


/* Configura linhas do teclado como entrada */
#define dir_key_lin1()	input0(key_lin1)
#define dir_key_lin2()	input0(key_lin2)
#define dir_key_lin3()	input0(key_lin3)
#define dir_key_lin4()	input0(key_lin4)

#define rd_key_lin1()	read0(key_lin1)
#define rd_key_lin2()	read0(key_lin2)
#define rd_key_lin3()	read0(key_lin3)
#define rd_key_lin4()	read0(key_lin4)

/* Configura colunas do teclado */
#define dir_key_col1()	LPC_GPIO1->FIODIR |= (1ul<<key_col1) 
#define dir_key_col2()	output1(key_col2)

#define key_col1_high()	LPC_GPIO1->FIOSET |= (1ul<<key_col1)
#define key_col2_high()	set1(key_col2)


#define key_col_all_high()	key_col1_high();	\
							key_col2_high()	
						

#define key_col1_low()	LPC_GPIO1->FIOCLR |= (1ul<<key_col1)
#define key_col2_low()	clr1(key_col2)

#define key_col_all_low()	key_col1_low();	\
							key_col2_low()	
						
/*********Definiçoes para o ar condicionado*********/

#define TEMPERATURA_MIN			16
#define TEMPERATURA_MAX			30
										 													 
/*********Definiçoes de hardware para KIT MINI 1768*********/

#define PIN_KEY1_BOARD		11	/* P2.11 */
#define PIN_KEY2_BOARD		12	/* P2.12 */
#define PIN_LED1_BOARD		25	/* P3.25 */
#define PIN_LED2_BOARD		26	/* P3.26 */
#define PIN_LED3_BOARD		18	/* P1.18 */

#define LED1_BOARD_TOG()  	if(!read3(PIN_LED1_BOARD))set3(PIN_LED1_BOARD); else clr3(PIN_LED1_BOARD);
#define LED2_BOARD_TOG()  	if(!read3(PIN_LED2_BOARD))set3(PIN_LED2_BOARD); else clr3(PIN_LED2_BOARD);
#define LED3_BOARD_TOG()  	if(!read1(PIN_LED3_BOARD))set1(PIN_LED3_BOARD); else clr1(PIN_LED3_BOARD);
#define LED1_BOARD(x) 		if(!x)set3(PIN_LED1_BOARD); else clr3(PIN_LED1_BOARD);
#define LED2_BOARD(x) 		if(!x)set3(PIN_LED2_BOARD); else clr3(PIN_LED2_BOARD);
#define LED3_BOARD(x) 		if(!x)set1(PIN_LED3_BOARD); else clr1(PIN_LED3_BOARD);

#define READ_KEY1_BOARD()	(read2(PIN_KEY1_BOARD))
#define READ_KEY2_BOARD()	(read2(PIN_KEY2_BOARD))

#define dir_key1_board()	input2(PIN_KEY1_BOARD)
#define dir_key2_board()	input2(PIN_KEY2_BOARD)

#define dir_led1_board()	output3(PIN_LED1_BOARD)
#define dir_led2_board()	output3(PIN_LED2_BOARD)
#define dir_led3_board()	output1(PIN_LED3_BOARD)

#define dir_board()			dir_key1_board(); \
							dir_key2_board(); \
							dir_led1_board(); \
							dir_led2_board(); \
							dir_led3_board(); \
							set3(PIN_LED1_BOARD); \
							set3(PIN_LED2_BOARD); \
							set1(PIN_LED3_BOARD);		


/*********Definiçoes de hardware GERAL*********/

/*PINOS*/

#define PIN_LED_ATEND		27	/* P0.27 */
#define PIN_LED_LOGO		28	/* P0.28 */


#define PIN_BUZZER			16  /* P0.16 */

#define PIN_LED_PWR			PIN_LED1_BOARD

#define READ_KEY_ATEND()	READ_KEY1_BOARD()
	
#define LED_PWR_TOG()  		LED1_BOARD_TOG(); 

#define LED_ATEND(x) 		if(x)set0(PIN_LED_ATEND); else clr0(PIN_LED_ATEND);
#define LED_ATEND_TOG()  	if(!read0(PIN_LED_ATEND))set0(PIN_LED_ATEND); else clr0(PIN_LED_ATEND);

#define LED_LOGO(x) 		if(x)set0(PIN_LED_LOGO); else clr0(PIN_LED_LOGO);
#define LED_LOGO_TOG()  	if(!read0(PIN_LED_LOGO))set0(PIN_LED_LOGO); else clr0(PIN_LED_LOGO);
													
#define BUZZER(x)			if(x)set0(PIN_BUZZER); else clr0(PIN_BUZZER);
#define BUZZER_TOG()		if(!read0(PIN_BUZZER))set0(PIN_BUZZER); else clr0(PIN_BUZZER);

#define dir_buzzer()		output0(PIN_BUZZER); BUZZER(0) 

#define dir_led_logo()		output0(PIN_LED_LOGO)
#define dir_led_aten()		output0(PIN_LED_ATEND)

#define dir_leds()		    dir_led_logo(); \
							dir_led_aten();	\
							LED_ATEND(0);	\
							LED_LOGO(0);	 
					


/**********************************************************/

#define init_gpio()		 	dir_board(); \
							dir_buzzer(); \
							dir_leds(); \
							dir_funcao_ir(); \
							dir_reg(); 	
				  	

#define wdt_feed()			LPC_WDT->WDFEED = 0xAA;	LPC_WDT->WDFEED = 0x55;

#endif
