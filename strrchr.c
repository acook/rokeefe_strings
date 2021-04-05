/* File : strrchr.c
Author : Richard A. O'Keefe.
Updated: 10 April 1984
Defines: strrchr(), rindex()

strrchr(s, c) returns a pointer to the last place in s where c
occurs, or NullS if c does not occur in s. This function is called
rindex in V7 and 4.?bsd systems; while not ideal the name is clearer
than strrchr, so rindex remains in strings.h as a macro. NB:
strrchr looks for single characters, not for sets or strings. The
parameter 'c' is declared 'int' so it will go in a register; if your
C compiler is happy with register char change it to that.
*/

#include "strings.h"

char *strrchr(s, c)
register _char_ *s;
register int c;
{
register char *t;

t = NullS;
do if (*s == c) t = s; while (*s++);
return t;
}

