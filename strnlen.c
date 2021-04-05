/* File : strnlen.c
Author : Richard A. O'Keefe.
Updated: 10 April 1984
Defines: strnlen()

strnlen(src, len)
returns the number of characters up to the first NUL in src, or len,
whichever is smaller. This is the same as strnend(src,len)-src.

Beware: the VaxAsm version only works for 0 <= len < 65535.
*/

#include "strings.h"

#if VaxAsm

int strnlen(src, len)
char *src;
int len;
{
asm("locc $0,8(ap),*4(ap)");
asm("subl3 4(ap),r1,r0");
}

#else ~VaxAsm

int strnlen(s, n)
register char *s;
register int n;
{
register int L;

for (L = 0; --n >= 0 && *s++; L++) ;
return L;
}

#endif VaxAsm

