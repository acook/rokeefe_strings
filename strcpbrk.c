/* File : strcpbrk.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strcpbrk()

strcpbrk(s1, s2) returns a pointer to the first character of s1 which
does not occur in s2. It is to strpbrk as strcspn is to strspn. It
relies on NUL never being in a set.
*/

#include "strings.h"
#include "_str2set.h"

char *strcpbrk(str, set)
register _char_ *str;
char *set;
{
_str2set(set);
while (_set_vec[*str++] == _set_ctr);
return *--str ? str : NullS;
}

