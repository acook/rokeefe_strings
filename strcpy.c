/* File : strcpy.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strcpy()

strcpy(dst, src) copies all the characters of src (including the
closing NUL) to dst, and returns the old value of dst. Maybe this
is useful for doing i = strlen(strcpy(dst, src)); I've always found
strmov handier.
*/

#include "strings.h"

char *strcpy(dst, src)
register char *dst, *src;
{
char *save;

for (save = dst; *dst++ = *src++; ) ;
return save;
}

