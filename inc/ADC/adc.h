/*****************************************************************************
 * adc.h 
 *
 * Project: LPC17xx Capacitive Touch Sensing demo program
 *
 * Description:
 *   Header file for the ADC module 
 *
 *----------------------------------------------------------------------------
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
 *                  (C) Copyright 2011 NXP Semiconductors
 *****************************************************************************/
#ifndef __ADC_H__
#define __ADC_H__

/* type definition for the ADC channel type */
typedef enum {
        CH0 = 0,
        CH1,
        CH2,
        CH3,
        CH4,
        CH5,
        CH6,
        CH7,
        NUM_CHANNELS,
        UNUSED_CHANNEL
} ChannelIdType;

/* function prototypes */
extern void calibrateAllChannels(void);
extern void processChannels(void);
extern void processKeystrokes(void);
extern void initAdc(uint32_t cpuFreq);  

/* data structures */
extern uint16_t average[NUM_CHANNELS];
extern uint16_t reading[NUM_CHANNELS];
extern bool     kbdPress[NUM_KPAD];

/* just a simple progressive counter on the number of key presses */
extern uint32_t kPressCntr;    

#endif    /* __ADC_H__ */


