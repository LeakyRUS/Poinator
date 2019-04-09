#pragma once
#ifndef _TOPOI_H_
#define _TOPOI_H_

#include <string>
#include <vector>

namespace Poinator
{
	namespace Core
	{
		namespace Transformation
		{
			namespace ASCII
			{
				std::string toPoi2(std::vector<unsigned char> byteCode);
				std::vector<unsigned char> fromPoi2(std::string poiText);
			}
		}
	}
}
#endif