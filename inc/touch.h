
#ifndef __TOUCH_H
#define __TOUCH_H

#include <RTL.H>
#include "adc.h"



/******************************************************************************
---> Explicativo dos touch's do painel <

---------------------------------------------------------
[T16]	[T17]				[T00]	[T01]	[T02]	[T03]

[T18]	[T19]				[T04]	[T05]	[T06]	[T07]

[T20]	[T21]				[T08]	[T09]	[T10]	[T11]

[T22]	[T23]				[T12]	[T13]	[T14]	[T15]
---------------------------------------------------------

OBS: O endereço do touch é o mesmo endereço para o led do touch pressionado 
     EX: T00 (Touch 00), (Led) bit 0  de 'out_leds'
	 	 T10 (Touch 10), (Led) bit 10 de 'out_leds'
		 T23 (Touch 23), (Led) bit 23 de 'out_leds'


******************************************************************************/
#define DEBOUNCE_PRESS_KEY 		500
#define DEBOUNCE_RELEASE_KEY 	8000

/*Associa linhas e solunas aos canais ad's */
//#define LIN_1		CH2	/*AD2 (P0.25)*/  
//#define LIN_2		CH0	/*AD0 (P0.23)*/
//#define LIN_3		CH3	/*AD3 (P0.26)*/ 
//#define LIN_4		CH1	/*AD1 (P0.24)*/
//
//#define COL_1		CH5	/*AD5 (P1.31)*/
//#define COL_2		CH4	/*AD4 (P1.30)*/


#define TOUCH_NONE	0xFF

#define BLINK_LED_30ms	0
#define BLINK_LED_50ms	1

typedef union _IR_STATE
{
	U8 all;
	struct _IR_STATE_bits
	{
	  	U8 PwrPainel		:1;
		U8 PwrAr			:1;
		U8 PwrTv			:1;
		U8 PwrHome			:1;
		U8 PlayPause		:1;
		U8 ArSwing			:1;
		U8 :1;
	}bit;
} IR_STATE;


enum
{
	TOUCH_0 = 0u,	TOUCH_1, TOUCH_2, TOUCH_3,
	TOUCH_4,		TOUCH_5, TOUCH_6, TOUCH_7,
	TOUCH_8,		TOUCH_9, TOUCH_10, TOUCH_11,
	TOUCH_12,		TOUCH_13, TOUCH_14, TOUCH_15,
	TOUCH_16, 		TOUCH_17, TOUCH_18, TOUCH_19,
	TOUCH_20,		TOUCH_21, TOUCH_22, TOUCH_23
};

enum
{
	TOUCH_SCENE_0 = TOUCH_16,
	TOUCH_SCENE_1 = TOUCH_18,
	TOUCH_SCENE_2 = TOUCH_20,
	TOUCH_SCENE_3 = TOUCH_22,
	NUM_SCENE    = 4u	/*Quantidade de 'TOUCH_SCENE' */ 
};

enum
{
	BEEP_PULSO = 0u,
	BEEP_CFG,
	BEEP_CHAMADA,
	BEEP_ERROR,
};


enum
{
	num16 = 0u,	num17,	num18,	num19,	
	num20,		num21,	num22,	num23,	key_none		
};

/* teclas */
typedef union _KEY_STATE
{
	uint16_t all;
	struct
	{
		uint16_t pressed :1;

	} key;
}KEY_STATE;

extern KEY_STATE key_state;

extern IR_STATE ir_state; 

extern char temp_ar;

extern int touchEnaDis;
extern char strTouchEnaDis[20];
extern char aux_scene[30];
extern char current_scene[30];
extern char current_id_scene;
extern char scene[NUM_SCENE][30];
extern char touch_led_press;

extern int debounce_press;
extern int debounce_release;


void init_touch(void);
char read_touch(void);

void init_scene(char modo);
void show_all_scene(void);
char save_scene(char *_scene,char addr);
//char save_scene_atual(char *_scene);
char read_scene(char addr,char *file);
char get_touch(void);
void touch_task(void);
void exe_scene(char num_scene);
void key_task(void);
void beep(char modo);

#endif /* end __TOUCH_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
