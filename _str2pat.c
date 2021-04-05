/* File : _str2pat.c
Author : Richard A. O'Keefe.
Updated: 2 June 1984
Defines: _pat_lim, _pat_vec[], _str2pat()

Searching in this package is done by an algorithm due to R. Nigel
Hospool, described in Software Practice & Experience 1980, p505.
Elsewhere I have a version of it which does exact case or either
case match, word more or literal mode, forwards or backwards, and
will look for the Nth instance. For most applications that is too
much and a simple exact case forward search will do. Hospool's
algorithm is a simplification of the Boyer-Moore algorithm which
doesn't guarantee linear time, but in practice is very good indeed.

_str2pat(pat) builds a search table for the string pat. As usual in
this pacakge, if pat == NullS, the table is not changed and the last
search string is re-used. To support this, _str2pat returns the
actual search string.
*/

#include "strings.h"
#include "_str2pat.h"

int _pat_lim;
int _pat_vec[_AlphabetSize];
static _char_ *oldPat = "";


_char_ *_str2pat(pat)
register _char_ *pat;
{
register int L, i;

if (pat == NullS) pat = oldPat; else oldPat = pat;
for (L = 0; *pat++; L++) ;
for (i = _AlphabetSize; --i >= 0; _pat_vec[i] = L) ;
for (pat = oldPat, i = L; --i > 0; _pat_vec[*pat++] = i) ;
_pat_lim = --L;
return oldPat;
}

