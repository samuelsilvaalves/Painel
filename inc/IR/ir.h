#ifndef __IR_H
#define __IR_H   

#include <RTL.H>
#include "hardware_profile.h"

#if USE_IR	/*Inclui na compilação a função IR da placa?*/

#include "control_ir.h"

extern char last_port_ir;

extern unsigned short ir[MAX_QTD_PULSOS];
extern unsigned short ir_cmp[MAX_QTD_PULSOS];
extern U16 ir_counter;

/*Funções locais*/
char save_ir(unsigned short *dado,short addr,short channel, int index_file);
char read_ir(unsigned short addr, int index_file);
char learn_ir(unsigned short addr,unsigned char channel, int index_file);
void erase_ir(unsigned short addr);
void erase_all_ir(void);
char read_ir(unsigned short addr, int index_file);

#endif

#endif













