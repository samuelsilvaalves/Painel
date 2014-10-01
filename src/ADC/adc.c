#include "includes.h"

/* local data tables and variables */
static uint16_t histCh2[NUM_CHANNELS][16];  /* this keeps the last 16 readings for the channels */
static uint8_t  avgindex[NUM_CHANNELS];     /* this is a pointer to the history channel */
static uint8_t  debounce[NUM_CHANNELS];     /* this is a counter for debouce functions */

/* local function prototypes */
static uint16_t _ADC_ReadCh0(void);
static uint16_t _ADC_ReadCh1(void);
static uint16_t _ADC_ReadCh2(void);
static uint16_t _ADC_ReadCh3(void);
static uint16_t _ADC_ReadCh4(void);
static uint16_t _ADC_ReadCh5(void);
static uint16_t _ADC_ReadCh6(void);
static uint16_t _ADC_ReadCh7(void);
static void _processAdcReading(ChannelIdType chNum);
static void _calibrateChannel(ChannelIdType chNum);


/* local data tables */
uint16_t average[NUM_CHANNELS];
uint16_t reading[NUM_CHANNELS];
bool   kbdPress[NUM_KPAD];
uint32_t kPressCntr = 0;    /* just a counter on the number of key presses */

/* definition of function type used to perform the adc reading */
typedef uint16_t (*_adcCallbackFctType)(ChannelIdType chNum);

/* table of callback functions for adc reading */
/* could be different for each channel */
const _adcCallbackFctType AdcReadTable[NUM_CHANNELS]  = 
{
    (_adcCallbackFctType) _ADC_ReadCh0,
    (_adcCallbackFctType) _ADC_ReadCh1,
    (_adcCallbackFctType) _ADC_ReadCh2,
    (_adcCallbackFctType) _ADC_ReadCh3,
    (_adcCallbackFctType) _ADC_ReadCh4,
    (_adcCallbackFctType) _ADC_ReadCh5,
    (_adcCallbackFctType) _ADC_ReadCh6,
    (_adcCallbackFctType) _ADC_ReadCh7        
};







/**********************************************************/
/* Public Functions */
/**********************************************************/


/* common macros for the ADC block */
#define delay(i,time) {\
	for(i=0;i<time;i++);\
}

#define _powerOnAdc() ( LPC_ADC->ADCR |= (1 << 21) )
#define _powerOffAdc() ( LPC_ADC->ADCR |= (1 << 21) )

#define _disableAllAdcInterrupts() ( LPC_ADC->ADINTEN &= 0x0 )
#define _powerOffAdc() ( LPC_ADC->ADCR |= (1 << 21) )

/* start conversion by software = 001 in bits 26:24 */
#define _startAdc() ( LPC_ADC->ADCR |= (1 << 24) )

/* clear conversion = 000 in bits 26:24 */
#define _stopAdc() ( LPC_ADC->ADCR &= 0xF8FFFFFF )

/* program adc divider value */
#define ADC_MAX_FREQ    (13000000) /* 13 MHz is upper limit for ADC speed on LPC1769 */

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

/* retrieve the ADC reading */        
#define _getAdcChVal(n)    ( (LPC_ADC->ADDR##n## >> 4) & 0x3FF )

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

#define _setCh0GpioCharge()  ( LPC_GPIO0->FIOSET |= (1<<23))
#define _setCh0GpioDirOut()  ( LPC_GPIO0->FIODIR |= (1<<23))

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

#define _setCh1GpioCharge()  ( LPC_GPIO0->FIOSET |= (1<<24) )
#define _setCh1GpioDirOut()  ( LPC_GPIO0->FIODIR |= (1<<24) )

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

#define _setCh2GpioDirOut()  ( LPC_GPIO0->FIODIR |= (1<<25) )
#define _setCh2GpioCharge()  ( LPC_GPIO0->FIOSET |= (1<<25) )


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

#define _setCh3GpioDirOut()  ( LPC_GPIO0->FIODIR |= (1<<26) )
#define _setCh3GpioCharge()  ( LPC_GPIO0->FIOSET |= (1<<26) )


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
   LPC_PINCON->PINSEL1 |= ADC_1_30;\
   LPC_PINCON->PINMODE1 |= FLOAT_1_30;\
}

#define _setCh4GpioDirOut()  ( LPC_GPIO1->FIODIR |= (1<<30) )
#define _setCh4GpioCharge()  ( LPC_GPIO1->FIOSET |= (1<<30) )

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
   LPC_PINCON->PINSEL1 |= ADC_1_31;\
   LPC_PINCON->PINMODE1 |= FLOAT_1_31;\
}

#define _setCh5GpioDirOut()  ( LPC_GPIO1->FIODIR |= (1u<<31) )
#define _setCh5GpioCharge()  ( LPC_GPIO1->FIOSET |= (1u<<31) )

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
#define _setCh6GpioDirOut()  ( LPC_GPIO0->FIODIR |= (1<<3) )
#define _setCh6GpioCharge()  ( LPC_GPIO0->FIOSET |= (1<<3) )


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

#define _setCh7GpioDirOut()  ( LPC_GPIO0->FIODIR |= (1<<2) )
#define _setCh7GpioCharge()  ( LPC_GPIO0->FIOSET |= (1<<2) )


/* this function updated the average channel reading at runtime */
void updateAverage(ChannelIdType chNum)
{
	int8_t index = avgindex[chNum];
	uint32_t sum = 0;
	uint32_t i;

	histCh2[chNum][index] = reading[chNum]; // put the last reading into history buffer

    /* compute the mean over the last 16 values */
	for(i=0;i<16;i++) 
    {
        sum += histCh2[chNum][index]; // sum all the values
	    if (--index < 0) index = 15;  // roll back pointer
	}

    /* update the mean value */
    average[chNum] = sum >> 4;		 // new average is sum/16

    /* update the new index for the mean */
    avgindex[chNum]++;
    if(avgindex[chNum] == 16) avgindex[chNum] = 0; 
	
}


/* process of adc reading */
/* readings are ordered per channel */
/* kpresses are ordered per kbd values */
#define UPPER_THR 8
#define LOWER_THR 3
static void _processAdcReading(ChannelIdType chNum)
{
	uint32_t currentAvg = average[chNum];
	uint32_t upperThreshold = currentAvg + (currentAvg*UPPER_THR)/100;
	uint32_t lowerThreshold = currentAvg + (currentAvg*LOWER_THR)/100;

    if (reading[chNum] > upperThreshold)        // above (average + 6% of average) -> press condition
    {
        if (debounce[chNum] > 8)                         // debounce, 8 successive triggers for press
        {
            kbdPress[Ch2KpadMap[chNum]] = 1;             // reached max, indicate pressed
			kPressCntr++;
        	debounce[chNum] = 0; // now it is pressed
		}
        else
            debounce[chNum] ++;                           // still going toward max	
    }
    else if (reading[chNum] < lowerThreshold)   // below (average + 3% of average) -> not detected condition
    {
            debounce[chNum] --;                           
    }

}

/* calibration channel function */    
#define CALIBRATION_LOOP (200)
static void _calibrateChannel(ChannelIdType chNum) 
{
    int calibCntr;

    for (calibCntr=0; calibCntr < CALIBRATION_LOOP; calibCntr++)                         
    {
        reading[chNum] = (*AdcReadTable[chNum])(chNum);
		updateAverage(chNum); 
    }
}


/* adc reading functions */
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

volatile uint32_t del = 0;
int i;
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

/**********************************************************/
/* Public Functions */
/**********************************************************/


/* calibration loop function */
void calibrateAllChannels(void)
{
    KeypadIdType i;
    
    for(i=KBD1; i< NUM_KPAD; i++) 
    if (UNUSED_CHANNEL != Kpad2ChMap[i]) _calibrateChannel(Kpad2ChMap[i]);
}



void initAdc(uint32_t cpuFreq)
{      
    /* peripheral clock has been already enabled in SystemIn */
    _powerOnAdc();

    /* configure the ADC clock as close to 13 MHz as possible */
    _setAdcDivider(cpuFreq);           

    /* disable adc interrupts */
	_disableAllAdcInterrupts();

    /* configure all used adc /GPIO pins to the default value */
    /* configure GPIO mode output */
    if (UNUSED_KPAD != Ch2KpadMap[CH0])
    { 
        _setCh0GpioDirOut();
    	_setCh0GpioPullup();
    	_setCh0GpioCharge();
        _setCh0GpioMode();
    }

    if (UNUSED_KPAD != Ch2KpadMap[CH1])
    {     
        _setCh1GpioDirOut();
    	_setCh1GpioPullup();
    	_setCh1GpioCharge();
        _setCh1GpioMode();
    }

    if (UNUSED_KPAD != Ch2KpadMap[CH2])
    {     
        _setCh2GpioDirOut();
    	_setCh2GpioPullup();
    	_setCh2GpioCharge();
    	_setCh2GpioMode();
    }

    if (UNUSED_KPAD != Ch2KpadMap[CH3])
    {     
        _setCh3GpioDirOut();
    	_setCh3GpioPullup();
    	_setCh3GpioCharge();
        _setCh3GpioMode();
    }

    if (UNUSED_KPAD != Ch2KpadMap[CH4])
    {     
        _setCh4GpioDirOut();
    	_setCh4GpioPullup();
    	_setCh4GpioCharge();
        _setCh4GpioMode();
    }

    if (UNUSED_KPAD != Ch2KpadMap[CH5])
    {     
        _setCh5GpioDirOut();
    	_setCh5GpioPullup();
    	_setCh5GpioCharge();
        _setCh5GpioMode();
    }

    if (UNUSED_KPAD != Ch2KpadMap[CH6])
    {     
        _setCh6GpioDirOut();
    	_setCh6GpioPullup();
    	_setCh6GpioCharge();
        _setCh6GpioMode();
    }

    if (UNUSED_KPAD != Ch2KpadMap[CH7])
    {     
        _setCh7GpioDirOut();
    	_setCh7GpioPullup();
    	_setCh7GpioCharge();
        _setCh7GpioMode();
    }
}

/* this function iterates through the result values on the current reading */
/* if keypress is detected, callback function is executed */
void processKeystrokes(void)
{
    if(USE_KBD1)
    {
        _processAdcReading(Kpad2ChMap[KBD1]);
        if(kbdPress[KBD1]) (*KeypadAction[KBD1])(KBD1);
    };

    if(USE_KBD2)
    {
        _processAdcReading(Kpad2ChMap[KBD2]);
        if(kbdPress[KBD2]) (*KeypadAction[KBD2])(KBD2);
    };

    if(USE_KBD3)
    {
        _processAdcReading(Kpad2ChMap[KBD3]);
        if(kbdPress[KBD3]) (*KeypadAction[KBD3])(KBD3);
    };

    if(USE_KBD4)
    {
        _processAdcReading(Kpad2ChMap[KBD4]);
        if(kbdPress[KBD4]) (*KeypadAction[KBD4])(KBD4);
    };

    if(USE_KBD5)
    {
        _processAdcReading(Kpad2ChMap[KBD5]);
        if(kbdPress[KBD5]) (*KeypadAction[KBD5])(KBD5);
    };

    if(USE_KBD6)
    {
        _processAdcReading(Kpad2ChMap[KBD6]);
        if(kbdPress[KBD6]) (*KeypadAction[KBD6])(KBD6);
    };

    if(USE_KBD7)
    {
        _processAdcReading(Kpad2ChMap[KBD7]);
        if(kbdPress[KBD7]) (*KeypadAction[KBD7])(KBD7);
    };

    if(USE_KBD8)
    {
        _processAdcReading(Kpad2ChMap[KBD8]);
        if(kbdPress[KBD8]) (*KeypadAction[KBD8])(KBD8);
    };
}

/* this function iterates through the channels and reads the adc values */
/* result is stored within the reading array */
void processChannels(void)
{
    ChannelIdType currentChannel;

    if(USE_KBD1)
    {
        currentChannel = Kpad2ChMap[KBD1];
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };

    if(USE_KBD2)
    {
        currentChannel = Kpad2ChMap[KBD2];
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };

    if(USE_KBD3)
    {
        currentChannel = Kpad2ChMap[KBD3];
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };

    if(USE_KBD4)
    {
        currentChannel = Kpad2ChMap[KBD4];
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };


    if(USE_KBD5)
    {
        currentChannel = Kpad2ChMap[KBD5];
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };

    if(USE_KBD6)
    {
        currentChannel = Kpad2ChMap[KBD6];
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };

    if(USE_KBD7)
    {
        currentChannel = Kpad2ChMap[KBD7];        
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };

    if(USE_KBD8)
    {
        currentChannel = Kpad2ChMap[KBD8];        
        reading[currentChannel] = (*AdcReadTable[currentChannel])(currentChannel);
    };
}
  
/* end of file */
