/****************************************Copyright (c)****************************************************
**								   http://www.OpenMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           adc.h
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
#ifndef __ADC_H
#define __ADC_H

#include <RTL.H>

#define USE_AD0		1
#define USE_AD1		1
#define USE_AD2		1
#define USE_AD3		1
#define USE_AD4		1
#define USE_AD5		1
#define USE_AD6		0
#define USE_AD7		0


#define ADC_DONE            0x80000000

#define DEV_QTD 			4
#define CT_QTD				6
#define CT_QTD_PARC			20
		
#define ctouch_set_all()	set_pl1_dm1();	\
							set_pl2_dm1();	\
							set_pl1_dm2();	\
							set_pl2_dm2();	\
							set_pl1_dm3();	\
							set_pl2_dm3();	\
							set1(10);		\
							set1(11)


											
/* struct */
typedef struct 
{
	volatile float valor_normal; 										/* valor normal do touch nao pressionado */
	float parc_leitura[ CT_QTD_PARC ];		  /* parcelas de leituras */
	float media_leitura;										/* media das parcelas das leituras */
	float cal;
	char  qtd_acima_media;									/* contagem de vezes que ficou acima da media	de leitura */
	char  qtd_abaixo_media;									/* contagem de vezes que ficou abaixo da media de leitura */
	volatile unsigned int   debounce;								
	char  qtd_acima_val_normal;							/* contagem de vezes que ficou acima do valor normal */
	char  qtd_abaixo_val_normal;						/* contagem de vezes que ficou abaixo do valor normal */
						 
}	CAPTOUCH;

/* struct */
typedef struct
{
	volatile char k_press[2];
	volatile char rf_state;
	char placa_dimmer;

} DEVICE;

	
/* extern */
extern DEVICE DEV[DEV_QTD];
extern CAPTOUCH CT[ CT_QTD ];
extern char CT_enable;
extern char CT_channel_num;	
extern unsigned int  CT_tmr_to_read;

extern char calIr[8][10];				  											
	
/* funções */				 	
void CT_Cheky_Press (char channelNum, CAPTOUCH *CT);

uint16_t _ADC_ReadCh0(void);
uint16_t _ADC_ReadCh1(void);
uint16_t _ADC_ReadCh2(void);
uint16_t _ADC_ReadCh3(void);
uint16_t _ADC_ReadCh4(void);
uint16_t _ADC_ReadCh5(void);
uint16_t _ADC_ReadCh6(void);
uint16_t _ADC_ReadCh7(void);

void init_adc(void); 
void CT_Varredura (void);


	

#define _powerOnAdc() 	( LPC_ADC->ADCR |= (1 << 21) )
#define _powerOffAdc() 	( LPC_ADC->ADCR |= (1 << 21) )

#define _disableAllAdcInterrupts() 	( LPC_ADC->ADINTEN &= 0x0 )

/* start conversion by software = 001 in bits 26:24 */
#define _startAdc() ( LPC_ADC->ADCR |= (1 << 24) )

/* clear conversion = 000 in bits 26:24 */
#define _stopAdc() 	( LPC_ADC->ADCR &= 0xF8FFFFFF )

/* program adc divider value */
#define ADC_MAX_FREQ    (13000000) /* 13 MHz is upper limit for ADC speed on LPC1769 */

#define CH0_DONE    (0x1 << 0)
#define CH1_DONE    (0x1 << 1)
#define CH2_DONE    (0x1 << 2)
#define CH3_DONE    (0x1 << 3)
#define CH4_DONE    (0x1 << 4)
#define CH5_DONE    (0x1 << 5)
#define CH6_DONE    (0x1 << 6)
#define CH7_DONE    (0x1 << 7)

/* poll the 'done' flag for indication of adc conversion end */
#define _waitForCh(n) {\
    while (!(LPC_ADC->ADSTAT & CH##n##_DONE));\
}

#define ADC_VALUE_MAX 0xFFF		/*AD 12bits*/
//#define ADC_VALUE_MAX 0x3FF		/*AD 10bits*/

///* retrieve the ADC reading 10bits*/        
//#define _getAdcChVal(n)    ( (LPC_ADC->ADDR##n## >> 4) & 0x3FF )
/* retrieve the ADC reading 12bits*/        
#define _getAdcChVal(n)    ( (LPC_ADC->ADDR##n## >> 4) &ADC_VALUE_MAX )

/**********************************************************/
/* configure AD0_0 - GPIO_0.23 */
/**********************************************************/
#define GPIO_0_23       (~(0x3 << 14))
#define PULL_UP_0_23    ((~(0x3 << 14)))

#define _setCh0GpioMode()   ( LPC_PINCON->PINSEL1 &= GPIO_0_23 )
#define _setCh0GpioPullup() ( LPC_PINCON->PINMODE1 &= PULL_UP_0_23 )

#define ADC_0_23        (0x1 << 14)
#define FLOAT_0_23      (0x2 << 14)

#define _setCh0AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 0);\
   LPC_PINCON->PINSEL1 |= ADC_0_23;\
   LPC_PINCON->PINMODE1 |= FLOAT_0_23;\
}

#define _Ch0GpioOff()  		 ( LPC_GPIO0->FIOPIN &= ~(1<<23))
#define _setCh0GpioCharge()  ( LPC_GPIO0->FIOSET |=  (1<<23))
#define _setCh0GpioDirOut()  ( LPC_GPIO0->FIODIR |=  (1<<23))
#define _setCh0GpioDirIn()   ( LPC_GPIO0->FIODIR &= ~(1<<23))

/**********************************************************/
/* configure AD0_1 - GPIO_0.24 */
/**********************************************************/
#define GPIO_0_24       (~(0x3 << 16))
#define PULL_UP_0_24    ((~(0x3 << 16)))

#define _setCh1GpioMode() ( LPC_PINCON->PINSEL1 &= GPIO_0_24 )
#define _setCh1GpioPullup() (LPC_PINCON->PINMODE1 &= PULL_UP_0_24)

#define ADC_0_24        (0x1 << 16)
#define FLOAT_0_24      (0x2 << 16)

#define _setCh1AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 1);\
   LPC_PINCON->PINSEL1 |= ADC_0_24;\
   LPC_PINCON->PINMODE1 |= FLOAT_0_24;\
}

#define _Ch1GpioOff()  		 ( LPC_GPIO0->FIOPIN &= ~(1<<24))
#define _setCh1GpioCharge()  ( LPC_GPIO0->FIOSET |=  (1<<24))
#define _setCh1GpioDirOut()  ( LPC_GPIO0->FIODIR |=  (1<<24))
#define _setCh1GpioDirIn()   ( LPC_GPIO0->FIODIR &= ~(1<<24))

/**********************************************************/
/* configure AD0_2 - GPIO_0.25 */
/**********************************************************/
#define GPIO_0_25       (~(0x3 << 18))
#define PULL_UP_0_25    ((~(0x3 << 18)))

#define _setCh2GpioMode() ( LPC_PINCON->PINSEL1 &= GPIO_0_25 )
#define _setCh2GpioPullup() ( LPC_PINCON->PINMODE1 &= PULL_UP_0_25 )

#define ADC_0_25        (0x1 << 18)
#define FLOAT_0_25      (0x2 << 18)

#define _setCh2GpioFloat() ( LPC_PINCON->PINMODE1 |= FLOAT_0_25 )

#define _setCh2AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 2);\
   LPC_PINCON->PINSEL1 |= ADC_0_25;\
   LPC_PINCON->PINMODE1 |= FLOAT_0_25;\
}

#define _Ch02GpioOff()  	 ( LPC_GPIO0->FIOPIN &= ~(1<<25))
#define _setCh2GpioDirOut()  ( LPC_GPIO0->FIODIR |=  (1<<25))
#define _setCh2GpioCharge()  ( LPC_GPIO0->FIOSET |=  (1<<25))
#define _setCh2GpioDirIn()   ( LPC_GPIO0->FIODIR &= ~(1<<25))


/**********************************************************/
/* configure AD0_3 - GPIO_0.26 */
/**********************************************************/
#define GPIO_0_26       (~(0x3 << 20))
#define PULL_UP_0_26    (~(0x3 << 20))

#define _setCh3GpioMode() ( LPC_PINCON->PINSEL1 &= GPIO_0_26 )
#define _setCh3GpioPullup() ( LPC_PINCON->PINMODE1 &= PULL_UP_0_26 )

#define ADC_0_26        (0x1 << 20)
#define FLOAT_0_26      (0x2 << 20)

#define _setCh3AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 3);\
   LPC_PINCON->PINSEL1 |= ADC_0_26;\
   LPC_PINCON->PINMODE1 |= FLOAT_0_26;\
}

#define _Ch3GpioOff()  		 ( LPC_GPIO0->FIOPIN &= ~(1<<26))
#define _setCh3GpioDirOut()  ( LPC_GPIO0->FIODIR |=  (1<<26))
#define _setCh3GpioCharge()  ( LPC_GPIO0->FIOSET |=  (1<<26))
#define _setCh3GpioDirIn()   ( LPC_GPIO0->FIODIR &= ~(1<<26))


/**********************************************************/
/* configure AD0_4 - GPIO_1.30 */
/**********************************************************/
#define GPIO_1_30       (~(0x3 << 28))
#define PULL_UP_1_30    (~(0x3 << 28))

#define _setCh4GpioMode() ( LPC_PINCON->PINSEL3 &= GPIO_1_30 )

#define _setCh4GpioPullup() ( LPC_PINCON->PINMODE3 &= PULL_UP_1_30 )

#define ADC_1_30        (0x3 << 28)
#define FLOAT_1_30      (0x2 << 28)

#define _setCh4AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 4);\
   LPC_PINCON->PINSEL3 |= ADC_1_30;\
   LPC_PINCON->PINMODE3 |= FLOAT_1_30;\
}

#define _Ch4GpioOff()  		 ( LPC_GPIO1->FIOPIN &= ~(1<<30))
#define _setCh4GpioDirOut()  ( LPC_GPIO1->FIODIR |=  (1<<30))
#define _setCh4GpioCharge()  ( LPC_GPIO1->FIOSET |=  (1<<30))
#define _setCh4GpioDirIn()   ( LPC_GPIO1->FIODIR &= ~(1<<30))

/**********************************************************/
/* configure AD0_5 - GPIO_1.31 */
/**********************************************************/
#define GPIO_1_31       (~(0x3u << 30))
#define PULL_UP_1_31    (~(0x3u << 30))

#define _setCh5GpioMode() ( LPC_PINCON->PINSEL3 &= GPIO_1_31 )
#define _setCh5GpioPullup() ( LPC_PINCON->PINMODE3 &= PULL_UP_1_31 )

#define ADC_1_31        (0x3u << 30)
#define FLOAT_1_31      (0x2u << 30)

#define _setCh5AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 5);\
   LPC_PINCON->PINSEL3 |= ADC_1_31;\
   LPC_PINCON->PINMODE3 |= FLOAT_1_31;\
}

#define _Ch5GpioOff()  		 ( LPC_GPIO1->FIOPIN &= ~(1u<<31))
#define _setCh5GpioDirOut()  ( LPC_GPIO1->FIODIR |=  (1u<<31))
#define _setCh5GpioCharge()  ( LPC_GPIO1->FIOSET |=  (1u<<31))
#define _setCh5GpioDirIn()   ( LPC_GPIO1->FIODIR &= ~(1u<<31))

/**********************************************************/
/* configure AD0_6 - GPIO_0.3 */
/**********************************************************/
#define GPIO_0_3       (~(0x3 << 6))
#define PULL_UP_0_3    (~(0x3 << 6))

#define _setCh6GpioMode()( LPC_PINCON->PINSEL0 &= GPIO_0_3 ) 
#define _setCh6GpioPullup() ( LPC_PINCON->PINMODE0 &= PULL_UP_0_3 )

#define ADC_0_6        (0x2 << 6)
#define FLOAT_0_6      (0x2 << 6)

#define _setCh6AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 6);\
   LPC_PINCON->PINSEL0 |= ADC_0_6;\
   LPC_PINCON->PINMODE0 |= FLOAT_0_6;\
}

#define _Ch6GpioOff()  		 ( LPC_GPIO0->FIOPIN &= ~(1<<3))
#define _setCh6GpioDirOut()  ( LPC_GPIO0->FIODIR |=  (1<<3))
#define _setCh6GpioCharge()  ( LPC_GPIO0->FIOSET |=  (1<<3))
#define _setCh6GpioDirIn()   ( LPC_GPIO0->FIODIR &= ~(1<<3))


/**********************************************************/
/* configure AD0_7 - GPIO_0.2 */
/**********************************************************/
#define GPIO_0_2       (~(0x3 << 4))
#define PULL_UP_0_2    (~(0x3 << 4))

#define _setCh7GpioMode() ( LPC_PINCON->PINSEL0 &= GPIO_0_2 )
#define _setCh7GpioPullup() ( LPC_PINCON->PINMODE0 &= PULL_UP_0_2 )

#define ADC_0_2        (0x2 << 4)
#define FLOAT_0_2      (0x2 << 4)

#define _setCh7AdcMode() {\
   LPC_ADC->ADCR &= 0xFFFFFF00;\
   LPC_ADC->ADCR |= (0x1 << 7);\
   LPC_PINCON->PINSEL0 |= ADC_0_2;\
   LPC_PINCON->PINMODE0 |= FLOAT_0_2;\
}

#define _Ch7GpioOff()  		 ( LPC_GPIO0->FIOPIN &= ~(1<<2))
#define _setCh7GpioDirOut()  ( LPC_GPIO0->FIODIR |=  (1<<2))
#define _setCh7GpioCharge()  ( LPC_GPIO0->FIOSET |=  (1<<2))
#define _setCh7GpioDirIn()   ( LPC_GPIO0->FIODIR &= ~(1<<2))

/* type definition for the ADC channel type */
typedef enum {
#if USE_AD0
        CH0 = 0,
#endif
#if USE_AD1
        CH1,
#endif
#if USE_AD2
        CH2,
#endif
#if USE_AD3
        CH3,
#endif
#if USE_AD4
        CH4,
#endif
#if USE_AD5
        CH5,
#endif
#if USE_AD6
		CH6,
#endif
#if USE_AD7
		CH7,
#endif
        NUM_CHANNELS,
        UNUSED_CHANNEL
} ChannelIdType;


//uint16_t _ADC_ReadCh0(void);
//uint16_t _ADC_ReadCh1(void);
//uint16_t _ADC_ReadCh2(void);
//uint16_t _ADC_ReadCh3(void);
//uint16_t _ADC_ReadCh4(void);
//uint16_t _ADC_ReadCh5(void);
//uint16_t _ADC_ReadCh6(void);
//uint16_t _ADC_ReadCh7(void);

//void init_adc(void); 
//void _calibrateChannel(char chNum); 
//short read_ad(char chNum);
//void cfgGpioTouch(void); 
//
//								
//extern uint16_t average[NUM_CHANNELS];
//extern uint16_t reading[NUM_CHANNELS];
//extern uint16_t  debounce[NUM_CHANNELS];  
//extern uint8_t  _p[NUM_CHANNELS];  


 /************************************************************/


#endif /* end __ADC_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
