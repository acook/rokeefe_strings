/* File : strnend.c
Author : Richard A. O'Keefe.
Updated: 1 June 1984
Defines: strnend()

strnend(src, len)
returns a pointer to just after the end of the string src, which is
terminated by a NUL character, or by exhaustion of the length bound
len. That is, strnend(s,L)-s = strnlen(s,L). s+strnlen(s,L) could
of course be used instead, but this is sometimes clearer.
Beware: the asm version works only if 0 <= len < 65535.
*/

#include "strings.h"

#if VaxAsm

char *strnend(src, len)
char *src;
int len;
{
asm("locc $0,8(ap),*4(ap)");
asm("movl r1,r0");
}

#else ~VaxAsm

char *strnend(src, len)
register char *src;
register int len;
{
while (--len >= 0 && *src) src++;
return src;
}

#endif VaxAsm

