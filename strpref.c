/* File : strpref.c
Author : Richard A. O'Keefe.
Updated: 11 April 1984
Defines: strpref()

strpref(src, prefix)
checks whether prefix is a prefix of src. If it is not, the result
is NullS. If it is, the result is a pointer to the first character
of src after the prefix (src+strlen(prefix)). You can use this in a
conditional as a test: if (strpref(....)), but this is only portable
provided you remember to declare strpref() properly or use strings.h
as if (...) tests numbers against 0 and pointers against a suitable
cast of 0; there is no guarantee that (char*)0 is represented by the
same bit pattern as (int)0.
*/

#include "strings.h"

char *strpref(src, prefix)
register char *src, *prefix;
{
while (*prefix) if (*src++ != *prefix++) return NullS;
return src;
}

