/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    SMTP_UIF.C
 *      Purpose: SMTP Client User Interface Module
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <RTL.h>
#include <LPC17xx.h>
#include <Net_Config.h>
#include <string.h>
#include <stdio.h>
#include "tcpip.h"
#include "rtc.h"

extern LOCALM localm[];
#define MY_IP localm[NETIF_ETH].IpAdr

/* Email definitions */
#define MAIL_FROM       "regisnog84@yahoo.com.br\0"
//#define RCPT_TO         "regis.ngr@gmail.com\0"
#define SMTP_USER       "regisnog84\0"
#define SMTP_PASSWORD   "411695\0"
#define MAIL_SUBJECT    "Bloqueador GSM [%s]\0"

#define MSG_HEADER            \
  "Olá,\r\n\r\n"				      \
	"Módulo de bloqueio GSM [%s]\r\n"	\
	"Local: %s\r\n"
	

#define MSG_FOOTER            \
  "----------------\r\n"			\
  "IP do Servidor: %s:%s (%02d/%02d/%04d %02d:%02d:%02d)\r\n"	\
	"IP Local: %d.%d.%d.%d (DHCP %s)\r\n"	\
	"versão	%s\r\n"

/* My structure of SMTP U32 storage variable. This variable is private and  */
/* is not altered by SMTP Client. It is only set to zero when smtp_cbfunc() */
/* is called for the first time.  */
typedef struct {
  U8  id;
  U16 idx;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)

/* Net_Config.c */
extern U8 lhost_name[];

/*----------------------------------------------------------------------------
 *      Functions
 *---------------------------------------------------------------------------*/

//extern U16 AD_in (U32 ch);

/*----------------------------------------------------------------------------
 *      SMTP CallBack Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- smtp_cbfunc -----------------------------------*/

U16 smtp_cbfunc (U8 code, U8 *buf, U16 buflen, U32 *pvar) {
  /* This function is called by the SMTP client to get email parameters and */
  /* data. It returns the number of bytes written to the output buffer.     */
  /* Hi-bit of return value (len is or-ed with 0x8000) is a repeat flag the */
  /* SMTP client. If this bit is set to 1, the system will call this func   */
  /* again with parameter 'pvar' pointing to a 4-byte buffer. This buffer   */
  /* can be used for storing different status variables for this function.  */
  /* It is set to 0 by SMTP client on first call and is not altered by SMTP */
  /* client for repeated calls. This function should NEVER write more than  */
  /* 'buflen' bytes to the buffer.                                          */
  /* Parameters:                                                            */
  /*   code   - function code with following values:                        */
  /*             0 - Username:   - for SMTP authentication if requested     */
  /*             1 - Password:   - for SMTP authentication if requested     */
  /*             2 - 'From   : ' - get email address of the sender          */
  /*             3 - 'To     : ' - get email address of recipient           */
  /*             4 - 'Subject: ' - get subject of email                     */
  /*             5 - 'Data   : ' - get email data in plain ascii format     */
  /*   buf    - SMTP transmit buffer                                        */
  /*   buflen - length of this buffer (500-1400 bytes - depends on MSS)     */
  /*   pvar   - pointer to local storage buffer used for repeated loops     */
  /*            This is a U32 variable - size is 4 bytes. Value is:         */
  /*            - on 1st call = 0                                           */
  /*            - 2nd call    = as set by this function on first call       */
  U32 len = 0;

  switch (code) {
    case 0:
      /* Enter Username for SMTP Server authentication. */
      len = str_copy (buf, SMTP_USER);
      break;

    case 1:
      /* Enter Password for SMTP Server authentication. */
      len = str_copy (buf, SMTP_PASSWORD);
      break;

    case 2:
      /* Enter email address of the sender. */
      len = str_copy (buf, MAIL_FROM);
      break;

    case 3:
      /* Enter email address of the recipient. */
      len = str_copy (buf, cfg_system.email/*RCPT_TO*/);
      break;

    case 4:
      /* Enter email subject. */
      //len = str_copy (buf, MAIL_SUBJECT);
		len = sprintf ((char *)buf, MAIL_SUBJECT, cfg_system.name);
		break;

    case 5:
      /* Enter email data. */
      switch (MYBUF(pvar)->id) {
        case 0:
          /* First call, enter an email header text. */
			 len = sprintf ((char *)buf, MSG_HEADER, cfg_system.name,cfg_system.local); //Original
			
          
          MYBUF(pvar)->id  = 2;
          MYBUF(pvar)->idx = 1;
					
          goto rep;
//
//        case 1:
//          /* Add email message body. */
//          for (len = 0; len < buflen-150; ) {
//            /* Let's use as much of the buffer as possible. */
//            /* This will produce less packets and speedup the transfer. */
//            len += sprintf ((char *)(buf+len), "%d. ",MYBUF(pvar)->idx);
//            for (i = 0; i < 8; i++) {
//              len += sprintf ((char *)(buf+len), "AD%d= %d  ",i,32/*AD_in(i)*/);
//            }
//            len += str_copy (buf+len, "\r\n");
//            if (++MYBUF(pvar)->idx > 500) {
//              MYBUF(pvar)->id = 2;
//              break;
//            }
//          }
//          /* Request a repeated call, bit 15 is a repeat flag. */
rep:      len |= 0x8000;
          break;

        case 2:
          /* Last one, add a footer text to this email. */
          //len = str_copy (buf, MSG_FOOTER);
					len = sprintf ((char *)buf, MSG_FOOTER, cfg_system.rem_ip,
																									cfg_system.rem_port,
																									local_time.RTC_Mday,
																									local_time.RTC_Mon,
																									local_time.RTC_Year,
																									local_time.RTC_Hour,
																									local_time.RTC_Min,
																									local_time.RTC_Sec,
																									MY_IP[0], MY_IP[1], 
																									MY_IP[2], MY_IP[3], 
																									tcp_state.bit.dhcp ? "habilitado":"desabilitado",
																									cfg_system.version);
        break;
      }
  }
  return ((U16)len);
}


/*--------------------------- smtp_accept_auth ------------------------------*/

BOOL smtp_accept_auth (U8 *srv_ip) {
  /* SMTP server with address 'srv_ip' is asking for user authentication. */
  /* Return value: __TRUE  = use the authentication                       */
  /*               __FALSE = do not use the authentication                */

  /* Accept the authentication. */
  return (__TRUE);
}



/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
