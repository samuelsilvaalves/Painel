
#include <RTL.H>
#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hardware_profile.h"
#include "pwm_ir.h"
#include "timer.h"
#include "control_ir.h"
#include "ir.h"
#include "uart.h"
#include "touch.h"
#include "extint.h"
#include "msd_sd_file.h"


#if USE_IR	/*Inclui na compila��o a fun��o IR da placa?*/

char last_port_ir;

unsigned short ir[MAX_QTD_PULSOS];
unsigned short ir_cmp[MAX_QTD_PULSOS];

U16 ir_counter;

/************************************************************************																										

************************************************************************/
char save_ir(unsigned short *dado,short addr,short channel,int index_file)
{
	FILE *f;
	char StrIdIr[50],str_aux[20];
	short i=0,fim=0;

	memset(StrIdIr,0,sizeof(StrIdIr));		/*Limpa vetor que ir� conter o endere�o onde o IR ser� armazenado*/
	if(index_file == FILE_INDEX_INFRARED)	/*Salvar IR na pasta INFRARED?*/
	{
		if(addr <= IR_ID6)
			/*(TV)->ID0:Source...ID1:CH-...ID2:CH+...ID3:ON...ID4:OFF...ID5:Vol-...ID6:Vol+*/
			strcat(StrIdIr,FILE_IR_DIR_TV);	
		else
		if(addr <= IR_ID18)
		{
			/*(HOME)->ID7:Source...ID8:VOL-...ID9:VOL+...ID10:ON...ID11:OFF...ID12:PLAY...ID13:PAUSE...ID14:BACK...ID15:NEXT*/
			/*ID16: Cursor Left...ID17: Cursor Righ...ID18: Cursor Down*/
			strcat(StrIdIr,FILE_IR_DIR_HOME);	
		}else
		{
			if(atoi(cfg.file.mode_func_ar)) 	/*Swing In (Fun��o swing embutida na temperatura)?*/
			{
				/*(AR)->ID19:16�...ID20:17�............ID33:30�...ID34:ON...ID35:OFF*/
				if(ir_state.bit.ArSwing)
					strcat(StrIdIr,FILE_IR_DIR_AR_SW_ON);
				else
					strcat(StrIdIr,FILE_IR_DIR_AR_SW_OFF);

			}else
			{
				/*(AR)->ID19:16�...ID20:17�............ID33:30�...ID34:ON...ID35:OFF..ID36:SWING ON..ID37:SWING OFF*/
				strcat(StrIdIr,FILE_IR_DIR_AR_SW_OUT);
			}
		}

		sprintf(str_aux,"%u.TXT\0",addr);	/*Copia o endere�o*/
		strcat(StrIdIr,str_aux);			/*Endere�o completo(caminho + endere�o)*/
	}else
	if(index_file == FILE_INDEX_CMDIR)	/*Salvar o IR como sendo um comando para gera��o de cenas?*/
	{
   		sprintf(StrIdIr,"%s%u.TXT\0",FILE_CMDIR,addr);
	}else
	if(index_file == FILE_INDEX_RAIZ)	/*Salvar o IR apenas na raiz do SD?*/
	{
		sprintf(StrIdIr,"IR.TXT\0");
	}else
		return ERROR_NOT_SAVED;		/*Error ao especificar o local de armazenamento do IR*/
	/*Apenas para debug do endere�o completo*/
	printf("[Save IR...addr:%s]\r",StrIdIr);
	fflush(stdout);

	f = fopen(StrIdIr,"w");	/*Abre arquivo para escrita*/
	if(f == NULL)
		return ERROR_NOT_SAVED;
	/*Arquivo abriu corretamente*/
	/*Loop para encontrar o primeiro pulso vazio do IR e armazenar nessa posi��o o canal de emiss�o*/
	for(i=0;i<MAX_QTD_PULSOS;i++)
	{
		if(dado[i] == 0xFFFF)	/*Posi��o vazia?*/
		{
			dado[i] = channel;	/*Armazena o canal e de emiss�o do IR*/
			fim = i + 1;		/*Guarda a posi��o do final do IR (uma posi��o a frente da localiza��o do canal)*/
			break;				/*Sai do la�o*/
		}
	}
	/*Loop para escrever no arquivo*/
	for(i=0;i<MAX_QTD_PULSOS;i++)
	{
		if(i == fim)					/*Chegou no fim?*/
			break;					   	/*Sai do la�o*/
		fprintf(f,"%u#\r\n",dado[i]);	/*Escreve no aruivo o pulso*/
	}
	/*Fecha arquivo e retorna sem erros*/
	fclose(f);	
	return NO_ERROR;
}

/*****************************************************************************

*****************************************************************************/
char read_ir(unsigned short addr, int index_file)
{
	FILE *f;
	char StrIdIr[30],str[10];
	int id=0,ch=0,i=0;

	/*Limpa vetor que ir� conter o endere�o onde o IR ser� armazenado e o vetor auxiliar*/
	memset(StrIdIr,0,sizeof(StrIdIr));
	memset(str,0,sizeof(str));

	if(index_file == FILE_INDEX_INFRARED)	/*Salvar IR na pasta INFRARED?*/
	{
		if(addr <= IR_ID6)
			/*(TV)->ID0:Source...ID1:CH-...ID2:CH+...ID3:ON...ID4:OFF...ID5:Vol-...ID6:Vol+*/
			strcat(StrIdIr,FILE_IR_DIR_TV);	
		else
		if(addr <= IR_ID18)
		{
			/*(HOME)->ID7:Source...ID8:VOL-...ID9:VOL+...ID10:ON...ID11:OFF...ID12:PLAY...ID13:PAUSE...ID14:BACK...ID15:NEXT*/
			/*ID16: Cursor Left...ID17: Cursor Righ...ID18: Cursor Down*/
			strcat(StrIdIr,FILE_IR_DIR_HOME);	
		}else
		{
			if(atoi(cfg.file.mode_func_ar)) 	/*Swing In (Fun��o swing embutida na temperatura)?*/
			{
				/*(AR)->ID19:16�...ID20:17�............ID33:30�...ID34:ON...ID35:OFF*/
				if(ir_state.bit.ArSwing)
					strcat(StrIdIr,FILE_IR_DIR_AR_SW_ON);
				else
					strcat(StrIdIr,FILE_IR_DIR_AR_SW_OFF);

			}else
			{
				/*(AR)->ID19:16�...ID20:17�............ID33:30�...ID34:ON...ID35:OFF..ID36:SWING ON..ID37:SWING OFF*/
				strcat(StrIdIr,FILE_IR_DIR_AR_SW_OUT);
			}
		}
		sprintf(StrIdIr,"%s%u.TXT\0",StrIdIr,addr);		/*Endere�o completo(caminho + endere�o)*/

	}else
	if(index_file == FILE_INDEX_RAIZ)	/*Salvar o IR apenas na raiz do SD?*/
		sprintf(StrIdIr,"IR.TXT\0");
	/*Apenas para debug do endere�o completo*/
	printf("\r[%s]\r",StrIdIr);
	fflush(stdout);

	f = fopen(StrIdIr,"r");			/*Abre aquivo para leitura*/
	memset(ir,0xFFFF,sizeof(ir));	/*Limpa vetor que vai armazenar o IR lido no SD*/
  	if(f == NULL)					/*Ocorreu erro?*/
	{
		printf("[File not found]\r");
		fflush(stdout);
   		return __FALSE; 
	}
	/*Arquivo aberto*/
	/*La�o que vai ler os pulsos e armazenar cada um*/
	while((ch = fgetc (f)) != EOF)
	{
		if(ch == '#')
		{
			ir[id] = atoi(str);	/*Armazena o pulso*/
			if(ir[id] <= 16)	/*Encontrou a posi��o no canal de emiss�o do IR?*/
				break;
			id++;		
		}else
		{
			if(ch != '\r' && ch != '\n')
			{
				str[i] = ch;
				i++;
			}else
			{
				/*Limpa e reseta contador as vezes que contrar caracteres indesejados (\r,\n)*/
				memset(str,0,sizeof(str));
				i=0;
			}
		}
	}
	printf("[File closed]\r");
	fflush(stdout);
	fclose(f);		/*Fecha arquivo*/    
	if(ir[id] > 0 && ir[id] < 16)	
		last_port_ir = ir[id];
	else
		last_port_ir = 7; /*Em todas as portas*/
	return NO_ERROR;
}

/*****************************************************************************

*****************************************************************************/
void erase_all_ir(void)
{	
	char StrIdIr[30];
	short i;
	 
	memset(StrIdIr,0,sizeof(StrIdIr));	
	for(i=0;i<MAX_QTD_IR;i++)
	{
		sprintf(StrIdIr,"%s%u.TXT\0",FILE_INFRARED,i);
		fdelete(StrIdIr);
	}	 
}

/*****************************************************************************
Fun��o destinada a apagar ir que se localiza no endere�o recebido pela fun��o.
*****************************************************************************/
void erase_ir(unsigned short addr)
{	 	
   	char StrIdIr[30];
	memset(StrIdIr,0,sizeof(StrIdIr));
	sprintf(StrIdIr,"%s%u.TXT\0",FILE_INFRARED,addr);
	fdelete(StrIdIr);	
}

/*****************************************************************************
Fun��o destinada a envia IR armazenado no endere�o recebido pela fun��o.
*****************************************************************************/
char send_ir(unsigned short addr, int index_file)
{
	unsigned int i=0;
	U32 lead_in_on=0, lead_in_off=0;
	char freq[30];

	if(!read_ir(addr, index_file))	/*L� IR localizado no endere�o 'addr'  e verifica se houve erro de leitura no sd*/
	{
		contEnableExtIr = 0;		/*Inicia temporiza��o para habilitar a interrup��o externa*/
		enable_timer(0);			/*Habilita timer 0*/
		return __FALSE;
	}

	disable_timer(0);				/*Desabilita timer 0*/
	NVIC_DisableIRQ(EINT3_IRQn);	/*Desabilita a interrup��o responsavel por detectar se um comando IR xegou no pino (IR CMD)*/

	/*IR no formato DEC*/
	memset(freq,0,sizeof(freq));
	lead_in_on = ir[0] * 4; 	/*Pulso Lead IN high em us*/ 
	lead_in_off = ir[1] * 4; /*Pulso Lead IN low em us*/

	/*SIRC-SONY: 40Khz..Lead In on: 2400us..Lead In of: 600us..Logic high ON: 1200us..Logic high OFF: 600us..
	Logic low ON: 600us..Logic low OFF: 600us..Pulse high without Lead IN: 12bits, 15bits or 20bits*/
	if( lead_in_on  >= 2400 - 2400 * 0.1 && lead_in_on  <= 2400 + 2400 * 0.1 /*&&
		lead_in_off >= 600  - 600  * 0.1 && lead_in_off <= 600  + 600  * 0.1*/ )	
	{
		PWM_freq_KHz = CARRIER_FREQ_40KHZ;
		strcpy(freq, "40KHz (SONY/SIRC)\0");

	}else
	/*RC5-PHILIPS: 36Khz..Lead In on: 889us..Lead In off: 889us..Logic high ON: 889us..Logic high OFF: 889us..
	  Logic low ON: 889us..Logic low OFF: 889us*/ 
	if( lead_in_on 	>= 889 - 889 * 0.1 && lead_in_on  <= 889 + 889 * 0.1 /*&&
		lead_in_off >= 889 - 889 * 0.1 && lead_in_off <= 889 + 889 * 0.1*/ )
	{
		PWM_freq_KHz = CARRIER_FREQ_36KHZ;
		strcpy(freq, "36KHz (RC5/PHILIPS)\0");

	}else
	/*RC6-PHILIPS: 36Khz..Lead In on: 2666us..Lead In off: 889us*/
	if( lead_in_on 	>= 2666 - 2666 * 0.1 && lead_in_on  <= 2666 + 2666 * 0.1 /*&&
	    lead_in_off >= 889  - 889  * 0.1 && lead_in_off <= 889  + 889  * 0.1*/ )	
	{
		PWM_freq_KHz = CARRIER_FREQ_36KHZ;
		strcpy(freq, "36KHz (RC6/PHILIPS)\0");

	}else
	{
		/*Frequencia default*/
   		PWM_freq_KHz = CARRIER_FREQ_38KHZ;
		strcpy(freq, "38KHz (DEFAULT)\0");
	}

	PWM_Set(PWM_freq_KHz);			/*Configura o PWM*/

	for(i=0;i<MAX_QTD_PULSOS;i++)	/*Loop que passa por todos os pulsos do IR*/
	{ 
		/*Sai do la�o na primeira posi��o vazia do vetor(0xffff) ou se o pulso for < 16 (porta do IR 0-15)*/	
		if(ir[i] >= 0xffff || ir[i] < 0x10)	
			break;		

		if(i%2==0)	
			PWM_Start(last_port_ir);	/*Numeros Pares...Liga PWM*/ 		
		else 	  
			PWM_Stop();					/*Numeros Impares...Desliga PWM*/
	
		timer1_counter = 0;	/*Reseta contador do timer*/
		LPC_TIM1->IR = 1;	/*Limpa flag da interrup��o*/
		LPC_TIM1->TCR = 2;	/*Reseta contador do timer*/
		LPC_TIM1->TCR = 1;	/*Inicia a contagem*/

		while(1)	/*La�o que aguarda o tempo necessario de cada pulso*/
		{
			/*Verifica se houve interrup��o para fazer o incremento do contador IR*/ 
			if(LPC_TIM1->IR & (1<<0))
			{
				LPC_TIM1->IR = 1;				/*Limpa flag da interrup��o do timer 1 para uma nova interrup��o*/
				if(++timer1_counter >= ir[i])	/*Passou-se o tempo necess�rio do pulso?*/
				{
					LPC_TIM1->TCR = 0;	/*Finaliza contagem*/
					break;				/*Sai do la�o para fazer a contagem de um novo pulso*/
				}
			}
		}
	}
	LPC_TIM1->TCR = 0;		/*Finaliza contagem*/
	PWM_Stop();				/*Desliga todos os PWMs*/
	enable_timer(0);		/*Habilita novamente o timer 0*/
	contEnableExtIr = 0;	/*Inicia temporiza��o para habilitar a interrup��o externa*/

	/*Informa��o das portas em que o IR foi emitido*/
	printf("\r***\r[IR:%u..Port:0(%s) 1(%s) 2(%s)]\r",addr,(last_port_ir & (1<<0))?"SIM":"N�O",(last_port_ir & (1<<1))?"SIM":"N�O",(last_port_ir & (1<<2))?"SIM":"N�O");
	fflush(stdout);
	/*Informa��es do IR DEC*/
	printf("Frequencia: %s\r",freq);
	printf("Lead IN ON: %uus\r",lead_in_on);
	printf("Lead IN OFF: %uus\r***\r\r",lead_in_off);
	fflush(stdout);

	return __TRUE;
}
/****************************************************************************
Fun��o destinada a envia IR armazenado no endere�o recebido pela fun��o.
*****************************************************************************/
char learn_ir(unsigned short addr, unsigned char channel, int index_file)
{
	U32 pulse = 0, cont_exit=0;
	U8 logic = 0, status = 1, erro = 0, learn_error = NO_ERROR; 

	memset(ir,0xFFFF,sizeof(ir));	/*Reseta vetor onde o IR ir� ser armazenados*/	
	beep(BEEP_PULSO);				/*Apena sinaliza a opera��o learn*/
	NVIC_DisableIRQ(EINT3_IRQn);	/*Desabilita a interrup��o responsavel por detectar que um IR xegou no pino*/
	disable_timer(0);				/*Desabilita timer 0*/

	timer1_counter = 0;
	LPC_TIM1->TCR = 1;		/*Inicia contagem do timer 1*/	

	while(1)
	{
		if(LPC_TIM1->IR & (1<<0))	/*A contagem chegou ao fim e gerou interrup��o?*/
		{
			LPC_TIM1->IR = 1;		/*Limpa flag da interrup��o para uma nova contagem*/
			timer1_counter++;		/*Incrementa contador*/
		}
		
		if(timer1_counter * 4 >= 50000)	/*Passou-se aproximadamente 50ms?*/
		{
			LED_LEARN_TOG();			/*Led board sinalizando que o sistema est� pronto pra ler o IR*/
			wdt_feed();
			timer1_counter=0;
			cont_exit++;
			if(cont_exit > 200)				/*Passou-se 10s esperando IR? (50ms * 200 = 10s)*/
			{
				LPC_TIM1->TCR = 0;			/*Desabilita Timer 1*/
				learn_error = ERROR_TIMEOUT;	
				printf("[Timeout learn]\r");
				fflush(stdout);
				erro = __TRUE;
				break;
			}
		}

		/*Fica contando tempo de espera enquanto nao recebe nenhum sinal de IR*/
		if(RECEIVE_IR())
			continue;

		LPC_TIM1->TCR = 0;	/*Desabilita Timer*/
		wdt_feed();

		ir_counter = 0;		/*Reseta contador do IR*/
		LPC_TIM1->IR = 1;	/*Limpa flag da interrup��o*/
		LPC_TIM1->TCR = 2;	/*Reseta contador do timer*/
		LPC_TIM1->TCR = 1;	/*Inicia a contagem*/
		while(1)	
		{	 		
			/*Verifica se houve interrup��o para fazer o incremento do contador IR*/ 	
			if(LPC_TIM1->IR & (1<<0))
			{
				LPC_TIM1->IR = 1;
				ir_counter++;
			}

			if(status)	/*Ainda est� acontecendo a leitura do IR?*/
			{
				if(!RECEIVE_IR())	/*IR est� em low?*/	
				{
					if(logic)	
					{
						logic = __FALSE;
						pulse++;  
					}
				}else
				{
					if(!logic)
					{
						logic = __TRUE;
						pulse++;  
					}
				}
				if(pulse >= MAX_QTD_PULSOS-1)	/*J� ocorreram o numero m�ximo de pulsos?*/
				{
					/*Overflow dos pulsos no IR. Reseta contadores e vetor do IR*/	
					memset(ir,0xFFFF,sizeof(ir));
					ir_counter = 0;
					pulse = 0;
					status = __FALSE;		/*Sinaliza que a leitura do IR j� terminou*/
					erro = __TRUE;			/*Sinaliza erro (Overflow de pulsos)*/	
				}
						 		 
				ir[pulse] = ((ir[pulse] == 0xFFFF) ? 0 : ir[pulse]) + ir_counter;	/*Vai incrementando os pulsos do IR*/
				ir_counter = 0;											/*Reseta para um novo incremento*/
				if(ir[pulse] * 4 >= TIMEOUT_END_IR * 1000 /*120000*/) /*Maior que 120ms?*/
				{	
					ir[pulse] = 0xFFFF; /*Reseta o ultimo pulso (timeout)*/
					status = __FALSE;	/*Sinaliza que a leitura do IR j� terminou*/	
				}
			}
			
			/*Sai do la�o se o IR foi armazenado*/
			if(!status)
				break;
		}
		LPC_TIM1->TCR = 0;	/*Desabilita Timer 1*/

		if(pulse > 10 && erro == __FALSE)	/*N�o houve erro?*/
		{
			printf("[IR Receiver...Pulses:%u...ADDR:%u]\r\r",pulse,addr);
			fflush(stdout);
			/*Chama fun��o que ir� salvar o IR lido no endere�o especificado*/
			if(save_ir(ir,addr,channel,index_file) == NO_ERROR)
				learn_error = NO_ERROR;			/*IR OK*/
			else
				learn_error = ERROR_NOT_SAVED;	
										
		}else
		{
			printf("[Error Learn %u..Try again..Pulses:%u]\r",learn_error,pulse);
			fflush(stdout);
			learn_error = ERROR_RECEIVER_IR;	/*Falha na recep��o de IR*/	
		}
		break;
	}

	enable_timer(0);
	contEnableExtIr = 0;

	return learn_error;
}
#endif



//char send_ir(unsigned short addr, int index_file, short PosStart, short PosStop)
//{
//	unsigned int i=0;
//	U32 lead_in_on=0, lead_in_off=0;
//	char freq[30];
//
//	if(!read_ir(addr, index_file))	/*L� IR localizado no endere�o 'addr'  e verifica se houve erro de leitura no sd*/
//	{
//		contEnableExtIr = 0;		/*Inicia temporiza��o para habilitar a interrup��o externa*/
//		enable_timer(0);			/*Habilita timer 0*/
//		return __FALSE;
//	}
//
//	disable_timer(0);				/*Desabilita timer 0*/
//	NVIC_DisableIRQ(EINT3_IRQn);	/*Desabilita a interrup��o responsavel por detectar se um comando IR xegou no pino (IR CMD)*/
//
//	/*IR no formato DEC*/
//	memset(freq,0,sizeof(freq));
//	lead_in_on = ir[0] * 4; 	/*Pulso Lead IN high em us*/ 
//	lead_in_off = ir[1] * 4; /*Pulso Lead IN low em us*/
//
//	/*SIRC-SONY: 40Khz..Lead In on: 2400us..Lead In of: 600us..Logic high ON: 1200us..Logic high OFF: 600us..
//	Logic low ON: 600us..Logic low OFF: 600us..Pulse high without Lead IN: 12bits, 15bits or 20bits*/
//	if( lead_in_on  >= 2400 - 2400 * 0.1 && lead_in_on  <= 2400 + 2400 * 0.1 /*&&
//		lead_in_off >= 600  - 600  * 0.1 && lead_in_off <= 600  + 600  * 0.1*/ )	
//	{
//		PWM_freq_KHz = CARRIER_FREQ_40KHZ;
//		strcpy(freq, "40KHz (SONY/SIRC)\0");
//
//	}else
//	/*RC5-PHILIPS: 36Khz..Lead In on: 889us..Lead In off: 889us..Logic high ON: 889us..Logic high OFF: 889us..
//	  Logic low ON: 889us..Logic low OFF: 889us*/ 
//	if( lead_in_on 	>= 889 - 889 * 0.1 && lead_in_on  <= 889 + 889 * 0.1 /*&&
//		lead_in_off >= 889 - 889 * 0.1 && lead_in_off <= 889 + 889 * 0.1*/ )
//	{
//		PWM_freq_KHz = CARRIER_FREQ_36KHZ;
//		strcpy(freq, "36KHz (RC5/PHILIPS)\0");
//
//	}else
//	/*RC6-PHILIPS: 36Khz..Lead In on: 2666us..Lead In off: 889us*/
//	if( lead_in_on 	>= 2666 - 2666 * 0.1 && lead_in_on  <= 2666 + 2666 * 0.1 /*&&
//	    lead_in_off >= 889  - 889  * 0.1 && lead_in_off <= 889  + 889  * 0.1*/ )	
//	{
//		PWM_freq_KHz = CARRIER_FREQ_36KHZ;
//		strcpy(freq, "36KHz (RC6/PHILIPS)\0");
//
//	}else
//	{
//		/*Frequencia default*/
//   		PWM_freq_KHz = CARRIER_FREQ_38KHZ;
//		strcpy(freq, "38KHz (DEFAULT)\0");
//	}
//										
//	PWM_Set(PWM_freq_KHz);			/*Configura o PWM*/
//
//	for(i=PosStart; i < (PosStop == STOP_IR_DEF) ? MAX_QTD_PULSOS : PosStop; i++)	/*Loop que passa por todos os pulsos do IR*/
//	{ 
//		/*Sai do la�o na primeira posi��o vazia do vetor(0xffff) ou se o pulso for < 16 (porta do IR 0-15)*/	
//		if(ir[i] >= 0xffff || ir[i] < 0x10)	
//			break;		
//
//		if(i%2==0)	
//			PWM_Start(last_port_ir);	/*Numeros Pares...Liga PWM*/ 		
//		else 	  
//			PWM_Stop();					/*Numeros Impares...Desliga PWM*/
//	
//		timer1_counter = 0;	/*Reseta contador do timer*/
//		LPC_TIM1->IR = 1;	/*Limpa flag da interrup��o*/
//		LPC_TIM1->TCR = 2;	/*Reseta contador do timer*/
//		LPC_TIM1->TCR = 1;	/*Inicia a contagem*/
//
//		while(1)	/*La�o que aguarda o tempo necessario de cada pulso*/
//		{
//			/*Verifica se houve interrup��o para fazer o incremento do contador IR*/ 
//			if(LPC_TIM1->IR & (1<<0))
//			{
//				LPC_TIM1->IR = 1;				/*Limpa flag da interrup��o do timer 1 para uma nova interrup��o*/
//				if(++timer1_counter >= ir[i])	/*Passou-se o tempo necess�rio do pulso?*/
//				{
//					LPC_TIM1->TCR = 0;	/*Finaliza contagem*/
//					break;				/*Sai do la�o para fazer a contagem de um novo pulso*/
//				}
//			}
//		}
//	}
//	LPC_TIM1->TCR = 0;		/*Finaliza contagem*/
//	PWM_Stop();				/*Desliga todos os PWMs*/
//	enable_timer(0);		/*Habilita novamente o timer 0*/
//	contEnableExtIr = 0;	/*Inicia temporiza��o para habilitar a interrup��o externa*/
//
//	/*Informa��o das portas em que o IR foi emitido*/
//	printf("\r***\r[IR:%u..Port:0(%s) 1(%s) 2(%s)]\r",addr,(last_port_ir & (1<<0))?"SIM":"N�O",(last_port_ir & (1<<1))?"SIM":"N�O",(last_port_ir & (1<<2))?"SIM":"N�O");
//	fflush(stdout);
//	/*Informa��es do IR DEC*/
//	printf("Frequencia: %s\r",freq);
//	printf("Lead IN ON: %uus\r",lead_in_on);
//	printf("Lead IN OFF: %uus\r***\r\r",lead_in_off);
//	fflush(stdout);
//
//	return __TRUE;
//}


