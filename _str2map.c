/* File : _str2map.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: _map_vec[], _str2map().

_str2map(option, from, to) constructs a translation table. If from
or to is NullS, the same string is used as last time, so if you want
to translate a whole lot of strings using the same mapping you don't
have to reconstruct it each time. The options are

0: initialise the map to the identity function,
then map each from[i] to the corresponding to[i].
If to[] is shorter than from[], its last character is
repeated as often as needed.

1: as 0, but don't initialise the map.

2: initialise the map to send every character to to[0],
then map each from[i] to itself.

For example, to build a map which forces letters to lower case but
sends everything else to blank, call

_str2map(2, "abcdefghijklmnopqrstuvwxyz", " ");
_str2map(1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz");

Only strtrans() and strntrans() in this package call _str2map; if
you want to build your own maps this way you can "fool" them into
using it, as when the two strings are NullS they don't change the
map. As an extra-special dubious *hack*, _map_vec has an extra NUL
character at the end, so after calling _str2map(0, "", ""), you can
use _map_vec+1 as a string of the 127 non-NUL characters (or if the
_AlphabetSize is 256, of the 255 non-NUL characters).
*/

#include "strings.h"
#include "_str2map.h"

static _char_ *oldFrom = "?";
static char *oldTo = "?";

char _map_vec[_AlphabetSize+1];

void _str2map(option, from, to)
int option;
register _char_ *from;
register char *to;
{
register int i, c;

if (from == NullS && to == NullS) return;
if (from == NullS) from = oldFrom; else oldFrom = from;
if (to == NullS) to = oldTo; else oldTo = to;
switch (option) {
case 0:
for (i = _AlphabetSize; --i >= 0; _map_vec[i] = i) ;
case 1:
while (i = *from++) {
_map_vec[i] = *to++;
if (!*to) {
c = *--to;
while (i = *from++) _map_vec[i] = c;
return;
}
}
return;
case 2:
c = *to;
for (i = _AlphabetSize; --i >= 0; _map_vec[i] = c) ;
while (c = *from++) _map_vec[c] = c;
return;
}
}

