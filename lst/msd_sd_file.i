#line 1 "src\\file_system\\MSD_SD_File.c"








 

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






 
  

 
#line 12 "src\\file_system\\MSD_SD_File.c"
#line 1 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"




















 









 

typedef enum IRQn
{
 
  NonMaskableInt_IRQn           = -14,       
  MemoryManagement_IRQn         = -12,       
  BusFault_IRQn                 = -11,       
  UsageFault_IRQn               = -10,       
  SVCall_IRQn                   = -5,        
  DebugMonitor_IRQn             = -4,        
  PendSV_IRQn                   = -2,        
  SysTick_IRQn                  = -1,        

 
  WDT_IRQn                      = 0,         
  TIMER0_IRQn                   = 1,         
  TIMER1_IRQn                   = 2,         
  TIMER2_IRQn                   = 3,         
  TIMER3_IRQn                   = 4,         
  UART0_IRQn                    = 5,         
  UART1_IRQn                    = 6,         
  UART2_IRQn                    = 7,         
  UART3_IRQn                    = 8,         
  PWM1_IRQn                     = 9,         
  I2C0_IRQn                     = 10,        
  I2C1_IRQn                     = 11,        
  I2C2_IRQn                     = 12,        
  SPI_IRQn                      = 13,        
  SSP0_IRQn                     = 14,        
  SSP1_IRQn                     = 15,        
  PLL0_IRQn                     = 16,        
  RTC_IRQn                      = 17,        
  EINT0_IRQn                    = 18,        
  EINT1_IRQn                    = 19,        
  EINT2_IRQn                    = 20,        
  EINT3_IRQn                    = 21,        
  ADC_IRQn                      = 22,        
  BOD_IRQn                      = 23,        
  USB_IRQn                      = 24,        
  CAN_IRQn                      = 25,        
  DMA_IRQn                      = 26,        
  I2S_IRQn                      = 27,        
  ENET_IRQn                     = 28,        
  RIT_IRQn                      = 29,        
  MCPWM_IRQn                    = 30,        
  QEI_IRQn                      = 31,        
  PLL1_IRQn                     = 32,        
  USBActivity_IRQn              = 33,        
  CANActivity_IRQn              = 34,        
} IRQn_Type;






 

 





#line 1 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"



















 




















































 

 
 
 
 
 
 
 
 


#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"
 
 





 









#line 25 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"

     







     










     











#line 260 "C:\\Keil\\ARM\\RV31\\INC\\stdint.h"



 


#line 86 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"

















 

#line 112 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"





 


 





 






 
typedef struct
{
  volatile uint32_t ISER[8];                       
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                       
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                       
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                       
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                       
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                       
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                          
}  NVIC_Type;


 
typedef struct
{
  volatile const  uint32_t CPUID;                         
  volatile uint32_t ICSR;                          
  volatile uint32_t VTOR;                          
  volatile uint32_t AIRCR;                         
  volatile uint32_t SCR;                           
  volatile uint32_t CCR;                           
  volatile uint8_t  SHP[12];                       
  volatile uint32_t SHCSR;                         
  volatile uint32_t CFSR;                          
  volatile uint32_t HFSR;                          
  volatile uint32_t DFSR;                          
  volatile uint32_t MMFAR;                         
  volatile uint32_t BFAR;                          
  volatile uint32_t AFSR;                          
  volatile const  uint32_t PFR[2];                        
  volatile const  uint32_t DFR;                           
  volatile const  uint32_t ADR;                           
  volatile const  uint32_t MMFR[4];                       
  volatile const  uint32_t ISAR[5];                       
} SCB_Type;


 
typedef struct
{
  volatile uint32_t CTRL;                          
  volatile uint32_t LOAD;                          
  volatile uint32_t VAL;                           
  volatile const  uint32_t CALIB;                         
} SysTick_Type;


 
typedef struct
{
  volatile  union  
  {
    volatile  uint8_t    u8;                        
    volatile  uint16_t   u16;                       
    volatile  uint32_t   u32;                       
  }  PORT [32];                                
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                           
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                           
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                           
       uint32_t RESERVED3[29];
  volatile uint32_t IWR;                           
  volatile uint32_t IRR;                           
  volatile uint32_t IMCR;                          
       uint32_t RESERVED4[43];
  volatile uint32_t LAR;                           
  volatile uint32_t LSR;                           
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                          
  volatile const  uint32_t PID5;
  volatile const  uint32_t PID6;
  volatile const  uint32_t PID7;
  volatile const  uint32_t PID0;
  volatile const  uint32_t PID1;
  volatile const  uint32_t PID2;
  volatile const  uint32_t PID3;
  volatile const  uint32_t CID0;
  volatile const  uint32_t CID1;
  volatile const  uint32_t CID2;
  volatile const  uint32_t CID3;
} ITM_Type;


 
typedef struct
{
       uint32_t RESERVED0;
  volatile const  uint32_t ICTR;                          



       uint32_t RESERVED1;

} InterruptType_Type;


 

typedef struct
{
  volatile const  uint32_t TYPE;                          
  volatile uint32_t CTRL;                          
  volatile uint32_t RNR;                           
  volatile uint32_t RBAR;                          
  volatile uint32_t RASR;                          
  volatile uint32_t RBAR_A1;                       
  volatile uint32_t RASR_A1;                       
  volatile uint32_t RBAR_A2;                       
  volatile uint32_t RASR_A2;                       
  volatile uint32_t RBAR_A3;                       
  volatile uint32_t RASR_A3;                       
} MPU_Type;



 
typedef struct
{
  volatile uint32_t DHCSR;                         
  volatile  uint32_t DCRSR;                         
  volatile uint32_t DCRDR;                         
  volatile uint32_t DEMCR;                         
} CoreDebug_Type;


 
#line 274 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"

#line 281 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"










 






#line 311 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"


 


 




#line 336 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"


 
 
 
 









 
extern uint32_t __get_PSP(void);









 
extern void __set_PSP(uint32_t topOfProcStack);









 
extern uint32_t __get_MSP(void);









 
extern void __set_MSP(uint32_t topOfMainStack);








 
extern uint32_t __REV16(uint16_t value);








 
extern int32_t __REVSH(int16_t value);


#line 502 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"









 









 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}








 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0x1ff);
}









 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}








 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}








 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}








 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}








 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}








 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}





#line 1044 "C:\\Keil\\ARM\\RV31\\INC\\core_cm3.h"



 













 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  
  reg_value  = ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                     
  reg_value &= ~((0xFFFFU << 16) | (0x0F << 8));                               
  reg_value  = ((reg_value | (0x5FA << 16) | (PriorityGroupTmp << 8)));   
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR = reg_value;
}









 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR >> 8) & 0x07);                                           
}









 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}









 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000) + 0x0100))->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}













 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 5)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)] = ((priority << (8 - 5)) & 0xff);    }         
}















 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 5)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)]           >> (8 - 5)));  }  
}
















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
 
  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}

















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
  
  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}



 



 














 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > ((1<<24) -1))  return (1);                                              

  ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD  =  (ticks & ((1<<24) -1)) - 1;                                       
  NVIC_SetPriority (SysTick_IRQn, (1<<5) - 1);                             
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL   =  (0x00);                                                               
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL = (1 << 2) | (1<<0) | (1<<1);  
  return (0);                                                                             
}







 








 
static __inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16) | (((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (0x700)) | (1<<2));  
  __dsb(0);                                                                                            
  while(1);                                                                             
}


 











 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (ch == '\n') ITM_SendChar('\r');
  
  if ((((CoreDebug_Type *) (0xE000EDF0))->DEMCR & (1 << 24))  &&
      (((ITM_Type *) (0xE0000000))->TCR & 1)                  &&
      (((ITM_Type *) (0xE0000000))->TER & (1UL << 0))  ) 
  {
    while (((ITM_Type *) (0xE0000000))->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000))->PORT[0].u8 = (uint8_t) ch;
  }  
  return (ch);
}







 
#line 97 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"
#line 1 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\system_LPC17xx.h"




















 









extern uint32_t SystemFrequency;     










 
extern void SystemInit (void);





#line 98 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"


 
 
 


#pragma anon_unions


 
typedef struct
{
  volatile uint32_t FLASHCFG;                
       uint32_t RESERVED0[31];
  volatile uint32_t PLL0CON;                 
  volatile uint32_t PLL0CFG;
  volatile const  uint32_t PLL0STAT;
  volatile  uint32_t PLL0FEED;
       uint32_t RESERVED1[4];
  volatile uint32_t PLL1CON;
  volatile uint32_t PLL1CFG;
  volatile const  uint32_t PLL1STAT;
  volatile  uint32_t PLL1FEED;
       uint32_t RESERVED2[4];
  volatile uint32_t PCON;
  volatile uint32_t PCONP;
       uint32_t RESERVED3[15];
  volatile uint32_t CCLKCFG;
  volatile uint32_t USBCLKCFG;
  volatile uint32_t CLKSRCSEL;
  volatile uint32_t	CANSLEEPCLR;
  volatile uint32_t	CANWAKEFLAGS;
       uint32_t RESERVED4[10];
  volatile uint32_t EXTINT;                  
       uint32_t RESERVED5;
  volatile uint32_t EXTMODE;
  volatile uint32_t EXTPOLAR;
       uint32_t RESERVED6[12];
  volatile uint32_t RSID;                    
       uint32_t RESERVED7[7];
  volatile uint32_t SCS;                     
  volatile uint32_t IRCTRIM;                 
  volatile uint32_t PCLKSEL0;
  volatile uint32_t PCLKSEL1;
       uint32_t RESERVED8[4];
  volatile uint32_t USBIntSt;                
  volatile uint32_t DMAREQSEL;
  volatile uint32_t CLKOUTCFG;               
 } LPC_SC_TypeDef;

 
typedef struct
{
  volatile uint32_t PINSEL0;
  volatile uint32_t PINSEL1;
  volatile uint32_t PINSEL2;
  volatile uint32_t PINSEL3;
  volatile uint32_t PINSEL4;
  volatile uint32_t PINSEL5;
  volatile uint32_t PINSEL6;
  volatile uint32_t PINSEL7;
  volatile uint32_t PINSEL8;
  volatile uint32_t PINSEL9;
  volatile uint32_t PINSEL10;
       uint32_t RESERVED0[5];
  volatile uint32_t PINMODE0;
  volatile uint32_t PINMODE1;
  volatile uint32_t PINMODE2;
  volatile uint32_t PINMODE3;
  volatile uint32_t PINMODE4;
  volatile uint32_t PINMODE5;
  volatile uint32_t PINMODE6;
  volatile uint32_t PINMODE7;
  volatile uint32_t PINMODE8;
  volatile uint32_t PINMODE9;
  volatile uint32_t PINMODE_OD0;
  volatile uint32_t PINMODE_OD1;
  volatile uint32_t PINMODE_OD2;
  volatile uint32_t PINMODE_OD3;
  volatile uint32_t PINMODE_OD4;
  volatile uint32_t I2CPADCFG;
} LPC_PINCON_TypeDef;

 
typedef struct
{
  union {
    volatile uint32_t FIODIR;
    struct {
      volatile uint16_t FIODIRL;
      volatile uint16_t FIODIRH;
    };
    struct {
      volatile uint8_t  FIODIR0;
      volatile uint8_t  FIODIR1;
      volatile uint8_t  FIODIR2;
      volatile uint8_t  FIODIR3;
    };
  };
  uint32_t RESERVED0[3];
  union {
    volatile uint32_t FIOMASK;
    struct {
      volatile uint16_t FIOMASKL;
      volatile uint16_t FIOMASKH;
    };
    struct {
      volatile uint8_t  FIOMASK0;
      volatile uint8_t  FIOMASK1;
      volatile uint8_t  FIOMASK2;
      volatile uint8_t  FIOMASK3;
    };
  };
  union {
    volatile uint32_t FIOPIN;
    struct {
      volatile uint16_t FIOPINL;
      volatile uint16_t FIOPINH;
    };
    struct {
      volatile uint8_t  FIOPIN0;
      volatile uint8_t  FIOPIN1;
      volatile uint8_t  FIOPIN2;
      volatile uint8_t  FIOPIN3;
    };
  };
  union {
    volatile uint32_t FIOSET;
    struct {
      volatile uint16_t FIOSETL;
      volatile uint16_t FIOSETH;
    };
    struct {
      volatile uint8_t  FIOSET0;
      volatile uint8_t  FIOSET1;
      volatile uint8_t  FIOSET2;
      volatile uint8_t  FIOSET3;
    };
  };
  union {
    volatile  uint32_t FIOCLR;
    struct {
      volatile  uint16_t FIOCLRL;
      volatile  uint16_t FIOCLRH;
    };
    struct {
      volatile  uint8_t  FIOCLR0;
      volatile  uint8_t  FIOCLR1;
      volatile  uint8_t  FIOCLR2;
      volatile  uint8_t  FIOCLR3;
    };
  };
} LPC_GPIO_TypeDef;

typedef struct
{
  volatile const  uint32_t IntStatus;
  volatile const  uint32_t IO0IntStatR;
  volatile const  uint32_t IO0IntStatF;
  volatile  uint32_t IO0IntClr;
  volatile uint32_t IO0IntEnR;
  volatile uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  volatile const  uint32_t IO2IntStatR;
  volatile const  uint32_t IO2IntStatF;
  volatile  uint32_t IO2IntClr;
  volatile uint32_t IO2IntEnR;
  volatile uint32_t IO2IntEnF;
} LPC_GPIOINT_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
       uint32_t RESERVED0[2];
  volatile uint32_t EMR;
       uint32_t RESERVED1[12];
  volatile uint32_t CTCR;
} LPC_TIM_TypeDef;

 
typedef struct
{
  volatile uint32_t IR;
  volatile uint32_t TCR;
  volatile uint32_t TC;
  volatile uint32_t PR;
  volatile uint32_t PC;
  volatile uint32_t MCR;
  volatile uint32_t MR0;
  volatile uint32_t MR1;
  volatile uint32_t MR2;
  volatile uint32_t MR3;
  volatile uint32_t CCR;
  volatile const  uint32_t CR0;
  volatile const  uint32_t CR1;
  volatile const  uint32_t CR2;
  volatile const  uint32_t CR3;
       uint32_t RESERVED0;
  volatile uint32_t MR4;
  volatile uint32_t MR5;
  volatile uint32_t MR6;
  volatile uint32_t PCR;
  volatile uint32_t LER;
       uint32_t RESERVED1[7];
  volatile uint32_t CTCR;
} LPC_PWM_TypeDef;

 
typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[7];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  volatile uint8_t  SCR;
       uint8_t  RESERVED3[3];
  volatile uint32_t ACR;
  volatile uint8_t  ICR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  FDR;
       uint8_t  RESERVED5[7];
  volatile uint8_t  TER;
       uint8_t  RESERVED6[39];
  volatile uint32_t FIFOLVL;
} LPC_UART_TypeDef;

typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[7];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  volatile uint8_t  SCR;
       uint8_t  RESERVED3[3];
  volatile uint32_t ACR;
  volatile uint8_t  ICR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  FDR;
       uint8_t  RESERVED5[7];
  volatile uint8_t  TER;
       uint8_t  RESERVED6[39];
  volatile uint32_t FIFOLVL;
} LPC_UART0_TypeDef;

typedef struct
{
  union {
  volatile const  uint8_t  RBR;
  volatile  uint8_t  THR;
  volatile uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  volatile uint8_t  DLM;
  volatile uint32_t IER;
  };
  union {
  volatile const  uint32_t IIR;
  volatile  uint8_t  FCR;
  };
  volatile uint8_t  LCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  MCR;
       uint8_t  RESERVED2[3];
  volatile const  uint8_t  LSR;
       uint8_t  RESERVED3[3];
  volatile const  uint8_t  MSR;
       uint8_t  RESERVED4[3];
  volatile uint8_t  SCR;
       uint8_t  RESERVED5[3];
  volatile uint32_t ACR;
       uint32_t RESERVED6;
  volatile uint32_t FDR;
       uint32_t RESERVED7;
  volatile uint8_t  TER;
       uint8_t  RESERVED8[27];
  volatile uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  volatile uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  volatile uint8_t  RS485DLY;
       uint8_t  RESERVED11[3];
  volatile uint32_t FIFOLVL;
} LPC_UART1_TypeDef;

 
typedef struct
{
  volatile uint32_t SPCR;
  volatile const  uint32_t SPSR;
  volatile uint32_t SPDR;
  volatile uint32_t SPCCR;
       uint32_t RESERVED0[3];
  volatile uint32_t SPINT;
} LPC_SPI_TypeDef;

 
typedef struct
{
  volatile uint32_t CR0;
  volatile uint32_t CR1;
  volatile uint32_t DR;
  volatile const  uint32_t SR;
  volatile uint32_t CPSR;
  volatile uint32_t IMSC;
  volatile uint32_t RIS;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t DMACR;
} LPC_SSP_TypeDef;

 
typedef struct
{
  volatile uint32_t I2CONSET;
  volatile const  uint32_t I2STAT;
  volatile uint32_t I2DAT;
  volatile uint32_t I2ADR0;
  volatile uint32_t I2SCLH;
  volatile uint32_t I2SCLL;
  volatile  uint32_t I2CONCLR;
  volatile uint32_t MMCTRL;
  volatile uint32_t I2ADR1;
  volatile uint32_t I2ADR2;
  volatile uint32_t I2ADR3;
  volatile const  uint32_t I2DATA_BUFFER;
  volatile uint32_t I2MASK0;
  volatile uint32_t I2MASK1;
  volatile uint32_t I2MASK2;
  volatile uint32_t I2MASK3;
} LPC_I2C_TypeDef;

 
typedef struct
{
  volatile uint32_t I2SDAO;
  volatile uint32_t I2SDAI;
  volatile  uint32_t I2STXFIFO;
  volatile const  uint32_t I2SRXFIFO;
  volatile const  uint32_t I2SSTATE;
  volatile uint32_t I2SDMA1;
  volatile uint32_t I2SDMA2;
  volatile uint32_t I2SIRQ;
  volatile uint32_t I2STXRATE;
  volatile uint32_t I2SRXRATE;
  volatile uint32_t I2STXBITRATE;
  volatile uint32_t I2SRXBITRATE;
  volatile uint32_t I2STXMODE;
  volatile uint32_t I2SRXMODE;
} LPC_I2S_TypeDef;

 
typedef struct
{
  volatile uint32_t RICOMPVAL;
  volatile uint32_t RIMASK;
  volatile uint8_t  RICTRL;
       uint8_t  RESERVED0[3];
  volatile uint32_t RICOUNTER;
} LPC_RIT_TypeDef;

 
typedef struct
{
  volatile uint8_t  ILR;
       uint8_t  RESERVED0[7];
  volatile uint8_t  CCR;
       uint8_t  RESERVED1[3];
  volatile uint8_t  CIIR;
       uint8_t  RESERVED2[3];
  volatile uint8_t  AMR;
       uint8_t  RESERVED3[3];
  volatile const  uint32_t CTIME0;
  volatile const  uint32_t CTIME1;
  volatile const  uint32_t CTIME2;
  volatile uint8_t  SEC;
       uint8_t  RESERVED4[3];
  volatile uint8_t  MIN;
       uint8_t  RESERVED5[3];
  volatile uint8_t  HOUR;
       uint8_t  RESERVED6[3];
  volatile uint8_t  DOM;
       uint8_t  RESERVED7[3];
  volatile uint8_t  DOW;
       uint8_t  RESERVED8[3];
  volatile uint16_t DOY;
       uint16_t RESERVED9;
  volatile uint8_t  MONTH;
       uint8_t  RESERVED10[3];
  volatile uint16_t YEAR;
       uint16_t RESERVED11;
  volatile uint32_t CALIBRATION;
  volatile uint32_t GPREG0;
  volatile uint32_t GPREG1;
  volatile uint32_t GPREG2;
  volatile uint32_t GPREG3;
  volatile uint32_t GPREG4;
  volatile uint8_t  RTC_AUXEN;
       uint8_t  RESERVED12[3];
  volatile uint8_t  RTC_AUX;
       uint8_t  RESERVED13[3];
  volatile uint8_t  ALSEC;
       uint8_t  RESERVED14[3];
  volatile uint8_t  ALMIN;
       uint8_t  RESERVED15[3];
  volatile uint8_t  ALHOUR;
       uint8_t  RESERVED16[3];
  volatile uint8_t  ALDOM;
       uint8_t  RESERVED17[3];
  volatile uint8_t  ALDOW;
       uint8_t  RESERVED18[3];
  volatile uint16_t ALDOY;
       uint16_t RESERVED19;
  volatile uint8_t  ALMON;
       uint8_t  RESERVED20[3];
  volatile uint16_t ALYEAR;
       uint16_t RESERVED21;
} LPC_RTC_TypeDef;

 
typedef struct
{
  volatile uint8_t  WDMOD;
       uint8_t  RESERVED0[3];
  volatile uint32_t WDTC;
  volatile  uint8_t  WDFEED;
       uint8_t  RESERVED1[3];
  volatile const  uint32_t WDTV;
  volatile uint32_t WDCLKSEL;
} LPC_WDT_TypeDef;

 
typedef struct
{
  volatile uint32_t ADCR;
  volatile uint32_t ADGDR;
       uint32_t RESERVED0;
  volatile uint32_t ADINTEN;
  volatile const  uint32_t ADDR0;
  volatile const  uint32_t ADDR1;
  volatile const  uint32_t ADDR2;
  volatile const  uint32_t ADDR3;
  volatile const  uint32_t ADDR4;
  volatile const  uint32_t ADDR5;
  volatile const  uint32_t ADDR6;
  volatile const  uint32_t ADDR7;
  volatile const  uint32_t ADSTAT;
  volatile uint32_t ADTRM;
} LPC_ADC_TypeDef;

 
typedef struct
{
  volatile uint32_t DACR;
  volatile uint32_t DACCTRL;
  volatile uint16_t DACCNTVAL;
} LPC_DAC_TypeDef;

 
typedef struct
{
  volatile const  uint32_t MCCON;
  volatile  uint32_t MCCON_SET;
  volatile  uint32_t MCCON_CLR;
  volatile const  uint32_t MCCAPCON;
  volatile  uint32_t MCCAPCON_SET;
  volatile  uint32_t MCCAPCON_CLR;
  volatile uint32_t MCTIM0;
  volatile uint32_t MCTIM1;
  volatile uint32_t MCTIM2;
  volatile uint32_t MCPER0;
  volatile uint32_t MCPER1;
  volatile uint32_t MCPER2;
  volatile uint32_t MCPW0;
  volatile uint32_t MCPW1;
  volatile uint32_t MCPW2;
  volatile uint32_t MCDEADTIME;
  volatile uint32_t MCCCP;
  volatile uint32_t MCCR0;
  volatile uint32_t MCCR1;
  volatile uint32_t MCCR2;
  volatile const  uint32_t MCINTEN;
  volatile  uint32_t MCINTEN_SET;
  volatile  uint32_t MCINTEN_CLR;
  volatile const  uint32_t MCCNTCON;
  volatile  uint32_t MCCNTCON_SET;
  volatile  uint32_t MCCNTCON_CLR;
  volatile const  uint32_t MCINTFLAG;
  volatile  uint32_t MCINTFLAG_SET;
  volatile  uint32_t MCINTFLAG_CLR;
  volatile  uint32_t MCCAP_CLR;
} LPC_MCPWM_TypeDef;

 
typedef struct
{
  volatile  uint32_t QEICON;
  volatile const  uint32_t QEISTAT;
  volatile uint32_t QEICONF;
  volatile const  uint32_t QEIPOS;
  volatile uint32_t QEIMAXPOS;
  volatile uint32_t CMPOS0;
  volatile uint32_t CMPOS1;
  volatile uint32_t CMPOS2;
  volatile const  uint32_t INXCNT;
  volatile uint32_t INXCMP;
  volatile uint32_t QEILOAD;
  volatile const  uint32_t QEITIME;
  volatile const  uint32_t QEIVEL;
  volatile const  uint32_t QEICAP;
  volatile uint32_t VELCOMP;
  volatile uint32_t FILTER;
       uint32_t RESERVED0[998];
  volatile  uint32_t QEIIEC;
  volatile  uint32_t QEIIES;
  volatile const  uint32_t QEIINTSTAT;
  volatile const  uint32_t QEIIE;
  volatile  uint32_t QEICLR;
  volatile  uint32_t QEISET;
} LPC_QEI_TypeDef;

 
typedef struct
{
  volatile uint32_t mask[512];               
} LPC_CANAF_RAM_TypeDef;

typedef struct                           
{
  volatile uint32_t AFMR;
  volatile uint32_t SFF_sa;
  volatile uint32_t SFF_GRP_sa;
  volatile uint32_t EFF_sa;
  volatile uint32_t EFF_GRP_sa;
  volatile uint32_t ENDofTable;
  volatile const  uint32_t LUTerrAd;
  volatile const  uint32_t LUTerr;
  volatile uint32_t FCANIE;
  volatile uint32_t FCANIC0;
  volatile uint32_t FCANIC1;
} LPC_CANAF_TypeDef;

typedef struct                           
{
  volatile const  uint32_t CANTxSR;
  volatile const  uint32_t CANRxSR;
  volatile const  uint32_t CANMSR;
} LPC_CANCR_TypeDef;

typedef struct                           
{
  volatile uint32_t MOD;
  volatile  uint32_t CMR;
  volatile uint32_t GSR;
  volatile const  uint32_t ICR;
  volatile uint32_t IER;
  volatile uint32_t BTR;
  volatile uint32_t EWL;
  volatile const  uint32_t SR;
  volatile uint32_t RFS;
  volatile uint32_t RID;
  volatile uint32_t RDA;
  volatile uint32_t RDB;
  volatile uint32_t TFI1;
  volatile uint32_t TID1;
  volatile uint32_t TDA1;
  volatile uint32_t TDB1;
  volatile uint32_t TFI2;
  volatile uint32_t TID2;
  volatile uint32_t TDA2;
  volatile uint32_t TDB2;
  volatile uint32_t TFI3;
  volatile uint32_t TID3;
  volatile uint32_t TDA3;
  volatile uint32_t TDB3;
} LPC_CAN_TypeDef;

 
typedef struct                           
{
  volatile const  uint32_t DMACIntStat;
  volatile const  uint32_t DMACIntTCStat;
  volatile  uint32_t DMACIntTCClear;
  volatile const  uint32_t DMACIntErrStat;
  volatile  uint32_t DMACIntErrClr;
  volatile const  uint32_t DMACRawIntTCStat;
  volatile const  uint32_t DMACRawIntErrStat;
  volatile const  uint32_t DMACEnbldChns;
  volatile uint32_t DMACSoftBReq;
  volatile uint32_t DMACSoftSReq;
  volatile uint32_t DMACSoftLBReq;
  volatile uint32_t DMACSoftLSReq;
  volatile uint32_t DMACConfig;
  volatile uint32_t DMACSync;
} LPC_GPDMA_TypeDef;

typedef struct                           
{
  volatile uint32_t DMACCSrcAddr;
  volatile uint32_t DMACCDestAddr;
  volatile uint32_t DMACCLLI;
  volatile uint32_t DMACCControl;
  volatile uint32_t DMACCConfig;
} LPC_GPDMACH_TypeDef;

 
typedef struct
{
  volatile const  uint32_t HcRevision;              
  volatile uint32_t HcControl;
  volatile uint32_t HcCommandStatus;
  volatile uint32_t HcInterruptStatus;
  volatile uint32_t HcInterruptEnable;
  volatile uint32_t HcInterruptDisable;
  volatile uint32_t HcHCCA;
  volatile const  uint32_t HcPeriodCurrentED;
  volatile uint32_t HcControlHeadED;
  volatile uint32_t HcControlCurrentED;
  volatile uint32_t HcBulkHeadED;
  volatile uint32_t HcBulkCurrentED;
  volatile const  uint32_t HcDoneHead;
  volatile uint32_t HcFmInterval;
  volatile const  uint32_t HcFmRemaining;
  volatile const  uint32_t HcFmNumber;
  volatile uint32_t HcPeriodicStart;
  volatile uint32_t HcLSTreshold;
  volatile uint32_t HcRhDescriptorA;
  volatile uint32_t HcRhDescriptorB;
  volatile uint32_t HcRhStatus;
  volatile uint32_t HcRhPortStatus1;
  volatile uint32_t HcRhPortStatus2;
       uint32_t RESERVED0[40];
  volatile const  uint32_t Module_ID;

  volatile const  uint32_t OTGIntSt;                
  volatile uint32_t OTGIntEn;
  volatile  uint32_t OTGIntSet;
  volatile  uint32_t OTGIntClr;
  volatile uint32_t OTGStCtrl;
  volatile uint32_t OTGTmr;
       uint32_t RESERVED1[58];

  volatile const  uint32_t USBDevIntSt;             
  volatile uint32_t USBDevIntEn;
  volatile  uint32_t USBDevIntClr;
  volatile  uint32_t USBDevIntSet;

  volatile  uint32_t USBCmdCode;              
  volatile const  uint32_t USBCmdData;

  volatile const  uint32_t USBRxData;               
  volatile  uint32_t USBTxData;
  volatile const  uint32_t USBRxPLen;
  volatile  uint32_t USBTxPLen;
  volatile uint32_t USBCtrl;
  volatile  uint32_t USBDevIntPri;

  volatile const  uint32_t USBEpIntSt;              
  volatile uint32_t USBEpIntEn;
  volatile  uint32_t USBEpIntClr;
  volatile  uint32_t USBEpIntSet;
  volatile  uint32_t USBEpIntPri;

  volatile uint32_t USBReEp;                 
  volatile  uint32_t USBEpInd;
  volatile uint32_t USBMaxPSize;

  volatile const  uint32_t USBDMARSt;               
  volatile  uint32_t USBDMARClr;
  volatile  uint32_t USBDMARSet;
       uint32_t RESERVED2[9];
  volatile uint32_t USBUDCAH;
  volatile const  uint32_t USBEpDMASt;
  volatile  uint32_t USBEpDMAEn;
  volatile  uint32_t USBEpDMADis;
  volatile const  uint32_t USBDMAIntSt;
  volatile uint32_t USBDMAIntEn;
       uint32_t RESERVED3[2];
  volatile const  uint32_t USBEoTIntSt;
  volatile  uint32_t USBEoTIntClr;
  volatile  uint32_t USBEoTIntSet;
  volatile const  uint32_t USBNDDRIntSt;
  volatile  uint32_t USBNDDRIntClr;
  volatile  uint32_t USBNDDRIntSet;
  volatile const  uint32_t USBSysErrIntSt;
  volatile  uint32_t USBSysErrIntClr;
  volatile  uint32_t USBSysErrIntSet;
       uint32_t RESERVED4[15];

  union {
  volatile const  uint32_t I2C_RX;                  
  volatile  uint32_t I2C_TX;
  };
  volatile const  uint32_t I2C_STS;
  volatile uint32_t I2C_CTL;
  volatile uint32_t I2C_CLKHI;
  volatile  uint32_t I2C_CLKLO;
       uint32_t RESERVED5[824];

  union {
  volatile uint32_t USBClkCtrl;              
  volatile uint32_t OTGClkCtrl;
  };
  union {
  volatile const  uint32_t USBClkSt;
  volatile const  uint32_t OTGClkSt;
  };
} LPC_USB_TypeDef;

 
typedef struct
{
  volatile uint32_t MAC1;                    
  volatile uint32_t MAC2;
  volatile uint32_t IPGT;
  volatile uint32_t IPGR;
  volatile uint32_t CLRT;
  volatile uint32_t MAXF;
  volatile uint32_t SUPP;
  volatile uint32_t TEST;
  volatile uint32_t MCFG;
  volatile uint32_t MCMD;
  volatile uint32_t MADR;
  volatile  uint32_t MWTD;
  volatile const  uint32_t MRDD;
  volatile const  uint32_t MIND;
       uint32_t RESERVED0[2];
  volatile uint32_t SA0;
  volatile uint32_t SA1;
  volatile uint32_t SA2;
       uint32_t RESERVED1[45];
  volatile uint32_t Command;                 
  volatile const  uint32_t Status;
  volatile uint32_t RxDescriptor;
  volatile uint32_t RxStatus;
  volatile uint32_t RxDescriptorNumber;
  volatile const  uint32_t RxProduceIndex;
  volatile uint32_t RxConsumeIndex;
  volatile uint32_t TxDescriptor;
  volatile uint32_t TxStatus;
  volatile uint32_t TxDescriptorNumber;
  volatile uint32_t TxProduceIndex;
  volatile const  uint32_t TxConsumeIndex;
       uint32_t RESERVED2[10];
  volatile const  uint32_t TSV0;
  volatile const  uint32_t TSV1;
  volatile const  uint32_t RSV;
       uint32_t RESERVED3[3];
  volatile uint32_t FlowControlCounter;
  volatile const  uint32_t FlowControlStatus;
       uint32_t RESERVED4[34];
  volatile uint32_t RxFilterCtrl;            
  volatile uint32_t RxFilterWoLStatus;
  volatile uint32_t RxFilterWoLClear;
       uint32_t RESERVED5;
  volatile uint32_t HashFilterL;
  volatile uint32_t HashFilterH;
       uint32_t RESERVED6[882];
  volatile const  uint32_t IntStatus;               
  volatile uint32_t IntEnable;
  volatile  uint32_t IntClear;
  volatile  uint32_t IntSet;
       uint32_t RESERVED7;
  volatile uint32_t PowerDown;
       uint32_t RESERVED8;
  volatile uint32_t Module_ID;
} LPC_EMAC_TypeDef;


#pragma no_anon_unions



 
 
 
 
#line 924 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"

 
#line 945 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"

 
#line 959 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"

 
#line 972 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"

 







 
 
 
#line 1031 "C:\\Keil\\ARM\\INC\\NXP\\LPC17xx\\LPC17xx.h"

#line 13 "src\\file_system\\MSD_SD_File.c"
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



 
#line 14 "src\\file_system\\MSD_SD_File.c"
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



 
#line 15 "src\\file_system\\MSD_SD_File.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"
 
 
 




 
 



 












  


 








#line 45 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


  
  typedef unsigned int size_t;










    



    typedef unsigned short wchar_t;  
#line 74 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { __int64 quot, rem; } lldiv_t;
    


#line 95 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"
   



 

   




 
#line 114 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) __int64 atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) __int64 strtoll(const char * __restrict  ,
                               char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned __int64 strtoull(const char * __restrict  ,
                                         char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 414 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 502 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 531 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"

extern __declspec(__nothrow) __pure int abs(int  );
   



 

extern __declspec(__nothrow) __pure div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __pure long int labs(long int  );
   



 




extern __declspec(__nothrow) __pure ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __pure __int64 llabs(__int64  );
   



 




extern __declspec(__nothrow) __pure lldiv_t lldiv(__int64  , __int64  );
   











 
#line 612 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"



 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __pure __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __pure __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 



 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 866 "C:\\Keil\\ARM\\RV31\\INC\\stdlib.h"


 
#line 16 "src\\file_system\\MSD_SD_File.c"
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



 
#line 17 "src\\file_system\\MSD_SD_File.c"
#line 1 ".\\inc\\file_system\\MSD_SD_File.h"








 




#line 1 ".\\inc\\tcpip\\tcpip.h"



#line 5 ".\\inc\\tcpip\\tcpip.h"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\Net_Config.h"









 




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





 
#line 18 "src\\file_system\\MSD_SD_File.c"
#line 1 ".\\inc\\touch.h"




#line 6 ".\\inc\\touch.h"
#line 1 ".\\inc\\adc.h"















 



#line 21 ".\\inc\\adc.h"

#line 30 ".\\inc\\adc.h"







		
#line 46 ".\\inc\\adc.h"


											
 
typedef struct 
{
	volatile float valor_normal; 										 
	float parc_leitura[ 20 ];		   
	float media_leitura;										 
	float cal;
	char  qtd_acima_media;									 
	char  qtd_abaixo_media;									 
	volatile unsigned int   debounce;								
	char  qtd_acima_val_normal;							 
	char  qtd_abaixo_val_normal;						 
						 
}	CAPTOUCH;

 
typedef struct
{
	volatile char k_press[2];
	volatile char rf_state;
	char placa_dimmer;

} DEVICE;

	
 
extern DEVICE DEV[4];
extern CAPTOUCH CT[ 6 ];
extern char CT_enable;
extern char CT_channel_num;	
extern unsigned int  CT_tmr_to_read;

extern char calIr[8][10];				  											
	
 				 	
void CT_Cheky_Press (char channelNum, CAPTOUCH *CT);

uint16_t _ADC_ReadCh0(void);
uint16_t _ADC_ReadCh1(void);
uint16_t _ADC_ReadCh2(void);
uint16_t _ADC_ReadCh3(void);
uint16_t _ADC_ReadCh4(void);
uint16_t _ADC_ReadCh5(void);
uint16_t _ADC_ReadCh6(void);
uint16_t _ADC_ReadCh7(void);

void init_adc(void); 
void CT_Varredura (void);


	






 


 


 


#line 123 ".\\inc\\adc.h"

 









         


 
 
 









#line 155 ".\\inc\\adc.h"






 
 
 









#line 179 ".\\inc\\adc.h"






 
 
 











#line 205 ".\\inc\\adc.h"







 
 
 









#line 230 ".\\inc\\adc.h"







 
 
 










#line 256 ".\\inc\\adc.h"






 
 
 









#line 280 ".\\inc\\adc.h"






 
 
 









#line 304 ".\\inc\\adc.h"







 
 
 









#line 329 ".\\inc\\adc.h"






 
typedef enum {

        CH0 = 0,


        CH1,


        CH2,


        CH3,


        CH4,


        CH5,
#line 361 ".\\inc\\adc.h"
        NUM_CHANNELS,
        UNUSED_CHANNEL
} ChannelIdType;























  





 
#line 7 ".\\inc\\touch.h"






















 



 














typedef union _IR_STATE
{
	U8 all;
	struct _IR_STATE_bits
	{
	  	U8 PwrPainel		:1;
		U8 PwrAr			:1;
		U8 PwrTv			:1;
		U8 PwrHome			:1;
		U8 PlayPause		:1;
		U8 ArSwing			:1;
		U8 :1;
	}bit;
} IR_STATE;


enum
{
	TOUCH_0 = 0u,	TOUCH_1, TOUCH_2, TOUCH_3,
	TOUCH_4,		TOUCH_5, TOUCH_6, TOUCH_7,
	TOUCH_8,		TOUCH_9, TOUCH_10, TOUCH_11,
	TOUCH_12,		TOUCH_13, TOUCH_14, TOUCH_15,
	TOUCH_16, 		TOUCH_17, TOUCH_18, TOUCH_19,
	TOUCH_20,		TOUCH_21, TOUCH_22, TOUCH_23
};

enum
{
	TOUCH_SCENE_0 = TOUCH_16,
	TOUCH_SCENE_1 = TOUCH_18,
	TOUCH_SCENE_2 = TOUCH_20,
	TOUCH_SCENE_3 = TOUCH_22,
	NUM_SCENE    = 4u	  
};

enum
{
	BEEP_PULSO = 0u,
	BEEP_CFG,
	BEEP_CHAMADA,
	BEEP_ERROR,
};


enum
{
	num16 = 0u,	num17,	num18,	num19,	
	num20,		num21,	num22,	num23,	key_none		
};

 
typedef union _KEY_STATE
{
	uint16_t all;
	struct
	{
		uint16_t pressed :1;

	} key;
}KEY_STATE;

extern KEY_STATE key_state;

extern IR_STATE ir_state; 

extern char temp_ar;

extern int touchEnaDis;
extern char strTouchEnaDis[20];
extern char aux_scene[30];
extern char current_scene[30];
extern char current_id_scene;
extern char scene[NUM_SCENE][30];
extern char touch_led_press;

extern int debounce_press;
extern int debounce_release;


void init_touch(void);
char read_touch(void);

void init_scene(char modo);
void show_all_scene(void);
char save_scene(char *_scene,char addr);

char read_scene(char addr,char *file);
char get_touch(void);
void touch_task(void);
void exe_scene(char num_scene);
void key_task(void);
void beep(char modo);




 
#line 19 "src\\file_system\\MSD_SD_File.c"
#line 1 ".\\inc\\timer.h"















 



#line 21 ".\\inc\\timer.h"
	





extern U8 tick;
extern U8 tick_10ms;
extern U8 tick_50ms;
extern U8 tick_30ms;
extern U64 timer1_counter;
extern U64 timer0_counter;

void timer_poll (void);
void delayMs(uint8_t timer_num, uint32_t delayInMs);
void init_timer(void); 

void enable_timer( uint8_t timer_num );
void disable_timer( uint8_t timer_num );
void reset_timer( uint8_t timer_num );
void TIMER0_IRQHandler (void);
void TIMER1_IRQHandler (void);




 
#line 20 "src\\file_system\\MSD_SD_File.c"
#line 1 ".\\inc\\Hardware_Profile.h"















 




#line 22 ".\\inc\\Hardware_Profile.h"

								 
 
#line 31 ".\\inc\\Hardware_Profile.h"

 
#line 39 ".\\inc\\Hardware_Profile.h"

 
#line 47 ".\\inc\\Hardware_Profile.h"

 
#line 55 ".\\inc\\Hardware_Profile.h"

 
#line 63 ".\\inc\\Hardware_Profile.h"

 





























#line 111 ".\\inc\\Hardware_Profile.h"








 
















#line 144 ".\\inc\\Hardware_Profile.h"


 









 

 





 




 










 









						






						
 



										 													 
 







#line 217 ".\\inc\\Hardware_Profile.h"











#line 236 ".\\inc\\Hardware_Profile.h"


 

 










	







													












					


 






				  	



#line 21 "src\\file_system\\MSD_SD_File.c"
#line 1 ".\\inc\\uart.h"













 













 
enum 
{
	ERROR_COMMAND = 0u,			
	ERROR_ADDR_UTILIZAD,		
	ERROR_FILE_NOT_FOUND,		
	ERROR_TIMEOUT, 				
	ERROR_RECEIVER_IR,		   	
	ERROR_OVERFLOW_PULSES_IR,	
	ERROR_OVERFLOW_FLASH,		
	ERROR_PARAMETER,		   	
	ERROR_ADDR_OVERFLOW,		
	ERROR_READ,					
	ERROR_IR_NOT_SEND,			
	ERROR_NOT_SAVED,			
	ERROR_NOT_EXIST_NAME,		
	ERROR_IR_NOT_EXIST,			
	ERROR_SD,					
	NO_ERROR,					
};



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








#line 22 "src\\file_system\\MSD_SD_File.c"

ST_FILES cfg;

WORD_VAL word_val;


char type_dim0[3u];
char type_dim1[3u];
char type_dim2[3u];



 
char init_msd (void) 
{
  	U32 retv;

	printf("[Iniciando sd card]");
  	while ((retv = finit (0)) != 0) 
	{            
    	if (retv == 1) 
		{
      		printf ("...[erro]\r\r");
			return 0x01;
    	}else 
		{
      		printf ("...[nao formatado]\r\r");
			return 0x02;
    	}
  	}
	printf("...[ok]\r\r");
	fflush((& __stdout));
	return 0x00;
}



 
void read_file_cfg(void)
{
	FILE *f;
	

 
	printf("[Open file %s]...","cfg.cfg\0");
	fflush((& __stdout));
	f = fopen("cfg.cfg\0","r");
	if(f == 0)
	{	 
		printf("[not found]\r");
		fflush((& __stdout));
		strcpy(cfg.file.mode_func_ar,"0\0");	
		strcpy(cfg.file.func_ir_scene,"0\0");

		strcpy(type_dim0,"1\0");
		strcpy(type_dim0,"1\0");
		strcpy(type_dim0,"1\0");

		strcpy(strTouchEnaDis,"16777215\0");		
	
	}else
	{
		fclose(f);
		printf("[ok]\r");
		fflush((& __stdout));
		fread_line(cfg.file.mode_func_ar, "cfg.cfg\0", LINE_MODE_FUNC_AR);
		fread_line(cfg.file.func_ir_scene, "cfg.cfg\0", LINE_FUNC_IR_SCENE);

		fread_line(type_dim0, "cfg.cfg\0", LINE_TYPE_DIM0);
		fread_line(type_dim1, "cfg.cfg\0", LINE_TYPE_DIM1);
		fread_line(type_dim2, "cfg.cfg\0", LINE_TYPE_DIM2);

		fread_line(strTouchEnaDis, "cfg.cfg\0", LINE_ENA_DIS_TOUCH);
		
		 
		if(!cfg.file.mode_func_ar[0])
			strcpy(cfg.file.mode_func_ar,"0\0"); 

		if(!cfg.file.func_ir_scene[0])
			strcpy(cfg.file.func_ir_scene,"0\0"); 

		if(!type_dim0[0])
			strcpy(type_dim0,"1\0"); 

		if(!type_dim1[0])
			strcpy(type_dim1,"1\0");

		if(!type_dim2[0])
			strcpy(type_dim2,"1\0");
			 
		if(!strTouchEnaDis[0])
			strcpy(strTouchEnaDis,"16777215\0");	
	}
	
	touchEnaDis = atoi(strTouchEnaDis);	
}


 
void read_cfg_tcp(void)
{
	char nibble_lsb=0,nibble_msb=0,i,x,j;
	FILE *f;

	

 
	printf("[Open file %s]...","tcp.cfg\0");
	fflush((& __stdout));
	f = fopen("tcp.cfg\0","r");
	if(f == 0)
	{	 
		printf("[not found]\r");
		fflush((& __stdout));





















		
		
		
		
		strcpy(cfg.tcp.static_ip,"192.168.0.2\0");
		strcpy(cfg.tcp.ip_serv_rem,"192.168.0.1\0");
		strcpy(cfg.tcp.port_serv_rem,"5004\0");
		strcpy(cfg.tcp.interval_packet_serv,"5\0");
		strcpy(cfg.tcp.host_name,"MOTEL\0");
		strcpy(cfg.tcp.port_serv_loc,"5002\0");
		strcpy(cfg.tcp.port_udp,"5000\0");
		
		sprintf(cfg.tcp.mac,"%02X.%02X.%02X.%02X.%02X.%02X\0",own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);
		strcpy(cfg.tcp.ip_app,"192.168.0.1\0");
		strcpy(cfg.tcp.mask,"255.255.255.0\0");
		strcpy(cfg.tcp.gateway,"192.168.0.1\0");

		 
	}else
	{
		fclose(f);
		printf("[ok]\r");
		fflush((& __stdout));
		fread_line(cfg.tcp.static_ip, "tcp.cfg\0", LINE_STATIC_IP);
		fread_line(cfg.tcp.ip_serv_rem, "tcp.cfg\0", LINE_IP_SERV_REM);
		fread_line(cfg.tcp.port_serv_rem, "tcp.cfg\0", LINE_PORT_SERV_REM);
		fread_line(cfg.tcp.interval_packet_serv, "tcp.cfg\0", LINE_INTERVAL_PACKET_SERV);
		fread_line(cfg.tcp.host_name, "tcp.cfg\0", LINE_HOST_NAME);
		fread_line(cfg.tcp.port_serv_loc, "tcp.cfg\0", LINE_PORT_SERV_LOC);
		fread_line(cfg.tcp.port_udp, "tcp.cfg\0", LINE_PORT_UDP);
		fread_line(cfg.tcp.mac, "tcp.cfg\0", LINE_MAC);
		fread_line(cfg.tcp.ip_app, "tcp.cfg\0", LINE_IP_APP);
		fread_line(cfg.tcp.mask, "tcp.cfg\0", LINE_MASK);
		fread_line(cfg.tcp.gateway, "tcp.cfg\0", LINE_GATEWAY);

		 
		for(i=0,x=0;x<6;i+=2,x++)
		{
			cfg.tcp.mac[i]   = tolower(cfg.tcp.mac[i]);
			cfg.tcp.mac[i+1] = tolower(cfg.tcp.mac[i+1]);

			nibble_msb = (cfg.tcp.mac[i]   >= 'a' && cfg.tcp.mac[i]   <= 'f') ? cfg.tcp.mac[i]   - 87 : cfg.tcp.mac[i]   - 48;
			nibble_lsb = (cfg.tcp.mac[i+1] >= 'a' && cfg.tcp.mac[i+1] <= 'f') ? cfg.tcp.mac[i+1] - 87 : cfg.tcp.mac[i+1] - 48;

			own_hw_adr[x] = 0;
			for(j=0;j<4;j++)	
				if(nibble_lsb & (1<<j))
					own_hw_adr[x] |= (1<<j);

			for(j=4;j<8;j++)	
				if(nibble_msb & (1<<j-4))
					own_hw_adr[x] |= (1<<j);





		}

		 
		if(!cfg.tcp.static_ip[0]){ printf("[Static IP empty. Loading default]\r");
			strcpy(cfg.tcp.static_ip,"192.168.0.2\0"); }
			
		if(!cfg.tcp.ip_serv_rem[0]){ printf("[IP server remote empty. Loading default]\r");			
			strcpy(cfg.tcp.ip_serv_rem,"192.168.0.1\0"); }

		if(!cfg.tcp.port_serv_rem[0]){ printf("[Port server remote empty. Loading default]\r");
			strcpy(cfg.tcp.port_serv_rem,"5004\0"); }

		if(!cfg.tcp.interval_packet_serv[0]){ printf("[Interval packet empty. Loading default]\r");
			strcpy(cfg.tcp.interval_packet_serv,"5\0"); }

		if(!cfg.tcp.host_name[0]){ printf("[Host Name empty. Loading default]\r");
			strcpy(cfg.tcp.host_name,"MOTEL\0"); }

		if(!cfg.tcp.port_serv_loc[0]) { printf("[Port server local empty. Loading default]\r");
			strcpy(cfg.tcp.port_serv_loc,"5002\0"); }

		if(!cfg.tcp.port_udp[0]){ printf("[Port udp empty. Loading default]\r");
			strcpy(cfg.tcp.port_udp,"5000\0"); }

		if(!cfg.tcp.mac[0]){ printf("[Mac empty. Loading default]\r");
			strcpy(cfg.tcp.mac,(const char*)own_hw_adr); }

		if(!cfg.tcp.ip_app[0]){ printf("[IP app empty. Loading default]\r");
			strcpy(cfg.tcp.ip_app,"192.168.0.1\0"); }

		if(!cfg.tcp.mask[0]){ printf("[Mask empty. Loading default]\r");
			strcpy(cfg.tcp.mask,"255.255.255.0\0"); }

		if(!cfg.tcp.gateway[0]){ printf("[Gateway empty. Loading default]\r");
			strcpy(cfg.tcp.gateway,"192.168.0.1\0"); }

		fflush((& __stdout));
	}
}


 
void init_file(void)
{	
	read_cfg_tcp();

	read_file_cfg();


	printf("[Server Port Local: %s]\r",cfg.tcp.port_serv_loc);



	printf("[Server IP: %s]\r",cfg.tcp.ip_serv_rem);
	printf("[Server Port Remoto: %s]\r",cfg.tcp.port_serv_rem);

	printf("[Interval Packet: %ss]\r",cfg.tcp.interval_packet_serv);




	printf("[Port UDP: %s]\r",cfg.tcp.port_udp);

	
	printf("[Static IP: %s]\r",cfg.tcp.static_ip);
	printf("[Static Mask: %s]\r",cfg.tcp.mask);
	printf("[Static Gateway: %s]\r",cfg.tcp.gateway); 
	printf("[Host name: %s]\r",cfg.tcp.host_name);
	printf("[MAC: %s..%02X.%02X.%02X.%02X.%02X.%02X]\r",cfg.tcp.mac,own_hw_adr[0],own_hw_adr[1],own_hw_adr[2],own_hw_adr[3],own_hw_adr[4],own_hw_adr[5]);	
	printf("[IP Aplica��o: %s]\r",cfg.tcp.ip_app);	
	printf("[Enable/Disable Touch: 0x%X]\r",touchEnaDis);
	printf("[Mode Ar: Swing %s]\r\r",(atoi(cfg.file.mode_func_ar)) ? "In" : "Out");
	
	printf("[Func IR Scene: %s]\r",(atoi(cfg.file.func_ir_scene)) ? "Enable" : "Disable");

	printf("[Type Out Dimmer: 0:%s..1:%s..2:%s]\r\r",atoi(type_dim0) ? "DIMMER":"ONOFF", 
		atoi(type_dim1) ? "DIMMER":"ONOFF", 
		atoi(type_dim2) ? "DIMMER":"ONOFF");
	
	fflush((& __stdout));
}



 
void file_task (void) 
{
	static U8 flag_sd_inserido = 1,flag_read_sd = 0, cnt_init_sd=0;
	static U16 cnt_type_dim=0; 
	char str[15][20],i,j;	

	if(!tick)
		return;

	if(!(++cnt_type_dim % 300))
	{
		sprintf(buf_tx,"TDI %u %u %u!\0", atoi(type_dim0), atoi(type_dim1), atoi(type_dim2)); 
		uart_putString(2,buf_tx);
	}

	if(flag_read_sd)
	{
		flag_read_sd = 0;
		init_scene(0xFF);					 
	
		for(i=0;i<15;i++)
			memset(str[i],0,sizeof(str[i]));
		 
	
		strcpy(str[0],cfg.tcp.static_ip);
		strcpy(str[1],cfg.tcp.ip_serv_rem);
		strcpy(str[2],cfg.tcp.port_serv_rem);
		strcpy(str[3],cfg.tcp.interval_packet_serv);
		strcpy(str[4],cfg.tcp.host_name);
		strcpy(str[5],cfg.tcp.port_serv_loc);
		strcpy(str[6],cfg.tcp.port_udp);
		strcpy(str[7],cfg.tcp.mac);
		strcpy(str[8],cfg.tcp.ip_app);
		strcpy(str[9],cfg.tcp.mask);
		strcpy(str[10],cfg.tcp.gateway);

		for(i=0;i<15;i++)
			for(j=0;j<20;j++)
				if(str[i][j] == '\r' || str[i][j] == '\n')
					str[i][j] = 0;	
















		read_cfg_tcp();	 















		 
		if(strcmp(str[0],cfg.tcp.static_ip)            || strcmp(str[1],cfg.tcp.ip_serv_rem) || strcmp(str[2],cfg.tcp.port_serv_rem) || 
		   strcmp(str[3],cfg.tcp.interval_packet_serv) || strcmp(str[4],cfg.tcp.host_name)   || strcmp(str[5],cfg.tcp.port_serv_loc) || 
		   strcmp(str[6],cfg.tcp.port_udp)             || strcmp(str[7],cfg.tcp.mac)         || strcmp(str[8],cfg.tcp.ip_app)        ||
		   strcmp(str[9],cfg.tcp.mask)                 || strcmp(str[10],cfg.tcp.gateway))
		{
			printf ("[TCP Config via SD..Reiniciando]\r\r");
			fflush((& __stdout));
			((LPC_WDT_TypeDef *) ((0x40000000UL) + 0x00000) )->WDTC = 0x003FFFF;	 
			((LPC_WDT_TypeDef *) ((0x40000000UL) + 0x00000) )->WDFEED = 0xAA; ((LPC_WDT_TypeDef *) ((0x40000000UL) + 0x00000) )->WDFEED = 0x55;;
			while(1);
		}

		read_file_cfg();	
	}else
	{
		if(!(((LPC_GPIO_TypeDef *) ((0x2009C000UL) + 0x00020) )->FIOPIN & (1 << 25)))	 
		{
			if(!flag_sd_inserido)
			{
				if(++cnt_init_sd >= 20)			 
				{
					flag_sd_inserido = 1;
					cnt_init_sd = 0;			  
					printf("[SD Card Inserido]\r");
					beep(BEEP_CFG);
					fflush((& __stdout)); 
					init_msd();					 
					flag_read_sd = 1;
				}	
			}
		}else
		{
			if(flag_sd_inserido)
			{ 
				flag_sd_inserido = 0;
				printf("[SD Card Retirado]\r");
				fflush((& __stdout));
				beep(BEEP_ERROR); 
			}
		}
	}
}












 
 char fread_line(char *ptr, const char *file, char num_line)
{
	FILE *f;
	char cur_line = 0;
 	int ch;

	f = fopen(file,"r");
	if(f == 0)	
		return 1;
	else
	{
		for(;;)
		{
			ch = fgetc(f);

			if(ch == (-1))
			{
				fclose(f);
				return 1;
			}

			if((cur_line == num_line) && (ch != '\r') && (ch != '\n'))
			{
				*ptr = ch;
				ptr++;
			}

			if(ch == '\n')
			{
				*ptr = '\0';
				cur_line++;
				if(cur_line > num_line)
					break;
			}
		}
		fclose(f);
	}
	return 0;
}


 
char fwrite_line(char *buf_write, const char *file, char num_line)
{
	FILE *f;
	char cur_line = 0,ptr[100],i;
 	int ch,j=0;
	char lines[50][100],buf[50];

	((LPC_WDT_TypeDef *) ((0x40000000UL) + 0x00000) )->WDFEED = 0xAA; ((LPC_WDT_TypeDef *) ((0x40000000UL) + 0x00000) )->WDFEED = 0x55;;

	for(i=0;i<50;i++)
		memset(lines[i],0,sizeof(lines[i]));
	memset(ptr,0,sizeof(ptr));
	memset(buf,0,sizeof(buf));

	strcpy(buf,buf_write);

	f = fopen(file,"r");
	if(f == 0)	
		return 0;
	else
	{
		for(;;)
		{
			ch = fgetc(f);

			if(ch == (-1) || cur_line >= 50)
				break;
			else
			{
				ptr[j] = ch;
				j++;

				if(ch == '\n')
				{
					j=0;
					strcpy(lines[cur_line],ptr);
					memset(ptr,0,sizeof(ptr));
					cur_line++;	
				}
			}
			((LPC_WDT_TypeDef *) ((0x40000000UL) + 0x00000) )->WDFEED = 0xAA; ((LPC_WDT_TypeDef *) ((0x40000000UL) + 0x00000) )->WDFEED = 0x55;;
		}
		fclose(f);
	}

	for(i=0;i<strlen(buf);i++)
		if(buf[i] == '\r' || buf[i] == '\n')
			buf[i] = 0;

	memset(lines[num_line],0,sizeof(lines[num_line]));
	strcpy(lines[num_line],buf);
	strcat(lines[num_line],"\r\n\0");

	f = fopen(file,"w");
	if(f == 0)
		return 0;

	for(j=0;j<cur_line;j++)
	{
		fprintf(f,"%s",lines[j]);
		if(strcmp(file,"cfg.cfg\0"))	
		{
			printf("Write...Linha %u: %s",j,lines[j]);
			fflush((& __stdout));
		}
	}
	fclose(f);

	return 1;
}


 

 

















































