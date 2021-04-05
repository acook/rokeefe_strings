/* File : strntrans.c
Author : Richard A. O'Keefe.
Updated: 2 June 1984
Defines: strntrans()

strntrans(dst, src, len, from, to)
Moves characters from src to dst, translating characters in from[]
to the corresponding characters in to[], until either len characters
have been moved or a NUL has been moved. If fewer than len characters
are moved, the remainder of dst will be filled with NULs, much like
strncpy and family. No value is returned.

Apology: in the previous distribution of this package, strntrans was
defined the way memtrans is now defined. This is more consistent with
the general naming conventions.
*/

#include "strings.h"
#include "_str2map.h"

#if VaxAsm

void strntrans(dst, src, len, from, to)
_char_ *dst, *src, *from, *to;
int len;
{
_str2map(0, from, to);
asm("movtuc 20(ap),*8(ap),$0,__map_vec,20(ap),*4(ap)");
/* now pad the destination out with NUL characters */
asm("movc5 $0,*8(ap),$0,r4,(r5)");
}

#else ~VaxAsm

void strntrans(dst, src, len, from, to)
register _char_ *dst, *src;
register int len;
_char_ *from, *to;
{
_str2map(0, from, to);
while (--len >= 0 && (*dst++ = _map_vec[*src++])) ;
while (--len >= 0) *dst++ = NUL;
}

#endif VaxAsm

