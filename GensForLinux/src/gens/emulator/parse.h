#ifndef _PARSE_H
#define _PARSE_H

#define MM					"--"
#define ENABLE				"enable"
#define DISABLE				"disable"
// 1 arg option

#define ROMPATH 			"rompath"
#define SAVEPATH	       	"savepath"
#define SRAMPATH        	"srampath"
#define BRAMPATH        	"brampath"
#define DUMPPATH        	"dumppath"
#define DUMPGYMPATH        	"dumpgympath"
#define SCRSHTPATH        	"screenshotpath"
#define PATPATH        		"patchpath"             
#define IPSPATH        		"ipspath"
#define GCOFFPATH        	"gcofflinepath"
#define GENSMANPATH        	"gensmanualpath"
#define GENBIOS        		"genesisbios"
#define USABIOS        		"usacdbios"
#define EURBIOS        		"europecdbios"
#define JAPBIOS        		"japancdbios"
#define _32X68kBIOS        	"32x68kbios"
#define _32XMBIOS        	"32xmsh2bios"
#define _32XSBIOS        	"32xssh2bios"
#define CONTRAST        	"contrast"
#define BRIGHTNESS        	"brightness"
#define WINDOWMODE        	"window-mode"
#define FSMODE        		"fs-mode"
#define FRAMESKIP        	"frameskip"
#define SOUNDRATE        	"soundrate"
#define MSH2SPEED        	"msh2-speed"
#define SSH2SPEED        	"ssh2-speed"
#define RAMCARTSIZE        	"ramcart-size"

// no arg option

#define FS        			"fs"
#define WINDOW    	   		"window"

// enable and disable options
#define STRETCH				"stretch"
#define STRETCH1        	ENABLE "-" STRETCH
#define STRETCH0	       	DISABLE "-" STRETCH

#define SWBLIT        		"swBlit"
#define SWBLIT1        		ENABLE "-" SWBLIT
#define SWBLIT0        		DISABLE "-" SWBLIT

#define GREYSCALE        	"greyscale"
#define GREYSCALE1        	ENABLE "-" GREYSCALE
#define GREYSCALE0	       	DISABLE "-" GREYSCALE

#define INVERT        		"invert"
#define INVERT1        		ENABLE "-" INVERT
#define INVERT0        		DISABLE "-" INVERT

#define SPRITELIMIT       	"spritelimit"
#define SPRITELIMIT1       	ENABLE "-" SPRITELIMIT
#define SPRITELIMIT0       	DISABLE "-" SPRITELIMIT

#define SOUND        		"sound"
#define SOUND1        		ENABLE "-" SOUND
#define SOUND0        		DISABLE "-" SOUND

#define STEREO        		"soundstereo"
#define STEREO1        		ENABLE "-" STEREO
#define STEREO0        		DISABLE "-" STEREO

#define Z80        			"z80"
#define Z801        		ENABLE "-" Z80
#define Z800        		DISABLE "-" Z80

#define YM2612        		"ym2612"
#define YM26121        		ENABLE "-" YM2612
#define YM26120        		DISABLE "-" YM2612

#define PSG        			"psg"
#define PSG1        		ENABLE "-" PSG
#define PSG0   		     	DISABLE "-" PSG

#define DAC        			"dac"
#define DAC1        		ENABLE "-" DAC
#define DAC0        		DISABLE "-" DAC

#define PCM       		 	"pcm"
#define PCM1       		 	ENABLE "-" PCM
#define PCM0        		DISABLE "-" PCM

#define PWM        			"pwm"
#define PWM1        		ENABLE "-" PWM
#define PWM0        		DISABLE "-" PWM

#define CDDA        		"cdda"
#define CDDA1        		ENABLE "-" CDDA
#define CDDA0        		DISABLE "-" CDDA

#define IMPROVED			"improved"

#define PSGIMPROVED      	IMPROVED "-" PSG
#define PSGIMPROVED1       	ENABLE "-" IMPROVED "-" PSG
#define PSGIMPROVED0       	DISABLE "-" IMPROVED "-" PSG

#define YMIMPROVED        	IMPROVED "-" YM2612
#define YMIMPROVED1        	ENABLE "-" IMPROVED "-" YM2612
#define YMIMPROVED0        	DISABLE "-" IMPROVED "-" YM2612

#define DACIMPROVED       	IMPROVED "-" DAC
#define DACIMPROVED1       	ENABLE "-" IMPROVED "-" DAC
#define DACIMPROVED0       	DISABLE "-" IMPROVED "-" DAC

#define PERFECTSYNC       	"perfectsynchro"
#define PERFECTSYNC1       	ENABLE "-" PERFECTSYNC
#define PERFECTSYNC0       	DISABLE "-" PERFECTSYNC

#define FASTBLUR        	"fastblur"
#define FASTBLUR1        	ENABLE "-" FASTBLUR
#define FASTBLUR0        	DISABLE "-" FASTBLUR

#define FPS        			"fps"
#define FPS1        		ENABLE "-" FPS
#define FPS0       		 	DISABLE "-" FPS

#define MSG        			"message"
#define MSG1        		ENABLE "-" MSG
#define MSG0        		DISABLE "-" MSG

#define LED        			"led"
#define LED1        		ENABLE "-" LED
#define LED0        		DISABLE "-" LED

#define FIXCHKSUM        	"fixchksum"
#define FIXCHKSUM1        	ENABLE "-" FIXCHKSUM
#define FIXCHKSUM0        	DISABLE "-" FIXCHKSUM

#define AUTOPAUSE        	"autopause"
#define AUTOPAUSE1        	ENABLE "-" AUTOPAUSE
#define AUTOPAUSE0        	DISABLE "-" AUTOPAUSE

#define HELP				"help"
#endif
