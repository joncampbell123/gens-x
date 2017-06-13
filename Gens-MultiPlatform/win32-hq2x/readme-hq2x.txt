Gens with hq2x
==============

hq2x filter code copyright (C) 2003 MaxSt (maxst@hiend3d.com)

I managed to get the hq2x filter working in Gens and it looks pretty
good. As far as I can tell, getting hq3x and hq4x working would be
fairly simple as far as tweaking the assembler goes, and quite tricky as
far as the Gens side goes because there are no 3x or 4x filters in Gens
yet. Since I develop on a laptop with an 800x600 screen, I'm not going
to work on those two filters - sorry. I'm happy to give help to anyone
who is (seriously) implementing them.

I'm pretty sure it won't work with 555 (15-bit) colour, but I can't test
that. I only have a few roms on the machine I code on, so it's not
tested with many different video modes, but I think I got it right.

This is taken from a quite old CVS tree, relatively soon after Gens went
open-source. There have been other (unofficial) changes since, which
aren't in here. You might want to keep your main Gens seperate from this
one. Although I fixed the Cave-speak text display.

GNU licence
===========

As far as I can tell, Gens is open source under the GNU licence. The
hq2x filter certainly is. Therefore I have to make my source available
and that's what I have done. If I missed anything, let me know. I hope
this filter gets into the main Gens source tree :) Devs, let me know if
I missed anything out.

Yes, it's a name
================

The hq2x filter is written by a guy called Maxim. I am also called
Maxim, but I didn't write it, I only put it in Gens. My website is at
http://www.smspower.org/maxim/
