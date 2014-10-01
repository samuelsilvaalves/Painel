#ifndef __CMDS_IR_H
#define __CMDS_IR_H   

#include "hardware_profile.h"
#if USE_IR	/*Inclui na compilação a função IR da placa?*/

/* Command Functions to IR*/
void cmd_ir_learn		(char *par);
void cmd_irl_scene		(char *par);
void cmd_ir_learn_app   (char *par);
void cmd_ir_send_app    (char *par);
void cmd_ir_send		(char *par);
void cmd_ir_erase		(char *par);
void cmd_ir_erase_all	(char *par);
void cmd_erase_flash	(char *par);
void cmd_ir_read		(char *par);

#endif

#endif
















