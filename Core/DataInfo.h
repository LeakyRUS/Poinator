#pragma once
#ifndef _DATAINFO_H_
#define _DATAINFO_H_

namespace Poinator
{
	namespace Core
	{
		class DataInfo
		{
		private:
			struct
			{
				unsigned char version : 6;
				unsigned char fibonacciDecodedMultiplier : 5;
				unsigned char fibonacciEncodedMultiplier : 5;
			} subData;

		public:
			void version(unsigned char value);
			unsigned char version() const;

			void decodedMultiplier(unsigned char value);
			unsigned char decodedMultiplier() const;

			void encodedMultiplier(unsigned char value);
			unsigned char encodedMultiplier() const;

			unsigned char* getData();
			void setData(unsigned char* data);

			size_t getDataSize() const;
		};
	}
}
#endif