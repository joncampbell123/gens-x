#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "port.h"
#include "save.h"
#include "cpu_68k.h"
#include "cpu_sh2.h"
#include "sh2.h"
#include "z80.h"
#include "cd_aspi.h"
#include "gens.h"
#include "g_main.h"
#include "g_sdldraw.h"
#include "g_sdlsound.h"
#include "g_sdlinput.h"
#include "vdp_io.h"
#include "vdp_rend.h"
#include "vdp_32x.h"
#include "rom.h"
#include "mem_m68k.h"
#include "mem_s68k.h"
#include "mem_sh2.h"
#include "mem_z80.h"
#include "ym2612.h"
#include "psg.h"
#include "pcm.h"
#include "pwm.h"
#include "scrshot.h"
#include "ggenie.h"
#include "io.h"
#include "misc.h"
#include "cd_sys.h"
#include "support.h"
#include "parse.h"

#define print_usage(option, helpmsg) fprintf(stderr, MM option"\n" helpmsg)
#define print_usage2(option, helpmsg) fprintf(stderr, MM ENABLE "-" option ", " MM DISABLE "-" option "\n" helpmsg "\n\n")

static void _usage()
{
	fprintf (stderr, "Gens for Linux v2.12-rc3\n");
	fprintf (stderr, "Usage : gens [options] romfile\n");
	print_usage(  HELP, "print this help");
	
	print_usage(  ROMPATH ,"path where your roms are stored");
	print_usage(  SAVEPATH ,"path where to save your states file");
	print_usage(  SRAMPATH ,"path where to save your states file");
	print_usage(  BRAMPATH ,"path where to save your states file");	
	print_usage(  DUMPPATH ,"path where to save your states file");
	print_usage(  DUMPGYMPATH ,"path where to save your states file");
	print_usage(  SCRSHTPATH ,"path where to save your states file");
	print_usage(  PATPATH ,"path where to save your states file");	
	print_usage(  IPSPATH ,"path where to save your states file");
	print_usage(  GCOFFPATH ,"path where to save your states file");
	print_usage(  GENSMANPATH ,"path where to save your states file");
	print_usage(  GENBIOS ,"");	
	print_usage(  USABIOS ,"");
	print_usage(  EURBIOS ,"");
	print_usage(  JAPBIOS ,"");
	print_usage(  _32X68kBIOS ,"");	
	print_usage(  _32XMBIOS ,"");
	print_usage(  _32XSBIOS ,"");
	print_usage(  CONTRAST ,"");
	print_usage(  BRIGHTNESS ,"");	
	print_usage(  WINDOWMODE ,"");
	print_usage(  FSMODE ,"");
	print_usage(  FRAMESKIP ,"");
	print_usage(  SOUNDRATE ,"");	
	print_usage(  MSH2SPEED ,"");
	print_usage(  SSH2SPEED ,"");
	print_usage(  RAMCARTSIZE,"");

	print_usage2(  STRETCH,"stretch mode");
	print_usage2(  SWBLIT,"software blitting");
	print_usage2(  GREYSCALE,"greyscale");
	print_usage2(  INVERT,"");
	print_usage2(  SPRITELIMIT,"");
	print_usage2(  SOUND,"");
	print_usage2(  STEREO,"");
	print_usage2(  Z80,"");
	print_usage2(  YM2612,"");
	print_usage2(  PSG,"");
	print_usage2(  DAC,"");
	print_usage2(  PCM,"");
	print_usage2(  PWM,"");
	print_usage2(  CDDA,"");
	print_usage2(  PSGIMPROVED,"");
	print_usage2(  YMIMPROVED,"");
	print_usage2(  DACIMPROVED,"");
	print_usage2(  PERFECTSYNC,"");
	print_usage2(  FASTBLUR,"");
	print_usage2(  FPS,"");
	print_usage2(  MSG,"");
	print_usage2(  LED,"");
	print_usage2(  FIXCHKSUM,"");
	print_usage2(  AUTOPAUSE,"");
	
	exit (0);	
}

int
parseArgs (int argc, char **argv)
{
  int c;

  while (1)
    {
      int option_index = 0;
      static struct option long_options[] = {
	{ROMPATH, required_argument, 0, 0},
	{SAVEPATH, required_argument, 0, 0},
	{SRAMPATH, required_argument, 0, 0},
	{BRAMPATH, required_argument, 0, 0},
	{DUMPPATH, required_argument, 0, 0},
	{DUMPGYMPATH, required_argument, 0, 0},
	{SCRSHTPATH, required_argument, 0, 0},
	{PATPATH, required_argument, 0, 0},
	{IPSPATH, required_argument, 0, 0},
	{GCOFFPATH, required_argument, 0, 0},
	{GENSMANPATH, required_argument, 0, 0},
	{GENBIOS, required_argument, 0, 0},
	{USABIOS, required_argument, 0, 0},
	{EURBIOS, required_argument, 0, 0},
	{JAPBIOS, required_argument, 0, 0},
	{_32X68kBIOS, required_argument, 0, 0},
	{_32XMBIOS, required_argument, 0, 0},
	{_32XSBIOS, required_argument, 0, 0},
	{FS, no_argument, 0, 0},
	{WINDOW, no_argument, 0, 0},
	{WINDOWMODE, required_argument, 0, 0},
	{FSMODE, required_argument, 0, 0},
	{STRETCH1, no_argument, 0, 0},
	{STRETCH0, no_argument, 0, 0},
	{SWBLIT1, no_argument, 0, 0},
	{SWBLIT0, no_argument, 0, 0},
	{CONTRAST, required_argument, 0, 0},
	{BRIGHTNESS, required_argument, 0, 0},
	{GREYSCALE1, no_argument, 0, 0},
	{GREYSCALE0, no_argument, 0, 0},
	{INVERT1, no_argument, 0, 0},
	{INVERT0, no_argument, 0, 0},
	{SPRITELIMIT1, no_argument, 0, 0},
	{SPRITELIMIT0, no_argument, 0, 0},
	{FRAMESKIP, required_argument, 0, 0},
	{SOUND1, no_argument, 0, 0},
	{SOUND0, no_argument, 0, 0},
	{SOUNDRATE, required_argument, 0, 0},
	{STEREO1, no_argument, 0, 0},
	{STEREO0, no_argument, 0, 0},
	{Z801, no_argument, 0, 0},
	{Z800, no_argument, 0, 0},
	{YM26121, no_argument, 0, 0},
	{YM26120, no_argument, 0, 0},
	{PSG1, no_argument, 0, 0},
	{PSG0, no_argument, 0, 0},
	{DAC1, no_argument, 0, 0},
	{DAC0, no_argument, 0, 0},
	{PCM1, no_argument, 0, 0},
	{PCM0, no_argument, 0, 0},
	{PWM1, no_argument, 0, 0},
	{PWM0, no_argument, 0, 0},
	{CDDA1, no_argument, 0, 0},
	{CDDA0, no_argument, 0, 0},
	{PSGIMPROVED1, no_argument, 0, 0},
	{PSGIMPROVED0, no_argument, 0, 0},
	{YMIMPROVED1, no_argument, 0, 0},
	{YMIMPROVED0, no_argument, 0, 0},
	{DACIMPROVED1, no_argument, 0, 0},
	{DACIMPROVED0, no_argument, 0, 0},
	{PERFECTSYNC1, no_argument, 0, 0},
	{PERFECTSYNC0, no_argument, 0, 0},
	{MSH2SPEED, required_argument, 0, 0},
	{SSH2SPEED, required_argument, 0, 0},
	{FASTBLUR1, no_argument, 0, 0},
	{FASTBLUR0, no_argument, 0, 0},
	{FPS1, no_argument, 0, 0},
	{FPS0, no_argument, 0, 0},
	{MSG1, no_argument, 0, 0},
	{MSG0, no_argument, 0, 0},
	{LED1, no_argument, 0, 0},
	{LED0, no_argument, 0, 0},
	{FIXCHKSUM1, no_argument, 0, 0},
	{FIXCHKSUM0, no_argument, 0, 0},
	{AUTOPAUSE1, no_argument, 0, 0},
	{AUTOPAUSE0, no_argument, 0, 0},
	{RAMCARTSIZE, required_argument, 0, 0},
	{HELP, no_argument, 0, 0},
	{0, 0, 0, 0}
      };

      c = getopt_long (argc, argv, "", long_options, &option_index);
      if (c == -1)
	break;
      if (!strcmp (long_options[option_index].name, ROMPATH))
	{
	  strcpy (Rom_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, SAVEPATH))
	{
	  strcpy (State_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, SRAMPATH))
	{
	  strcpy (SRAM_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, BRAMPATH))
	{
	  strcpy (BRAM_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, DUMPPATH))
	{
	  strcpy (Dump_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, DUMPGYMPATH))
	{
	  strcpy (Dump_GYM_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, SCRSHTPATH))
	{
	  strcpy (ScrShot_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, PATPATH))
	{
	  strcpy (Patch_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, IPSPATH))
	{
	  strcpy (IPS_Dir, optarg);
	}
      else if (!strcmp (long_options[option_index].name, GCOFFPATH))
	{
	  strcpy (CGOffline_Path, optarg);
	}
      else if (!strcmp (long_options[option_index].name, GENSMANPATH))
	{
	  strcpy (Manual_Path, optarg);
	}
      else if (!strcmp (long_options[option_index].name, GENBIOS))
	{
	  strcpy (Genesis_Bios, optarg);
	}
      else if (!strcmp (long_options[option_index].name, USABIOS))
	{
	  strcpy (US_CD_Bios, optarg);
	}
      else if (!strcmp (long_options[option_index].name, EURBIOS))
	{
	  strcpy (EU_CD_Bios, optarg);
	}
      else if (!strcmp (long_options[option_index].name, JAPBIOS))
	{
	  strcpy (JA_CD_Bios, optarg);
	}
      else if (!strcmp (long_options[option_index].name, _32X68kBIOS))
	{
	  strcpy (_32X_Genesis_Bios, optarg);
	}
      else if (!strcmp (long_options[option_index].name, _32XMBIOS))
	{
	  strcpy (_32X_Master_Bios, optarg);
	}
      else if (!strcmp (long_options[option_index].name, _32XSBIOS))
	{
	  strcpy (_32X_Slave_Bios, optarg);
	}
      else if (!strcmp (long_options[option_index].name, FS))
	{
	  Full_Screen = 1;
	}
      else if (!strcmp (long_options[option_index].name, WINDOW))
	{
	  Full_Screen = 0;
	}
      else if (!strcmp (long_options[option_index].name, WINDOWMODE))
	{
	  Render_W = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, FSMODE))
	{
	  Render_FS = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, STRETCH1))
	{
	  Stretch = 1;
	}
      else if (!strcmp (long_options[option_index].name, STRETCH0))
	{
	  Stretch = 0;
	}
      else if (!strcmp (long_options[option_index].name, SWBLIT1))
	{
	  Blit_Soft = 1;
	}
      else if (!strcmp (long_options[option_index].name, SWBLIT0))
	{
	  Blit_Soft = 0;
	}
      else if (!strcmp (long_options[option_index].name, CONTRAST))
	{
	  Contrast_Level = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, BRIGHTNESS))
	{
	  Brightness_Level = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, GREYSCALE1))
	{
	  Greyscale = 1;
	}
      else if (!strcmp (long_options[option_index].name, GREYSCALE0))
	{
	  Greyscale = 0;
	}
      else if (!strcmp (long_options[option_index].name, INVERT1))
	{
	  Invert_Color = 1;
	}
      else if (!strcmp (long_options[option_index].name, INVERT0))
	{
	  Invert_Color = 0;
	}
      else if (!strcmp (long_options[option_index].name, SPRITELIMIT1))
	{
	  Sprite_Over = 1;
	}
      else if (!strcmp (long_options[option_index].name, SPRITELIMIT0))
	{
	  Sprite_Over = 0;
	}
      else if (!strcmp (long_options[option_index].name, FRAMESKIP))
	{
	  Frame_Skip = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, SOUND1))
	{
	  Sound_Enable = 1;
	}
      else if (!strcmp (long_options[option_index].name, SOUND0))
	{
	  Sound_Enable = 0;
	}
      else if (!strcmp (long_options[option_index].name, SOUNDRATE))
	{
	  Sound_Rate = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, STEREO1))
	{
	  Sound_Stereo = 1;
	}
      else if (!strcmp (long_options[option_index].name, STEREO0))
	{
	  Sound_Stereo = 0;
	}
      else if (!strcmp (long_options[option_index].name, Z801))
	{
	  Z80_State = 1;
	}
      else if (!strcmp (long_options[option_index].name, Z800))
	{
	  Z80_State = 0;
	}
      else if (!strcmp (long_options[option_index].name, YM26121))
	{
	  YM2612_Enable = 1;
	}
      else if (!strcmp (long_options[option_index].name, YM26120))
	{
	  YM2612_Enable = 0;
	}
      else if (!strcmp (long_options[option_index].name, PSG1))
	{
	  PSG_Enable = 1;
	}
      else if (!strcmp (long_options[option_index].name, PSG0))
	{
	  PSG_Enable = 0;
	}
      else if (!strcmp (long_options[option_index].name, DAC1))
	{
	  DAC_Enable = 1;
	}
      else if (!strcmp (long_options[option_index].name, DAC0))
	{
	  DAC_Enable = 0;
	}
      else if (!strcmp (long_options[option_index].name, PCM1))
	{
	  PCM_Enable = 1;
	}
      else if (!strcmp (long_options[option_index].name, PCM0))
	{
	  PCM_Enable = 0;
	}
      else if (!strcmp (long_options[option_index].name, PWM1))
	{
	  PWM_Enable = 1;
	}
      else if (!strcmp (long_options[option_index].name, PWM0))
	{
	  PWM_Enable = 0;
	}
      else if (!strcmp (long_options[option_index].name, CDDA1))
	{
	  CDDA_Enable = 1;
	}
      else if (!strcmp (long_options[option_index].name, CDDA0))
	{
	  CDDA_Enable = 0;
	}
      else if (!strcmp (long_options[option_index].name, PSGIMPROVED1))
	{
	  PSG_Improv = 1;
	}
      else if (!strcmp (long_options[option_index].name, PSGIMPROVED0))
	{
	  PSG_Improv = 0;
	}
      else if (!strcmp (long_options[option_index].name, YMIMPROVED1))
	{
	  YM2612_Improv = 1;
	}
      else if (!strcmp (long_options[option_index].name, YMIMPROVED0))
	{
	  YM2612_Improv = 0;
	}
      else if (!strcmp (long_options[option_index].name, DACIMPROVED1))
	{
	  DAC_Improv = 1;
	}
      else if (!strcmp (long_options[option_index].name, DACIMPROVED0))
	{
	  DAC_Improv = 0;
	}
      else if (!strcmp (long_options[option_index].name, PERFECTSYNC1))
	{
	  SegaCD_Accurate = 1;
	}
      else if (!strcmp (long_options[option_index].name, PERFECTSYNC0))
	{
	  SegaCD_Accurate = 0;
	}
      else if (!strcmp (long_options[option_index].name, MSH2SPEED))
	{
	  MSH2_Speed = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, SSH2SPEED))
	{
	  SSH2_Speed = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, FASTBLUR1))
	{
	  Fast_Blur = 1;
	}
      else if (!strcmp (long_options[option_index].name, FASTBLUR0))
	{
	  Fast_Blur = 0;
	}
      else if (!strcmp (long_options[option_index].name, FPS1))
	{
	  Show_FPS = 1;
	}
      else if (!strcmp (long_options[option_index].name, FPS0))
	{
	  Show_FPS = 0;
	}
      else if (!strcmp (long_options[option_index].name, MSG1))
	{
	  Show_Message = 1;
	}
      else if (!strcmp (long_options[option_index].name, MSG0))
	{
	  Show_Message = 0;
	}
      else if (!strcmp (long_options[option_index].name, LED1))
	{
	  Show_LED = 1;
	}
      else if (!strcmp (long_options[option_index].name, LED0))
	{
	  Show_LED = 0;
	}
      else if (!strcmp (long_options[option_index].name, FIXCHKSUM1))
	{
	  Auto_Fix_CS = 1;
	}
      else if (!strcmp (long_options[option_index].name, FIXCHKSUM0))
	{
	  Auto_Fix_CS = 0;
	}
      else if (!strcmp (long_options[option_index].name, AUTOPAUSE1))
	{
	  Auto_Pause = 1;
	}
      else if (!strcmp (long_options[option_index].name, AUTOPAUSE0))
	{
	  Auto_Pause = 0;
	}
      else if (!strcmp (long_options[option_index].name, RAMCARTSIZE))
	{
	  BRAM_Ex_Size = strtol (optarg, (char **) NULL, 10);
	}
      else if (!strcmp (long_options[option_index].name, HELP))
	{
		_usage();
	} else 
	{
		_usage();
	}
    }

  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
		printf ("%s ", argv[optind++]);
      printf ("\n");
    }
}

