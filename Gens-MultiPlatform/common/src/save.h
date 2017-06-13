#ifndef SAVE_H_
#define SAVE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

//Upthorn's code.
#define GENESIS_STATE_LENGHT    0x22478 
#define GENESIS_LENGHT_EX 0x30D8 //Upthmodif - subtracted STATE_LENGHT from original value. Original value follows 0x25554 //Modif
#define SEGACD_LENGHT_EX     0xE0000 //Upthmodif - These values are now additive
#define G32X_LENGHT_EX       0x82A00 //Upthmodif - for additional flexibility of use
//#define SCD32X_STATE_FILE_LENGHT     (0x22500 + 0xE0000 + 0x82A00) //Upthmodif - no longer needed
#define MAX_STATE_FILE_LENGHT_SCD       (GENESIS_STATE_LENGHT + GENESIS_LENGHT_EX + SEGACD_LENGHT_EX + G32X_LENGHT_EX) //Upthmodif - No longer hard-coded. Was previously "SCD32X_STATE_FILE_LENGHT".

#define GENESIS_STATE_FILE_LENGHT    0x22478
#define GENESIS_STATE_FILE_LENGHT_EX 0x25550
#define SEGACD_STATE_FILE_LENGHT     (0x22500 + 0xE0000)
#define G32X_STATE_FILE_LENGHT       (0x22500 + 0x82A00)
#define SCD32X_STATE_FILE_LENGHT     (0x22500 + 0xE0000 + 0x82A00)
#define MAX_STATE_FILE_LENGHT        SCD32X_STATE_FILE_LENGHT

extern char State_Dir[1024];
extern char SRAM_Dir[1024];
extern char BRAM_Dir[1024];

int Change_File_S(char *Dest, char *Dir, char *Titre, char *Filter, char *Ext);
int Change_File_L(char *Dest, char *Dir, char *Titre, char *Filter, char *Ext);
int Change_Dir(char *Dest, char *Dir, char *Titre, char *Filter, char *Ext);
FILE *Get_State_File();
void Get_State_File_Name(char *name);
int Load_State(char *Name);
int Save_State(char *Name);
void Import_Genesis(unsigned char *Data);
void Export_Genesis(unsigned char *Data);
void Import_SegaCD(unsigned char *Data);
void Export_SegaCD(unsigned char *Data);
void Import_32X(unsigned char *Data);
void Export_32X(unsigned char *Data);
int Save_Config(char *File_Name);
int Save_As_Config(HWND hWnd);
int Load_Config(char *File_Name, void *Game_Active);
int Load_As_Config(HWND hWnd, void *Game_Active);
int Load_SRAM(void);
int Save_SRAM(void);
int Load_BRAM(void);
int Save_BRAM(void);
void Format_Backup_Ram(void);

#ifdef __cplusplus
};
#endif

#endif