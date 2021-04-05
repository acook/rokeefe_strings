/* File : strmov.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strmov()

strmov(dst, src) moves all the characters of src (including the
closing NUL) to dst, and returns a pointer to the new closing NUL in
dst. The similar UNIX routine strcpy returns the old value of dst,
which I have never found useful. strmov(strmov(dst,a),b) moves a//b
into dst, which seems useful.
*/

#include "strings.h"

char *strmov(dst, src)
register char *dst, *src;
{
while (*dst++ = *src++) ;
return dst-1;
}

