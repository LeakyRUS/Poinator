#include <Windows.h>
#include <cstdlib>
#include <stdexcept>
#include "Dll.h"

#define APICALL __stdcall

typedef char*(APICALL _encode_ascii)(const char* input_text);
typedef char*(APICALL _decode_ascii)(const char* input_text);
typedef char*(APICALL _get_last_error)();

HMODULE hModule;

_encode_ascii* encode_ascii;
_decode_ascii* decode_ascii;
_get_last_error* get_last_error;

Ed::Ed()
{
	hModule = ::LoadLibrary("Core.dll");

	encode_ascii = (_encode_ascii*)::GetProcAddress(hModule, "encode_ascii");
	decode_ascii = (_decode_ascii*)::GetProcAddress(hModule, "decode_ascii");
	get_last_error = (_get_last_error*)::GetProcAddress(hModule, "get_last_error");

	if ((encode_ascii == nullptr) || (decode_ascii == nullptr) || (get_last_error == nullptr)) isInit = false;
	else isInit = true;

	if (!isInit) throw new std::runtime_error("Core library is not loaded");
}

Ed::~Ed()
{
	FreeLibrary(hModule);
}

char* Ed::Encode(const char* inputText)
{
	if(isInit) return encode_ascii(inputText);
	else return nullptr;
}

char* Ed::Decode(const char* inputText)
{
	if (isInit) return decode_ascii(inputText);
	else return nullptr;
}

char* Ed::GetLastError()
{
	if (isInit) return get_last_error();
	else return nullptr;
}