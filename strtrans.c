/* File : strtrans.c
Author : Richard A. O'Keefe.
Updated: 2 June 1984
Defines: strtrans()

strtrans(dst, src, from, to)
copies characters from src[] to dst[], stopping when dst gets a NUL
character, translating characters in from[] to the corresponding
characters in to[]. Courtesy of _str2map, if from or to is null its
previous value will be used, and if both are NullS the table won't
be rebuilt. Note that copying stops when a NUL is put into dst[],
which can normally happen only when a NUL has been fetched from
src[], but if you have built your own translation table it may be
earlier (if some character is mapped to NUL) or later (if NUL is
mapped to something else). No value is returned.

The VaxAsm version only works from strlen(src) < 2^16.
*/

#include "strings.h"
#include "_str2map.h"

#if VaxAsm

void strtrans(dst, src, from, to)
_char_ *dst, *src, *from, *to;
{
_str2map(0, from, to);
asm("movtuc $65535,*8(ap),$0,__map_vec,$65535,*4(ap)");
/* That stops when the "escape" is found, and we want to move it */
asm("movb $0,(r5)");
}

#else ~VaxAsm

void strtrans(dst, src, from, to)
register _char_ *dst, *src;
_char_ *from, *to;
{
_str2map(0, from, to);
while (*dst++ = _map_vec[*src++]) ;
}

#endif VaxAsm

