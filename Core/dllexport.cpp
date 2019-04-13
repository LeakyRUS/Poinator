#include "dllexport.h"
#include "EncodeAndDecode.h"

static std::string errorMessage;

char* APICALL encode_ascii(const char* input_text)
{
	std::string userMessage = input_text;
	std::string result;

	try
	{
		result = Poinator::Core::Transformation::ASCII::encoding(userMessage);
	}
	catch (std::runtime_error e)
	{
		errorMessage = std::string("Library error: ") + e.what();
		result = " ";
	}
	catch (...)
	{
		errorMessage = "STD exception";
		result = " ";
	}

	errorMessage.erase();

	char* res = new char[result.size() + 1];
	strcpy_s(res, result.size() + 1, result.c_str());

	return res;
}

char* APICALL decode_ascii(const char* input_text)
{
	std::string userMessage = input_text;
	std::string result;

	try
	{
		result = Poinator::Core::Transformation::ASCII::decoding(userMessage);
	}
	catch (std::runtime_error e)
	{
		errorMessage = std::string("Library error: ") + e.what();
		result = " ";
	}
	catch (...)
	{
		errorMessage = "STD exception";
		result = " ";
	}

	errorMessage.erase();

	char* res = new char[result.size() + 1];
	strcpy_s(res, result.size() + 1, result.c_str());

	return res;
}

char* APICALL get_last_error()
{
	if (errorMessage.empty()) errorMessage = "All good, no errors here";

	char* res = new char[errorMessage.size() + 1];
	strcpy_s(res, errorMessage.size() + 1, errorMessage.c_str());

	errorMessage.erase();

	return res;
}