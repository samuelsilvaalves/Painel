/****************************************************************************
 *   $Id:: extint.h 5670 2010-11-19 01:33:16Z usb00423                      $
 *   Project: NXP LPC17xx EXTINT example
 *
 *   Description:
 *     This file contains EINT code header definition.
 *
 ****************************************************************************
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
****************************************************************************/
#ifndef __EXTINT_H 
#define __EXTINT_H
#include <RTL.H>
#include "generic_type_defs.h"

#define USE_EXT0	0
#define USE_EXT1	0
#define USE_EXT2	0

#define USE_EXT_ANY_GPIO2	1
#define	PIN_EXT_ANY_GPIO2	3

#define USE_EXT_ANY_GPIO0	0
#define	PIN_EXT_ANY_GPIO0	7

/*Atenção: Verificar no HardwareProfile o pino correto de leitura de IR*/

#define EINT0		0x00000001
#define EINT1		0x00000002
#define EINT2		0x00000004
#define EINT3		0x00000008

#define EINT0_EDGE	0x00000001
#define EINT1_EDGE	0x00000002
#define EINT2_EDGE	0x00000004
#define EINT3_EDGE	0x00000008

#define EINT0_RISING	0x00000001
#define EINT1_RISING	0x00000002
#define EINT2_RISING	0x00000004
#define EINT3_RISING	0x00000008

#if USE_EXT_ANY_GPIO0 && USE_EXT_ANY_GPIO2
	#error "Apenas uma dessas propriedades pode ser verdadeira, pois compartilham a mesma EINT3"
#endif 

//extern WORD_VAL word_val; 

extern int contEnableExtIr;


void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void ext_task(void);

uint32_t Init_EINT (void);

#endif /* end __EXTINT_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/

