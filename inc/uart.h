/*----------------------------------------------------------------------------
 * Name:    Serial.h
 * Purpose: MCB1700 Low level serial definitions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __SERIAL_H
#define __SERIAL_H

#define RCV_CMD_UART_0				0x01
#define RCV_CMD_UART_2 				0x02
#define RCV_CMD_TCP_CLIENT			0x03
#define RCV_CMD_TCP_SERVER			0x04


//#define FILE_DIMMER_SCENE_SAVED		"DIMMER\\SCENE_SAVED.TXT\0"
#define FILE_DIMMER_SCENE	 		"DIMMER\\SCENE_\0"	

/*Identificação de erros*/
enum 
{
	ERROR_COMMAND = 0u,			//0
	ERROR_ADDR_UTILIZAD,		//1
	ERROR_FILE_NOT_FOUND,		//2
	ERROR_TIMEOUT, 				//3
	ERROR_RECEIVER_IR,		   	//4
	ERROR_OVERFLOW_PULSES_IR,	//5
	ERROR_OVERFLOW_FLASH,		//6
	ERROR_PARAMETER,		   	//7
	ERROR_ADDR_OVERFLOW,		//8
	ERROR_READ,					//9
	ERROR_IR_NOT_SEND,			//10
	ERROR_NOT_SAVED,			//11
	ERROR_NOT_EXIST_NAME,		//12
	ERROR_IR_NOT_EXIST,			//13
	ERROR_SD,					//14
	NO_ERROR,					//15
};

#define UART_LINK_LPC		2

enum 
{
	BACKSPACE = 0x08, 
    LF        = 0x0A, 
    CR        = 0x0D, 
    CNTLQ     = 0x11, 
    CNTLS     = 0x13, 
    ESC       = 0x1B, 
    DEL       = 0x7F
};


/* Command definitions structure. */
typedef struct scmd 
{
	char val[8];
  	void (*func)(char *par);
} SCMD;

extern int cntUART2;
extern int cntUART0;
extern char buf_rx[160];
extern char buf_tx[160];
extern char rcv_cmd;
extern char rcv;

/*Funçoes da uart*/
char *get_entry     (char *cp, char **pNext);
void init_uart      (void);
int  uart_getChar   (int uart);
int  uart_getChar_nb(int uart);
int  uart_putChar   (int uart, int c);
void uart_putString (int uart, char *s); 

void cmd_ar_swing(char *par); 
void cmd_enable_touch(char *par);
void cmd_disable_touch(char *par);
void cmd_set_real_time(char *par);
void cmd_detect_swing(char *par);
void cmd_type_dim(char *par);
void cmd_reset_board(char *par);
void cmd_rcv_touch(char *par);  
void cmd_scene(char *par); 
void cmd_run_scene(char *par);
void cmd_ena_dis_func(char *par); 
void cmd_msg_dimmer(char *par);
void cmd_rel(char *par); 
void cmd_task(void);

#endif






