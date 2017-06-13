#include <string.h>
#include <stdio.h>
#include "port.h"

void SetCurrentDirectory(const char *directory)
{
}

int stricmp(const char *str1, const char *str2)
{
	return strcasecmp(str1, str2);
}

int	strnicmp(const char *str1, const char *str2, unsigned long nchars)
{
	return strncasecmp(str1, str2, nchars);
}

void MessageBox(int parent, const char *text, const char *error, int type)
{
	puts(text);
}

int GetPrivateProfileInt(const char *section, const char *var,
	int def, const char *filename)
{
	return def;
}

void GetPrivateProfileString(const char *section, const char *var,
	const char *def, char *get, int length, const char *filename)
{
	strncpy(get, def, length);
}

void WritePrivateProfileString(const char *section, const char *var,
	const char *var_name, const char *filename)
{
}

void DestroyMenu(HMENU hmenu)
{
}

void SetMenu(HWND hwnd, HMENU hmenu)
{
}
