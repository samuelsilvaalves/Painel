/****************************************************************************
 *
 *                  Generic Type Definitions
 *
 ****************************************************************************
 * FileName:        GenericTypeDefs.h
 * Dependencies:	None
 *
 * !!!!!  Versão modificada para não entrar em conflito com a biblioteca RF	 (Régis 20/08/2012)
 *
 */

#ifndef __GENERIC_TYPE_DEFS_H_
#define __GENERIC_TYPE_DEFS_H_

//typedef enum __BOOL { FALSE = 0, TRUE, LOW = 0, HIGH } _BOOL;	// Undefined size

#ifndef NULL
#define NULL    0//((void *)0)
#endif

#define	PUBLIC                                  // Function attributes
#define PROTECTED
#define PRIVATE   static

typedef unsigned char		BYTE;				// 8-bit unsigned
typedef unsigned short int	WORD;				// 16-bit unsigned
typedef unsigned long		DWORD;				// 32-bit unsigned
typedef unsigned long long	QWORD;				// 64-bit unsigned
typedef signed char			CHAR;				// 8-bit signed
typedef signed short int	SHORT;				// 16-bit signed
typedef signed long			LONG;				// 32-bit signed
typedef signed long long	LONGLONG;			// 64-bit signed

/* Alternate definitions */
typedef void                VOID;

typedef char                CHAR8;
typedef unsigned char       UCHAR8;

/* Processor & Compiler independent, size specific definitions */
// To Do:  We need to verify the sizes on each compiler.  These
//         may be compiler specific, we should either move them
//         to "compiler.h" or #ifdef them for compiler type.
typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;
typedef signed long long    INT64;

typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
typedef unsigned long int   UINT32;  // other name for 32-bit integer
typedef unsigned long long  UINT64;

typedef unsigned char U8;
//typedef unsigned int U16;
//typedef unsigned long U32;

typedef signed char S8;
//typedef signed int S16;
//typedef signed long S32;

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

#define LSB(a)          ((a).v[0])
#define MSB(a)          ((a).v[1])

#define LOWER_LSB(a)    ((a).v[0])
#define LOWER_MSB(a)    ((a).v[1])
#define UPPER_LSB(a)    ((a).v[2])
#define UPPER_MSB(a)    ((a).v[3])

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

#endif //__GENERIC_TYPE_DEFS_H_
