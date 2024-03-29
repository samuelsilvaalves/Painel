#line 1 "src\\Retarget.c"









 

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



 
#line 13 "src\\Retarget.c"
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



 
#line 14 "src\\Retarget.c"
#line 1 "C:\\Keil\\ARM\\RV31\\INC\\rt_sys.h"







 











 
typedef int FILEHANDLE;



 
extern FILEHANDLE _sys_open(const char *  , int  );



 










 
extern const char __stdin_name[];
extern const char __stdout_name[];
extern const char __stderr_name[];



 
extern int _sys_close(FILEHANDLE  );





 
extern int _sys_write(FILEHANDLE  , const unsigned char *  ,
                      unsigned  , int  );

























 
extern int _sys_read(FILEHANDLE  , unsigned char *  ,
                     unsigned  , int  );




 
extern void _ttywrch(int  );



 
extern int _sys_istty(FILEHANDLE  );




 
extern int _sys_seek(FILEHANDLE  , long  );





 
extern int _sys_ensure(FILEHANDLE  );







 
extern long _sys_flen(FILEHANDLE  );





 
extern int _sys_tmpnam(char *  , int  , unsigned  );




 
extern void _sys_exit(int  );    





 
extern char *_sys_command_string(char *  , int  );





#line 15 "src\\Retarget.c"
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



#line 16 "src\\Retarget.c"
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








#line 17 "src\\Retarget.c"

#pragma import(__use_no_semihosting_swi)






 

 




 
const char __stdin_name[]  = "STDIN";
const char __stdout_name[] = "STDOUT";
const char __stderr_name[] = "STDERR";

struct __FILE { int handle;   };




 
int sendchar (int c) {

  if (c == '\n')  {
  	uart_putChar (0, 0x0D);
	}
  uart_putChar (0, c);
  

  return (c);
}




 
int getkey (void) {

  return (uart_getChar(0));
}


 

void _ttywrch (int ch) {

  sendchar(ch);	

}

 

FILEHANDLE _sys_open (const char *name, int openmode) {
   
  if (strcmp(name, "STDIN") == 0) {
    return (0x8001);
  }
  if (strcmp(name, "STDOUT") == 0) {
    return (0x8002);
  }
  if (strcmp(name, "STDERR") == 0) {
    return (0x8003);
  }
  return (__sys_open (name, openmode));
}

 

int _sys_close (FILEHANDLE fh) {
  if (fh > 0x8000) {
    return (0);
  }
  return (__sys_close (fh));
}

 

int _sys_write (FILEHANDLE fh, const U8 *buf, U32 len, int mode) {

  if (fh == 0x8002) {
     
    for (  ; len; len--) {
      sendchar (*buf++);
    }
    return (0);
  }

  if (fh > 0x8000) {
    return (-1);
  }
  return (__sys_write (fh, buf, len));
}

 

int _sys_read (FILEHANDLE fh, U8 *buf, U32 len, int mode) {

  if (fh == 0x8001) {
     
    for (  ; len; len--) {
      *buf++ = getkey ();
    }
    return (0);
  }

  if (fh > 0x8000) {
    return (-1);
  }
  return (__sys_read (fh, buf, len));
}

 

int _sys_istty (FILEHANDLE fh) {
  if (fh > 0x8000) {
    return (1);
  }
  return (0);
}

 

int _sys_seek (FILEHANDLE fh, long pos) {
  if (fh > 0x8000) {
    return (-1);
  }
  return (__sys_seek (fh, pos));
}

 

int _sys_ensure (FILEHANDLE fh) {
  if (fh > 0x8000) {
    return (-1);
  }
  return (__sys_ensure (fh));
}

 

long _sys_flen (FILEHANDLE fh) {
  if (fh > 0x8000) {
    return (0);
  }
  return (__sys_flen (fh));
}

 

int _sys_tmpnam (char *name, int sig, unsigned maxlen) {
  return (1);
}

 

char *_sys_command_string (char *cmd, int len) {
  return (cmd);
}

 

void _sys_exit (int return_code) {
   
  while (1);
}



 
