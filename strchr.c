/* File : strchr.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strchr(), index()

strchr(s, c) returns a pointer to the first place in s where c
occurs, or NullS if c does not occur in s. This function is called
index in V7 and 4.?bsd systems; while not ideal the name is clearer
than strchr, so index remains in strings.h as a macro. NB: strchr
looks for single characters, not for sets or strings. To find the
NUL character which closes s, use strchr(s, '\0') or strend(s). The
parameter 'c' is declared 'int' so it will go in a register; if your
C compiler is happy with register _char_ change it to that.
*/

#include "strings.h"

char *strchr(s, c)
register _char_ *s;
register int c;
{
for (;;) {
if (*s == c) return s;
if (!*s++) return NullS;
}
}

