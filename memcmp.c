/* File : memcmp.c
Author : Richard A. O'Keefe.
Updated: 25 May 1984
Defines: memcmp()

memcmp(lhs, rhs, len)
compares the two memory areas lhs[0..len-1] ?? rhs[0..len-1]. It
returns an integer less than, equal to, or greater than 0 according
as lhs[-] is lexicographically less than, equal to, or greater than
rhs[-]. Note that this is not at all the same as bcmp, which tells
you *where* the difference is but not what.

Note: suppose we have int x, y; then memcmp(&x, &y, sizeof x) need
not bear any relation to x-y. This is because byte order is machine
dependent, and also, some machines have integer representations that
are shorter than a machine word and two equal integers might have
different values in the spare bits. On a ones complement machine,
-0 == 0, but the bit patterns are different.

This could have a Vax assembly code version, but as the return value
is not the value left behind by the cmpc3 instruction I haven't
bothered.
*/

int memcmp(lhs, rhs, len)
register char *lhs, *rhs;
register int len;
{
while (--len >= 0)
if (*lhs++ != *rhs++) return lhs[-1]-rhs[-1];
return 0;
}

