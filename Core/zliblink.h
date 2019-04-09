#pragma once
#include <Windows.h>

HMODULE hModule = ::LoadLibrary("zlibwapi.dll");

typedef int (_cdecl _compress2)(unsigned char *dest, unsigned long int *destLen,
	const unsigned char *source, unsigned long int sourceLen,
	int level);

typedef int(_cdecl _uncompress2)(unsigned char *dest, unsigned long int *destLen,
	const unsigned char *source, unsigned long int *sourceLen);

_compress2* compress2 = (_compress2*)::GetProcAddress(hModule, "compress2");
_uncompress2* uncompress2 = (_uncompress2*)::GetProcAddress(hModule, "uncompress2");
