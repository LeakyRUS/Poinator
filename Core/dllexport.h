#pragma once

#ifdef POINATOR_CORE_INTERFACE
#define POINATOR_CORE_API __declspec(dllexport)
#else
#define POINATOR_CORE_API __declspec(dllimport)
#endif
#define CEXTERN extern "C"
#define APICALL _cdecl

CEXTERN POINATOR_CORE_API char* APICALL encode_ascii(const char* input_text);

CEXTERN POINATOR_CORE_API char* APICALL decode_ascii(const char* input_text);

CEXTERN POINATOR_CORE_API char* APICALL get_last_error();