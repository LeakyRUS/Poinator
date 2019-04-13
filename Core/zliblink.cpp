#include <Windows.h>
#include <cstdlib>
#include "zliblink.h"
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

#define APICALL _cdecl

typedef int(APICALL _compress2)(unsigned char *dest, unsigned long int *destLen,
	const unsigned char *source, unsigned long int sourceLen,
	int level);

typedef int(APICALL _uncompress2)(unsigned char *dest, unsigned long int *destLen,
	const unsigned char *source, unsigned long int *sourceLen);

HMODULE hModule;

_compress2* zlib_compress;
_uncompress2* zlib_uncompress;

ZlibLink::ZlibLink()
{
	HMODULE hModule = ::LoadLibrary("zlibwapi.dll");

	zlib_compress = (_compress2*)::GetProcAddress(hModule, "compress2");
	zlib_uncompress = (_uncompress2*)::GetProcAddress(hModule, "uncompress2");

	if ((zlib_compress == nullptr) || (zlib_uncompress == nullptr)) isInit = false;
	else isInit = true;

	if (!isInit) throw new std::runtime_error("zlib library is not loaded");
}

ZlibLink::~ZlibLink()
{
	FreeLibrary(hModule);
}

int ZlibLink::compress2(unsigned char *dest, unsigned long int *destLen,
	const unsigned char *source, unsigned long int sourceLen,
	int level)
{
	if(isInit) return ::zlib_compress(dest, destLen, source, sourceLen, level);
	else return 1;
}

int ZlibLink::uncompress2(unsigned char *dest, unsigned long int *destLen,
	const unsigned char *source, unsigned long int *sourceLen)
{
	if(isInit) return ::zlib_uncompress(dest, destLen, source, sourceLen);
	else return 1;
}