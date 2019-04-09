#pragma once
#ifndef _ENCODEANDDECODE_H_
#define _ENCODEANDDECODE_H_
#include <string>

namespace Poinator
{
	namespace Core
	{
		namespace Transformation
		{
			constexpr unsigned char ver = 63;

			namespace ASCII
			{
				::std::string encoding(::std::string userText);
				::std::string decoding(::std::string poiText);
			}
		}
	}
}
#endif
