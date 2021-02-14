#include <stddef.h>

#define WORD sizeof(size_t)

void *Memcpy(void *dst, const void *src, size_t n);
void *Memset(void *s, int c, size_t n);
 void *Memmove(void *dst, const void *src, size_t n);
