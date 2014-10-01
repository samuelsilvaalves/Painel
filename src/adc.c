/****************************************Copyright (c)****************************************************
**								   http://www.OpenMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           adc.c
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

#include <LPC17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adc.h"
#include "touch.h"
#include "timer.h"
#include "register.h"
#include "tcpip.h"
#include "uart.h"

//uint16_t average[NUM_CHANNELS];
//uint16_t reading[NUM_CHANNELS];
//uint16_t  debounce[NUM_CHANNELS]; 
//
//uint8_t  _p[NUM_CHANNELS];   
//
/////* local data tables and variables */
//static uint16_t histCh[NUM_CHANNELS][20];  /* this keeps the last 16 readings for the channels */
//static uint8_t  avgindex[NUM_CHANNELS];     /* this is a pointer to the history channel */
//	

/* definition of function type used to perform the adc reading */
typedef uint16_t (*_adcCallbackFctType)(char chNum);

/* table of callback functions for adc reading */
/* could be different for each channel */
const _adcCallbackFctType AdcReadTable[NUM_CHANNELS]  = 
{
#if USE_AD0
    (_adcCallbackFctType) _ADC_ReadCh0,
#endif
#if USE_AD1
    (_adcCallbackFctType) _ADC_ReadCh1,
#endif
#if USE_AD2
    (_adcCallbackFctType) _ADC_ReadCh2,
#endif
#if USE_AD3
    (_adcCallbackFctType) _ADC_ReadCh3,
#endif
#if USE_AD4
    (_adcCallbackFctType) _ADC_ReadCh4,
#endif
#if USE_AD5
    (_adcCallbackFctType) _ADC_ReadCh5,
#endif
#if USE_AD6
    (_adcCallbackFctType) _ADC_ReadCh6,
#endif
#if USE_AD7
    (_adcCallbackFctType) _ADC_ReadCh7 
#endif      
};

#define DEBOUNCE_KEY 800 //1500

CAPTOUCH CT[ CT_QTD ];

char CT_enable = 0;
char CT_channel_num;
unsigned int CT_tmr_to_read;	
				 

char calIr[8][10];
				 
DEVICE DEV[DEV_QTD];

/*****************************************************************************
** Function name:               ADC_Cheky_Press
**
** Descriptions:                Verificar se está sendo pressionado 
**
** parameters:                  channelNum , *pCT
** Returned value:              void
**
*****************************************************************************/
void CT_Cheky_Press (char channelNum, CAPTOUCH *pCT)
{
	//static int cont = 0; 
	unsigned short curReading=0;
	float   soma_parc;
	int i,j;
	static unsigned char key_press;
	static int debounce[1] = {0};//,cont_press_release = 0;
	float trigger=0.0, media=0.0;
	//static int tdeb=0;
	static unsigned char press = 0;
	static int cnt_press = 0;
	static int cnt_qtd_press[8] = {0,0,0,0,0,0,0,0}, sub[6] = {0,0,0,0,0,0};
	
	/* leitura do captouch */
	switch(channelNum)
	{
		case 0:			
			curReading = _ADC_ReadCh0();
			break;

		case 1:
			curReading = _ADC_ReadCh1();
			break;

		case 2:
			curReading = _ADC_ReadCh2();
			break;

		case 3:
			curReading = _ADC_ReadCh3();
			break;

		case 4:
			curReading = _ADC_ReadCh4();
			break;

		case 5:
			curReading = _ADC_ReadCh5();
			break;
		
		case 8:
			key_press = 0;
			return;

	}

	/* rotaciona as parcelas */
	for (i=0; i<(CT_QTD_PARC-1); i++)
		pCT->parc_leitura[i] = pCT->parc_leitura[i+1];

	pCT->parc_leitura[CT_QTD_PARC-1] = (float)curReading;

	/* calcula a media das leituras */
	soma_parc = 0.0;
	for(i=0; i<CT_QTD_PARC; i++)
		soma_parc += pCT->parc_leitura[i];
	soma_parc = soma_parc / CT_QTD_PARC;

	pCT->media_leitura = (soma_parc + pCT->media_leitura) / 2;

//	printf("\r[%d][%d][%d]",channelNum,pCT->media_leitura,pCT->valor_normal);
	media = (float)pCT->media_leitura;

	/* leitura do captouch */
	trigger = pCT->valor_normal * pCT->cal;

	/* verifica se o valor esta acima da media -> PRESSIONANDO */
	if(media > trigger)
	{
		//if(pCT->debounce >= 25)//---------------------
		if(pCT->debounce >= 25)
		{
			int aux = DEV[channelNum/2].k_press[channelNum%2];

			DEV[channelNum/2].k_press[channelNum%2] = 1;
			
			key_press |= (1<<channelNum);

			press |= (1<<channelNum);

			sub[channelNum] = pCT->media_leitura - pCT->valor_normal;
			
			pCT->debounce = 200;

//			if(sub[channelNum] > 15)
//			{
//				sub[channelNum] = 0;
//				press &= ~(1<<channelNum);
//				key_press &= ~(1<<channelNum);
//			}

			/* debug */
			if(1 && !aux) 
			{
					
       			printf("[+%d][%5.3f][%5.3f][%5.4f]..[%c%c%c%c%c%c%c%c]\r\r",channelNum,pCT->media_leitura,pCT->valor_normal,pCT->cal,
				                                     key_press & (1<<0) ? '1':'0',
													 key_press & (1<<1) ? '1':'0',
													 key_press & (1<<2) ? '1':'0',
													 key_press & (1<<3) ? '1':'0',
													 key_press & (1<<4) ? '1':'0',
													 key_press & (1<<5) ? '1':'0',
													 key_press & (1<<6) ? '1':'0',
													 key_press & (1<<7) ? '1':'0');
				fflush(stdout);
 			}
		}
		else
		{
			if(pCT->debounce < 200) /* Alterado */
				pCT->debounce ++;
		}
		pCT->qtd_acima_val_normal = 0;
		pCT->qtd_abaixo_val_normal = 0;
	}
	/* verifica se esta abaixo da media -> NAO PRESSIONANDO */
	else
	{
		if(pCT->debounce == 0)
		//if(pCT->debounce <= 5)
		{
			int aux = DEV[channelNum/2].k_press[channelNum%2];
			
			DEV[channelNum/2].k_press[channelNum%2] = 0;
			
//			if(++chs[0] > 1000)
//			{
//				chs[0] = 0;
//				sprintf(buf_tx,"SLCS - %u\r\n\0",lastChannelNum);	
//				tcpSend (buf_tx, strlen(buf_tx), tcp_client_soc[0],CMD_SEND_TO_CLIENT);	
//			}

			/* debug */
   			if(1 && aux) 
			{	 
				//sprintf(buf_tx,"SLCS - %d\r\n\0",channelNum);
				//for(j=0;j<MAX_NUM_SOC;j++)
					//tcpSend (buf_tx, strlen(buf_tx), tcp_client_soc[0],CMD_SEND_TO_CLIENT);
				//lastChannelNum = channelNum;
 				printf("[-%d][%5.2f][%5.2f]\r", channelNum, pCT->media_leitura, pCT->valor_normal);
				fflush(stdout);	
			}
		}
		else
		{
			if (pCT->debounce)
				pCT->debounce --;
//			if (pCT->debounce <= 2)
//				pCT->debounce -= 2;

			pCT->qtd_acima_val_normal = 0;
			pCT->qtd_abaixo_val_normal = 0;
		}
	}

	i = 0;

	/* calibra valor normal quando não está pressionado */
  	if(!debounce[i] /*|| pCT->debounce == 0*/)
	{
		//key_press = 0;
		//tdeb = 0;
		if(pCT->media_leitura >= pCT->valor_normal)
		{
			pCT->qtd_acima_val_normal ++;
			pCT->qtd_abaixo_val_normal = 0;
		}
		else
		{
			pCT->qtd_acima_val_normal = 0;
			pCT->qtd_abaixo_val_normal ++;
		}

		/* Se a leitura for menor que a media */
		if(pCT->qtd_abaixo_val_normal >= 30/*15*/)
		{
			pCT->valor_normal = (pCT->media_leitura + (10 * pCT->valor_normal)) / 11;
			//pCT->valor_normal = (pCT->media_leitura +  pCT->valor_normal) / 2;
			pCT->qtd_abaixo_val_normal = 0;
		}

		/* Se a leitura for maior que a media */
		if(pCT->qtd_acima_val_normal >= 200/*100*/)
		{
	  		pCT->valor_normal = (pCT->media_leitura + (3 * pCT->valor_normal)) / 4;
			//pCT->valor_normal = (pCT->media_leitura +  pCT->valor_normal) / 2;
			pCT->qtd_acima_val_normal = 0;
    	}
  	}

	if(flag_wait_touch)
		return;

//	if(touch_led_press != TOUCH_NONE)
//		key_press = 0;

	switch(key_press)
	{
		/*L1 x C1: Scene 0*/
		case 0x24:	
			if(!debounce[i]) {
				exe_scene(0);
				//printf("Scene 0\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[0] >= 1000)
			{
				cnt_qtd_press[0] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;

		/*L4 x C1: Scene 6*/
		case 0x22:			
			if(!debounce[i]) {
				exe_scene(6);
				//printf("Scene 6\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[6] >= 1000)
			{
				cnt_qtd_press[6] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;

		/*L2 x C1: Scene 2*/
		case 0x21:
			if(!debounce[i]) {
				exe_scene(2);
				//printf("Scene 2\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[2] >= 1000)
			{
				cnt_qtd_press[2] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;

		/*L1 x C2: Scene 1*/
		case 0x14:
			if(!debounce[i]) {
				exe_scene(1);
				//printf("Scene 1\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[1] >= 1000)
			{
				cnt_qtd_press[1] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;

		/*L4 x C2: Scene 7 (OFF)*/
		case 0x12:
			if(!debounce[i]) {
				exe_scene(7);
				//printf("Scene 7\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[7] >= 1000)
			{
				cnt_qtd_press[7] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;

		/*L2 x C2: Scene 3*/
		case 0x11:
			if(!debounce[i]) {
				exe_scene(3);
				//printf("Scene 3\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[3] >= 1000)
			{
				cnt_qtd_press[3] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;
	
		/*L3 x C1: Scene 4*/
		case 0x28:
			if(!debounce[i]) {
				exe_scene(4);
				//printf("Scene 4\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[4] >= 1000)
			{
				cnt_qtd_press[4] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;

		/*L3 x C2: Scene 5*/
		case 0x18:
			if(!debounce[i]) {
				exe_scene(5);
				//printf("Scene 5\r");
				//pCT->valor_normal = media;
				//debounce[i] = DEBOUNCE_KEY;
			}
			if(++cnt_qtd_press[5] >= 1000)
			{
				cnt_qtd_press[5] = 0;
				debounce[i] = 0;
			}else
				debounce[i] = DEBOUNCE_KEY;
			//key_press = 0;
			break;

		default:
				

			//debounce = 0;
//			if(touch_led_press != TOUCH_NONE)
//			{
//				if(!tick)
//					return;
//				if(++cont_press_release >= 3)
//				{
//					cont_press_release = 0;
//					touch_led_press = TOUCH_NONE;
//				}
//			}
//			else
//			{				
//				for(j=TOUCH_SCENE_0;j<3*NUM_SCENE;j++)	/*Loop para desligar todos os leds 4x2*/
//					out_leds &= ~(1 << j);
//			}
			break;
	}
	fflush(stdout);

	/* se passar muito tempo pressionado */
// 	if(debounce[i]){
// 		tdeb++;
// 		if(tdeb>(2*DEBOUNCE_KEY)) {
// 			tdeb = 0;
// 			debounce[i] = 1;
// 			for(j=0; j<CT_QTD; j++)	{
// 				CT[j].debounce = 0;
// 			}
// 		}
// 	}

//	for(i=0;i<16;i++)
	//clear_debounce(i);

	if( press != 0)
	{
		if((press & (1<<5) ? 1:0 + press & (1<<4) ? 1:0 + press & (1<<3) ? 1:0 + press & (1<<2) ? 1:0 + 
		    press & (1<<1) ? 1:0 + press & (1<<0) ? 1:0) > 2)
		{
			key_press = 0;
			press = 0;	
			for(j=0;j<CT_QTD;j++)
			{
				CT[j].debounce = 0;
				CT[j].valor_normal = 0xFFF;
				CT[j].debounce = 0;
				CT[j].qtd_acima_val_normal = 0;
				CT[j].qtd_abaixo_val_normal = 0;
				CT[j].qtd_acima_media = 0;
				CT[j].qtd_abaixo_media = 0;
			}
		}else
		{
			if(++cnt_press >= 500)
			{
				cnt_press = 0;
				
	//			sprintf(buf_tx,"SLCS %c %c %c %c %c %c\r\0",press & (1<<5) ? '1':'0',
	//													 press & (1<<4) ? '1':'0',
	//													 press & (1<<3) ? '1':'0',
	//													 press & (1<<2) ? '1':'0',
	//													 press & (1<<1) ? '1':'0',
	//													 press & (1<<0) ? '1':'0');
				
				sprintf(buf_tx,"SLCS %c %u %c %u %c %u %c %u %c %u %c %u\r\0",press & (1<<5) ? '1':'0', sub[5],
														 press & (1<<4) ? '1':'0', sub[4],
														 press & (1<<3) ? '1':'0', sub[3],
														 press & (1<<2) ? '1':'0', sub[2],
														 press & (1<<1) ? '1':'0', sub[1],
														 press & (1<<0) ? '1':'0', sub[0]);
	
				tcpSend (buf_tx, strlen(buf_tx), tcp_client_soc[0],CMD_SEND_TO_CLIENT);
				press = 0;
			}
		}
	}else
		cnt_press = 0;

//	if((press & (1<<5) ? 1:0 + press & (1<<4) ? 1:0 + press & (1<<3) ? 1:0 + press & (1<<2) ? 1:0 + 
//	    press & (1<<1) ? 1:0 + press & (1<<0) ? 1:0) > 2)
//	{
//		key_press = 0;	
//		for(j=0;j<CT_QTD;j++)
//		{
//			CT[j].debounce = 0;
//			CT[j].valor_normal = 0xFFF;
//			CT[j].debounce = 0;
//			CT[j].qtd_acima_val_normal = 0;
//			CT[j].qtd_abaixo_val_normal = 0;
//			CT[j].qtd_acima_media = 0;
//			CT[j].qtd_abaixo_media = 0;
//		}
//		printf("Init Cal\r");
//		fflush(stdout);
//	}


//	if(DEV[channelNum/2].k_press[channelNum%2])
//	{
//		if(++cont >= 5)
//		{
//			cont = 0;
//			sprintf(buf_tx,"SLCS + %d\r\n\0",channelNum);
//			tcpSend (buf_tx, strlen(buf_tx), tcp_client_soc[0],CMD_SEND_TO_CLIENT);
//		}
//	}

	if(debounce[i])	
	{					
		debounce[i]--;	
		if(!debounce[i])	  
		{						
			touch_led_press = TOUCH_NONE;					   
			for(j=TOUCH_SCENE_0;j<3*NUM_SCENE;j++) 
				out_leds &= ~(1 << j);			   
		} 											
		return;			
	}
}




/*----------------------------------------------------------------------------
  Define clock ADC
 *----------------------------------------------------------------------------*/
void _setAdcDivider(uint32_t cpuFreq)
{
    uint8_t adcClkDivider = 4; 
    div_t divresult;

    /* determine which dividing factor is used from CPU clock */        
    switch(((LPC_SC->PCLKSEL0) >> 24) & 0x3)
    {
        case 0x0:
            adcClkDivider = 4;	
            break;
        case (0x1):
            adcClkDivider = 1;
            break;
        case (0x2):
            adcClkDivider = 2;
            break;
        case (0x3):
            adcClkDivider = 8;
            break;
    }

    /* calculate the lowest possible divider to get as close as possible to max adc speed */    
    divresult = div (cpuFreq / adcClkDivider, ADC_MAX_FREQ);
    LPC_ADC->ADCR |= ((uint8_t)divresult.quot) << 8;  
}
/*----------------------------------------------------------------------------
  this function updated the average channel reading at runtime 
 *----------------------------------------------------------------------------*/  
//void updateAverage(char chNum)
//{
//	int8_t index = avgindex[chNum];
//	uint32_t sum = 0;
//	uint32_t i;
//
//	histCh2[chNum][index] = reading[chNum]; /* put the last reading into history buffer */
//
//    /* compute the mean over the last 16 values */
//	for(i=0;i<16;i++) 
//    {
//        sum += histCh2[chNum][index]; 	/* sum all the values */
//	    if (--index < 0) index = 15;  	/* roll back pointer	*/
//	}
//
//    /* update the mean value */
//    average[chNum] = (sum >> 4 );		 	/* new average is sum/16 */
//
//    /* update the new index for the mean */
//    avgindex[chNum]++;
//    if(avgindex[chNum] == 16) avgindex[chNum] = 0; 
//	
//}
/*----------------------------------------------------------------------------
   process of adc reading 
   readings are ordered per channel 
   kpresses are ordered per kbd values 
 *----------------------------------------------------------------------------*/  
//#define UPPER_THR 8
//#define LOWER_THR 3
//char _processAdcReading(char chNum)
//{
//	uint32_t currentAvg = average[chNum];
//	uint32_t upperThreshold = currentAvg + (currentAvg*UPPER_THR)/100;
//	uint32_t lowerThreshold = currentAvg + (currentAvg*LOWER_THR)/100;
//
//    if (reading[chNum] > upperThreshold)        /* above (average + 6% of average) -> press condition */
//    {
//        if (debounce[chNum] > 8)                /* debounce, 8 successive triggers for press */
//        {
//            //kbdPress[Ch2KpadMap[chNum]] = 1;             /* reached max, indicate pressed */
//			//kPressCntr++;
//        	debounce[chNum] = 0; // now it is pressed
//			return __TRUE;
//		}else
//            debounce[chNum] ++;                           /* still going toward max */	
//    }else 
//	if (reading[chNum] < lowerThreshold)   /* below (average + 3% of average) -> not detected condition */
//    {
//    	debounce[chNum] --;                           
//    }
//	return __FALSE;
//}

/*----------------------------------------------------------------------------
  calibration channel function 
 *----------------------------------------------------------------------------*/  
#define CALIBRATION_LOOP (200)
//static void _calibrateChannel(char chNum) 
//{
//    int calibCntr,i;
//	float med,aver;
//
//	for(i=0,aver=0;i<5;i++)
//	{
//		for (calibCntr=0,med=0; calibCntr < CALIBRATION_LOOP; calibCntr++)                   
//			med = (*AdcReadTable[chNum])(chNum) + med;
//		aver = aver + (med/CALIBRATION_LOOP); 
//	}	 
//	average[chNum] = aver/5;
//
//
//

//    for (calibCntr=0; calibCntr < CALIBRATION_LOOP; calibCntr++)                         
//    {
//		reading[chNum] = (*AdcReadTable[chNum])(chNum);
//		updateAverage(chNum); 
//    }
//	average[chNum] = average[chNum] + SENSIBILITY_MASTER;
//}
/*----------------------------------------------------------------------------
  
 *----------------------------------------------------------------------------*/  
//#define UPPER_THR 5
//short read_ad(char chNum)
//{
//	int i,j,x;
//	float med;
//	uint32_t upperThreshold = average[chNum] + (average[chNum]*UPPER_THR)/100;
//
//	reading[chNum] = 0;
//	for(j=0,x=0;j<2;j++)
//	{
//		for(i=0,med=0;i<CALIBRATION_LOOP;i++)
//			med = (*AdcReadTable[chNum])(chNum) + med;
//
//		reading[chNum] = med/CALIBRATION_LOOP;
//		if (reading[chNum] > upperThreshold)        /* above (average + 6% of average) -> press condition */
//		{
//			if(++x >= 2)
//				return __TRUE;
//		}else
//			x=0;
//	}
//	return __FALSE;
//}

//#define SENS       		 	4  //7   
//#define UPPER_THR 			40 //50	  /*(+) Diminui sensibilidade (-) Aumenta sensibilidade */
//#define LOWER_THR 			30 //40

//#define SENS       		 	20  //7   
//#define UPPER_THR 			15 //50	  /*(+) Diminui sensibilidade (-) Aumenta sensibilidade */

//#define UPPER_THR 			10 //50	
//
//#define LOWER_THR 			UPPER_THR/2

//const char upper[NUM_CHANNELS] = {8,15,16,10,10,10};

//const char upper[NUM_CHANNELS] = {3,2,4,2,2,2};
//
//const char SENS[NUM_CHANNELS] = {10,10,10,5,5,5};





//const char upper[NUM_CHANNELS] = {3,2,4,2,2,2};

//const char SENS[NUM_CHANNELS] = {5,5,5,5,5,5};

//const char upper[NUM_CHANNELS] = {20,20,20,20,20,20};	//ok 4
//
//const char SENS[NUM_CHANNELS] = {20,20,20,20,20,20}; //ok 10



//
//#define SENS			30 
//
//#define UPPER_THR 		10
//
//#define LOWER_THR 		UPPER_THR/2
//
///*
//	AD0(L2): Variação máx de 5
//	AD1(L4): Variação máx de 4
//	AD2(L1): Variação máx de 6
//	AD3(L3): Variação máx de 5
//	AD4(C2): Variação máx de 5
//	AD5(C1): Variação máx de 4
//*/
//
//short read_ad(char chNum)
//{
//	static U8 calibration = 0;
//
//	//static U16 last_reading[NUM_CHANNELS];
//	U8  loop,i;//,j;
//	U32 med=0;
//	U16 upperThreshold = average[chNum] + UPPER_THR; 
//	U16 lowerThreshold = average[chNum] + LOWER_THR;
//
//	//U16 upperThreshold = average[chNum] + upper[chNum]; 
//	
//	if(!(calibration & (1<<chNum)))
//	{
//		loop = CALIBRATION_LOOP;
//		//memset(last_reading,0xffff,sizeof(last_reading));
//	}else
//		loop = 100;
//	
//	for(i=0,med=0;i<loop;i++)						/*Loop para pegar a media das leituras*/
//		med = (*AdcReadTable[chNum])(chNum) + med;
//	reading[chNum] = med/loop;
//
////
////	if((calibration & (1<<chNum)))
////	{
////		if(reading[chNum] >= last_reading[chNum] + 10) //15
////		{
////			reading[chNum] = reading[chNum] - 9;	   //14
////		}else
////			last_reading[chNum] = reading[chNum] + 1;
////	}	
//
//
//	if(reading[chNum] > upperThreshold)        /* above (average + UPPER_THR) -> press condition */
//	{
//		if(++debounce[chNum] >= /*SENS[chNum]*/ SENS || !(calibration & (1<<chNum)))
//		{
//			_p[chNum] = 1;
//			if(debounce[chNum] >= SENS /*SENS[chNum]*/ + 100)
//			{
//				average[chNum] = reading[chNum] + 70;
//				debounce[chNum] = 0;
//				avgindex[chNum] = 0;
//				//memset(histCh[chNum],0,sizeof(histCh[chNum]));
//				return __FALSE;
//			}
////
//			if(!(calibration & (1<<chNum)))
//			{
//				calibration |= (1<<chNum);
//				average[chNum] = reading[chNum] + 70;	/*First Average*/
//				debounce[chNum] = 0;
//				avgindex[chNum] = 0;
//				//memset(histCh[chNum],0,sizeof(histCh[chNum]));	
//				return __FALSE;
//			}else
//				return __TRUE;
//		}
//	}else										/* not detected condition */
//	if(reading[chNum] < lowerThreshold)
//	{
//		if(debounce[chNum] >= 5) 
//			debounce[chNum]-= 5;
//								
////		if(debounce[chNum] >= 2) //3
////			debounce[chNum] -= 2;//3
////		else
////		{
////			_p[chNum] = 0;
////			debounce[chNum] = 0;
////		}
//			
//		if(debounce[chNum] <= 5)
//		{
//			_p[chNum] = 0;
//			if(avgindex[chNum] >= 20)
//			{
//				for(i=0,med=0;i<20;i++)
//					med = histCh[chNum][i] + med;
//			
//				average[chNum] = (med/20);
//				memset(histCh[chNum],0,sizeof(histCh[chNum]));
//				avgindex[chNum] = 0;
//			}else
//			{
//				histCh[chNum][avgindex[chNum]] = reading[chNum];
//				avgindex[chNum]++;
//			}
//		}
//	}
//		
//			
//	return __FALSE;
//}




//
//const char upper[NUM_CHANNELS] = {3,2,4,2,2,2};
//
//const char SENS[NUM_CHANNELS] = {5,5,5,5,5,5};
//
///*
//	AD0(L2): Variação máx de 5
//	AD1(L4): Variação máx de 4
//	AD2(L1): Variação máx de 6
//	AD3(L3): Variação máx de 5
//	AD4(C2): Variação máx de 5
//	AD5(C1): Variação máx de 4
//*/
//
//short read_ad(char chNum)
//{
//	static U8 calibration = 0;
////	static U8 last_debounce[NUM_CHANNELS];
//	static U16 last_reading[NUM_CHANNELS];
//	U8  loop,i;//,j;
//	U32 med=0;
//	//U16 upperThreshold = average[chNum] + UPPER_THR; 
////	U16 lowerThreshold = average[chNum] + LOWER_THR;
//
//	U16 upperThreshold = average[chNum] + upper[chNum]; 
//
//	
//		if(!(calibration & (1<<chNum)))
//		{
//			loop = CALIBRATION_LOOP;
//			memset(last_reading,0xffff,sizeof(last_reading));
//		}else
//			loop = 20;
//	
//		for(i=0,med=0;i<loop;i++)						/*Loop para pegar a media das leituras*/
//			med = (*AdcReadTable[chNum])(chNum) + med;
//		reading[chNum] = med/loop;
//
//		if((calibration & (1<<chNum)))
//		{
//			if(reading[chNum] >= last_reading[chNum] + 15)
//			{
//				reading[chNum] = reading[chNum] - 14;
//			}else
//				last_reading[chNum] = reading[chNum] + 1;
//		}	
//
//
//		if(reading[chNum] > upperThreshold)        /* above (average + UPPER_THR) -> press condition */
//		{
//			if(++debounce[chNum] >= SENS[chNum] || !(calibration & (1<<chNum)))
//			{
////				avgindex[chNum] = 0;
////				memset(histCh[chNum],0,sizeof(histCh[chNum]));
//
//				_p[chNum] = 1;
//				if(debounce[chNum] >= SENS[chNum] + 200)
//				{
//					average[chNum] = reading[chNum] + 200;
//					debounce[chNum] = 0;
//					avgindex[chNum] = 0;
//					memset(histCh[chNum],0,sizeof(histCh[chNum]));
//					return __FALSE;
//				}
////
//				if(!(calibration & (1<<chNum)))
//				{
//					calibration |= (1<<chNum);
//					average[chNum] = reading[chNum] + 200;	/*First Average*/
//					debounce[chNum] = 0;
//					avgindex[chNum] = 0;
//					memset(histCh[chNum],0,sizeof(histCh[chNum]));	
//					return __FALSE;
//				}else
//					return __TRUE;
//			}
//
//		}else										/* not detected condition */
//		//if(reading[chNum] < lowerThreshold)
//		{
//				
//			if(debounce[chNum] >= 3)
//				debounce[chNum] -= 3;
//			else
//			{
//				_p[chNum] = 0;
//				debounce[chNum] = 0;
//			}
//			
//		
//			//if(debounce[chNum] <= 5)
//			//{
//				if(avgindex[chNum] >= 20)
//				{
//					for(i=0,med=0;i<20;i++)
//						med = histCh[chNum][i] + med;
//				
//					average[chNum] = (med/20);
//
//					memset(histCh[chNum],0,sizeof(histCh[chNum]));
//					avgindex[chNum] = 0;
//
//				}else
//				{
//					histCh[chNum][avgindex[chNum]] = reading[chNum];
//					avgindex[chNum]++;
//				}
//		}
//		
//			
//	return __FALSE;
//}

/*----------------------------------------------------------------------------
  calibration loop function 
 *----------------------------------------------------------------------------*/
//void calibrateAllChannels(void)
//{
//    char i;
//
//	printf("---------------\r\r");
//	fflush(stdout);
//    for(i=0; i<NUM_CHANNELS; i++) 
//	{
//    	_calibrateChannel(i);
//		printf("[Average AD(%u): %u]\r",i,average[i]);
//		fflush(stdout);
//	}
//	printf("---------------\r\r");
//	fflush(stdout);	
//}


/*****************************************************************************
** Function name:               CT_Varredura
**
** Descriptions:                Varredura dos Touchs
**
** parameters:                  void
** Returned value:              void
**
*****************************************************************************/
void CT_Varredura (void)
{
	/*
		Posição das teclas c/ respectivos pares dos conversores AD
		 2,5		 2,4		

		 0,5		 0,4		 

		 3,5		 3,4		 

		 1,5		 1,4		 

	*/

	char seq[16] = {2,5, 1,4, 0,5, 3,4,
				    3,5, 0,4, 1,5, 2,4};

//	char seq[16] = {2,5, 0,5, 3,5, 1,5,
//				    2,4, 0,4, 3,4, 1,4};

	//static float cal_temp[6] = {2,2,2,2,2,2};
	static int i=0;
	static int delay=0;
	static U32 cont_wait_touch = 0;
	U32 j;

	if(flag_wait_touch)
	{
		if(!tick_10ms)	
			return;
		if(++cont_wait_touch > 200)
		{
		 	flag_wait_touch = __FALSE;
			cont_wait_touch = 0;
			i=0;
			for(j=0; j<CT_QTD; j++)
			{
				CT[j].valor_normal = 0xFFF;
				CT[j].debounce = 0;
				CT[j].qtd_acima_val_normal = 0;
				CT[j].qtd_abaixo_val_normal = 0;
				CT[j].qtd_acima_media = 0;
				CT[j].qtd_abaixo_media = 0;
			}
			CT_Cheky_Press(8, &CT[0]);	/* Limpa tecla */
			delay = 20;

//			printf("Volta a ler\r");
//			fflush(stdout);
		}
		return;
	}

 	if(!delay) 
	{
		CT_channel_num =  seq[i];

		CT_Cheky_Press(CT_channel_num, &CT[CT_channel_num]);

		if(i%2) 
		{
 			delay = 20;
			CT_Cheky_Press(8, &CT[0]);	/* limpa tecla */
		}
 		else
 			delay = 1;

		++i;
		if(i>=16)
			i=0;
	}
	--delay;
}


/*----------------------------------------------------------------------------
  adc 0 reading function 
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh0(void)
{
    _setCh0AdcMode();
    _startAdc();
    _waitForCh(0);
    _stopAdc();
    _setCh0GpioMode();
	_setCh0GpioPullup();
    return(_getAdcChVal(0));
}
/*----------------------------------------------------------------------------
  adc 1 reading function 
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh1(void)
{
    _setCh1AdcMode();
    _startAdc();
    _waitForCh(1);
    _stopAdc();
    _setCh1GpioMode();
    _setCh1GpioPullup();
    return(_getAdcChVal(1));
}
/*----------------------------------------------------------------------------
  adc 2 reading function 
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh2(void)
{
	_setCh2AdcMode();
    _startAdc();
    _waitForCh(2);
    _stopAdc();
    _setCh2GpioMode();
    _setCh2GpioPullup();
    return(_getAdcChVal(2));
}
/*----------------------------------------------------------------------------
 adc 3 reading function  
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh3(void)
{
    _setCh3AdcMode();
    _startAdc();
    _waitForCh(3);
    _stopAdc();
    _setCh3GpioMode();
    _setCh3GpioPullup();
    return(_getAdcChVal(3));
}
/*----------------------------------------------------------------------------
 adc 4 reading function  
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh4(void)
{
    _setCh4AdcMode();
    _startAdc();
    _waitForCh(4);
    _stopAdc();
    _setCh4GpioMode();
    _setCh4GpioPullup();
    return(_getAdcChVal(4));
}
/*----------------------------------------------------------------------------
 adc 5 reading function  
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh5(void)
{
    _setCh5AdcMode();
    _startAdc();
    _waitForCh(5);
    _stopAdc();
    _setCh5GpioMode();
    _setCh5GpioPullup();
    return(_getAdcChVal(5));
}
/*----------------------------------------------------------------------------
 adc 6 reading function  
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh6(void)
{
    _setCh6AdcMode();
    _startAdc();
    _waitForCh(6);
    _stopAdc();
    _setCh6GpioMode();
    _setCh6GpioPullup();
    return(_getAdcChVal(6));
}
/*----------------------------------------------------------------------------
  adc 7 reading function 
 *----------------------------------------------------------------------------*/
uint16_t _ADC_ReadCh7(void)
{
    _setCh7AdcMode();
    _startAdc();
    _waitForCh(7);
    _stopAdc();
    _setCh7GpioMode();
    _setCh7GpioPullup();
    return(_getAdcChVal(7));
}
/*----------------------------------------------------------------------------
  configure all used adc /GPIO pins to the default value 
 *----------------------------------------------------------------------------*/
void cfgGpioTouch(void) 
{	
    /* configure GPIO mode output */
#if USE_AD0					/*Inclui na compilação o uso do AD0?*/
	_setCh0GpioDirOut();
    _setCh0GpioPullup();
    _setCh0GpioCharge();
    _setCh0GpioMode();
#endif
#if USE_AD1    				/*Inclui na compilação o uso do AD1?*/
    _setCh1GpioDirOut();
    _setCh1GpioPullup();
   	_setCh1GpioCharge();
    _setCh1GpioMode();
#endif
#if USE_AD2 			   	/*Inclui na compilação o uso do AD2?*/
    _setCh2GpioDirOut();
    _setCh2GpioPullup();
    _setCh2GpioCharge();
    _setCh2GpioMode();
#endif
#if USE_AD3 			   	/*Inclui na compilação o uso do AD3?*/
    _setCh3GpioDirOut();
    _setCh3GpioPullup();
    _setCh3GpioCharge();
    _setCh3GpioMode();
#endif
#if USE_AD4   			  	/*Inclui na compilação o uso do AD4?*/
    _setCh4GpioDirOut();
    _setCh4GpioPullup();
    _setCh4GpioCharge();
    _setCh4GpioMode();
#endif
#if USE_AD5  			 	/*Inclui na compilação o uso do AD5?*/
    _setCh5GpioDirOut();
    _setCh5GpioPullup();
   	_setCh5GpioCharge();
    _setCh5GpioMode();
#endif
#if USE_AD6   			   /*Inclui na compilação o uso do AD6?*/
	_setCh6GpioDirOut();
   	_setCh6GpioPullup();
   	_setCh6GpioCharge();
   	_setCh6GpioMode();
#endif
#if USE_AD7  			   /*Inclui na compilação o uso do AD7?*/
	_setCh7GpioDirOut();
    _setCh7GpioPullup();
    _setCh7GpioCharge();
    _setCh7GpioMode();
#endif

}
/*----------------------------------------------------------------------------
  initialize ADC 
 *----------------------------------------------------------------------------*/
void init_adc (void) 
{
	int i,j; 

	LPC_SC->PCONP |= (1<<12);     /*Enable power to ADC block*/

	/* peripheral clock has been already enabled in SystemIn */
    _powerOnAdc();					

	/* configure the ADC clock as close to 13 MHz as possible */
    _setAdcDivider(SystemFrequency);	 

	/* disable adc interrupts */
	_disableAllAdcInterrupts();
	
	/* configure all used adc /GPIO pins to the default value */
	cfgGpioTouch(); 

	memset(DEV,0,sizeof(DEV));



	/*Reset variables*/
//	memset(average,0,sizeof(average));
//	memset(histCh,0,sizeof(histCh));
//	memset(avgindex,0,sizeof(avgindex));
//	memset(debounce,0,sizeof(debounce));

	/* calibration loop on all active channels to setup mean threshold value */
	//calibrateAllChannels();

}
/*********************************************************************************
**                            End Of File
*********************************************************************************/
