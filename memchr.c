/* File : memchr.c
Author : Richard A. O'Keefe.
Updated: 25 May 1984
Defines: memchr()

memchr(src, chr, len)
searches the memory area pointed to by src extending for len bytes,
looking for an occurrence of the byte value chr. It returns NullS
if there is no such occurrence. Otherwise it returns a pointer to
the FIRST such occurrence.

See the "Character Comparison" section in the READ-ME file.
*/

#include "strings.h"

#if VaxAsm

char *memchr(src, chr, len)
char *src;
char chr;
int len;
{
asm("locc 8(ap),12(ap),*4(ap)");
asm("bneq L1");
asm("movl r1,r0");
asm("L1: ret");
}

#else ~VaxAsm

char *memchr(src, chr, len)
register char *src;
register int chr; /* should be char */
register int len;
{
while (--len >= 0)
if (*src++ == chr) return src-1;
return NullS;
}

#endif VaxAsm

