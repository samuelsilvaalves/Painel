#ifndef __CONTROL_H
#define __CONTROL_H   

#include "hardware_profile.h"

#define FILE_INFRARED 		"INFRARED\\IR_\0"			/*NÃO ADICIONAR A EXTENSÃO .TXT AQUI*/
#define FILE_INDEX_INFRARED	0 	

#define FILE_CMDIR 			"CMDIR\\IR_\0"			/*NÃO ADICIONAR A EXTENSÃO .TXT AQUI*/
#define FILE_INDEX_CMDIR	1
#define FILE_INDEX_RAIZ		2
#define NO_FILE				0xFF
 
/*pasta onde estão contidos os IR's relacionados a TV*/
#define FILE_IR_DIR_TV		"INFRARED\\TV\\IR_"

/*(TV)->ID0:Source...ID1:CH-...ID2:CH+...ID3:ON...ID4:OFF...ID5:Vol-...ID6:Vol+*/

#define ADDR_TV_SCR			"0\0"
#define ADDR_TV_CH_DOWN		"1\0"
#define ADDR_TV_CH_UP		"2\0"
#define ADDR_TV_ON			"3\0"
#define ADDR_TV_OFF			"4\0"
#define ADDR_TV_VOL_DOWN	"5\0"
#define ADDR_TV_VOL_UP		"6\0"

/*pasta onde estão contidos os IR's relacionados ao HOME*/
#define FILE_IR_DIR_HOME	"INFRARED\\HOME\\IR_"

/*(HOME)->ID7:Source...ID8:VOL-...ID9:VOL+...ID10:ON...ID11:OFF...ID12:PLAY...ID13:PAUSE...ID14:BACK...ID15:NEXT*/
			/*ID16: Cursor Left...ID17: Cursor Righ...ID18: Cursor Down*/

#define ADDR_HOME_SCR		"7\0"
#define ADDR_HOME_VOL_DOWN	"8\0"
#define ADDR_HOME_VOL_UP	"9\0"
#define ADDR_HOME_ON		"10\0"
#define ADDR_HOME_OFF		"11\0"
#define ADDR_HOME_PLAY		"12\0"
#define ADDR_HOME_PAUSE		"13\0"
#define ADDR_HOME_BACK		"14\0"
#define ADDR_HOME_NEXT		"15\0"
#define ADDR_HOME_LEFT		"16\0"
#define ADDR_HOME_RIGH		"17\0"
#define ADDR_HOME_DOWN		"18\0"

/*Pastas onde estão contidos os IR's relacionados ao AR*/	
#define FILE_IR_DIR_AR_SW_ON	"INFRARED\\AR\\SWON\\IR_"
#define FILE_IR_DIR_AR_SW_OFF	"INFRARED\\AR\\SWOFF\\IR_"
#define FILE_IR_DIR_AR_SW_OUT	"INFRARED\\AR\\SWOUT\\IR_"

/*(AR)->ID19:16°...ID20:17°............ID33:30°...ID34:ON...ID35:OFF..ID36:SWING ON..ID37:SWING OFF*/

#define ADDR_AR_PWR_ON		"34\0"
#define ADDR_AR_PWR_OFF		"35\0"
#define ADDR_AR_SWING_ON	"36\0"
#define ADDR_AR_SWING_OFF	"37\0"

enum
{	
	IR_ID0 = 0u, IR_ID1, IR_ID2, IR_ID3, IR_ID4, IR_ID5,
	IR_ID6, IR_ID7,	IR_ID8,	IR_ID9,	IR_ID10, IR_ID11, IR_ID12,
	IR_ID13, IR_ID14, IR_ID15, IR_ID16,	IR_ID17, IR_ID18,
	IR_ID19, IR_ID20, IR_ID21
};
								
#define TIMEOUT_END_IR 		120		/*timeout em ms*/

#define START_IR_DEF		0x0000
#define STOP_IR_DEF			0xFFFF

/***********************************************************************************************/
#define	MAX_QTD_PULSOS		400		/*Máxima quantidade de pulsos que cada IR cadastrado pode ter*/
#define	MAX_QTD_IR			2480 	/*Até o setor 30..MAX:2535*/	
#define TIMER_IR 			1		/*Timer utilizado para contagem dos pulsos do IR a ser cadastrado/reproduzido*/

#ifndef USE_IR
#error "This property must be defined!"
#endif


#define	CARRIER_FREQ_30KHZ		830		/* T:33.2us...F:30.12KHZ */

#define	CARRIER_FREQ_31KHZ		794		/* T:31.6us...F:31.65KHZ */

#define	CARRIER_FREQ_32KHZ		774	   	/* T:31.0us...F:32.26KHZ */

#define	CARRIER_FREQ_33KHZ		754		/* T:30.2us...F:33.11KHZ */ 

#define	CARRIER_FREQ_34KHZ		730		/* T:29.2us...F:34.25KHZ */

#define	CARRIER_FREQ_35KHZ		707		/* T:28.2us...F:35.46KHZ */

#define	CARRIER_FREQ_36KHZ		691		/* T:27.6us...F:36.23KHZ */ 
 
#define	CARRIER_FREQ_37KHZ		682		/* T:27.2us...F:36.76KHZ */ 

#define	CARRIER_FREQ_38KHZ		657	   	/* T:26.3us...F:38.02KHZ */ 

#define	CARRIER_FREQ_39KHZ		641		/*         ...F:39.06KHZ*/

#define	CARRIER_FREQ_40KHZ		620//625		/* T:25.0us...F:40.00KHZ.....620=40.32khz */

#define	CARRIER_FREQ_41KHZ		605		/* T:2.0us...F:41.32KHZ */

#define	CARRIER_FREQ_56KHZ		446	  

/*Funções locais*/
void control_ir_task(void);

#endif


