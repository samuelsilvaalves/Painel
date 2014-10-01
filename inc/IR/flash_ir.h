/****************************************Copyright (c)**************************************************
**                               ShenZhen ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.openmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name: 			AT45DB161Drv.h
** Last modified Date: 	2007-04-25
** Last Version: 		1.0
** Descriptions: 		M45PE161µÄ²Ù×÷º¯Êý
**
**------------------------------------------------------------------------------------------------------
** Created 	 By: 		OpenMCU
** Created date: 		2010-12-23
** Version: 1.0
** Descriptions: 		First version
**
**------------------------------------------------------------------------------------------------------
** Modified by: 	
** Modified date: 	
** Version:
** Descriptions:  	
**
********************************************************************************************************/

#ifndef __F016BDRV_H 
#define __F016BDRV_H

#include "hardware_profile.h"

	/*Inclui a função IR da placa e compila com armazenamento dos IR's no cartão SD?*/
#if USE_IR && !SAVE_IR_IN_MEMORY_SD

#include "control_ir.h"

#define CE_Low()      LPC_GPIO0->FIOPIN &=  ~(1<<16)
#define CE_High()     LPC_GPIO0->FIOPIN |=   (1<<16)

#define SST_WriteEnable				0x06 
#define SST_WriteDisable			0x04
#define SST_EnableWriteStatusReg	0x50 
#define SST_WriteStatusReg			0x01
#define SST_ReadStatusReg			0x05
#define SST_ByteProgram				0x02
#define SST_ReadData				0x03 
#define SST_FastReadData			0x0B 
#define SST_SectorErase4K			0x20
#define SST_SectorErase32K			0x52 
#define SST_SectorErase64K			0xD8     
#define SST_JedecDeviceID			0x9F
#define SST_ReadID 					0x90
#define SST_ChipErase				0xC7 

#define ERASE_4K		0x00
#define ERASE_32K		0x01
#define ERASE_64K		0x02

#define INI_SETOR_0 	0x000000
#define INI_SETOR_1 	0x010000
#define INI_SETOR_2 	0x020000
#define INI_SETOR_3 	0x030000
#define INI_SETOR_4 	0x040000
#define INI_SETOR_5 	0x050000
#define INI_SETOR_6 	0x060000
#define INI_SETOR_7 	0x070000
#define INI_SETOR_8 	0x080000
#define INI_SETOR_9 	0x090000
#define INI_SETOR_10 	0x0A0000
#define INI_SETOR_11 	0x0B0000
#define INI_SETOR_12 	0x0C0000
#define INI_SETOR_13 	0x0D0000
#define INI_SETOR_14 	0x0E0000 
#define INI_SETOR_15 	0x0F0000 
#define INI_SETOR_16 	0x100000
#define INI_SETOR_17 	0x110000 
#define INI_SETOR_18 	0x120000 
#define INI_SETOR_19 	0x130000 
#define INI_SETOR_20 	0x140000
#define INI_SETOR_21 	0x150000 
#define INI_SETOR_22 	0x160000 
#define INI_SETOR_23 	0x170000 
#define INI_SETOR_24 	0x180000 
#define INI_SETOR_25 	0x190000 
#define INI_SETOR_26 	0x1A0000 
#define INI_SETOR_27 	0x1B0000 
#define INI_SETOR_28 	0x1C0000 
#define INI_SETOR_29 	0x1D0000 
#define INI_SETOR_30 	0x1E0000  
#define INI_SETOR_31 	0x1F0000
	    
unsigned char SPI_Flash_ReadSR(void);  
void SPI_Init(void);       
void SPI_FLASH_Write_SR(unsigned char sr);  	
void SPI_FLASH_Write_Enable(void);  
void SPI_FLASH_Write_Disable(void);	
void SPI_FLASH_Write_Enable_SR(void);
void SPI_FLASH_Write_SR(unsigned char byte); 
void SPI_Flash_Byte_Program(unsigned char* pBuffer,unsigned int addr,unsigned short NumByteToWrite);  
void SPI_Flash_Read(unsigned char* pBuffer,unsigned int addr,unsigned short NumByteToRead);   
void SPI_Flash_Write(unsigned char* pBuffer,unsigned int addr,unsigned short NumByteToWrite);
void SPI_Flash_Erase_Sector(unsigned int addr,unsigned char modo);
void SPI_Flash_Wait_Busy(void);           			 
unsigned char SPIx_ReadWriteByte(unsigned char TxData);

void save_ir_flash(unsigned short *dado,unsigned short addr,unsigned short channel);
void read_ir_flash(unsigned short addr);
void save_name_ir_flash(unsigned char *name);
void read_name_ir_flash(void);
void save_channel_ir(unsigned short addr,unsigned char channel);
char read_channel_ir(unsigned short addr);

extern unsigned char buf_flash[MAX_QTD_PULSOS*2];

#endif

#endif











