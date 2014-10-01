#line 1 "src\\file_system\\File_Config.c"









 

#line 1 "C:\\Keil\\ARM\\RV31\\INC\\File_Config.h"









 




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



#line 13 "src\\file_system\\File_Config.c"



















































































































          



































          




























































































































#line 1 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"









 

#line 1 "C:\\Keil\\ARM\\RV31\\INC\\absacc.h"
 
 
 










#line 13 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"

#pragma thumb
#pragma O3



 

 





 





 
#line 43 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"

 
#line 56 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"

 



 
struct iob _iob[8];

 
U16 const _NFILE   = 8;
U16 const _NDRV    = (0 + 0 + 0 + 1 + 0 + 0 + 0 + 0);



 
#line 81 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
#line 95 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
#line 140 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
#line 150 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"
  
 static U32 mc0_cache[(2+1) * 256] ;
 static FAT_VI mc0_vol;

#line 165 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"
   
    
  extern SPI_DRV spi0_drv;
  static MMC_DEV mmc0_dev;
#line 175 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"
  


   
  static BOOL mc0_Init (U32 mode) {
    return (mmc_Init (mode,&mmc0_dev));
  }
  static BOOL mc0_UnInit (U32 mode) {
    return (mmc_UnInit (mode,&mmc0_dev));
  }
  static BOOL mc0_RdSect (U32 sect, U8 *buf, U32 cnt) {
    return (mmc_ReadSector (sect,buf,cnt,&mmc0_dev));
  }
  static BOOL mc0_WrSect (U32 sect, U8 *buf, U32 cnt) {
    return (mmc_WriteSector (sect,buf,cnt,&mmc0_dev));
  }
  static BOOL mc0_RdInfo (Media_INFO *info) {
    return (mmc_ReadInfo (info,&mmc0_dev));
  }
  static U32 mc0_ChkMedia (void) {
    if (!spi0_drv . CheckMedia) return (0x01);
    return (spi0_drv . CheckMedia());
  }

   
  FAT_DRV mc0_drv = {
    mc0_Init,
    mc0_UnInit,
    mc0_RdSect,
    mc0_WrSect,
    mc0_RdInfo,
    mc0_ChkMedia,
  };

 


 
#line 276 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
#line 287 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
#line 298 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
#line 389 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
FS_DEV fs_DevPool[(0 + 0 + 0 + 1 + 0 + 0 + 0 + 0)] = {
#line 404 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"
  { &mc0_vol,  "M0", 0x04 | 1  | 0x08 },
#line 418 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"
}; 




 
void fs_config (void) {

#line 435 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"

#line 445 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"

#line 454 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"


  mc0_vol.CaSize  = 2 * 2;
  mc0_vol.CaBuf   = mc0_cache;
  mc0_vol.drv     = &mc0_drv;




   
  mmc0_dev.spi    = &spi0_drv;



#line 480 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"













#line 500 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"
}


  
 BOOL efs_rename (const char *filename, IOB *fcb) { return (0); }
 BOOL efs_create (const char *fname, IOB *fcb)    { return (0); }
 BOOL efs_delete (IOB *fcb)                       { return (0); }
 U32  efs_free (EFS_VI *vi)                       { return (0); }
 BOOL efs_format (EFS_VI *vi)                     { return (0); }
 BOOL efs_ffind (FINFO *info, IOB *fcb)           { return (0); }
 BOOL efs_wclose (IOB *fcb)                       { return (0); }
 U32  efs_read (IOB *fcb, U8 *buf, U32 len)       { return (0); }
 BOOL efs_write (IOB *fcb, const U8 *buf, U32 len){ return (0); }
 BOOL efs_ensure (IOB *fcb)                       { return (0); }
 BOOL efs_seek (IOB *fcb, U32 pos)                { return (0); }
 void efs_fsize (IOB *fcb)                        { ; }
 BOOL efs_find (const char *name, IOB *fcb)       { return (0); }
 int  efs_analyse (EFS_VI *vi)                    { return (0); }
 BOOL efs_check (EFS_VI *vi)                      { return (0); }
 BOOL efs_defrag (IOB *fcb)                       { return (0); }


#line 539 "C:\\Keil\\ARM\\RV31\\INC\\File_lib.c"



 
#line 291 "src\\file_system\\File_Config.c"




 
