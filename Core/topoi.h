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
				// ���������� ������ ���� � "Poi" �����
				std::string toPoi2(std::vector<unsigned char> byteCode);

				// ������������ "Poi" ����� � ������ ����
				std::vector<unsigned char> fromPoi2(std::string poiText);
			}
		}
	}
}
#endif