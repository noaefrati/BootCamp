#ifndef __STRINGS_H_
#define __STRINGS_H__

#include <stddef.h>   /* size_t */
char *StrCpy(char *dest, const char *src);
char *StrNCpy(char *dest, const char *src, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *str, int c);
size_t StrLen(const char *s);
char *StrDup(const char *s);
char *StrCat(char *dest, const char *src);
char *StrNCat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);
int isPolindrom(char *s);

#endif /*__STRINGS_H__*/
