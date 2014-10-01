/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    MSD_SD_FILE.H
 *      Purpose: File manipulation example definitions
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#ifndef __MSD_SD_FILE_H__
#define __MSD_SD_FILE_H__

#include "tcpip.h"

/*
	Configurações geral do file cfg
*/
#define FILE_CFG_CFG 						"cfg.cfg\0"
#define DEFAULT_MODE_AR						"0\0"	/*1: Swing In  0: Swing Out*/
#define DEFAULT_FUNC_IR_SCENE				"0\0"	/*Desabilitada*/
#define DEFAULT_TYPE_DIM0					"1\0"	/*1:Dimmer 0:On/Off*/
#define DEFAULT_TYPE_DIM1					"1\0"	/*1:Dimmer 0:On/Off*/
#define DEFAULT_TYPE_DIM2					"1\0"	/*1:Dimmer 0:On/Off*/
#define DEFAULT_ENA_DIS_TOUCH				"16777215\0"	/*Seta os bits de todas as 24 teclas habilitando-as*/
/*
	Configurações default TCP
*/
#define FILE_TCP_CFG 						"tcp.cfg\0"

#define DEFAULT_LOC_IP						"192.168.0.2\0"
#define DEFAULT_MASK						"255.255.255.0\0"
#define DEFAULT_GATEWAY						"192.168.0.1\0"
#define DEFAULT_HOST_NAME					"MOTEL\0"

#define DEFAULT_REM_IP_SERV					"192.168.0.1\0"
#define DEFAULT_INTERVAL_PAC_SERV			"5\0"

#define DEFAULT_REM_PORT_SERV				"5004\0"
#define DEFAULT_LOC_PORT_SERV				"5002\0"	
#define DEFAULT_PORT_UDP					"5000\0"
#define DEFAULT_IP_APP						"192.168.0.1\0"


/*
	Configurações default para cenas
*/

#define DEFAULT_SCENE_0						"SET 100100100111\0"
#define DEFAULT_SCENE_1						"SET 060060060000\0"
#define DEFAULT_SCENE_2						"SET 010010010111\0"
#define DEFAULT_SCENE_3						"SET 000000000000\0"

enum _FILE_LINES
{
	/* arquivo tcp.cfg */
	LINE_STATIC_IP = 0u,
	LINE_IP_SERV_REM,
	LINE_PORT_SERV_REM,
	LINE_INTERVAL_PACKET_SERV,
	LINE_HOST_NAME,

	LINE_PORT_SERV_LOC,
	LINE_PORT_UDP,
	LINE_MAC,
	LINE_IP_APP,
	LINE_MASK,
	LINE_GATEWAY,
	
	/* arquivo cfg.cfg */
	LINE_MODE_FUNC_AR = 0u,
	LINE_FUNC_IR_SCENE,
	LINE_TYPE_DIM0,
	LINE_TYPE_DIM1,
	LINE_TYPE_DIM2,
	LINE_ENA_DIS_TOUCH
};


typedef struct _FILE_TCP
{
	char static_ip[16u];
	char mask[16u];
	char gateway[16u];	
	char host_name[16u];
	char ip_serv_rem[16u];
	char port_serv_rem[6u];
	char port_serv_loc[6u];		
	char interval_packet_serv[6u];
	char port_udp[6u];
	char ip_app[16u];
	char mac[16u];
	
} FILE_TCP;	

typedef struct _FILE_CFG
{
	char mode_func_ar[3u];
	char func_ir_scene[3u];	
} FILE_CFG;				


typedef struct _ST_FILES
{
	FILE_TCP	tcp;
	FILE_CFG	file;
		
} ST_FILES;


extern ST_FILES cfg;


extern char type_dim0[3u];
extern char type_dim1[3u];
extern char type_dim2[3u];

void read_file_cfg(void);
char init_msd (void);
void init_file (void); 
void file_task (void); 
char fread_line(char *ptr, const char *file, char num_line);
char fwrite_line(char *buf_write, const char *file, char num_line);


#endif
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
