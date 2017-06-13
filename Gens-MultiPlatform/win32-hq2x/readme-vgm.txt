Gens with VGM logging
=====================

I decided to finally release this myself since it's taking a while for 
my changes to make it into the official Gens release...

This is, simply, Gens 2.1 with VGM logging added. VGM is a file format 
similar to GYM, except that it is capable of recording data with highly 
accurate timing. This means that, for the Genesis, DAC data (usually 
used for drums or samples) is reproduced extremely accurately.

Check the "VGM sample accurate" menu item if the music to be recorded 
does not sound right when recorded as GYM or non-sample-accurate VGM 
(which is fundamentally the same). Other than that, it's exactly like 
recording GYM files.

Go and visit http://www.smspower.org/music for information and tools for 
the VGM format. Note that my VGMTool program does not (at the time of 
writing) support the Genesis music chip (YM2612) very well, but my 
Winamp plugin (in_vgm) does.

This is taken from a quite old CVS tree, relatively soon after Gens went 
open-source. There have been other (unofficial) changes since, which 
aren't in here. You might want to keep your main Gens seperate from this 
one. Although I fixed the Cave-speak text display.

GNU licence
===========

As far as I can tell, Gens is open source under the GNU licence. I don't
want to get those nutty Free Like Speech Not Beer people after me;
therefore, I promise to show you my source if you ask. It should end up
in the main Gens source at some point anyway.
