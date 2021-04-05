# File : strings.d/Makefile
# Author : Richard A. O'Keefe.
# Updated: 2 June 1984.
# Purpose: UNIX make(1)file for the strings library.

# If you are not using a Vax, or if your strings might be 2^16
# characters long or longer, use
# CFLAGS=-O
# On the Vax we can use the string instructions some but not all the time.
CFLAGS=-O -DVaxAsm

# The SIII functions are the ones described in the System III
# string(3) manual page, and also in ctype(3), atoi(3).

SIII=strcat.o strncat.o strcmp.o strncmp.o strcpy.o strncpy.o strlen.o\
strchr.o strrchr.o strpbrk.o strspn.o strcspn.o strtok.o\
_c2type.o str2int.o getopt.o

# The Sys5 functions are the ones described in the System V
# memory(3C) manual page. mem{mov,rchr,rev} are in "mine".

Sys5=memccpy.o memchr.o memcmp.o memcpy.o memmov.o memrchr.o memset.o

# The BSD2 functions are the ones described in the 4.2bsd
# bstring(3) manual page, plus a couple of my additions.
# All except ffs have VAX-specific machine code versions.

BSD2=bcmp.o bcopy.o bfill.o bmove.o bzero.o ffs.o

# The "xstr" functions are Tony Hansen's "xstring(3c)" package with
# some additions of mine. All the code is mine, the names are his.
# It is not clear whether his strxncpy pads with NULs as strncpy does.
# In this package str[x]n{cpy,mov} all pad to exactly len chars with NUL.

xstr=strxcat.o strxcpy.o strxmov.o strxncat.o strxncpy.o strxnmov.o

# The "mine" functions are the ones which are entirely my own
# invention, though they are supposed to fit into the SIII conventions.

mine=strmov.o strnmov.o strrpt.o strnrpt.o strend.o strnlen.o strcpbrk.o\
strpack.o strcpack.o strtrans.o strntrans.o strpref.o strsuff.o\
strtrim.o strctrim.o strfield.o strkey.o int2str.o substr.o\
strnend.o strconc.o strrev.o strnrev.o _str2map.o _str2set.o\
memmov.o memrchr.o memrev.o

# The "find" functions are my code, but they are based on published
# work by Boyer, Moore, and Hospool. (See _str2pat.c.)

find=strfind.o strrepl.o

strings.a: ${SIII} ${Sys5} ${BSD2} ${xstr} ${mine} ${find}
rm strings.a; ar rc strings.a *.o; ranlib strings.a

scan=strpbrk.o strcprbk.o strspn.o strcspn.o strpack.o strcpack.o \
strtrim.o strctrim.o strtok.o

${scan} _str2set.o: _str2set.h

tran=strtrans.o strntrans.o

${tran} _str2map.o: _str2map.h

${find}: _str2pat.h

str2int.o: ctypes.h

${SIII} ${Sys5} ${BSD2} ${mine} ${xstr} ${find}: strings.h

clean:
-rm *.o

# The compilations should be done with the sources and headers in the
# same directory. However, users should find everything in the proper
# places: /usr/include/{strings,memory}.h and /usr/lib/strings.a
# /usr/local/lib would be ok. Why is there no /usr/local/include?

install:
cp memory.h strings.h /usr/include
mv strings.a /usr/lib
