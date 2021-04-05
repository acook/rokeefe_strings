/* File : strlen.c
Author : Richard A. O'Keefe.
Updated: 23 April 1984
Defines: strlen()

strlen(s) returns the number of characters in s, that is, the number
of non-NUL characters found before the closing NULEosCh. Note: some
non-standard C compilers for 32-bit machines take int to be 16 bits,
either put up with short strings or change int to long throughout
this package. Better yet, BOYCOTT such shoddy compilers.
Beware: the asm version works only if strlen(s) < 65536.
*/

#include "strings.h"

#if VaxAsm

int strlen(s)
char *s;
{
asm("locc $0,$65535,*4(ap)");
asm("subl3 r0,$65535,r0");
}

#else ~VaxAsm

int strlen(s)
register char *s;
{
register int L;

for (L = 0; *s++; L++) ;
return L;
}

#endif VaxAsm

