#include "EncodeAndDecode.h"
#include "zliblink.h"
#include "topoi.h"
#include "utils.h"
#include "DataInfo.h"
#include <vector>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

//#pragma comment(lib, "zlibwapi.lib")
//#pragma comment(linker, "/DELAYLOAD:zlibwapi.dll")

namespace Poinator
{
	namespace Core
	{
		namespace Transformation
		{
			struct BufferSize
			{
				unsigned long decoded;
				unsigned long encoded;
			};

			namespace ASCII
			{
				// Взять у пользователя текст
				// Сжать его
				//     Переместить в другой массив
				// Кодировать в Poi
				::std::string encoding(::std::string userText)
				{
					DataInfo dataInfo;
					BufferSize bufferSize;
					unsigned char *buff;
					std::vector<unsigned char> encodedText;
					std::string poiText;

					int err;

					// сжать текст
					bufferSize.encoded = userText.size() + 12;
					bufferSize.decoded = userText.size() + 1;
					buff = new unsigned char[bufferSize.encoded];
					memset(buff, 0, bufferSize.encoded);
					err = compress2(buff, &bufferSize.encoded, (const unsigned char*)userText.c_str(), userText.size(), 9);
					if (err != 0)
					{
						delete[] buff;
						throw std::runtime_error("Encoding error - not enough memory!");
					}

					dataInfo.version(ver);
					dataInfo.decodedMultiplier(Utils::findFibNbigger(bufferSize.decoded));
					dataInfo.encodedMultiplier(Utils::findFibNbigger(bufferSize.encoded));

					unsigned char* dataI = dataInfo.getData();
#ifdef _DEBUG
					std::cout << "DataInfo hex data: ";
#endif
					for (size_t i = 0; i < dataInfo.getDataSize(); i++)
					{
						encodedText.push_back(dataI[i]);

#ifdef _DEBUG
						std::cout << std::hex << (uint16_t)dataI[i] << ' ';
#endif
					}
#ifdef _DEBUG
					std::cout << "\nzlib data: ";
#endif
					for (int i = 0; i < bufferSize.encoded; i++)
					{
						encodedText.push_back(buff[i]);

#ifdef _DEBUG
						std::cout << std::hex << (uint16_t)buff[i];
#endif
					}
#ifdef _DEBUG
					std::cout << "\nbufferSize.decoded = " << std::dec << bufferSize.decoded << "\nbufferSize.encoded = " << bufferSize.encoded << std::endl;
#endif

					delete[] buff;
					delete[] dataI;

					// Кодировать в Poi
					poiText = toPoi2(encodedText);

					return poiText;
				}

				// Декодировать в сжатый текст
				// Декодировать в текст
				::std::string decoding(::std::string poiText)
				{
					DataInfo dataInfo;
					BufferSize bufferSize;

					std::string userText;
					unsigned char *buff;
					std::vector<unsigned char> encodedText;

					int err;

					unsigned char* dataI = new unsigned char[2];

					// Декодировать в сжатый текст
					encodedText = fromPoi2(poiText);
					if (encodedText.size() < 5)
					{
						delete[] dataI;
						throw new std::runtime_error("Decoding error - wrong encoding data!");
					}
#ifdef _DEBUG
					std::cout << "DataInfo hex data: ";
#endif
					for (int i = 0; i < dataInfo.getDataSize(); i++)
					{
						dataI[i] = encodedText[i];
#ifdef _DEBUG
						std::cout << std::hex << (uint16_t)dataI[i] << ' ';
#endif
					}
#ifdef _DEBUG
					std::cout << std::endl;
#endif
					encodedText.erase(encodedText.begin(), encodedText.begin() + sizeof(unsigned char) * 2);

					dataInfo.setData(dataI);
					delete[] dataI;

					if (dataInfo.version() != ver)
					{
						throw std::runtime_error("Decoding error - the coded text version is not suitable!");
					}

					bufferSize.decoded = Utils::findFibonacci(dataInfo.decodedMultiplier());
					bufferSize.encoded = encodedText.size();

					// Декодировать в текст
					buff = new unsigned char[bufferSize.decoded];
					memset(buff, 0, bufferSize.decoded);

#ifdef _DEBUG
					std::cout << "\nzlib data: ";
					for (size_t i = 0; i < bufferSize.encoded; i++)
					{
						std::cout << std::hex << (uint16_t)encodedText[i];
					}
					std::cout << "\nbufferSize.decoded = " << std::dec << bufferSize.decoded << "\nbufferSize.encoded = " << bufferSize.encoded << std::endl;
#endif

					err = uncompress2(buff, &bufferSize.decoded, (const unsigned char*)encodedText.data(), &bufferSize.encoded);
#ifdef _DEBUG
					std::cout << "\nbufferSize.decoded = " << std::dec << bufferSize.decoded << "\nbufferSize.encoded = " << bufferSize.encoded << std::endl;
#endif
					if (err != 0)
					{
						delete[] buff;
						throw std::runtime_error("Decoding error - wrong encoding data!");
					}
					for (int i = 0; i < bufferSize.decoded; i++)
					{
						userText += (char)buff[i];
					}
					delete[] buff;

					return userText;
				}
			}
		}
	}
}