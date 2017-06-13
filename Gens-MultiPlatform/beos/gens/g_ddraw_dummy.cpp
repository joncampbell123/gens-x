#include "port.h"
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "timer.h"
#include "g_ddraw.h"
#include "g_dsound.h"
#include "g_input.h"
#include "g_main.h"
#include "resource.h"
#include "gens.h"
#include "mem_m68k.h"
#include "vdp_io.h"
#include "vdp_rend.h"
#include "misc.h"
#include "blit.h"
#include "scrshot.h"
//#include "net.h"
void Sleep(int i);

#include "cdda_mp3.h"
BITMAP *surface = 0;
//SDL_Surface *surface = 0;

clock_t Last_Time = 0, New_Time = 0;
clock_t Used_Time = 0;

int x_offset, y_offset = 0;

int Flag_Clr_Scr = 0;
int Sleep_Time;
int FS_VSync;
int W_VSync;
int Stretch; 
int Blit_Soft;
int Effect_Color = 7;
int FPS_Style = EMU_MODE | BLANC;
int Message_Style = EMU_MODE | BLANC | SIZE_X2;
int Kaillera_Error = 0;

static char Info_String[1024] = "";
static int Message_Showed = 0;
static unsigned int Info_Time = 0;

void (*Blit_FS)(unsigned char *Dest, int pitch, int x, int y, int offset);
void (*Blit_W)(unsigned char *Dest, int pitch, int x, int y, int offset);
int (*Update_Frame)();
int (*Update_Frame_Fast)();

unsigned long GetTickCount();

void Put_Info(char *Message, int Duree)
{
	if (Show_Message)
	{
		strcpy(Info_String, Message);
		Info_Time = GetTickCount() + Duree;
		Message_Showed = 1;
	}
}


int Init_Fail(int hwnd, char *err)
{
	End_DDraw();
	puts(err);
	//MessageBox(hwnd, err, "Oups ...", MB_OK);
	//DestroyWindow(hwnd);
	exit(0);
	return 0;
}


int Init_DDraw(int hWnd, int w, int h, int flags)
{
	set_color_depth(16);
	if(flags & GFX_AUTODETECT_FULLSCREEN)
	{
		x_offset = 160, y_offset = 120;
	}
	
	if (set_gfx_mode(flags, w, h, 0, 0) != 0)
	{
		allegro_message("Error setting graphics mode\n%s\n", allegro_error);
		exit(0);
	}
	surface = create_bitmap_ex(16, w, h);
	return 1;
}

void End_DDraw()
{
}

int Flip(int hWnd)
{
	float Ratio_X, Ratio_Y;
	int Dep, i;
	static float FPS = 0.0f, frames[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	static unsigned int old_time = 0, view_fps = 0, index_fps = 0, freq_cpu[2] = {0, 0};
	unsigned int new_time[2];

	if (Message_Showed)
	{
		if (GetTickCount() > Info_Time)
		{
			Message_Showed = 0;
			strcpy(Info_String, "");
		}
		else Print_Text(Info_String, strlen(Info_String), 10, 210, Message_Style);

	}
	else if (Show_FPS)
	{	
		if (freq_cpu[0] > 1)				// accurate timer ok
		{
			if (++view_fps >= 16)
			{
				GetPerformanceCounter((long long *) new_time);
				if (new_time[0] != old_time)
				{					
					FPS = (float) (freq_cpu[0]) * 16.0f / (float) (new_time[0] - old_time);
					sprintf(Info_String, "%.1f", FPS);
				}
				else
				{
					sprintf(Info_String, "too much...");
				}

				old_time = new_time[0];
				view_fps = 0;
			}
		}
		else if (freq_cpu[0] == 1)			// accurate timer not supported
		{
			if (++view_fps >= 10)
			{
				new_time[0] = GetTickCount();
		
				if (new_time[0] != old_time) frames[index_fps] = 10000 / (float)(new_time[0] - old_time);
				else frames[index_fps] = 2000;

				index_fps++;
				index_fps &= 7;
				FPS = 0.0f;

				for(i = 0; i < 8; i++) FPS += frames[i];

				FPS /= 8.0f;
				old_time = new_time[0];
				view_fps = 0;
			}

			sprintf(Info_String, "%.1f", FPS);
		}
		else
		{
			GetPerformanceFrequency((long long *) freq_cpu);
			if (freq_cpu[0] == 0) freq_cpu[0] = 1;

			sprintf(Info_String, "", FPS);
		}

		Print_Text(Info_String, strlen(Info_String), 10, 210, FPS_Style);
	}

	if (Fast_Blur) Half_Blur();

		if ((VDP_Reg.Set4 & 0x1) || (Debug))
		{
			Dep = 0;
		}
		else
		{
			Dep = 64;
		}
		
		if(W_VSync) vsync();
		if (Render_W == 0)
		{
			Blit_W((unsigned char *) surface->dat + (((surface->w*2) * ((240 - VDP_Num_Vis_Lines) >> 1) + Dep)), surface->w*2, 320 - Dep, VDP_Num_Vis_Lines, 32 + Dep * 2);
			blit(surface, screen, 0, 0, x_offset, y_offset, 320, 240);
		}
		else
		{
			Blit_W((unsigned char *) surface->dat + (((surface->w*2) * ((240 - VDP_Num_Vis_Lines) >> 1) + Dep) << 1), surface->w*2, 320 - Dep, VDP_Num_Vis_Lines, 32 + Dep * 2);
			blit(surface, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		}
	return 1;
}


int Update_Gens_Logo(int hWnd)
{
#if 0
	int i, j, m, n;
	static short tab[64000], Init = 0;
	static float renv = 0, ang = 0, zoom_x = 0, zoom_y = 0, pas;
	unsigned short c;

	if (!Init)
	{
		HBITMAP Logo;

		Logo = LoadBitmap(ghInstance,  MAKEINTRESOURCE(IDB_LOGO_BIG));
		GetBitmapBits(Logo, 64000 * 2, tab);
		pas = 0.05;
		Init = 1;
	}

	renv += pas;
	zoom_x = sin(renv);
	if (zoom_x == 0.0) zoom_x = 0.0000001;
	zoom_x = (1 / zoom_x) * 1;
	zoom_y = 1;

	if (VDP_Reg.Set4 & 0x1)
	{
		for(j = 0; j < 240; j++)
		{
			for(i = 0; i < 320; i++)
			{
				m = (float)(i - 160) * zoom_x;
				n = (float)(j - 120) * zoom_y;

				if ((m < 130) && (m >= -130) && (n < 90) && (n >= -90))
				{
					c = tab[m + 130 + (n + 90) * 260];
					if ((c > 31) || (c < 5)) MD_Screen[TAB336[j] + i + 8] = c;
				}
			}
		}
	}
	else
	{
		for(j = 0; j < 240; j++)
		{
			for(i = 0; i < 256; i++)
			{
				m = (float)(i - 128) * zoom_x;
				n = (float)(j - 120) * zoom_y;

				if ((m < 130) && (m >= -130) && (n < 90) && (n >= -90))
				{
					c = tab[m + 130 + (n + 90) * 260];
					if ((c > 31) || (c < 5)) MD_Screen[TAB336[j] + i + 8] = c;
				}
			}
		}
	}

	Half_Blur();
	Flip(hWnd);
#endif
	return 1;
}


int Update_Crazy_Effect(int hWnd)
{
	int i, j, offset;
	int r = 0, v = 0, b = 0, prev_l, prev_p;
	int RB, G;

 	for(offset = 336 * 240, j = 0; j < 240; j++)
	{
		for(i = 0; i < 336; i++, offset--)
		{
			prev_l = MD_Screen[offset - 336];
			prev_p = MD_Screen[offset - 1];

			if (Mode_555 & 1)
			{
				RB = ((prev_l & 0x7C1F) + (prev_p & 0x7C1F)) >> 1;
				G = ((prev_l & 0x03E0) + (prev_p & 0x03E0)) >> 1;

				if (Effect_Color & 0x4)
				{
					r = RB & 0x7C00;
					if (rand() > 0x2C00) r += 0x0400;
					else r -= 0x0400;
					if (r > 0x7C00) r = 0x7C00;
					else if (r < 0x0400) r = 0;
				}

				if (Effect_Color & 0x2)
				{
					v = G & 0x03E0;
					if (rand() > 0x2C00) v += 0x0020;
					else v -= 0x0020;
					if (v > 0x03E0) v = 0x03E0;
					else if (v < 0x0020) v = 0;
				}

				if (Effect_Color & 0x1)
				{
					b = RB & 0x001F;
					if (rand() > 0x2C00) b++;
					else b--;
					if (b > 0x1F) b = 0x1F;
					else if (b < 0) b = 0;
				}
			}
			else
			{
				RB = ((prev_l & 0xF81F) + (prev_p & 0xF81F)) >> 1;
				G = ((prev_l & 0x07C0) + (prev_p & 0x07C0)) >> 1;

				if (Effect_Color & 0x4)
				{
					r = RB & 0xF800;
					if (rand() > 0x2C00) r += 0x0800;
					else r -= 0x0800;
					if (r > 0xF800) r = 0xF800;
					else if (r < 0x0800) r = 0;
				}

				if (Effect_Color & 0x2)
				{
					v = G & 0x07C0;
					if (rand() > 0x2C00) v += 0x0040;
					else v -= 0x0040;
					if (v > 0x07C0) v = 0x07C0;
					else if (v < 0x0040) v = 0;
				}

				if (Effect_Color & 0x1)
				{
					b = RB & 0x001F;
					if (rand() > 0x2C00) b++;
					else b--;
					if (b > 0x1F) b = 0x1F;
					else if (b < 0) b = 0;
				}
			}

			MD_Screen[offset] = r + v + b;
		}
	}

	Flip(hWnd);

	return 1;
}


int Update_Emulation(int hWnd)
{
	static int Over_Time = 0;
	int current_div;

	if (Frame_Skip != -1)
	{
		if (Sound_Enable)
		{
			WP = (WP + 1) & (Sound_Segs - 1);

			if (WP == Get_Current_Seg())
				WP = (WP + Sound_Segs - 1) & (Sound_Segs - 1);

			Write_Sound_Buffer(NULL);
		}

		Update_Controllers();

		if (Frame_Number++ < Frame_Skip)
		{
			Update_Frame_Fast();
		}
		else
		{
			Frame_Number = 0;
			Update_Frame();
			Flip(hWnd);
		}
	}
	else
	{
		if (Sound_Enable)
		{
			//while (WP == Get_Current_Seg()) Sleep(Sleep_Time);
			
			//RP = Get_Current_Seg();

			//while (WP != RP)
			//{
				Write_Sound_Buffer(NULL);
				//WP = (WP + 1) & (Sound_Segs - 1);
				Update_Controllers();

				//if (WP != RP)
				//{
				//	Update_Frame_Fast();
				//}
				//else
				//{
					Update_Frame();
					Flip(hWnd);
				//}
			//}
		}
		else
		{
			if (CPU_Mode) current_div = 20;
			else current_div = 16 + (Over_Time ^= 1);

			New_Time = GetTickCount();
			Used_Time += (New_Time - Last_Time);
			Frame_Number = Used_Time / current_div;
			Used_Time %= current_div;
			Last_Time = New_Time;

			if (Frame_Number > 8) Frame_Number = 8;

			for (; Frame_Number > 1; Frame_Number--)
			{
				Update_Controllers();
				Update_Frame_Fast();
			}

			if (Frame_Number)
			{
				Update_Controllers();
				Update_Frame();
				Flip(hWnd);
			}
			else Sleep(Sleep_Time);
		}
	}

	return 1;
}


int Update_Emulation_One(int hWnd)
{
	Update_Controllers();
	Update_Frame();
	Flip(hWnd);

	return 1;
}


int Update_Emulation_Netplay(int hWnd, int player, int num_player)
{
#if 0
	static int Over_Time = 0;
	int current_div;

	if (CPU_Mode) current_div = 20;
	else current_div = 16 + (Over_Time ^= 1);

	New_Time = GetTickCount();
	Used_Time += (New_Time - Last_Time);
	Frame_Number = Used_Time / current_div;
	Used_Time %= current_div;
	Last_Time = New_Time;

	if (Frame_Number > 6) Frame_Number = 6;

	for (; Frame_Number > 1; Frame_Number--)
	{
		if (Sound_Enable)
		{
			if (WP == Get_Current_Seg()) WP = (WP - 1) & (Sound_Segs - 1);
			Write_Sound_Buffer(NULL);
			WP = (WP + 1) & (Sound_Segs - 1);
		}

		Scan_Player_Net(player);
		if (Kaillera_Error != -1) Kaillera_Error = Kaillera_Modify_Play_Values((void *) (Kaillera_Keys), 2);
		//Kaillera_Error = Kaillera_Modify_Play_Values((void *) (Kaillera_Keys), 2);
		Update_Controllers_Net(num_player);
		Update_Frame_Fast();
	}

	if (Frame_Number)
	{
		if (Sound_Enable)
		{
			if (WP == Get_Current_Seg()) WP = (WP - 1) & (Sound_Segs - 1);
			Write_Sound_Buffer(NULL);
			WP = (WP + 1) & (Sound_Segs - 1);
		}

		Scan_Player_Net(player);
		if (Kaillera_Error != -1) Kaillera_Error = Kaillera_Modify_Play_Values((void *) (Kaillera_Keys), 2);
		//Kaillera_Error = Kaillera_Modify_Play_Values((void *) (Kaillera_Keys), 2);
		Update_Controllers_Net(num_player);
		Update_Frame();
		Flip(hWnd);
	}
#endif
	return 1;
}


int Eff_Screen(void)
{
	int i;

	for(i = 0; i < 336 * 240; i++) MD_Screen[i] = 0;

	return 1;
}


int Pause_Screen(void)
{
	int i, j, offset;
	int r, v, b, nr, nv, nb;

	r = v = b = nr = nv = nb = 0;

	for(offset = j = 0; j < 240; j++)
	{
		for(i = 0; i < 336; i++, offset++)
		{
			if (Mode_555 & 1)
			{
				r = (MD_Screen[offset] & 0x7C00) >> 10;
				v = (MD_Screen[offset] & 0x03E0) >> 5;
				b = (MD_Screen[offset] & 0x001F);
			}
			else
			{
				r = (MD_Screen[offset] & 0xF800) >> 11;
				v = (MD_Screen[offset] & 0x07C0) >> 6;
				b = (MD_Screen[offset] & 0x001F);
			}

			nr = nv = nb = (r + v + b) / 3;
			
			if ((nb <<= 1) > 31) nb = 31;

			nr &= 0x1E;
			nv &= 0x1E;
			nb &= 0x1E;

			if (Mode_555 & 1)
				MD_Screen[offset] = (nr << 10) + (nv << 5) + nb;
			else
				MD_Screen[offset] = (nr << 11) + (nv << 6) + nb;
		}
	}

	return 1;
}


int Show_Genesis_Screen(int hWnd)
{
	Do_VDP_Only();
	Flip(hWnd);

	return 1;
}


int Take_Shot()
{
	Save_Shot((unsigned char *) surface->dat, Mode_555 & 1, surface->w, surface->h, surface->w*2);
#if 0
	HRESULT rval;
	DDSURFACEDESC2 ddsd;
	RECT RD;
	POINT p;

	if (Full_Screen)
	{
		if (Render_FS == 0)
		{
			if ((Stretch) || (VDP_Reg.Set2 & 0x08))
			{
				RD.top = 0;
				RD.bottom = 240;
			}
			else
			{
				RD.top = 8;
				RD.bottom = 224 + 8;
			}
			if ((Stretch) || (VDP_Reg.Set4 & 0x01))
			{
				RD.left = 0;
				RD.right = 320;
			}
			else
			{
				RD.left = 32;
				RD.right = 256 + 32;
			}
		}
		else if (Render_FS == 1)
		{
			if ((Stretch) || (VDP_Reg.Set2 & 0x08))
			{
				RD.top = 0;
				RD.bottom = 480;
			}
			else
			{
				RD.top = 16;
				RD.bottom = 448 + 16;
			}
			if ((Stretch) || (VDP_Reg.Set4 & 0x01))
			{
				RD.left = 0;
				RD.right = 640;
			}
			else
			{
				RD.left = 64;
				RD.right = 512 + 64;
			}
		}
		else
		{
			if (VDP_Reg.Set2 & 0x08)
			{
				RD.top = 0;
				RD.bottom = 480;
			}
			else
			{
				RD.top = 16;
				RD.bottom = 448 + 16;
			}
			if (VDP_Reg.Set4 & 0x01)
			{
				RD.left = 0;
				RD.right = 640;
			}
			else
			{
				RD.left = 64;
				RD.right = 512 + 64;
			}
		}
	}
	else
	{
		p.x = p.y = 0;
		GetClientRect(HWnd, &RD);
		ClientToScreen(HWnd, &p);

		RD.top = p.y;
		RD.left = p.x;
		RD.bottom += p.y;
		RD.right += p.x;

		if (Render_W == 0)
		{
			if ((!Stretch) && ((VDP_Reg.Set2 & 0x08) == 0))
			{
				RD.top += 8;
				RD.bottom -= 8;
			}
			if ((!Stretch) && ((VDP_Reg.Set4 & 0x01) == 0))
			{
				RD.left += 32;
				RD.right -= 32;
			}

		}
		else
		{
			if ((!Stretch) && ((VDP_Reg.Set2 & 0x08) == 0))
			{
				RD.top += 16;
				RD.bottom -= 16;
			}
			if ((!Stretch) && ((VDP_Reg.Set4 & 0x01) == 0))
			{
				RD.left += 64;
				RD.right -= 64;
			}
		}
	}

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	rval = lpDDS_Primary->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);

	if (rval == DD_OK)
	{
		Save_Shot((unsigned char *) ddsd.lpSurface + (RD.top * ddsd.lPitch) + (RD.left * 2), Mode_555 & 1, (RD.right - RD.left), (RD.bottom - RD.top), ddsd.lPitch);
		lpDDS_Primary->Unlock(NULL);
		return 1;
	}
	else return 0;
#endif
	return 0;
}







/*
void MP3_init_test()
{
	FILE *f;

	f = fopen("\\vc\\gens\\release\\test.mp3", "rb");
	
	if (f == NULL) return;
	
	MP3_Test(f);

	Play_Sound();
}


void MP3_update_test()
{
	int *buf[2];
		
	buf[0] = Seg_L;
	buf[1] = Seg_R;

	while (WP == Get_Current_Seg());
			
	RP = Get_Current_Seg();

	while (WP != RP)
	{
		Write_Sound_Buffer(NULL);
		WP = (WP + 1) & (Sound_Segs - 1);

		memset(Seg_L, 0, (Seg_Lenght << 2));
		memset(Seg_R, 0, (Seg_Lenght << 2));
		MP3_Update(buf, Seg_Lenght);
	}
}
*/
