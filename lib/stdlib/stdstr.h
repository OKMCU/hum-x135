/**
  ******************************************************************************
  * @file    stdstr.h
  * @author  SUN Wentao
  * @version V0.0.1
  * @date    17-DEC-2018
  * @brief   
  ******************************************************************************
  */ 

#ifndef __STDSTR_H__
#define __STDSTR_H__

#ifndef NULL
#define NULL 0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#define STDSTR_EN_mem_set       1
#define STDSTR_EN_str_cmp       1
#define STDSTR_EN_str_len       1
#define STDSTR_EN_str_chr       1
#define STDSTR_EN_str_spn       1
#define STDSTR_EN_str_pbrk      1
#define STDSTR_EN_str_tok_r     1

#if STDSTR_EN_mem_set > 0
extern void *mem_set  (void *s, char val, size_t n);
#endif

#if STDSTR_EN_str_cmp > 0
extern int str_cmp(const char *dest, const char *source);
#endif

#if STDSTR_EN_str_len > 0
extern size_t str_len (const char *s);
#endif

#if STDSTR_EN_str_chr > 0
extern char *str_chr(const char *p, int ch);
#endif

#if STDSTR_EN_str_spn > 0
extern int str_spn(const char *p, const char *s);
#endif

#if STDSTR_EN_str_pbrk > 0
extern char *str_pbrk(const char *s1, const char *s2);
#endif

#if STDSTR_EN_str_tok_r > 0
extern char *str_tok_r(char *s, const char *delim, char **save_ptr);
#endif


#endif

