#include <string>
#include <iostream>
#include "zlib.h"
#include "base64.h"
#include "topoi.h"
#include <vector>
#include <stdexcept>

#pragma comment(lib, "zlibwapi.lib")
#pragma comment(linker, "/DELAYLOAD:zlibwapi.dll")

std::string encoding(std::string userText)
{
	union
	{
		uLong			T_E_S[2];
		unsigned char	chars[(sizeof(uLong) * 2)];
	} bufferSize;

	unsigned char *buff = new unsigned char[userText.size() + 12];
	std::vector<BYTE> encodedText;
	std::string base64EncodedText;
	std::string poiText;

	int err;

	// сжать текст
	bufferSize.T_E_S[1] = userText.size() + 12;
	bufferSize.T_E_S[0] = userText.size() + 1;
	buff = new unsigned char[userText.size() + 12];
	memset(buff, 0, bufferSize.T_E_S[1]);
	err = compress2(buff, &bufferSize.T_E_S[1], (const BYTE*)userText.c_str(), userText.size(), 9);
	if (err != 0)
	{
		delete[] buff;
		throw std::runtime_error("Encoding error - not enough memory!");
	}

	for (int i = 0; i < (sizeof(uLong) * 2); i++)
	{
		encodedText.push_back(bufferSize.chars[i]);
	}
	for (int i = 0; i < bufferSize.T_E_S[1]; i++)
	{
		encodedText.push_back(buff[i]);
	}

	delete[] buff;

	// Кодировать в base64
	base64EncodedText = base64_encode((const BYTE*)encodedText.data(), encodedText.size());

	// Кодировать в Poi
	poiText = toPoi(base64EncodedText);

	return poiText;
}

std::string decoding(std::string poiText)
{
	union
	{
		uLong			T_E_S[2];
		unsigned char	chars[(sizeof(uLong) * 2)];
	} bufferSize;

	bufferSize.T_E_S[0] = 0;
	bufferSize.T_E_S[1] = 0;

	uLong swallow;

	std::string userText;
	unsigned char *buff = new unsigned char[userText.size() + 12];
	std::vector<BYTE> encodedText;
	std::string base64EncodedText;

	int err;

	// Декодировать в base64
	base64EncodedText = fromPoi(poiText);

	// Декодировать в сжатый текст
	encodedText = base64_decode(base64EncodedText);
	for (int i = 0; i < (sizeof(uLong) * 2); i++)
	{
		bufferSize.chars[i] = encodedText[i];
	}
	encodedText.erase(encodedText.begin(), encodedText.begin()+(sizeof(uLong) * 2));

	// Декодировать в текст
	buff = new unsigned char[bufferSize.T_E_S[0]];
	memset(buff, 0, bufferSize.T_E_S[0]);
	swallow = bufferSize.T_E_S[0];
	uLong what = encodedText.size();
	err = uncompress2(buff, &swallow, (const BYTE*)encodedText.data(), &what);
	if (err != 0)
	{
		delete[] buff;
		throw std::runtime_error("Decoding error - wrong encoding data!");
	}
	for (int i = 0; i < bufferSize.T_E_S[0]; i++)
	{
		userText += (char)buff[i];
	}
	delete[] buff;

	return userText;
}

int main()
{
	// Взять у пользователя текст
	// Сжать его
	//     Переместить в другой массив
	// Кодировать в base64
	// Кодировать в Poi
	// -----
	// Декодировать в base64
	// Декодировать в сжатый текст
	// Декодировать в текст

	while (true)
	{
		std::string choise;
		std::cout << "Encode or decode (only ASCI) (x to exit)? (e/d/x) > ";
		std::getline(std::cin, choise);

		if ((choise[0] == 'e') || (choise[0] == 'd'))
		{
			std::string userText;

			// Взять у пользователя текст
			std::cout << "Put your text here > ";
			std::getline(std::cin, userText);

			std::string ed;
			try
			{
				if (choise[0] == 'e')
				{
					ed = encoding(userText);
					std::cout << "Your encoded text: " << ed << "\nLength: " << ed.size() << '\n';
				}
				else if (choise[0] == 'd')
				{
					ed = decoding(userText);
					std::cout << "Your decoded text: " << ed << "\nLength: " << ed.size() << '\n';
				}
			}
			catch (std::runtime_error e)
			{
				std::cout << e.what() << '\n';
			}
		}
		else if (choise[0] == 'x')
		{
			break;
		}
		else std::cout << "Wrong choice!\n";

		std::cout << std::endl;
	}

	return 0;
}
