/* File : strkey.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strkey()

strkey(dst, head, tail, options)
copies tail-head characters from head to dst according to the
options. If tail is NullS, it copies up to the terminating
NUL of head. This function is meant for doing comparisons as
by sort(1). The options are thus a string of characters
taken from "bdfin". In case the options came from somewhere
else other letters are ignored.

-b: leading layout characters are not copied.

-d: only letters, digits, and blanks are copied.
-i: only graphic characters (32..126) are copied.
-n: a numeric string is copied.
These options are incompatible, and the last is taken.

-f: upper case letters are copied as lower case.

The question of what to do with a numeric string is an interesting
one, and I don't claim that this is a brilliant answer. However,
the solution used here does mean that the caller can compare two
strings as strings without needing to know that they are numeric. A
number is copied as <sign><9 digits>.<remaining digits>, where
<sign> is '-' for a negative number and '0' for a positive number.
The magic number 9 is defined to be DigitMagic.

The idea is that to compare two lines using the keys
-tx +m1.n1<flags> -m2.n2
you do
h1 = strfield(line1, m1, n1, 0, 'x');
t1 = strfield(h1, 1, 0, 0, 'x');
strkey(buff1, h1, t1, "flags");
h2 = strfield(line2, m2, n2, 0, 'x');
t2 = strfield(h2, 1, 0, 0, 'x');
strkey(buff2, h2, t2, "flags");
... strcmp(buff1, buff2) ...

The point of all this, of course, is to make it easier to write new
utilities which are compatible with sort(1) than ones which are not.
*/

#include "strings.h"

#define DigitMagic 9

char *strkey(dst, head, tail, flags)
register char *dst, *head, *tail;
char *flags;
{
register int c;
int b = 0; /* b option? */
int f = 0; /* f option? */
int k = 0; /* 3->n, 2->d, 1->i, 0->none of them */

while (*flags) switch (*flags++|32) {
case 'b': b++; break;
case 'f': f++; break;
case 'i': k = 1; break;
case 'd': k = 2; break;
case 'n': k = 3; break;
default : /*ignore*/break;
}
flags = dst; /* save return value */

if (tail == NullS) for (tail = head; *tail; tail++) ;

if (b) while (head != tail && *head <= ' ') head++;

switch (k) {
case 0:
if (f) {
while (head != tail) {
c = *head++;
if (c >= 'A' && c <= 'Z') c |= 32;
*dst++ = c;
}
} else {
while (head != tail) *dst++ = *head++;
}
break;
case 1:
if (f) {
while (head != tail) {
c = *head++;
if (c >= 32 && c <= 126) {
if (c >= 'A' && c <= 'Z') c |= 32;
*dst++ = c;
}
}
} else {
while (head != tail) {
c = *head++;
if (c >= 32 && c <= 126) *dst++ = c;
}
}
break;
case 2:
if (f) f = 32;
while (head != tail) {
c = *head++;
if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c == ' ') {
*dst++ = c;
} else
if (c >= 'A' && c <= 'Z') {
*dst++ = c|f;
}
}
break;
case 3:
if (*head == '-' && head != tail) {
*dst++ = *head++;
head++;
} else {
*dst++ = '0';
}
b = 0;
while (head != tail) {
c = *head;
if (c < '0' || c > '9') break;
b++, head++;
}
f = DigitMagic-b;
while (--f >= 0) *dst++ = '0';
head -= b;
while (--b >= 0) *dst++ = *head++;
if (*head == '.' && head != tail) {
*dst++ = *head++;
while (head != tail) {
c = *head++;
if (c < '0' || c > '9') break;
*dst++ = c;
}
/* now remove trailing 0s and possibly the '.' as well */
while (*--dst == '0') ;
if (*dst != '.') dst++;
}
break;
}
*dst = NUL;
return flags; /* saved initial value of dst */
}

