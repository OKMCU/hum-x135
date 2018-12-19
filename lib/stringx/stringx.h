/******************************************************************************

 @file  

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/
#ifndef __STRINGX_H__
#define __STRINGX_H__

#include "stdint.h"

#define STRINGX_EN_hexstr2uint          1
#define STRINGX_EN_decstr2uint          1
#define STRINGX_EN_decstr2sint          1
#define STRINGX_EN_tostr_sint           1
#define STRINGX_EN_tostr_uint           1
#define STRINGX_EN_tostr_hex8           1
#define STRINGX_EN_tostr_hex16          1
#define STRINGX_EN_tostr_hex32          1
#define STRINGX_EN_str_starts_with      0
#define STRINGX_EN_str_ends_with        0

#if STRINGX_EN_tostr_sint > 0
#define SINT_STR_LEN_MAX    11
#endif
#if STRINGX_EN_tostr_uint > 0
#define UINT_STR_LEN_MAX    10
#endif
#if STRINGX_EN_tostr_hex8 > 0
#define HEX8_STR_LEN_MAX    2
#endif
#if STRINGX_EN_tostr_hex16 > 0
#define HEX16_STR_LEN_MAX   4
#endif
#if STRINGX_EN_tostr_hex32 > 0
#define HEX32_STR_LEN_MAX   8
#endif

#if STRINGX_EN_hexstr2uint > 0
extern uint8_t hexstr2uint(const char *str, uint32_t *num);
#endif

#if STRINGX_EN_decstr2uint > 0
extern uint8_t decstr2uint(const char *str, uint32_t *num);
#endif

#if STRINGX_EN_decstr2sint > 0
extern uint8_t decstr2sint(const char *str, int32_t *num);
#endif

#if STRINGX_EN_tostr_sint > 0
extern uint8_t tostr_sint(int32_t num, char *str);
#endif

#if STRINGX_EN_tostr_uint > 0
extern uint8_t tostr_uint(uint32_t num, char *str);
#endif

#if STRINGX_EN_tostr_hex8 > 0
extern uint8_t tostr_hex8(uint8_t num, char *str);
#endif

#if STRINGX_EN_tostr_hex16 > 0
extern uint8_t tostr_hex16(uint16_t num, char *str);
#endif

#if STRINGX_EN_tostr_hex32 > 0
extern uint8_t tostr_hex32(uint32_t num, char *str);
#endif

#if STRINGX_EN_str_starts_with > 0
extern char *str_starts_with(char *str1, const char *str2);
#endif

#if STRINGX_EN_str_ends_with > 0
extern char *str_ends_with(char *str1, const char *str2);
#endif

#endif

