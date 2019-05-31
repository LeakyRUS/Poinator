#pragma once
#ifndef _DATAINFO_H_
#define _DATAINFO_H_

namespace Poinator
{
	namespace Core
	{
		// Класс, работающий с шашпкой данных
		class DataInfo
		{
		private:
			// контейнер, содержащий распакованные данные шапки
			struct
			{
				unsigned char version : 6;
				unsigned char fibonacciDecodedMultiplier : 5;
				unsigned char fibonacciEncodedMultiplier : 5;
			} subData;

		public:
			// установить версию
			void version(unsigned char value);
			// взять версию
			unsigned char version() const;

			// установить множитель фибоначчи для распакованных данных
			void decodedMultiplier(unsigned char value);
			// взять множитель фибоначчи для распакованных данных
			unsigned char decodedMultiplier() const;

			// установить множитель фибоначчи для запакованных данных
			void encodedMultiplier(unsigned char value);
			// взять множитель фибоначчи для запакованных данных
			unsigned char encodedMultiplier() const;

			// взять шапку для дальнейшей распаковки
			unsigned char* getData();
			// установить шапку для дальнейшей распаковки
			void setData(unsigned char* data);

			// узнать размер шапки
			size_t getDataSize() const;
		};
	}
}
#endif