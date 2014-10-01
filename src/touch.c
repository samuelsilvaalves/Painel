
#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hardware_profile.h"
#include "touch.h"
#include "adc.h"
#include "timer.h"
#include "uart.h"
#include "cmds_ir.h"
#include "register.h"
#include "tcpip.h"
#include "msd_sd_file.h"
#include "control_ir.h"

KEY_STATE key_state;

//TOUCH_ENA_DIS touchEnaDis;
int	 touchEnaDis;
char strTouchEnaDis[20];

int debounce_press = DEBOUNCE_PRESS_KEY;
int debounce_release = DEBOUNCE_RELEASE_KEY;

char temp_ar = TEMPERATURA_MIN;

char aux_scene[30];					/*Auxilia na leitura e escrita das cenas no cartão sd*/
char current_scene[30];				/*Irá conter sempre a ultima cena*/
char current_id_scene=7;
char scene[NUM_SCENE][30];			/*Ficam armazenadas todas as cenas contidas no cartão SD ficam armazenadas*/
char touch_led_press = TOUCH_NONE;	/*Armazena o led correspondente do touch pressionado*/
int  cont_save_current_scene = 0;

int cnt_erase_leds = 0;

/*****************************************************************************

*****************************************************************************/
char save_scene(char *_scene,char addr)
{
	FILE *f;
	char str[50];

	memset(str,0,sizeof(str));
	sprintf(str,"%s%u.TXT\0",FILE_DIMMER_SCENE,addr);
	f = fopen(str,"w");

	if(f == NULL)
		return __FALSE;

	fprintf(f,"%s\r\n",_scene);	
	fclose(f);
	return __TRUE;
}

/*****************************************************************************

*****************************************************************************/
//char save_scene_atual(char *_scene)
//{
//	FILE *f;
//
//	wdt_feed();
//	f = fopen(FILE_DIMMER_SCENE_SAVED,"w");
//	if(f == NULL)
//		return __FALSE;
//
//	fprintf(f,"%s\r\n",_scene);
//	fclose(f);
//	wdt_feed();
//	return __TRUE;
//}

/*****************************************************************************

*****************************************************************************/
char read_scene(char addr,char *file)
{	
	FILE *f;
	char str[30];
	int ch=0,i=0;

	memset(str,0,sizeof(str));	
//	if(!strcmp(file,FILE_DIMMER_SCENE_SAVED))
//		strcpy(str,file);
//	else
		sprintf(str,"%s%u.TXT\0",file,addr);
	f = fopen(str,"r");
  	if(f == NULL)
   		return __FALSE; 

	memset(str,0,sizeof(str));
	while((ch = fgetc (f)) != EOF && i<16)
	{
		str[i] = ch;   
		i++;
	}
	fclose(f); 	
	if(i == 16) /*A cena precisa ter 16 caracteres*/
	{
		memset(aux_scene,0,sizeof(aux_scene));
		strcpy(aux_scene,str);
	}else	
		return __FALSE;
	return __TRUE;	   
}

/*****************************************************************************

*****************************************************************************/
void show_all_scene(void)
{
	char str[20];
	int j;

	wdt_feed();
	sprintf(str, "TDI %u %u %u!\0", atoi(type_dim0), atoi(type_dim1), atoi(type_dim2)); 
	uart_putString(UART_LINK_LPC,str);
	for(j=0;j<6000000;j++);	

	exe_scene(0);	/*Executa a cena 0*/ 
	wdt_feed();
	ir_state.bit.PwrPainel = 1;	/*Luzes do painel Ligadas*/
}

/*****************************************************************************

*****************************************************************************/
void init_scene(char modo)
{
	static U8 init = __FALSE;
	char erro = __FALSE,i,start=0,end=0;

	if(!init)				/*Executa apenas na inicialização do micro*/	
		ir_state.all = 0u;
	
	if(modo == 0xFF)		/*Inicializar todas as cenas?*/
		end   = NUM_SCENE;
	else				    /*Inicializa apenas uma cena cujo endereço é o argumento 'modo' */
	{
		start = modo;
		end   = modo+1;
	}

	for(i=start; i<end; i++)	/*Loop para ler as cenas contidas no cartão sd*/
	{
		memset(aux_scene,0,sizeof(aux_scene));
		memset(scene[i],0,sizeof(scene[i]));
		if(read_scene(i,FILE_DIMMER_SCENE))			/*Lê a cena 'i' contida no endereço 'FILE_DIMMER_SCENE' e retorna 1 se obter sucesso*/
		{
			/*Leitura completa. A cena está contida dentro da variavel aux*/	
			strcpy(scene[i],aux_scene);				/*Copia a cena*/
			//if(!init)	/*Executa apenas na inicialização do micro*/		
				printf("[Read...Scene %u: %s]\r",i,scene[i]);
		}else
		{
			erro = __TRUE;							/*Não foi possivel ler a cena 'i' */
			
			if(i == 0) strcpy(scene[i],DEFAULT_SCENE_0);		/*Copia a cena default 0*/
			else if(i == 1) strcpy(scene[i],DEFAULT_SCENE_1);	/*Copia a cena default 1*/
			else if(i == 2) strcpy(scene[i],DEFAULT_SCENE_2);	/*Copia a cena default 2*/
			else if(i == 3) strcpy(scene[i],DEFAULT_SCENE_3);	/*Copia a cena default 3*/

			//if(!init)	/*Executa apenas na inicialização do micro*/
				printf("[Read...Scene %u not found...Loading default: %s]\r",i,scene[i]);
		}
		fflush(stdout);
	}
	if(!init)	/*Executa apenas na inicialização do micro*/
	{
		init = __TRUE;
		if(erro)				/*Houve erro de leitura?*/
			beep(BEEP_ERROR);
		else
			beep(BEEP_CFG);
	}
}

/*****************************************************************************

*****************************************************************************/
void exe_scene(char num_scene)
{
	int i;
	
	/*Desliga led anterior (Scene) caso ainda esteja ligado*/
	for(i=TOUCH_16;i<=TOUCH_23;i++)
		out_leds &= ~(1 << i);
	
	touch_led_press = TOUCH_16 + 2 * num_scene;
					
	if(scene[num_scene][0] != 0)					/*Existe cena contida no endereço 'id_current_scene' ?*/
	{
		current_id_scene = num_scene;				/*Id da cena pode assumir de 0 a 7*/		
		strcpy(current_scene,scene[num_scene]);		/*Armazena a cena atual*/        					
		sprintf(buf_tx,"%s!\0",current_scene);		
		uart_putString(UART_LINK_LPC,buf_tx);		/*Envia a cena para o LPC1113*/
												   
		printf("[Touch Scene(%u):%s]\r\r\0",num_scene,current_scene);	
		fflush(stdout);

		beep(BEEP_PULSO);								 
		uart_putString(UART_LINK_LPC,buf_tx); 		/*Envia novamente a cena para o LPC1113*/
		/*Envia status das cenas para os clientes*/
		sprintf(buf_tx,"%s%u\r\n\0",current_scene,current_id_scene);
		for(i=0;i<MAX_NUM_SOC;i++)
			tcpSend (buf_tx, strlen(buf_tx), tcp_client_soc[i], CMD_SEND_TO_CLIENT);

		cont_save_current_scene = 0;
		cnt_erase_leds = 0;
		
	}else
	{	
		printf("[Touch Scene(%u):not found]\r\r\0",num_scene);		
		fflush(stdout);
		beep(BEEP_ERROR);
	}
	memset(buf_tx,0,sizeof(buf_tx));
}

/*****************************************************************************
** Function name:	void init_touch(void)
**
** Descriptions:	inicia teclado
**
** parameters:		None
**
** Returned value:None
** 
*****************************************************************************/
void init_touch(void)
{
	dir_key_col1();
	dir_key_col2();
	
	dir_key_lin1();
	dir_key_lin2();
	dir_key_lin3();
	dir_key_lin4();

	key_state.all = 0u;
}

/*****************************************************************************
** Function name:	char get_key(void)
**
** Descriptions:	lê tecla pressionada
**
** parameters:		None
**
** Returned value:tecla pressionada
**
*****************************************************************************/
char read_touch(void)
{
	uint16_t i;

	key_col_all_high();
	key_col1_low();
	for(i=0;i<0xFF;i++);
	wdt_feed();

	if(!rd_key_lin1())
		return num16;

	if(!rd_key_lin2())
		return num18;

	if(!rd_key_lin3())
		return num20;

	if(!rd_key_lin4())
		return num22;

	key_col_all_high();
	key_col2_low();
	for(i=0;i<0xFF;i++);
	wdt_feed();

	if(!rd_key_lin1())
		return num17;

	if(!rd_key_lin2())
		return num19;

	if(!rd_key_lin3())
		return num21;

	if(!rd_key_lin4())
		return num23;

	return key_none;
}

/*****************************************************************************
Tarefas relacionadas ao touch 4x2 (Dimmer e Ar Condicionado)
*****************************************************************************/
void touch_task(void)
{
	char key, str_IdIr[4], str_aux[100], flag_send_ir = __FALSE;	
	U32 i;

	memset(str_IdIr,0,sizeof(str_IdIr));
	memset(str_aux,0,sizeof(str_aux));

	key = read_touch();

	if(key != key_none)
	{
		if(!key_state.key.pressed && !debounce_press)
		{
			key_state.key.pressed = 1;
			
			switch(key)
			{
				/*Cenas*/  
			
				case num16:	if(!(touchEnaDis & (1<<TOUCH_SCENE_0)))
								break;

							touch_led_press = TOUCH_SCENE_0; 
							exe_scene(0);	
							break;	/*Executa Cena 0*/

				case num18:	if(!(touchEnaDis & (1<<TOUCH_SCENE_1)))
								break;

							touch_led_press = TOUCH_SCENE_1; 
							exe_scene(1);	
							break;	/*Executa Cena 1*/

				case num20:	if(!(touchEnaDis & (1<<TOUCH_SCENE_2)))
								break;

							touch_led_press = TOUCH_SCENE_2; 
							exe_scene(2);	
							break;	/*Executa Cena 2*/

				case num22:	if(!(touchEnaDis & (1<<TOUCH_SCENE_3)))
								break;

							touch_led_press = TOUCH_SCENE_3; 
							exe_scene(3);	
							break;	/*Executa Cena 3 (OFF)*/

				/*Ar Condicionado*/
				case num17:	/*Power*/ 
					if(!(touchEnaDis & (1<<TOUCH_17)))
						break;

					if(!ir_state.bit.PwrAr)strcpy(str_IdIr,ADDR_AR_PWR_ON);  /*IR power ar on*/
					else				   strcpy(str_IdIr,ADDR_AR_PWR_OFF); /*IR power ar off*/
						
					ir_state.bit.PwrAr = !ir_state.bit.PwrAr;
					sprintf(str_aux,"[%s] [SWING %s] [IR ID:%s] [POWER %s AR]\r",(atoi(cfg.file.mode_func_ar))? "IN":"OUT", 
					   (ir_state.bit.ArSwing)? "ON":"OFF", str_IdIr, (ir_state.bit.PwrAr) ? "ON":"OFF");	/*String para debug*/

					touch_led_press = TOUCH_17;
					flag_send_ir = __TRUE;
					break;

				case num19:	/*Temperatura+*/ 
					if(!(touchEnaDis & (1<<TOUCH_19)))
						break;

				case num21:	/*Temperatura-*/ 
					if(!(touchEnaDis & (1<<TOUCH_21)))
						break;

				case num23:	/*Swing*/	
					if(!(touchEnaDis & (1<<TOUCH_23)))
						break;

					if(key == num19)
					{
						if(temp_ar < TEMPERATURA_MAX) 
							temp_ar++;
						touch_led_press = TOUCH_19;
						flag_send_ir = __TRUE;
						sprintf(str_IdIr,"%u\0",temp_ar + 3); 	/*IR temp*/

					}else
					if(key == num21)
					{
						if(temp_ar > TEMPERATURA_MIN)
							temp_ar--;
						touch_led_press = TOUCH_21;
						flag_send_ir = __TRUE;
						sprintf(str_IdIr,"%u\0",temp_ar + 3); 	/*IR temp*/

					}else
					if(key == num23)
					{
						ir_state.bit.ArSwing = !ir_state.bit.ArSwing;			/*IR swing ar*/
						if(atoi(cfg.file.mode_func_ar)) 	/*Swing In (Função swing embutida na temperatura)?*/
							sprintf(str_IdIr,"%u\0",temp_ar + 3);  
						else
						{
							if(!ir_state.bit.ArSwing)strcpy(str_IdIr,ADDR_AR_SWING_ON); 	/*Endereço Swing On*/
							else					 strcpy(str_IdIr,ADDR_AR_SWING_OFF); 	/*Endereço Swing Off*/		 
						}
						touch_led_press = TOUCH_23;
						flag_send_ir = __TRUE;
					}

					sprintf(str_aux,"[%s] [SWING %s] [IR ID:%s] [TEMP %u°]\r",(atoi(cfg.file.mode_func_ar))? "IN":"OUT", 
					   (ir_state.bit.ArSwing)? "ON":"OFF", str_IdIr, temp_ar);	/*String para debug*/

					break;
			}

			/*Liga led referente ao touch*/
			out_leds |= (1 << touch_led_press);
			atualiza_saidas();

			if(flag_send_ir)			/*Precisa enviar IR?*/
			{
				beep(BEEP_PULSO);		
				cmd_ir_send(str_IdIr);	/*Chama função que envia o ir cujo id do ir é pasado como parâmetro*/
				if(buf_tx[0] == 'E')    /*Houve algum erro ao enviar o IR?*/
				{
					beep(BEEP_ERROR);
					strcat(buf_tx,"\r\r\0");
					uart_putString(0,buf_tx);
	
				}else
				{				/*Sem erros*/
					//printf("%s\r",str_aux);
					//fflush(stdout);
				}
				printf("%s\r",str_aux);
				fflush(stdout);
			}	
		}

		debounce_press = DEBOUNCE_PRESS_KEY;
		debounce_release = DEBOUNCE_RELEASE_KEY;

	}else
	{
		key_state.key.pressed = 0;
		if(debounce_press)	
 			debounce_press--;	
	}

	if(debounce_release)	
	{ 							
		debounce_release--;						
		if(!debounce_release)
		{
			touch_led_press = TOUCH_NONE;					   
			for(i=TOUCH_16;i<=TOUCH_23;i++) 
				out_leds &= ~(1 << i);
		}																				
	}

	if(!tick)	
		return;
	/*A cada 100ms*/

	/*Timeout geral para desligar todos os leds caso estejam a muito tempo ligados (pressionando)*/
	if(touch_led_press != TOUCH_NONE)
	{
	 	if(++cnt_erase_leds >= 500)
		{
			cnt_erase_leds = 0;
			for(i=TOUCH_0;i<TOUCH_23;i++)
				out_leds &= ~(1 << i);
			touch_led_press = TOUCH_NONE;
		}
	}else
		cnt_erase_leds = 0;

	/*Contagem para salvar a cena atual no cartão sd*/
//	if(++cont_save_current_scene > 300)  
//	{
//		cont_save_current_scene = 0;
//		if(current_id_scene != last_current_id_scene && current_scene[0] != 0)
//		{
//			last_current_id_scene = current_id_scene;
//			printf("[Save current Scene(%u):%s]\r\r\0",current_id_scene,current_scene);		
//			fflush(stdout);
//			save_scene_atual(current_scene);	/*Salva a cena atual*/
//		}
//	}			
}

/*****************************************************************************

*****************************************************************************/
void beep(char modo)
{
	U64 j=0;
	U8 i;
	
	wdt_feed();
	BUZZER(1);
	if(modo == BEEP_CFG)
	{
		for(i=0;i<4;i++)
		{
			for(j=0;j<500000;j++);
			BUZZER_TOG();
		}	
	}else
	if(modo == BEEP_PULSO) 
		for(j=0;j<300000;j++);
	else
	if(modo == BEEP_CHAMADA)
	{ 
		for(i=0;i<6;i++)
		{
			wdt_feed();
			for(j=0;j<6000000;j++);
			BUZZER_TOG();
			LED_ATEND_TOG();
		}
	}else
	if(modo == BEEP_ERROR) 
		for(j=0;j<3000000;j++);
	
	wdt_feed();
	BUZZER(0);
}

/*****************************************************************************

*****************************************************************************/
void key_task(void)
{
	static U16 cnt_buz=0, cnt_led=0, cnt_deb=0;

	if(!tick)		
		return;
	/* Executa a cada 100ms */

	/*Atendimento*/
	if(!READ_KEY_ATEND())
	{
		if(++cnt_deb < 5)
			return;

		if(!(++cnt_led % 3))
		{
			LED2_BOARD_TOG();
			LED_ATEND_TOG();		
		}	
			
		if(++cnt_buz == 1)
		{
			beep(BEEP_CHAMADA);
		}
	}else
	{
		cnt_buz = 0;
		cnt_deb = 0;
		LED2_BOARD(0);
		LED_ATEND(0);		
	}
}


///*****************************************************************************
//
//*****************************************************************************/
//void key_task(void)
//{
//	static U16 cnt_buz=0;
//#if KEY_ATENDIMENTO_TOG
//	static U8  key_tog=0, cnt_tog=0;
//#if TIMEOUT_ATEND
//	static U16 timeout_tog=0;
//#endif
//#endif
//
//	if(!tick)		
//		return;
//
//	/* Executa a cada 100ms */
//
//#if !KEY_ATENDIMENTO_TOG
//
//	if(!READ_KEY_ATEND())
//	{
//		LED_ATEND_TOG();
//		if(++cnt_buz >= 50)
//		{
//			cnt_buz = 0;
//			beep(BEEP_CHAMADA);
//		}
//	}else
//	{
//		cnt_buz = 0;
//		LED_ATEND(0);	
//	}
//
//#else
//
//	if(!READ_KEY_ATEND())	
//	{
//		if(!key_tog)
//		{
//			if(++cnt_tog >= 3)
//			{
//				cnt_tog = 0;
//				key_tog = __TRUE;
//			}
//		}else
//		{
//			if(++cnt_tog >= 3)
//			{
//				cnt_tog = 0;
//				key_tog = __FALSE;
//			}
//		}
//	}else
//		cnt_tog = 0;
//		
//	if(key_tog)
//	{
//		LED_ATEND_TOG();
//		if(++cnt_buz >= 50)
//		{
//			cnt_buz = 0;
//			beep(BEEP_CHAMADA);
//		}
//#if TIMEOUT_ATEND
//		if(++timeout_tog >= 1000)
//			key_tog = __FALSE;
//#endif
//	}else
//	{
//#if TIMEOUT_ATEND
//		timeout_tog=0;
//#endif
//		cnt_buz = 0;
//		LED_ATEND(0);
//	}
//#endif	
//}


///*****************************************************************************
//
//*****************************************************************************/
//char get_multi_touch(void)
//{
//	char press = 0;	
//	if(read_ad(COL_1))
//	{
//		if(read_ad(LIN_1))press |= (1<<0);
//		if(read_ad(LIN_2))press |= (1<<2);	
//		if(read_ad(LIN_3))press |= (1<<4);	
//		if(read_ad(LIN_4))press |= (1<<6);
//	}else
//	if(read_ad(COL_2))
//	{
//		if(read_ad(LIN_1))press |= (1<<1);	
//		if(read_ad(LIN_2))press |= (1<<3);	
//		if(read_ad(LIN_3))press |= (1<<5);	
//		if(read_ad(LIN_4))press |= (1<<7);	
//	}
//	if(!press)
//		return TOUCH_NONE;
//	return press;			
//}

///*****************************************************************************
//
//*****************************************************************************/
//void led_key_press(char led)
//{
//	U8 j;
//
//	for(j=0;j<5;/*j++*/)
//	{	
//		if(tick_30ms)
//		{	  	
//			if(!(j%2))out_leds |=  (1 << led);
//			else      out_leds &= ~(1 << led);
//			atualiza_saidas();
//			j++;
//		}
//		timer_poll();
//	}		
//	out_leds |=  (1 << led);
//	atualiza_saidas();
//}

