/* File : memtrans.c
Author : Richard A. O'Keefe.
Updated: 2 June 1984
Defines: memtrans()

memtrans(dst, src, from, to, len)
copies exactly len characters from src[] to dst[], translating chars
in from[] to corresponding characters in to[]. From[] and to[] are
handled by _str2map. BEWARE: _str2map normally expects characters in
the range 0..127. The Vax MOVTC instruction thinks its table is 256
bytes long; if you want to translate arbitrary bytes you'd better be
sure that the _map_vec array is 256 bytes long. As distributed, the
memtrans function is only for translating ASCII (to 8-bit codes).

The VaxAsm code can only handle 0 <= len < 2^16, and is presented as
usual for your interest and amusement. Why *do* designers of 32-bit
machines put 16-bit limits on strings? (Dec aren't the only ones.)
*/

#include "strings.h"
#include "_str2map.h"

#if VaxAsm

void memtrans(dst, src, from, to, len)
_char_ *dst, *src, *from, *to;
int len;
{
_str2map(0, from, to);
asm("movtc 20(ap),*8(ap),$0,__map_vec,20(ap),*4(ap)");
}

#else ~VaxAsm

void memtrans(dst, src, from, to, len)
register _char_ *dst, *src;
_char_ *from, *to;
register int len;
{
_str2map(0, from, to);
while (--len >= 0) *dst++ = _map_vec[*src++];
}

#endif VaxAsm

