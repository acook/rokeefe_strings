/* File : strfield.c
Author : Richard A. O'Keefe.
Updated: 21 April 1984
Defines: strfield()

strfield(src, fields, chars, blanks, tabch)
is based on the key specifications of the sort(1) command.

tabch corresponds to 'x' in -t'x'. If it is NUL, a field
is leading layout (spaces, tabs &c) followed by at least
one non-layout character, and is terminated by the next
layout character or NUL. If it is not NUL, a field is
terminated by tabch or NUL.

fields is the number of fields to skip over. It corresponds
to m in -m.n or +m.n . There must be at least this many
fields, and only the last may be terminated by NUL.

chars is the number of characters to skip after the fields
have been skipped. At least this many non-NUL characters
must remain after the fields have been skipped. Note that
it is entirely possible for this skip to cross one or more
field boundaries. This corresponds to n in +m.n or -m.n .

Finally, if blanks is not 0, any layout characters will be
skipped. There need not be any. This corresponds to the
letter b in +2.0b or -0.4b .

The result is NullS if the source ran out of fields or ran
out of chars. Otherwise it is a pointer to the first
character of src which was not skipped. It is quite possible
for this character to be the terminating NUL.

Example:
to skip to the user-id field of /etc/passwd:
user_id = strfield(line, 2, 0, 0, ':');

to check whether "line" is at least 27 characters long:
if (strfield(line, 0, 27, 0, 0)) then-it-is;

to select the third blank-delimited field in a line:
head = strfield(line, 2, 0, 1, 0);
tail = strfield(head, 1, 0, 0, 0);
(* the field is the tail-head characters starting at head *)

It's not a bug, it's a feature: "layout" means any ASCII character
in the range '\1' .. ' ', including '\n', '\f' and so on.
*/

#include "strings.h"

char *strfield(src, fields, chars, blanks, tabch)
register char *src;
int fields, chars, blanks, tabch;
{
if (tabch <= 0) {
while (--fields >= 0) {
while (*src <= ' ') if (!*src++) return NullS;
while (*++src > ' ') ;
}
} else
if (fields > 0) {
do if (!*src) return NullS;
while (*src++ != tabch || --fields > 0);
}
while (--chars >= 0) if (!*src++) return NullS;
if (blanks) while (*src && *src++ <= ' ') ;
return src;
}
