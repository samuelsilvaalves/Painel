
#include <LPC17xx.H>					/* LPC17xx definitions */
#include <stdio.h>
#include <ctype.h>                    	/* character functions */
#include <string.h>                   	/* string and memory functions */
#include <stdlib.h> 
#include "hardware_profile.h"
#include "cmds_ir.h"
#include "control_ir.h"
#include "ir.h"
#include "uart.h"
#include "timer.h"
#include "touch.h"
#include "extint.h"
#include "tcpip.h"
#include "msd_sd_file.h"

#if USE_IR	/*Inclui na compilação a função IR da placa?*/

/*Variaveis usadas (apenas neste ponto c) para armazenar endereço/porta do IR*/
static unsigned short rcv_addr_ir;
static unsigned char  rcv_port_ir;

/*
** Os comandos a seguir são pertencentes a função IR.
** Quando a função não é utilizada os comandos não são compilados.
*/


char send_ir(unsigned short addr, int index_file);
//char send_ir(unsigned short addr, int index_file, short PosStart, short PosStop);

/*****************************************************************************

*****************************************************************************/
char get_addr_channel(char *str)
{
	char string[20];
	char str_addr_ir[20];
	char str_port_ir[20];
	char i,j;
	
	/*Limpa todas as variaveis que irão armazenar os dados*/	 		
	memset(string     ,0,sizeof(string));
	memset(str_addr_ir,0,sizeof(str_addr_ir));
	memset(str_port_ir,0,sizeof(str_port_ir));
	strcpy(string,str);

	/*Loop para armazenar o endereço do IR*/
	for(j=0;j<20;j++)			
	{
		if(string[j] != ':')
		{
			if(string[j] < '0' || string[j] > '9')
				string[j] = 0;
			str_addr_ir[j] = string[j];
		}else	
			break;
	}

	/*Loop para armazenar a porta do IR*/			
	for(i=0,j++;i<20;i++,j++) 						
		if(string[j] != '\r' && string[j] != '\n')
			str_port_ir[i] = string[j];
		else 
			break;

	/*Converte para inteiro endereço e porta recebidas pela função como string*/
	rcv_addr_ir = atoi(str_addr_ir);
	rcv_port_ir = atoi(str_port_ir);

	/*Analisa possiveis erros de parâmetro*/
	if(str_port_ir[0] == '?')
		/*Retorna valor que informa que está sendo requisitado a porta do IR de endereço recebido*/ 
		return 2;
	if(rcv_port_ir>16 || rcv_port_ir == 0 || rcv_addr_ir>=MAX_QTD_IR || str_addr_ir[0] == 0 || str_port_ir[0] == 0)
		/*Erro encontrado*/	
		return 0;
	else
		/*Nenhum erro encontrado*/
		return 1;
}
/****************************************************************************
Função destinada para salvar no endereço recebido um novo IR
****************************************************************************/
void cmd_ir_learn(char *par)
{
	char j;

	/*Chama função que retorna se o endereço e a porta do IR estão corretos*/
	if(get_addr_channel(par))
	{
		/*Endereço e porta corretos. Chama função para lê o IR. A função retornará valor que indicará
		  se houve erro na leitura do IR*/
		j = learn_ir(rcv_addr_ir,rcv_port_ir,FILE_INDEX_INFRARED);	
		if(j == ERROR_TIMEOUT || j == ERROR_RECEIVER_IR || j == ERROR_OVERFLOW_PULSES_IR || j == ERROR_OVERFLOW_FLASH || j == ERROR_NOT_SAVED)
			sprintf(buf_tx,"ERROR %u",j);
		else
			sprintf(buf_tx,"OK %u",rcv_addr_ir);	/*IR salvo na memoria flash*/			
	}else
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);			 				
}
/****************************************************************************
Função destinada para salvar no endereço recebido um novo IR que funcionará
como um comando para gerar uma cena
****************************************************************************/
void cmd_irl_scene(char *par)
{
	char j;

	/*Chama função que retorna se o endereço e a porta do IR estão corretos*/
	if(get_addr_channel(par))
	{
		/*Endereço e porta corretos. Chama função para lê o IR. A função retornará valor que indicará
		  se houve erro na leitura do IR*/
		if(rcv_addr_ir >= NUM_SCENE)	/*Endereços de 0 a 7 referente as cenas*/
		{
			sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);
	   		return;
		}

		j = learn_ir(rcv_addr_ir,rcv_port_ir,FILE_INDEX_CMDIR);	
		if(j == ERROR_TIMEOUT || j == ERROR_RECEIVER_IR || j == ERROR_OVERFLOW_PULSES_IR || j == ERROR_OVERFLOW_FLASH || j == ERROR_NOT_SAVED)
			sprintf(buf_tx,"ERROR %u",j);
		else
			sprintf(buf_tx,"OK %u",rcv_addr_ir);	/*IR salvo na memoria flash*/			
	}else
		sprintf(buf_tx,"ERROR %u",ERROR_PARAMETER);			 				
}
/****************************************************************************
Função destinada para aprender um novo IR e colocar na raiz do SD
****************************************************************************/
void cmd_ir_learn_app(char *par)
{
	char j;

	j = learn_ir(0,7,FILE_INDEX_RAIZ);	
	if(j == ERROR_TIMEOUT || j == ERROR_RECEIVER_IR || j == ERROR_OVERFLOW_PULSES_IR || j == ERROR_OVERFLOW_FLASH || j == ERROR_NOT_SAVED)
		sprintf(buf_tx,"ERROR %u",j);
	else
		sprintf(buf_tx,"OK");	/*IR salvo na raiz do SD*/				 				
}

/****************************************************************************
Função destinada para executar o IR contido na raiz do SD
****************************************************************************/
void cmd_ir_send_app(char *par)
{
	if(send_ir(0, FILE_INDEX_RAIZ))
		sprintf(buf_tx,"OK");	/*IR salvo na raiz do SD reproduido*/
	else
		sprintf(buf_tx,"ERROR %u",ERROR_IR_NOT_SEND);

//	if(send_ir(0, FILE_INDEX_RAIZ, START_IR_DEF, STOP_IR_DEF))
//		sprintf(buf_tx,"OK");	/*IR salvo na raiz do SD reproduido*/
//	else
//		sprintf(buf_tx,"ERROR %u",ERROR_IR_NOT_SEND);					 				
}

/****************************************************************************
Função destinada para enviar IR localizado no endereço recebido pela função
****************************************************************************/
void cmd_ir_send(char *par)
{
	rcv_addr_ir = atoi(par);
	if(rcv_addr_ir < MAX_QTD_IR)		/*Endereço é maior que a quantidade maxima?*/
	{
		/*Chama função que reproduz o IR salvo no endereço pasado como parametro.
		  A função retorna __TRUE se o IR foi reproduzido com sucesso*/

		if(send_ir(rcv_addr_ir, FILE_INDEX_INFRARED))
			sprintf(buf_tx,"OK %u",rcv_addr_ir);	/*IR reproduzido*/									
		else	
			sprintf(buf_tx,"ERROR %u",ERROR_IR_NOT_SEND);	/*IR não reproduzido*/
		
//		if(send_ir(rcv_addr_ir, FILE_INDEX_INFRARED, START_IR_DEF, STOP_IR_DEF))
//			sprintf(buf_tx,"OK %u",rcv_addr_ir);	/*IR reproduzido*/									
//		else	
//			sprintf(buf_tx,"ERROR %u",ERROR_IR_NOT_SEND);	/*IR não reproduzido*/

		return;	
	}
	sprintf(buf_tx,"ERROR %u",ERROR_ADDR_OVERFLOW);	/*Overflow addr*/					
}
/****************************************************************************
Função destinada para deletar um IR localizado no endereço recebido pela função
****************************************************************************/
void cmd_ir_erase(char *par)
{
	rcv_addr_ir = atoi(par);
	if(rcv_addr_ir >= MAX_QTD_IR)			/*Endereço é maior que a quantidade maxima?*/
		sprintf(buf_tx,"ERROR %u",ERROR_ADDR_OVERFLOW);	/*Overflow addr*/
	else
	{	
		/*Chama função que deletará IR localizado no endereço passado para função como parametro*/
		sprintf(buf_tx,"OK %u [Erase infrared in address: %u]",rcv_addr_ir,rcv_addr_ir);
		erase_ir(rcv_addr_ir);		
	}			
}
/*****************************************************************************
Função destinada para apagar todos os IRs da memoria flash
*****************************************************************************/
void cmd_ir_erase_all(char *par)
{
	erase_all_ir();
	sprintf(buf_tx,"OK 1 [Erase all infrared of memory]"); 
}
/*****************************************************************************
Função destinada para fazer a leitura de um IR localizado no endereço
recebido pela função
*****************************************************************************/
void cmd_ir_read(char *par)
{
	short i;
	rcv_addr_ir = atoi(par);
	if(rcv_addr_ir >= MAX_QTD_IR)
		sprintf(buf_tx,"ERROR %u",ERROR_ADDR_OVERFLOW);	/*Overflow addr*/
	else
	{
		if(read_ir(rcv_addr_ir, FILE_INDEX_INFRARED) == NO_ERROR)	/*Função que lê IR localizado no endereço passado como parametro para função*/
		{
			printf("Addr IR:%u...\r",rcv_addr_ir);

			/*IR no formato DEC*/
			for(i=0;i<MAX_QTD_PULSOS;i++)
				printf("[%03u]:%u\r",i,ir[i]);
			
			fflush(stdout);
			sprintf(buf_tx,"OK %u [Read infrared in address: %u]",rcv_addr_ir,rcv_addr_ir);
		}else
			sprintf(buf_tx,"ERROR %u",ERROR_READ);	
	}	
}
#endif
