#ifndef __TCPIP_H__
#define __TCPIP_H__

#include <stdio.h>
#include <Net_Config.h>
#include "generic_type_defs.h"

/*****************************************************************************
** Configurações de funcionamento das funções TCPIP
*****************************************************************************/
#define USE_UDP				1
#define USE_TCP_SERVER		1
#define USE_TCP_CLIENT		1
#define USE_PCK_SERV		1

#define MAX_NUM_SOC 	 	4

/*****************************************************************************/

#define CMD_TCP_CALL_SERVER			0x00
#define CMD_TCP_CALL_CLIENT			0x01
#define CMD_SEND_TO_SERVER			0x00
#define CMD_SEND_TO_CLIENT			0x01


#define DBG_UDP
#define TIMER_TICK					100

#define LEN_TCP_BUF 				32
#define LEN_UDP_BUF 				256

#define DHCP_TOUT	(50000/TIMER_TICK)     /* DHCP timeout 5 seconds */

extern LOCALM localm[];						/* Local Machine Settings */
#define MY_IP localm[NETIF_ETH].IpAdr
#define MY_GATEWAY localm[NETIF_ETH].DefGW
#define MY_MASK localm[NETIF_ETH].NetMask

typedef enum State
{
	USER_STATE_IDLE,
	USER_STATE_ERROR,
	USER_STATE_RESERVED,
	USER_STATE_ACTIVE,
	USER_STATE_WAITING
} tcpState;

typedef union _FTP_STATE
{
	BYTE all;
	struct _FTP_STATE_bits
	{	  
		BYTE UpdateScene	:1;
		BYTE UpdateTcp		:1;
		BYTE UpdateFileCfg	:1;
	}bit;
} FTP_STATE;

typedef union _TCP_STATE
{
	BYTE all;
	struct _TCP_STATE_bits
	{	  
		BYTE serverConnected	:1;
	  	BYTE dhcp				:1;
		BYTE dataToSend			:1;
	}bit;
} TCP_STATE;

typedef union _TCP_CNT
{
	BYTE all;
	struct _TCP_CNT_bits
	{
	  BYTE tryConServer	:1;
	  BYTE trySendEmail :1;
	}bit;
} TCP_CNT;

typedef struct _CFG_TCP
{
	BYTE ftp_user[16u];
	BYTE ftp_password[16u];
} CFG_TCP;

/* Net_Config.c */
extern U8 lhost_name[16];
extern U8 own_hw_adr[ETH_ADRLEN];

/*Estruuras*/
extern TCP_STATE tcp_state;
extern FTP_STATE ftp_state;
extern TCP_CNT tcp_cnt;
extern CFG_TCP cfg_tcp;

/*Variaveis (tcpip.c)*/

extern U8 last_soc_client;
extern U8 tcp_client_soc[MAX_NUM_SOC];

extern U8 tcp_server_soc;

extern U8 udp_buf[LEN_UDP_BUF];
extern U8 udp_soc;

/*Funções (tcpip.c)*/
void dhcp_check (void);
void user_init (void);
void tcp_task(void);
void inet_aton(U8 *strp, U8 *np);


U16 tcp_callback (U8 socket, U8 event, U8 *ptr, U16 par, U8 modo);
U16 tcpSend (char *p, U8 sz,U8 soc,U8 send);
U16 tcp_callback_client (U8 socket, U8 event, U8 *ptr, U16 par);
U16 tcp_callback_server (U8 socket, U8 event, U8 *ptr, U16 par);

void udpSendBroadcast(U8 *udp_msg); 
void udpSendUnicast(U8 *udp_msg,char *strIp); 
U16 udp_callback (U8 socket, U8 *remip, U16 port, U8 *buf, U16 len);


#endif
