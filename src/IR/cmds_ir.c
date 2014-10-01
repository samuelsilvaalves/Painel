
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

#if USE_IR	/*Inclui na compila��o a fun��o IR da placa?*/

/*Variaveis usadas (apenas neste ponto c) para armazenar endere�o/porta do IR*/
static unsigned short rcv_addr_ir;
static unsigned char  rcv_port_ir;

/*
** Os comandos a seguir s�o pertencentes a fun��o IR.
** Quando a fun��o n�o � utilizada os comandos n�o s�o compilados.
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
	
	/*Limpa todas as variaveis que ir�o armazenar os dados*/	 		
	memset(string     ,0,sizeof(string));
	memset(str_addr_ir,0,sizeof(str_addr_ir));
	memset(str_port_ir,0,sizeof(str_port_ir));
	strcpy(string,str);

	/*Loop para armazenar o endere�o do IR*/
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

	/*Converte para inteiro endere�o e porta recebidas pela fun��o como string*/
	rcv_addr_ir = atoi(str_addr_ir);
	rcv_port_ir = atoi(str_port_ir);

	/*Analisa possiveis erros de par�metro*/
	if(str_port_ir[0] == '?')
		/*Retorna valor que informa que est� sendo requisitado a porta do IR de endere�o recebido*/ 
		return 2;
	if(rcv_port_ir>16 || rcv_port_ir == 0 || rcv_addr_ir>=MAX_QTD_IR || str_addr_ir[0] == 0 || str_port_ir[0] == 0)
		/*Erro encontrado*/	
		return 0;
	else
		/*Nenhum erro encontrado*/
		return 1;
}
/****************************************************************************
Fun��o destinada para salvar no endere�o recebido um novo IR
****************************************************************************/
void cmd_ir_learn(char *par)
{
	char j;

	/*Chama fun��o que retorna se o endere�o e a porta do IR est�o corretos*/
	if(get_addr_channel(par))
	{
		/*Endere�o e porta corretos. Chama fun��o para l� o IR. A fun��o retornar� valor que indicar�
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
Fun��o destinada para salvar no endere�o recebido um novo IR que funcionar�
como um comando para gerar uma cena
****************************************************************************/
void cmd_irl_scene(char *par)
{
	char j;

	/*Chama fun��o que retorna se o endere�o e a porta do IR est�o corretos*/
	if(get_addr_channel(par))
	{
		/*Endere�o e porta corretos. Chama fun��o para l� o IR. A fun��o retornar� valor que indicar�
		  se houve erro na leitura do IR*/
		if(rcv_addr_ir >= NUM_SCENE)	/*Endere�os de 0 a 7 referente as cenas*/
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
Fun��o destinada para aprender um novo IR e colocar na raiz do SD
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
Fun��o destinada para executar o IR contido na raiz do SD
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
Fun��o destinada para enviar IR localizado no endere�o recebido pela fun��o
****************************************************************************/
void cmd_ir_send(char *par)
{
	rcv_addr_ir = atoi(par);
	if(rcv_addr_ir < MAX_QTD_IR)		/*Endere�o � maior que a quantidade maxima?*/
	{
		/*Chama fun��o que reproduz o IR salvo no endere�o pasado como parametro.
		  A fun��o retorna __TRUE se o IR foi reproduzido com sucesso*/

		if(send_ir(rcv_addr_ir, FILE_INDEX_INFRARED))
			sprintf(buf_tx,"OK %u",rcv_addr_ir);	/*IR reproduzido*/									
		else	
			sprintf(buf_tx,"ERROR %u",ERROR_IR_NOT_SEND);	/*IR n�o reproduzido*/
		
//		if(send_ir(rcv_addr_ir, FILE_INDEX_INFRARED, START_IR_DEF, STOP_IR_DEF))
//			sprintf(buf_tx,"OK %u",rcv_addr_ir);	/*IR reproduzido*/									
//		else	
//			sprintf(buf_tx,"ERROR %u",ERROR_IR_NOT_SEND);	/*IR n�o reproduzido*/

		return;	
	}
	sprintf(buf_tx,"ERROR %u",ERROR_ADDR_OVERFLOW);	/*Overflow addr*/					
}
/****************************************************************************
Fun��o destinada para deletar um IR localizado no endere�o recebido pela fun��o
****************************************************************************/
void cmd_ir_erase(char *par)
{
	rcv_addr_ir = atoi(par);
	if(rcv_addr_ir >= MAX_QTD_IR)			/*Endere�o � maior que a quantidade maxima?*/
		sprintf(buf_tx,"ERROR %u",ERROR_ADDR_OVERFLOW);	/*Overflow addr*/
	else
	{	
		/*Chama fun��o que deletar� IR localizado no endere�o passado para fun��o como parametro*/
		sprintf(buf_tx,"OK %u [Erase infrared in address: %u]",rcv_addr_ir,rcv_addr_ir);
		erase_ir(rcv_addr_ir);		
	}			
}
/*****************************************************************************
Fun��o destinada para apagar todos os IRs da memoria flash
*****************************************************************************/
void cmd_ir_erase_all(char *par)
{
	erase_all_ir();
	sprintf(buf_tx,"OK 1 [Erase all infrared of memory]"); 
}
/*****************************************************************************
Fun��o destinada para fazer a leitura de um IR localizado no endere�o
recebido pela fun��o
*****************************************************************************/
void cmd_ir_read(char *par)
{
	short i;
	rcv_addr_ir = atoi(par);
	if(rcv_addr_ir >= MAX_QTD_IR)
		sprintf(buf_tx,"ERROR %u",ERROR_ADDR_OVERFLOW);	/*Overflow addr*/
	else
	{
		if(read_ir(rcv_addr_ir, FILE_INDEX_INFRARED) == NO_ERROR)	/*Fun��o que l� IR localizado no endere�o passado como parametro para fun��o*/
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
