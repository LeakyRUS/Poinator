#pragma once

/*
	dll export
*/
#ifdef POINATOR_CORE_INTERFACE
#define POINATOR_CORE_API __declspec(dllexport)
#else
#define POINATOR_CORE_API __declspec(dllimport)
#endif
#define CEXTERN extern "C"
#define APICALL _cdecl

// зашифровать
CEXTERN POINATOR_CORE_API char* APICALL encode_ascii(const char* input_text);

// разшифровать
CEXTERN POINATOR_CORE_API char* APICALL decode_ascii(const char* input_text);

// получить сообщение об ошибке
CEXTERN POINATOR_CORE_API char* APICALL get_last_error();