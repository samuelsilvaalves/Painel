
#ifndef __REGISTER_H
#define __REGISTER_H

#define	QTD_OUTS					24 

#define REGISTER_START_SEND_LSB		0	
#define REGISTER_START_SEND_MSB		1

#if	(REGISTER_START_SEND_LSB && REGISTER_START_SEND_MSB) || (!REGISTER_START_SEND_LSB && !REGISTER_START_SEND_MSB)
	#error "REGISTER_START_SEND_LSB ou REGISTER_START_SEND_MSB incorreto"	
#endif			

extern unsigned int out_leds;		 			 				

void init_register(void);
void atualiza_saidas(void);
void led_task(void);


#endif /* end __REGISTER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
