Info on the R. O'Keefe Strings Library
======================================

Backstory
---------

Early in April 2021 I got sucked into a hyperfocus around string implementations, c stdlibs, and related topics.

My main purpose was as a backing standard library for my own programming languages (either backed in C or translated based on existing research).

Thus, I decided to look at the string implementations of projects that I suspected should have good string performance. What I chose to look into was databases, in particular MariaDB and PostgreSQL.
I discovered that those string libraries (which were notable for not relying on libc) were typically just copy/pasted from pre-existing libraries.
Sometimes modified, often seeming to have been corrupted or made worse, or left incomplete with odd patches that grew organically over time.

Somewhere I can no longer recall (maybe I'll come back and update this when I figure it out) I came across mentions of O'Keefe's work and I wanted to check it out.
However, it became clear to me that it wasn't readily available in its pure form anywhere. Bits and pieces had been pulled out and used in many projects over the decades, but it was unclear to me how it started out.

Notably, [O'Keefe's own website](http://www.cs.otago.ac.nz/staffpriv/ok/software.htm) does not have it available.

So I started digging. Many false starts and partial archives and oceans of dead links. But I eventually found a mailing/news archive which dated back to the 80s and was able to find one that O'Keefe had originally posted.

Origin Timeline:

- Henry Spencer writes GetOpt - which is later incorporated into O'Keefe's code.
- April 1984: early (first?) public release - unable to find a clean archive of this.
- July 1st 1984: the updated release with additional utilities - in the original shar archive.

Repo Timeline:

- The first commit in this repo was the July 1st `shar` archive, unmodified for posterity.
- Much to my delight the `shar` self-extracting archive worked flawlessly 37 years later thanks to POSIX, and the second commit is the result of that extraction.
- I split out the informal license from the readme for clarity.
- Minor tweak to make the readme look less anachronistic to modern readers.

Any further changes will be clean up and improvements, often based on later forks of this original code.

