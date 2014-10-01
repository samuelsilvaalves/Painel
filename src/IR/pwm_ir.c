/****************************************************************************
 *   $Id:: pwm.c 5748 2010-11-30 23:48:37Z usb00423                         $
 *   Project: NXP LPC17xx PWM example
 *
 *   Description:
 *     This file contains PWM code example which include PWM initialization, 
 *     PWM interrupt handler, and APIs for PWM access.
 *
 ***************************************************************************/

#include <LPC17xx.h>
#include <stdio.h>
#include "pwm_ir.h"
#include "control_ir.h"

#if USE_IR	/*Inclui na compilação a função IR da placa?*/

int PWM_freq_KHz = CARRIER_FREQ_38KHZ;

/******************************************************************************

******************************************************************************/
void PWM1_IRQHandler (void) 
{
  	uint32_t regVal;
  	regVal = LPC_PWM1->IR;
  	if ( regVal & MR0_INT )	
		PWM_Set(PWM_freq_KHz);
  	LPC_PWM1->IR |= regVal;				 
  	return;
}

/******************************************************************************

******************************************************************************/
void PWM_Init(void)
{
	char i=0;
								
	LPC_PWM1->TCR = TCR_RESET;			/*Counter Reset*/  
	LPC_PWM1->PR  = 0x00;				/*Prescaler  count frequency:Fpclk*/ 
	LPC_PWM1->MCR = PWMMR0I;			/*Interrupt on PWMMR0, reset on PWMMR0, reset  TC if PWM matches*/ 				
	PWM_Set(CARRIER_FREQ_38KHZ);		/*Configura a frequencia do PWM default*/
	LPC_PWM1->PCR = 0;
	LPC_PWM1->TCR = 0x00;				/*Stop all PWMs*/ 

	for(i=0;i<3;i++)
		LPC_GPIO2->FIODIR |= (1<<i); 	/*P2.0 ....P2.2 como saidas*/
	
#if USE_IR_OUT_ON_HIGH
	LPC_GPIO2->FIOPIN = 0x00;		 	/*Desliga P2.0 ....P2.7*/
#else
	LPC_GPIO2->FIOPIN 	|=  (1<<0);
	LPC_GPIO2->FIOPIN 	|=  (1<<1);
	LPC_GPIO2->FIOPIN 	|=  (1<<2);
#endif						

	NVIC_EnableIRQ(PWM1_IRQn);
}

/******************************************************************************

******************************************************************************/
void PWM_Set(uint32_t cycle)
{
	/*Configura PWM*/
//	LPC_PWM1->MR0 = cycle;	 
//	LPC_PWM1->MR1 = cycle * 5/6;  
//	LPC_PWM1->MR2 = cycle * 5/6;  
//	LPC_PWM1->MR3 = cycle * 5/6;  
//	LPC_PWM1->MR4 = cycle * 5/6;  
//	LPC_PWM1->MR5 = cycle * 5/6;  
//	LPC_PWM1->MR6 = 0;


	LPC_PWM1->MR0 = cycle;	 
	LPC_PWM1->MR1 = cycle/2;		/*50% duty cycle*/  
	LPC_PWM1->MR2 = cycle/2;  
	LPC_PWM1->MR3 = cycle/2; 
	LPC_PWM1->MR4 = cycle/2;  
	LPC_PWM1->MR5 = cycle/2;
	LPC_PWM1->MR6 = 0;
			  
	/*The LER will be cleared when the Match 0 takes place, in order to
	  load and execute the new value of match registers, all the PWMLERs need to
	  reloaded. all PWM latch enabled*/ 
	LPC_PWM1->LER = LER0_EN | LER1_EN | LER2_EN; //| LER3_EN | LER4_EN | LER5_EN;
}

/******************************************************************************

******************************************************************************/
void PWM_Start(char channel)
{
	if(channel == 0 || channel >= 16)
	{	
//		/*Configura P2.4 para PWM1_5*/
//		LPC_PINCON->PINSEL4 &= ~(1<<9); 
//		LPC_PINCON->PINSEL4 |=  (1<<8);
//		LPC_PWM1->PCR |= PWMENA5;

		/*Configura P2.0 para PWM1_1*/
		LPC_PINCON->PINSEL4 &= ~(1<<1);  
		LPC_PINCON->PINSEL4 |=  (1<<0);
		LPC_PWM1->PCR |= PWMENA1;
		/*Configura P2.1 para PWM1_2*/
		LPC_PINCON->PINSEL4 &= ~(1<<3); 
		LPC_PINCON->PINSEL4 |=  (1<<2);
		LPC_PWM1->PCR |= PWMENA2;
		/*Configura P2.2 para PWM1_3*/
		LPC_PINCON->PINSEL4 &= ~(1<<5); 
		LPC_PINCON->PINSEL4 |=  (1<<4);
		LPC_PWM1->PCR |= PWMENA3;				
								
	}else
	{
		if(channel & (1<<0))
		{	
			/*Configura P2.0 para PWM1_1*/
			LPC_PINCON->PINSEL4 &= ~(1<<1);  
			LPC_PINCON->PINSEL4 |=  (1<<0);
			LPC_PWM1->PCR |= PWMENA1;		
		}
		if(channel & (1<<1))
		{	
			/*Configura P2.1 para PWM1_2*/
			LPC_PINCON->PINSEL4 &= ~(1<<3); 
			LPC_PINCON->PINSEL4 |=  (1<<2);
			LPC_PWM1->PCR |= PWMENA2;		
		}
		if(channel & (1<<2))
		{	
			/*Configura P2.2 para PWM1_3*/
			LPC_PINCON->PINSEL4 &= ~(1<<5); 
			LPC_PINCON->PINSEL4 |=  (1<<4);
			LPC_PWM1->PCR |= PWMENA3;		
		}
	}

	LPC_PWM1->PR  = 0x00;				/*Prescaler  count frequency:Fpclk*/ 
	LPC_PWM1->MCR = PWMMR0I;			/*Interrupt on PWMMR0, reset on PWMMR0, reset  TC if PWM matches*/ 
	PWM_Set(PWM_freq_KHz);				/*Configura a ultima frequencia configurada*/

	/*counter enable, PWM enable*/
	LPC_PWM1->TCR = TCR_CNT_EN | TCR_PWM_EN;	 
}

/******************************************************************************

******************************************************************************/
void PWM_Stop(void)
{	
	/*Desliga todos os PWMs*/
	LPC_PWM1->PCR = 0;
	LPC_PWM1->TCR = 0x00;	

	/*Configura P2.0 para GPIO*/
	LPC_PINCON->PINSEL4 &= ~(1<<1); 
	LPC_PINCON->PINSEL4 &= ~(1<<0);
	 
#if USE_IR_OUT_ON_HIGH
	LPC_GPIO2->FIOPIN 	&= ~(1<<0);
#else
	LPC_GPIO2->FIOPIN 	|=  (1<<0);
#endif
	
	/*Configura P2.1 para GPIO*/ 
	LPC_PINCON->PINSEL4 &= ~(1<<3); 
	LPC_PINCON->PINSEL4 &= ~(1<<2);

#if USE_IR_OUT_ON_HIGH
	LPC_GPIO2->FIOPIN 	&= ~(1<<1);
#else
	LPC_GPIO2->FIOPIN 	|=  (1<<1);
#endif 
	 
	/*Configura P2.2 para GPIO*/
	LPC_PINCON->PINSEL4 &= ~(1<<5); 
	LPC_PINCON->PINSEL4 &= ~(1<<4);	

#if USE_IR_OUT_ON_HIGH
	LPC_GPIO2->FIOPIN 	&= ~(1<<2);
#else
   	LPC_GPIO2->FIOPIN 	|= (1<<2);
#endif
								
}
/******************************************************************************
                            End Of File
******************************************************************************/

#endif

