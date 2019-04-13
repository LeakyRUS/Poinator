#pragma once

class Ed
{
	bool isInit;
public:
	Ed();
	~Ed();
	char* Encode(const char* inputText);
	char* Decode(const char* inputText);;
	char* GetLastError();
};
