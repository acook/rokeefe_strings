/* File : str2int.c
Author : Richard A. O'Keefe
Updated: 27 April 1984
Defines: str2int(), atoi(), atol()

str2int(src, radix, lower, upper, &val)
converts the string pointed to by src to an integer and stores it in
val. It skips leading spaces and tabs (but not newlines, formfeeds,
backspaces), then it accepts an optional sign and a sequence of digits
in the specified radix. The result should satisfy lower <= *val <= upper.
The result is a pointer to the first character after the number;
trailing spaces will NOT be skipped.

If an error is detected, the result will be NullS, the value put
in val will be 0, and errno will be set to
EDOM if there are no digits
ERANGE if the result would overflow or otherwise fail to lie
within the specified bounds.
Check that the bounds are right for your machine.
This looks amazingly complicated for what you probably thought was an
easy task. Coping with integer overflow and the asymmetric range of
twos complement machines is anything but easy.

So that users of atoi and atol can check whether an error occured,
I have taken a wholly unprecedented step: errno is CLEARED if this
call has no problems.
*/

#include "strings.h"
#include "ctypes.h"
#include <errno.h>
extern int errno;

/* CHECK THESE CONSTANTS FOR YOUR MACHINE!!! */

#if pdp11
# define MaxInt 0x7fffL /* int = 16 bits */
# define MinInt 0x8000L
# define MaxLong 0x7fffffffL /* long = 32 bits */
# define MinLong 0x80000000L
#else !pdp11
# define MaxInt 0x7fffffffL /* int = 32 bits */
# define MinInt 0x80000000L
# define MaxLong 0x7fffffffL /* long = 32 bits */
# define MinLong 0x80000000L
#endif pdp11


char *str2int(src, radix, lower, upper, val)
register char *src;
register int radix;
long lower, upper, *val;
{
int sign; /* is number negative (+1) or positive (-1) */
int n; /* number of digits yet to be converted */
long limit; /* "largest" possible valid input */
long scale; /* the amount to multiply next digit by */
long sofar; /* the running value */
register int d; /* (negative of) next digit */
char *answer;

/* Make sure *val is sensible in case of error */

*val = 0;

/* Check that the radix is in the range 2..36 */

if (radix < 2 || radix > 36) {
errno = EDOM;
return NullS;
}

/* The basic problem is: how do we handle the conversion of
a number without resorting to machine-specific code to
check for overflow? Obviously, we have to ensure that
no calculation can overflow. We are guaranteed that the
"lower" and "upper" arguments are valid machine integers.
On sign-and-magnitude, twos-complement, and ones-complement
machines all, if +|n| is representable, so is -|n|, but on
twos complement machines the converse is not true. So the
"maximum" representable number has a negative representative.
Limit is set to min(-|lower|,-|upper|); this is the "largest"
number we are concerned with. */

/* Calculate Limit using Scale as a scratch variable */

if ((limit = lower) > 0) limit = -limit;
if ((scale = upper) > 0) scale = -scale;
if (scale < limit) limit = scale;

/* Skip leading spaces and check for a sign.
Note: because on a 2s complement machine MinLong is a valid
integer but |MinLong| is not, we have to keep the current
converted value (and the scale!) as *negative* numbers,
so the sign is the opposite of what you might expect.
Should the test in the loop be isspace(*src)?
*/
while (*src == ' ' || *src == '\t') src++;
sign = -1;
if (*src == '+') src++; else
if (*src == '-') src++, sign = 1;

/* Check that there is at least one digit */

if (_c2type[1+ *src] >= radix) {
errno = EDOM;
return NullS;
}

/* Skip leading zeros so that we never compute a power of radix
in scale that we won't have a need for. Otherwise sticking
enough 0s in front of a number could cause the multiplication
to overflow when it neededn't.
*/
while (*src == '0') src++;

/* Move over the remaining digits. We have to convert from left
to left in order to avoid overflow. Answer is after last digit.
*/
for (n = 0; _c2type[1+ *src++] < radix; n++) ;
answer = --src;

/* The invariant we want to maintain is that src is just
to the right of n digits, we've converted k digits to
sofar, scale = -radix**k, and scale < sofar < 0. Now
if the final number is to be within the original
Limit, we must have (to the left)*scale+sofar >= Limit,
or (to the left)*scale >= Limit-sofar, i.e. the digits
to the left of src must form an integer <= (Limit-sofar)/(scale).
In particular, this is true of the next digit. In our
incremental calculation of Limit,

IT IS VITAL that (-|N|)/(-|D|) = |N|/|D|
*/

for (sofar = 0, scale = -1; --n >= 0; ) {
d = _c2type[1+ *--src];
if (-d < limit) {
errno = ERANGE;
return NullS;
}
limit = (limit+d)/radix, sofar += d*scale;
if (n != 0) scale *= radix; /* watch out for overflow!!! */
}
/* Now it might still happen that sofar = -32768 or its equivalent,
so we can't just multiply by the sign and check that the result
is in the range lower..upper. All of this caution is a right
pain in the neck. If only there were a standard routine which
says generate thus and such a signal on integer overflow...
But not enough machines can do it *SIGH*.
*/
if (sign < 0 && sofar < -MaxLong /* twos-complement problem */
|| (sofar*=sign) < lower || sofar > upper) {
errno = ERANGE;
return NullS;
}
*val = sofar;
errno = 0; /* indicate that all went well */
return answer;
}


int atoi(src)
char *src;
{
long val;
str2int(src, 10, MinInt, MaxInt, &val);
return (int)val;
}


long atol(src)
char *src;
{
long val;
str2int(src, 10, MinLong, MaxLong, &val);
return val;
}

