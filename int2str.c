/* File : int2str.c
Author : Richard A. O'Keefe
Updated: 30 April 1984
Defines: int2str(), itoa(), ltoa()

int2str(dst, radix, val)
converts the (long) integer "val" to character form and moves it to
the destination string "dst" followed by a terminating NUL. The
result is normally a pointer to this NUL character, but if the radix
is dud the result will be NullS and nothing will be changed.

If radix is -2..-36, val is taken to be SIGNED.
If radix is 2.. 36, val is taken to be UNSIGNED.
That is, val is signed if and only if radix is. You will normally
use radix -10 only through itoa and ltoa, for radix 2, 8, or 16
unsigned is what you generally want.

_dig_vec is public just in case someone has a use for it.
The definitions of itoa and ltoa are actually macros in strings.h,
but this is where the code is.
*/

#include "strings.h"

char _dig_vec[] =
"0123456789abcdefghijklmnopqrstuvwxyz";


char *int2str(dst, radix, val)
register char *dst;
register int radix;
register long val;
{
char buffer[33];
register char *p;

if (radix < 0) {
if (radix < -36 || radix > -2) return NullS;
if (val < 0) {
*dst++ = '-';
val = -val;
}
radix = -radix;
} else {
if (radix > 36 || radix < 2) return NullS;
}
/* The slightly contorted code which follows is due to the
fact that few machines directly support unsigned long / and %.
Certainly the VAX C compiler generates a subroutine call. In
the interests of efficiency (hollow laugh) I let this happen
for the first digit only; after that "val" will be in range so
that signed integer division will do. Sorry 'bout that.
CHECK THE CODE PRODUCED BY YOUR C COMPILER. The first % and /
should be unsigned, the second % and / signed, but C compilers
tend to be extraordinarily sensitive to minor details of style.
This works on a VAX, that's all I claim for it.
*/
p = &buffer[32];
*p = '\0';
*--p = _dig_vec[(unsigned long)val%(unsigned long)radix];
val = (unsigned long)val/(unsigned long)radix;
while (val != 0) *--p = _dig_vec[val%radix], val /= radix;
while (*dst++ = *p++) ;
return dst-1;
}

