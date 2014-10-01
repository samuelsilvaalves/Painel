#line 1 "src\\tcpip\\FTP_uif.c"









 

#line 1 "C:\\Keil\\ARM\\RV31\\INC\\Net_Config.h"









 




#line 1 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"









 




 

 


#line 27 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"







 typedef unsigned int   size_t;


typedef signed char     S8;
typedef unsigned char   U8;
typedef short           S16;
typedef unsigned short  U16;
typedef int             S32;
typedef unsigned int    U32;
typedef long long       S64;
typedef unsigned long long U64;
typedef unsigned char   BIT;
typedef unsigned int    BOOL;

#line 54 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"

#line 66 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"



 





 
typedef U32 OS_SEM[2];

 

typedef U32 OS_MBX[];

 
typedef U32 OS_MUT[3];

 
typedef U32 OS_TID;

 
typedef void *OS_ID;

 
typedef U32 OS_RESULT;

 












 




#line 194 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"



 



 
extern void      os_set_env    (void);
extern void      rt_sys_init   (void (*task)(void), U8 priority, void *stk);
extern void      rt_tsk_pass   (void);
extern OS_TID    rt_tsk_self   (void);
extern OS_RESULT rt_tsk_prio   (OS_TID task_id, U8 new_prio);
extern OS_TID    rt_tsk_create (void (*task)(void), U8 priority, void *stk, void *argv);
extern OS_RESULT rt_tsk_delete (OS_TID task_id);

#line 230 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"

extern void      _os_sys_init(U32 p, void (*task)(void), U32 prio_stksz,
                                     void *stk)                        __svc_indirect(0);
extern OS_TID    _os_tsk_create (U32 p, void (*task)(void), U32 prio_stksz,
                                        void *stk, void *argv)         __svc_indirect(0);
extern OS_TID    _os_tsk_create_ex (U32 p, void (*task)(void *), U32 prio_stksz,
                                           void *stk, void *argv)      __svc_indirect(0);
extern OS_TID    _os_tsk_self (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_pass (U32 p)                                  __svc_indirect(0);
extern OS_RESULT _os_tsk_prio (U32 p, OS_TID task_id, U8 new_prio)     __svc_indirect(0);
extern OS_RESULT _os_tsk_delete (U32 p, OS_TID task_id)                __svc_indirect(0);

 
extern OS_RESULT rt_evt_wait (U16 wait_flags,  U16 timeout, BOOL and_wait);
extern void      rt_evt_set  (U16 event_flags, OS_TID task_id);
extern void      rt_evt_clr  (U16 clear_flags, OS_TID task_id);
extern U16       rt_evt_get  (void);







extern OS_RESULT _os_evt_wait(U32 p, U16 wait_flags, U16 timeout,
                                     BOOL and_wait)                    __svc_indirect(0);
extern void      _os_evt_set (U32 p, U16 event_flags, OS_TID task_id)  __svc_indirect(0);
extern void      _os_evt_clr (U32 p, U16 clear_flags, OS_TID task_id)  __svc_indirect(0);
extern U16       _os_evt_get (U32 p)                                   __svc_indirect(0);
extern void      isr_evt_set (U16 event_flags, OS_TID task_id);

 
extern void      rt_sem_init (OS_ID semaphore, U16 token_count);
extern OS_RESULT rt_sem_send (OS_ID semaphore);
extern OS_RESULT rt_sem_wait (OS_ID semaphore, U16 timeout);





extern void      _os_sem_init (U32 p, OS_ID semaphore, 
                                      U16 token_count)                 __svc_indirect(0);
extern OS_RESULT _os_sem_send (U32 p, OS_ID semaphore)                 __svc_indirect(0);
extern OS_RESULT _os_sem_wait (U32 p, OS_ID semaphore, U16 timeout)    __svc_indirect(0);
extern void      isr_sem_send (OS_ID semaphore);

 
extern void      rt_mbx_init  (OS_ID mailbox, U16 mbx_size);
extern OS_RESULT rt_mbx_send  (OS_ID mailbox, void *p_msg,    U16 timeout);
extern OS_RESULT rt_mbx_wait  (OS_ID mailbox, void **message, U16 timeout);
extern OS_RESULT rt_mbx_check (OS_ID mailbox);







extern void      _os_mbx_init (U32 p, OS_ID mailbox, U16 mbx_size)     __svc_indirect(0);
extern OS_RESULT _os_mbx_send (U32 p, OS_ID mailbox, void *message_ptr,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_wait (U32 p, OS_ID mailbox, void  **message,
                                      U16 timeout)                     __svc_indirect(0);
extern OS_RESULT _os_mbx_check (U32 p, OS_ID mailbox)                  __svc_indirect(0);
extern void      isr_mbx_send (OS_ID mailbox, void *message_ptr);
extern OS_RESULT isr_mbx_receive (OS_ID mailbox, void **message);

 
extern void      rt_mut_init    (OS_ID mutex);
extern OS_RESULT rt_mut_release (OS_ID mutex);
extern OS_RESULT rt_mut_wait    (OS_ID mutex, U16 timeout);





extern void      _os_mut_init (U32 p, OS_ID mutex)                     __svc_indirect(0);
extern OS_RESULT _os_mut_release (U32 p, OS_ID mutex)                  __svc_indirect(0);
extern OS_RESULT _os_mut_wait (U32 p, OS_ID mutex, U16 timeout)        __svc_indirect(0);

 
extern void      rt_dly_wait (U16 delay_time);
extern void      rt_itv_set  (U16 interval_time);
extern void      rt_itv_wait (void);





extern void      _os_dly_wait (U32 p, U16 delay_time)                  __svc_indirect(0);
extern void      _os_itv_set (U32 p, U16 interval_time)                __svc_indirect(0);
extern void      _os_itv_wait (U32 p)                                  __svc_indirect(0);

 
extern OS_ID     rt_tmr_create (U16 tcnt, U16 info);
extern OS_ID     rt_tmr_kill   (OS_ID timer);




extern OS_ID     _os_tmr_create (U32 p, U16 tcnt, U16 info)            __svc_indirect(0);
extern OS_ID     _os_tmr_kill (U32 p, OS_ID timer)                     __svc_indirect(0);

 
extern void      rt_tsk_lock   (void);
extern void      rt_tsk_unlock (void);




extern void      _os_tsk_lock (U32 p)                                  __svc_indirect(0);
extern void      _os_tsk_unlock (U32 p)                                __svc_indirect(0);

 
extern int       _init_box (void *box_mem, U32 box_size, U32 blk_size);
extern void     *_alloc_box (void *box_mem);
extern void     *_calloc_box (void *box_mem);
extern int       _free_box (void *box_mem, void *box);








 




 

typedef struct {                         
  U8  hr;                                
  U8  min;                               
  U8  sec;                               
  U8  day;                               
  U8  mon;                               
  U16 year;                              
} RL_TIME;

typedef struct {                         
  S8  name[256];                         
  U32 size;                              
  U16 fileID;                            
  U8  attrib;                            
  RL_TIME time;                          
} FINFO;

extern int finit (const char *drive);
extern int funinit (const char *drive);
extern int fdelete (const char *filename);
extern int frename (const char *oldname, const char *newname);
extern int ffind (const char *pattern, FINFO *info);
extern U64 ffree (const char *drive);
extern int fformat (const char *drive);
extern int fanalyse (const char *drive);
extern int fcheck (const char *drive);
extern int fdefrag (const char *drive);

 




 

 



 
#line 409 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"

 
#line 417 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"

 
#line 430 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"

 





 
#line 444 "C:\\Keil\\ARM\\RV31\\INC\\RTL.h"

 




 



extern void init_TcpNet (void);
extern void main_TcpNet (void);
extern void timer_tick (void);
extern U8   udp_get_socket (U8 tos, U8 opt, 
                            U16 (*listener)(U8 socket, U8 *remip, U16 port, U8 *buf, U16 len));
extern BOOL udp_release_socket (U8 socket);
extern BOOL udp_open (U8 socket, U16 locport);
extern BOOL udp_close (U8 socket);
extern BOOL udp_mcast_ttl (U8 socket, U8 ttl);
extern U8  *udp_get_buf (U16 size);
extern BOOL udp_send (U8 socket, U8 *remip, U16 remport, U8 *buf, U16 dlen);
extern U8   tcp_get_socket (U8 type, U8 tos, U16 tout,
                            U16 (*listener)(U8 socket, U8 event, U8 *buf, U16 len));
extern BOOL tcp_release_socket (U8 socket);
extern BOOL tcp_listen (U8 socket, U16 locport);
extern BOOL tcp_connect (U8 socket, U8 *remip, U16 remport, U16 locport);
extern U8  *tcp_get_buf (U16 size);
extern U16  tcp_max_dsize (U8 socket);
extern BOOL tcp_check_send (U8 socket);
extern U8   tcp_get_state (U8 socket);
extern BOOL tcp_send (U8 socket, U8 *buf, U16 dlen);
extern BOOL tcp_close (U8 socket);
extern BOOL tcp_abort (U8 socket);
extern void tcp_reset_window (U8 socket);
extern BOOL arp_cache_ip (U8 *ipadr, U8 type);
extern void ppp_listen (char const *user, char const *passw);
extern void ppp_connect (char const *dialnum, char const *user, char const *passw);
extern void ppp_close (void);
extern BOOL ppp_is_up (void);
extern void slip_listen (void);
extern void slip_connect (char const *dialnum);
extern void slip_close (void);
extern BOOL slip_is_up (void);
extern U8   get_host_by_name (U8 *hostn, void (*cbfunc)(U8 event, U8 *host_ip));
extern BOOL smtp_connect (U8 *ipadr, U16 port, void (*cbfunc)(U8 event));
extern void dhcp_disable (void);
extern BOOL igmp_join (U8 *group_ip);
extern BOOL igmp_leave (U8 *group_ip);
extern BOOL snmp_trap (U8 *manager_ip, U8 gen_trap, U8 spec_trap, U16 *obj_list);
extern BOOL snmp_set_community (const char *community);






 
  

 
#line 16 "C:\\Keil\\ARM\\RV31\\INC\\Net_Config.h"

 



                                   





 




 




 
#line 50 "C:\\Keil\\ARM\\RV31\\INC\\Net_Config.h"

 





 
#line 73 "C:\\Keil\\ARM\\RV31\\INC\\Net_Config.h"

 





typedef struct os_frame {          
  U16 length;                      
  U16 index;                       
  U8  data[1];                     
} OS_FRAME;


typedef struct arp_info {          
  U8  State;                       
  U8  Type;                        
  U8  Retries;                     
  U8  Tout;                        
  U8  HwAdr[6];           
  U8  IpAdr[4];            
} ARP_INFO;


typedef struct igmp_info {         
  U8  State;                       
  U8  Tout;                        
  U8  GrpIpAdr[4];         
} IGMP_INFO;


typedef struct udp_info {          
  U8  State;                       
  U8  McastTtl;                    
  U16 LocPort;                     
  U8  Tos;                         
  U8  Opt;                         
                                   
  U16 (*cb_func)(U8 socket, U8 *rem_ip, U16 port, U8 *buf, U16 len);
} UDP_INFO;


typedef struct tcp_info {          
  U8  State;                       
  U8  Type;                        
  U8  Flags;                       
  U8  Tos;                         
  U8  RemIpAdr[4];         
  U16 RemPort;                     
  U16 LocPort;                     
  U16 MaxSegSize;                  
  U16 WinSize;                     
  U32 SendSeq;                     
  U32 SendSeqNext;                 
  U32 RecSeqNext;                  
  U16 Tout;                        
  U16 AliveTimer;                  
  U16 RetryTimer;                  
  U8  TxFlags;                     
  U8  Retries;                     
  OS_FRAME *ReTransFrm;            
                                   
  U16 (*cb_func)(U8 socket, U8 event, U8 *p1, U16 p2);
} TCP_INFO;


typedef struct http_info {         
  U8  State;                       
  U8  Socket;                      
  U16 Flags;                       
  U8  FType;                       
  U8  PostSt;                      
  U16 DelimSz;                     
  U32 CGIvar;                      
  U32 DLen;                        
  U32 Count;                       
  U16 BCnt;                        
  U8  Lang[6];                     
  U32 LMDate;                      
  U8 *Script;                      
  U8 *pDelim;                      
  void *sFile;                     
  void *dFile;                     
} HTTP_INFO;


typedef struct http_file {         
  const U32 Id;                    
  const U8 *Start;                 
} HTTP_FILE;


typedef struct tnet_info {         
  U8  State;                       
  U8  Socket;                      
  U8  Flags;                       
  U8  BCnt;                        
  U16 Tout;                        
  U8  Widx;                        
  U8  Ridx;                        
  U32 SVar;                        
  U8  LBuf[96];           
  U8  Fifo[128];           
  U8  hNext;                       
  U8  hCurr;                       
  U8  Hist[128];           
} TNET_INFO;


typedef struct tftp_info {         
  U8  State;                       
  U8  Retries;                     
  U8  Flags;                       
  U16 Timer;                       
  U8  RemIpAdr[4];         
  U16 RemPort;                     
  U16 BlockNr;                     
  void *File;                      
  U32 FPos;                        
} TFTP_INFO;


typedef struct ftp_info {          
  U8  State;                       
  U8  Socket;                      
  U8  Flags;                       
  U8  Resp;                        
  U8  RemIpAdr[4];         
  U16 DPort;                       
  U8  DSocket;                     
  U8  PathLen;                     
  U8 *Path;                        
  U8 *Name;                        
  void *File;                      
} FTP_INFO;


typedef struct dns_cache {         
  U32 HostId;                      
  U32 Ttl;                         
  U8  IpAdr[4];            
} DNS_CACHE;


typedef struct localm {            
  U8 IpAdr[4];             
  U8 DefGW[4];             
  U8 NetMask[4];           
  U8 PriDNS[4];            
  U8 SecDNS[4];            
} LOCALM;


typedef struct remotem {           
  U8 IpAdr[4];             
  U8 HwAdr[6];            
} REMOTEM;


typedef struct mib_entry {         
  U8   Type;                       
  U8   OidLen;                     
  U8   Oid[13];             
  U8   ValSz;                      
  void *Val;                       
  void (*cb_func)(int mode);       
} MIB_ENTRY;


typedef enum {                     
  ERR_MEM_ALLOC,
  ERR_MEM_FREE,
  ERR_MEM_CORRUPT,
  ERR_UDP_ALLOC,
  ERR_TCP_ALLOC,
  ERR_TCP_STATE
} ERROR_CODE;




 

 
extern void init_system (void);
extern void run_system (void);
extern void process_hl_igmp (OS_FRAME *frame);
extern void process_hl_udp (OS_FRAME *frame);
extern void process_hl_tcp (OS_FRAME *frame);
extern BOOL dispatch_frame (OS_FRAME *frame, U8 netif);
extern BOOL eth_chk_adr (OS_FRAME *frame);
extern U8  *eth_get_adr (U8 *ipadr);
__weak void arp_notify (void);
extern void sys_error (ERROR_CODE code);

 
extern OS_FRAME *alloc_mem (U32 byte_size);
extern void free_mem (OS_FRAME *mem_ptr);

 
extern void init_eth_link (void);
extern void run_eth_link (void);
extern void put_in_queue (OS_FRAME *frame);
extern BOOL eth_send_frame (OS_FRAME *frame);

 
extern void init_ppp_link (void);
extern void run_ppp_link (void);
extern BOOL ppp_send_frame (OS_FRAME *frame, U16 prot);

 
extern void init_slip_link (void);
extern void run_slip_link (void);
extern BOOL slip_send_frame (OS_FRAME *frame);

 
extern int  mem_copy (void *dp, void *sp, int len);
extern void mem_rcopy (void *dp, void *sp, int len);
extern BOOL mem_comp (void *sp1, void *sp2, int len);
extern void mem_set (void *dp, U8 val, int len);
extern BOOL mem_test (void *sp, U8 val, int len);
extern BOOL str_scomp (U8 *sp, U8 const *cp);
extern int  str_copy (U8 *dp, U8 *sp);
extern void str_up_case (U8 *dp, U8 *sp);
extern U16  SwapB (U16 w16);
extern U16  get_u16 (U8 *p16);
extern U32  get_u32 (U8 *p32);
extern void set_u32 (U8 *p32, U32 val);

 
extern void arp_send_req (U32 entry);

 
extern void init_igmp (void);
extern void run_igmp_host (void);
extern void process_igmp (OS_FRAME *frame);

 
extern void init_udp (void);
extern void process_udp (OS_FRAME *frame);

 
extern void init_tcp (void);
extern void tcp_poll_sockets (void);
extern void process_tcp (OS_FRAME *frame_r);

 
extern void init_http (void);
extern void run_http_server (void);
extern void *http_fopen (U8 *name);
extern void http_fclose (void *file);
extern U16  http_fread (void *file, U8 *buf, U16 len);
extern BOOL http_fgets (void *file, U8 *buf, U16 size);
extern U32  http_finfo (U8 *name);
extern void cgi_process_var (U8 *qstr);
extern void cgi_process_data (U8 code, U8 *dat, U16 len);
extern U16  cgi_func (U8 *env, U8 *buf, U16 buflen, U32 *pcgi);
extern U8  *cgx_content_type (void);
extern BOOL http_accept_host (U8 *rem_ip, U16 rem_port);
extern U8  *http_get_var (U8 *env, void *ansi, U16 maxlen);
extern U8  *http_get_lang (void);
extern void http_get_info (REMOTEM *info);
extern U8   http_get_session (void);
extern U8  *http_get_content_type (void);
extern U32  http_date (RL_TIME *time);

 
extern void init_tnet (void);
extern void run_tnet_server (void);
extern U16  tnet_cbfunc (U8 code, U8 *buf, U16 buflen);
extern U16  tnet_process_cmd (U8 *cmd, U8 *buf, U16 buflen, U32 *pvar);
extern BOOL tnet_ccmp (U8 *buf, U8 *cmd);
extern void tnet_set_delay (U16 cnt);
extern void tnet_get_info (REMOTEM *info);
extern U8   tnet_get_session (void);
extern BOOL tnet_msg_poll (U8 session);

 
extern void init_tftp (void);
extern void run_tftp_server (void);
extern void *tftp_fopen (U8 *fname, U8 *mode);
extern void tftp_fclose (void *file);
extern U16  tftp_fread (void *file, U32 fpos, U8 *buf);
extern U16  tftp_fwrite (void *file, U8 *buf, U16 len);

 
extern void init_ftp (void);
extern void run_ftp_server (void);
extern void *ftp_fopenftp_fopen (U8 *fname, U8 *mode);
extern void ftp_fclose (void *file);
extern U16  ftp_fread (void *file, U8 *buf, U16 len);
extern U16  ftp_fwrite (void *file, U8 *buf, U16 len);
extern BOOL ftp_fdelete (U8 *fname);
extern BOOL ftp_frename (U8 *fname, U8 *newn);
extern U16  ftp_ffind (U8 code, U8 *buf, U8 *mask, U16 len);

 
extern void init_dhcp (void);
extern void run_dhcp_client (void);

 
extern void init_nbns (void);

 
extern void init_dns (void);
extern void run_dns_client (void);
extern U8   get_host_by_name (U8 *hostn, void (*cbfunc)(U8, U8 *));

 
extern void init_smtp (void);
extern void run_smtp_client (void);
extern U16  smtp_cbfunc (U8 code, U8 *buf, U16 buflen, U32 *pvar);
extern BOOL smtp_accept_auth (U8 *srv_ip);

 
extern void init_ethernet (void);
extern void send_frame (OS_FRAME *frame);
extern void poll_ethernet (void);
extern void int_enable_eth (void);
extern void int_disable_eth (void);

 
extern void init_serial (void);
extern int  com_getchar (void);
extern BOOL com_putchar (U8 c);
extern BOOL com_tx_active (void);

 
extern void init_modem (void);
extern void modem_dial (U8 *dialnum);
extern void modem_hangup (void);
extern void modem_listen (void);
extern BOOL modem_online (void);
extern BOOL modem_process (U8 ch);
extern void modem_run (void);







 



#line 13 "src\\tcpip\\FTP_uif.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"









 




#line 16 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 
#line 24 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 





 
#line 52 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 



 



 




 



 



 
#line 82 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 
#line 97 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 
#line 105 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 




 
typedef enum {
  RTV_NOERR = 0,                        
  ERR_INVALID_PARAM,                    

  ERR_FTL_ECC,                          
  ERR_FTL_WARN,                         
  ERR_FTL_BB,                           
  ERR_FTL_LBN,                          
  ERR_FTL_ALLOC,                        
  ERR_FTL_RANGE,                        
  ERR_FTL_NOT_FOUND,                    
  ERR_FTL_NOT_FOUND_EOB,                
  ERR_FTL_FATAL,                        

  ERR_ECC_COR,                          
  ERR_ECC_UNCOR,                        

  ERR_NAND_PROG,                        
  ERR_NAND_ERASE,                       
  ERR_NAND_HW_TOUT,                     
  ERR_NAND_DMA_TOUT,                    
  ERR_NAND_UNSUPPORTED,                 
} NAND_FTL_ERROR;

#pragma push
#pragma anon_unions

 
typedef struct iob {
  U16  flags;                            
  U32  fsize;                            
  U32  fpos;                             
  void *vi;                              
  union {
    struct {                             
      U16 fileID;                        
      U16 fblock;                        
      U16 fidx;                          
      U16 nfidx;                         
      U32 fbot;                          
      U32 ftop;                          
    } efs;
    struct {                             
      U8  attrib;                        
      U8  currDatSect;                   
      U16 lastEntOffs;                   
      U32 currDatClus;                   
      U32 firstClus;                     
      U32 lastEntClus;                   
    } fat;
  };
} IOB;
#pragma pop

 
typedef struct DevConf {
  U32 bStart;                            
  U32 bEnd;                              
} const EFS_CFG;

 
typedef struct fatinfo {
  U32 BootRecSec;                        
  U8  FatType;                           
  U8  NumOfFat;                          
  U8  SecPerClus;                        
  U16 FatSize;                           
  U16 RsvdSecCnt;                        
  U32 DskSize;                           
  U32 DataSecCnt;                        
  U16 RootEntCnt;                        
  U16 BytesPerSec;                       
  U32 DataClusCnt;                       
  U16 RootDirAddr;                       
  U16 RootSecCnt;                        
  U32 ClusSize;                          
  U16 EntsPerClus;                       
                                         
  U16 FAT32_ExtFlags;                    
  U32 FAT32_RootClus;                    
  U16 FAT32_FSInfo;                      
  U16 FAT32_BkBootSec;                   
} FATINFO;

 
typedef struct fcache {
  U32 sect;                              
  U8  *buf;                              
  BIT dirty;                             
} FCACHE;

 
typedef struct dcache {
  U32 sect;
  U32 csect;
  U8  *buf;
  U8  *cbuf;
  U8  nwr;
  U8  nrd;
} DCACHE;

 
typedef struct {
  U16 pbn;
  U16 lbn;
  U8  typ;
  U8  nextPg;                            
  U8  *pgIdx;
} BLOCK_CACHE;

 
typedef struct {
  U32 row;
  U8 *buf;
} PAGE_CACHE;

 
typedef struct {
  U32 CacheBS;                           
  U32 CachePS;                           
  U16 CachedBlocks;
  U16 CachedPages;
  BLOCK_CACHE *Block;
  PAGE_CACHE  *Page;
} NAND_FTL_CACHE;

 
typedef struct {
  U8  Pos_LSN;                           
  U8  Pos_COR;                           
  U8  Pos_BBM;                           
  U8  Pos_ECC;                           
  U16 SectInc;                           
  U16 SpareOfs;                          
                                         
  U16 SpareInc;                            
} NAND_PG_LAY;

 
typedef struct {  
  NAND_PG_LAY *PgLay;                    
  U16 NumBlocks;                         
  U16 NumPages;                          
  U16 PageSize;                          
  U16 SectorsPerBlock;                   
  U8  SectorsPerPage;                    
  U8  AddrCycles;                        
  U8  SwEccEn;                           
  U8  DrvInst;                           
} const NAND_DRV_CFG;

 
typedef struct {
   
  NAND_DRV_CFG DrvCfg;
   
  U16 BttStartBn;                        
  U16 BttEndBn;                          
   
  U16 DataStartBn;                       
  U16 DataEndBn;                         
     
  U16 NumCacheBlocks;
  U16 NumCachePages;
  U16 TsnTableSize;
   
  U8  *PgBuf;
  BLOCK_CACHE *BlockCache;
  U8  *BlockCacheBuf;
  PAGE_CACHE  *PageCache;
  U8  *PageCacheBuf;
  U32 *TsnTable;
} const NAND_FTL_CFG;

 
typedef struct {
  void *dcb;                             
  char id[3];                            
  U8   attr;                             
} const FS_DEV;

 
typedef struct {
  U32  block_cnt;                        
  U16  read_blen;                        
  U16  write_blen;                       
} Media_INFO;

 
typedef struct {
  U32  free_clus;
  U32  top_clus;
  U32  startDirClus;
  U32  firstEntClus;
  U16  firstEntOffs;
  U8   numOfEntries;
  BIT  in_root_1x;
  char name_buf[260];
} FATVAR;

 
typedef struct {
  BOOL (*Init)        (U32 adr, U32 clk);
  BOOL (*UnInit)      (void);
  BOOL (*ReadData)    (U32 adr, U32 sz, U8 *buf);  
                                         
  BOOL (*ProgramPage) (U32 adr, U32 sz, U8 *buf);
  BOOL (*EraseSector) (U32 adr);
  BOOL (*EraseChip)   (void);            
} const EFS_DRV;

 
typedef struct {
  U32  (*Init)        (NAND_DRV_CFG *cfg);
  U32  (*UnInit)      (NAND_DRV_CFG *cfg);
  U32  (*PageRead)    (U32 row, U8 *buf, NAND_DRV_CFG *cfg);
  U32  (*PageWrite)   (U32 row, U8 *buf, NAND_DRV_CFG *cfg);
  U32  (*BlockErase)  (U32 row, NAND_DRV_CFG *cfg);
} const NAND_DRV;

 
typedef struct {
  BOOL (*Init)        (void);
  BOOL (*UnInit)      (void);
  U8   (*Send)        (U8 outb);
  BOOL (*SendBuf)     (U8 *buf, U32 sz);
  BOOL (*RecBuf)      (U8 *buf, U32 sz);
  BOOL (*BusSpeed)    (U32 kbaud);
  BOOL (*SetSS)       (U32 ss);
  U32  (*CheckMedia)  (void);            
} const SPI_DRV;

 
typedef struct {
  BOOL (*Init)        (void);
  BOOL (*UnInit)      (void);
  void (*Delay)       (U32 us);
  BOOL (*BusMode)     (U32 mode);
  BOOL (*BusWidth)    (U32 width);
  BOOL (*BusSpeed)    (U32 kbaud);
  BOOL (*Command)     (U8  cmd, U32 arg, U32 resp_type, U32 *rp);
  BOOL (*ReadBlock)   (U32 bl, U8 *buf, U32 cnt);
  BOOL (*WriteBlock)  (U32 bl, U8 *buf, U32 cnt);
  BOOL (*SetDma)      (U32 mode, U8 *buf, U32 cnt);  
                                          
  U32  (*CheckMedia)  (void);            
} const MCI_DRV;

 
typedef struct {
  BOOL (*Init)        (U32 mode);
  BOOL (*UnInit)      (U32 mode);
  BOOL (*ReadSect)    (U32 sect, U8 *buf, U32 cnt);
  BOOL (*WriteSect)   (U32 sect, U8 *buf, U32 cnt);
  BOOL (*ReadInfo)    (Media_INFO *cfg);
  U32  (*CheckMedia)  (void);            
} const FAT_DRV;

 
typedef struct {
  U8    CardType;                        
  U32   SerNum;                          
  SPI_DRV *spi;                          
} MMC_DEV;

 
typedef struct {
  U8    CardType;                        
  U16   CardRCA;                         
  U32   SerNum;                          
  MCI_DRV *drv;                          
} MCI_DEV;

 
typedef struct {
  NAND_PG_LAY PgLay;                     
  U8  PageSectors;                       
  U8  SPP;                               
                                         
  U8  PPB;                               
                                         
  U8  SPB;                               
                                         
  U8  EPS;                               
                                         
  U8  LastECC;                           
  U16 LastDBN;                           
                                         
  U16 LastTBN;                           
                                         
  U32 CurrLBN;                           
  U32 GcLBN;                             
                                         
  U16 PbnQ[3];                           
  U16 BadBlockCnt;                       
  U16 NumDataBlocks;                     
                                         
  U8  *PgBuf;
  U32 *TsnTable;
  U16 TsnTableSize;
  NAND_FTL_CACHE Ca;
  NAND_FTL_CFG  *Cfg;
  NAND_DRV      *Drv;
} NAND_FTL_DEV;

 
typedef struct {
  U32     Status;                        
  FAT_DRV *drv;                          
  U32     *CaBuf;                        
  U32     CaSize;                        
  FATINFO cfg;                           
  FCACHE  fat;                           
  DCACHE  ca;                            
  FATVAR  lv;                            
} FAT_VI;

 
typedef struct {
  U32     Status;                        
  EFS_DRV *drv;                          
  U32     BaseAdr;                       
  U32     InitVal;                       
  U32     NumSect;                       
  U32     Size;                          
  EFS_CFG *DevCfg;                       
  U32     CpuClk;                        
} EFS_VI;

 
extern void  fs_config (void);

 
extern int  __sys_open (const char *fname, int openmode);
extern int  __sys_close (int handle);
extern int  __sys_read (int handle, U8 *buf, U32 len);
extern int  __sys_write (int handle, const U8 *buf, U32 len);
extern int  __sys_ensure (int handle);
extern int  __sys_seek (int handle, U32 pos);
extern long __sys_flen (int handle);

 
#line 461 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"

 
extern int  fat_init (FAT_VI *vi);
extern BOOL fat_find (const char *fn, IOB *fcb);
extern BOOL fat_seek (IOB *fcb, U32 pos);
extern U32  fat_read (IOB *fcb, U8 *buf, U32 len);
extern BOOL fat_write (IOB *fcb, const U8 *buf, U32 len);
extern U64  fat_free (FAT_VI *vi);
extern BOOL fat_delete (const char *fn, IOB *fcb);
extern BOOL fat_wclose (IOB *fcb);
extern BOOL fat_rename (const char *old, const char *newn, IOB *fcb);
extern BOOL fat_create (const char *fn, IOB *fcb);
extern BOOL fat_format (FAT_VI *vi, const char *label);
extern BOOL fat_ffind  (const char *fn, FINFO *info, IOB *fcb);

 
extern FAT_VI *ioc_getcb (const char *drive);
extern int  ioc_init (FAT_VI *vi);
extern int  ioc_uninit (FAT_VI *vi);
extern BOOL ioc_read_info (Media_INFO *info, FAT_VI *vi);
extern BOOL ioc_read_sect (U32 sect, U8 *buf, U32 cnt, FAT_VI *vi);
extern BOOL ioc_write_sect (U32 sect, U8 *buf, U32 cnt, FAT_VI *vi);

 
extern BOOL mmc_Init (U32 mode, MMC_DEV *mmc);
extern BOOL mmc_UnInit (U32 mode, MMC_DEV *mmc);
extern BOOL mmc_ReadSector (U32 sect, U8 *buf, U32 cnt, MMC_DEV *mmc);
extern BOOL mmc_WriteSector (U32 sect, U8 *buf, U32 cnt, MMC_DEV *mmc);
extern BOOL mmc_ReadInfo (Media_INFO *info, MMC_DEV *mmc);

 
extern BOOL mci_Init (U32 mode, MCI_DEV *mci);
extern BOOL mci_UnInit (U32 mode, MCI_DEV *mci);
extern BOOL mci_ReadSector (U32 sect, U8 *buf, U32 cnt, MCI_DEV *mci);
extern BOOL mci_WriteSector (U32 sect, U8 *buf, U32 cnt, MCI_DEV *mci);
extern BOOL mci_ReadInfo (Media_INFO *info, MCI_DEV *mci);

 
extern BOOL ftl_Init (U32 mode, NAND_FTL_DEV *ftl);
extern BOOL ftl_UnInit (U32 mode, NAND_FTL_DEV *ftl);
extern U32  ftl_ReadSect (U32 lsn, U8 *buf, U32 cnt, NAND_FTL_DEV *ftl);
extern U32  ftl_WriteSect(U32 lsn, U8 *buf, U32 cnt, NAND_FTL_DEV *ftl);
extern BOOL ftl_Format (NAND_FTL_DEV *ftl);
extern BOOL ftl_ReadInfo (Media_INFO *info, NAND_FTL_DEV *ftl);

 
extern BOOL efs_rename (const char *filename, IOB *fcb);
extern BOOL efs_create (const char *fname, IOB *fcb);
extern BOOL efs_delete (IOB *fcb);
extern U32  efs_free (EFS_VI *vi);
extern BOOL efs_format (EFS_VI *vi);
extern BOOL efs_ffind (FINFO *info, IOB *fcb);
extern BOOL efs_wclose (IOB *fcb);
extern U32  efs_read (IOB *fcb, U8 *buf, U32 len);
extern BOOL efs_write (IOB *fcb, const U8 *buf, U32 len);
extern BOOL efs_ensure (IOB *fcb);
extern BOOL efs_seek (IOB *fcb, U32 pos);
extern void efs_fsize (IOB *fcb);
extern BOOL efs_find (const char *name, IOB *fcb);
extern int  efs_analyse (EFS_VI *vi);
extern BOOL efs_check (EFS_VI *vi);
extern BOOL efs_defrag (IOB *fcb);

 
extern U32  fs_get_time (void);
extern U32  fs_get_date (void);



#line 14 "src\\tcpip\\FTP_uif.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"
 
 
 





 






 









#line 34 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"


  
  typedef unsigned int size_t;    








 
 

 
  typedef struct __va_list __va_list;





   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 125 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 
extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 944 "C:\\Keil\\ARM\\RV31\\INC\\stdio.h"



 
#line 15 "src\\tcpip\\FTP_uif.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
 
 
 
 




 








 











#line 37 "C:\\Keil\\ARM\\RV31\\INC\\string.h"


  
  typedef unsigned int size_t;








extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 184 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 200 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 223 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 238 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 261 "C:\\Keil\\ARM\\RV31\\INC\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 493 "C:\\Keil\\ARM\\RV31\\INC\\string.h"



 
#line 16 "src\\tcpip\\FTP_uif.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"
 
 
 
 





 






 







#line 32 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"






#line 46 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"

 
#line 56 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"

 
 









 
#line 78 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"





#line 130 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"

extern __declspec(__nothrow) __pure unsigned char **__rt_ctype_table(void);







    extern int (isalnum)(int  );

     





    extern int (isalpha)(int  );

     





    extern int (iscntrl)(int  );

     
     

 




    extern int (isdigit)(int  );

     

    extern int (isblank)(int  );
     
     
     





    extern int (isgraph)(int  );

     





    extern int (islower)(int  );

     





    extern int (isprint)(int  );

     
     





    extern int (ispunct)(int  );

     





    extern int (isspace)(int  );

     





    extern int (isupper)(int  );

     

 
 

__inline int __isxdigit_helper(int __t) { return (__t ^ (__t << 2)); }




    extern int (isxdigit)(int  );

     



extern int tolower(int  );
     
     

extern int toupper(int  );
     
     







#line 269 "C:\\Keil\\ARM\\RV31\\INC\\ctype.h"



 
#line 17 "src\\tcpip\\FTP_uif.c"
#line 1 ".\\inc\\tcpip\\tcpip.h"



#line 5 ".\\inc\\tcpip\\tcpip.h"
#line 6 ".\\inc\\tcpip\\tcpip.h"
#line 1 ".\\inc\\generic_type_defs.h"










 














typedef unsigned char		BYTE;				
typedef unsigned short int	WORD;				
typedef unsigned long		DWORD;				
typedef unsigned long long	QWORD;				
typedef signed char			CHAR;				
typedef signed short int	SHORT;				
typedef signed long			LONG;				
typedef signed long long	LONGLONG;			

 
typedef void                VOID;

typedef char                CHAR8;
typedef unsigned char       UCHAR8;

 



typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;
typedef signed long long    INT64;

typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
typedef unsigned long int   UINT32;  
typedef unsigned long long  UINT64;

typedef unsigned char U8;



typedef signed char S8;



typedef union _BYTE_VAL
{
    BYTE Val;
	BYTE v[2];
	struct
    {
			BYTE LN;
			BYTE HN;
    } nible;
    struct
    {
        unsigned char bit0:1;
        unsigned char bit1:1;
        unsigned char bit2:1;
        unsigned char bit3:1;
        unsigned char bit4:1;
        unsigned char bit5:1;
        unsigned char bit6:1;
        unsigned char bit7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union _WORD_VAL
{
    WORD Val;
    BYTE v[2];
    struct
    {
			BYTE LB;
			BYTE HB;
    } byte;
    struct
    {
        unsigned char bit0:1;
        unsigned char bit1:1;
        unsigned char bit2:1;
        unsigned char bit3:1;
        unsigned char bit4:1;
        unsigned char bit5:1;
        unsigned char bit6:1;
        unsigned char bit7:1;
        unsigned char bit8:1;
        unsigned char bit9:1;
        unsigned char bit10:1;
        unsigned char bit11:1;
        unsigned char bit12:1;
        unsigned char bit13:1;
        unsigned char bit14:1;
        unsigned char bit15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union _DWORD_VAL
{
    DWORD val;
	WORD w[2];
    BYTE v[4];
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct
    {
        unsigned char bit0:1;
        unsigned char bit1:1;
        unsigned char bit2:1;
        unsigned char bit3:1;
        unsigned char bit4:1;
        unsigned char bit5:1;
        unsigned char bit6:1;
        unsigned char bit7:1;
        unsigned char bit8:1;
        unsigned char bit9:1;
        unsigned char bit10:1;
        unsigned char bit11:1;
        unsigned char bit12:1;
        unsigned char bit13:1;
        unsigned char bit14:1;
        unsigned char bit15:1;
        unsigned char bit16:1;
        unsigned char bit17:1;
        unsigned char bit18:1;
        unsigned char bit19:1;
        unsigned char bit20:1;
        unsigned char bit21:1;
        unsigned char bit22:1;
        unsigned char bit23:1;
        unsigned char bit24:1;
        unsigned char bit25:1;
        unsigned char bit26:1;
        unsigned char bit27:1;
        unsigned char bit28:1;
        unsigned char bit29:1;
        unsigned char bit30:1;
        unsigned char bit31:1;
    } bits;
} DWORD_VAL;









typedef union _QWORD_VAL
{
    QWORD Val;
	DWORD d[2];
	WORD w[4];
    BYTE v[8];
    struct
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct
    {
        unsigned char bit0:1;
        unsigned char bit1:1;
        unsigned char bit2:1;
        unsigned char bit3:1;
        unsigned char bit4:1;
        unsigned char bit5:1;
        unsigned char bit6:1;
        unsigned char bit7:1;
        unsigned char bit8:1;
        unsigned char bit9:1;
        unsigned char bit10:1;
        unsigned char bit11:1;
        unsigned char bit12:1;
        unsigned char bit13:1;
        unsigned char bit14:1;
        unsigned char bit15:1;
        unsigned char bit16:1;
        unsigned char bit17:1;
        unsigned char bit18:1;
        unsigned char bit19:1;
        unsigned char bit20:1;
        unsigned char bit21:1;
        unsigned char bit22:1;
        unsigned char bit23:1;
        unsigned char bit24:1;
        unsigned char bit25:1;
        unsigned char bit26:1;
        unsigned char bit27:1;
        unsigned char bit28:1;
        unsigned char bit29:1;
        unsigned char bit30:1;
        unsigned char bit31:1;
        unsigned char bit32:1;
        unsigned char bit33:1;
        unsigned char bit34:1;
        unsigned char bit35:1;
        unsigned char bit36:1;
        unsigned char bit37:1;
        unsigned char bit38:1;
        unsigned char bit39:1;
        unsigned char bit40:1;
        unsigned char bit41:1;
        unsigned char bit42:1;
        unsigned char bit43:1;
        unsigned char bit44:1;
        unsigned char bit45:1;
        unsigned char bit46:1;
        unsigned char bit47:1;
        unsigned char bit48:1;
        unsigned char bit49:1;
        unsigned char bit50:1;
        unsigned char bit51:1;
        unsigned char bit52:1;
        unsigned char bit53:1;
        unsigned char bit54:1;
        unsigned char bit55:1;
        unsigned char bit56:1;
        unsigned char bit57:1;
        unsigned char bit58:1;
        unsigned char bit59:1;
        unsigned char bit60:1;
        unsigned char bit61:1;
        unsigned char bit62:1;
        unsigned char bit63:1;
    } bits;
} QWORD_VAL;

#line 7 ".\\inc\\tcpip\\tcpip.h"



 







 















extern LOCALM localm[];						 




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

 
extern U8 lhost_name[16];
extern U8 own_hw_adr[6];

 
extern TCP_STATE tcp_state;
extern FTP_STATE ftp_state;
extern TCP_CNT tcp_cnt;
extern CFG_TCP cfg_tcp;

 

extern U8 last_soc_client;
extern U8 tcp_client_soc[4];

extern U8 tcp_server_soc;

extern U8 udp_buf[256];
extern U8 udp_soc;

 
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


#line 18 "src\\tcpip\\FTP_uif.c"
#line 1 ".\\inc\\file_system\\MSD_SD_File.h"








 




#line 15 ".\\inc\\file_system\\MSD_SD_File.h"



 
#line 26 ".\\inc\\file_system\\MSD_SD_File.h"


 


















 






enum _FILE_LINES
{
	 
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





 
#line 19 "src\\tcpip\\FTP_uif.c"

static char last_file_ftp[30];


 

 

void *ftp_fopen (U8 *fname, U8 *mode) {

	memset(last_file_ftp,0,sizeof(last_file_ftp));
	strcpy(last_file_ftp,(const char*)fname);

  	 
  	return (fopen ((const char *)fname, (const char *)mode));
}


 

void ftp_fclose (void *file) {
   
  fclose (file);
}


 

U16 ftp_fread (void *file, U8 *buf, U16 len) {
   
   
  return (fread (buf, 1, len, file));
}


 


U16 ftp_fwrite (void *file, U8 *buf, U16 len) {

	char i,str[30];

	 
	memset(str,0,sizeof(str));
	strcpy(str,"tcp.cfg\0");

	for(i=0;i<strlen(last_file_ftp);i++)
		last_file_ftp[i] = toupper(last_file_ftp[i]);

	for(i=0;i<strlen(str);i++)
		str[i] = toupper (str[i]);

	if(strstr(last_file_ftp,str))
		ftp_state.bit.UpdateTcp = 1;
	

	 
	memset(str,0,sizeof(str));
	strcpy(str,"SCENE");

	for(i=0;i<strlen(str);i++)
		str[i] = toupper (str[i]);
	
	if(strstr(last_file_ftp,str))
		ftp_state.bit.UpdateScene = 1;

	 
	memset(str,0,sizeof(str));
	strcpy(str,"CFG.CFG");

	for(i=0;i<strlen(str);i++)
		str[i] = toupper (str[i]);
	
	if(strstr(last_file_ftp,str))
		ftp_state.bit.UpdateFileCfg = 1;
  	
	
	

	 
  	return (fwrite (buf, 1, len, file));
}


 

BOOL ftp_fdelete (U8 *fname) {
   
  if (fdelete((char *)fname) == 0) {
    return (1);
  }
  return (0);
}


 

BOOL ftp_frename (U8 *fname, U8 *newn) {
   
  if (frename((char *)fname, (char *)newn) == 0) {
    return (1);
  }
  return (0);
}


 

U16 ftp_ffind (U8 code, U8 *buf, U8 *mask, U16 buflen) {
   
   
   
   
   
   
   
   
   
   
  static FINFO info;
  U32 rlen,v;
  U8 *tp;

  if (code < 4) {
     
    info.fileID = 0;
  }

  rlen = 0;
next:
  if (ffind ((char *)mask, &info) == 0) {
     
    if (info.name[0] == '.') {
      if ((info.name[1] == 0) || (info.name[1] == '.' && info.name[2]) == 0) {
         
        goto next;
      }
    }
    switch (code) {
      case 0:
         
        rlen = sprintf ((char *)buf,"%d\r\n", info.size);
        break;

      case 1:
         
        rlen  = sprintf ((char *)buf,"%04d%02d%02d",
                         info.time.year, info.time.mon, info.time.day);
        rlen += sprintf ((char *)&buf[rlen],"%02d%02d%02d\r\n",
                         info.time.hr, info.time.min, info.time.sec);
        break;

      case 2:
      case 4:
         
        rlen = sprintf ((char *)buf,"%s\r\n", info.name);
        break;

      case 3:
      case 5:
         
        rlen  = sprintf ((char *)buf,"%02d-%02d-%02d", 
                         info.time.mon, info.time.day, info.time.year%100);
         
        v = info.time.hr % 12;
        if (v == 0) v = 12;
        if (info.time.hr < 12) tp = "AM";
        else                   tp = "PM";
        rlen += sprintf ((char *)&buf[rlen],"  %02d:%02d%s",v,info.time.min,tp);
        if (info.attrib & 0x10) {
          rlen += sprintf ((char *)&buf[rlen],"%-21s","       <DIR>");
        }
        else {
          rlen += sprintf ((char *)&buf[rlen],"%21d", info.size);
        }
        rlen += sprintf ((char *)&buf[rlen]," %s\r\n", info.name);
        break;
    }
  }
  return (rlen);
}



 
