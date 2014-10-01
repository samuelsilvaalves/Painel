
#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
#include "hardware_profile.h"
#include "control_ir.h"
#include "pwm_ir.h"
#include "ir.h"

#if USE_IR	/*Inclui na compilação a função IR da placa?*/

/*****************************************************************************
 
*****************************************************************************/
void control_ir_task(void)
{
	//if(READ_IROUT_0() || READ_IROUT_1() || READ_IROUT_2())	/*Desliga todos os PWM's*/
		PWM_Stop();		
}

#endif
					 





