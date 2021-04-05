/* File : strtok.c
Author : Richard A. O'Keefe.
Updated: 11 April 1984
Defines: istrtok(), strtok()

strtok(src, set)
skips over initial characters of src[] which occur in set[].
The result is a pointer to the first character of src[]
which does not occur in set[]. It then skips until it finds
a character which does occur in set[], and changes it to NUL.
If src is NullS, it is as if you had specified the place
just after the last NUL was written. If src[] contains no
characters which are not in set[] (e.g. if src == "") the
result is NullS.

To read a sequence of words separated by spaces you might write
p = strtok(sequence, " ");
while (p) {process_word(p); p = strtok(NullS, " ");}
This is unpleasant, so there is also a function

istrtok(src, set)
which builds the set and notes the source string for future
reference. With this function, you can write

for (istrtok(wordlist, " \t"); p = strtok(NullS, NullS); )
process_word(p);
*/

#include "strings.h"
#include "_str2set.h"

static char *oldSrc = "";

void istrtok(src, set)
char *src, *set;
{
_str2set(set);
if (src != NullS) oldSrc = src;
}


char *strtok(src, set)
register char *src;
char *set;
{
char *save;

_str2set(set);
if (src == NullS) src = oldSrc;
while (_set_vec[*src] == _set_ctr) src++;
if (!*src) return NullS;
save = src;
while (_set_vec[*++src] != _set_ctr) ;
*src++ = NUL;
oldSrc = src;
return save;
}

