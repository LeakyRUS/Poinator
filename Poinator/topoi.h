#pragma once
#ifndef _TOPOI_H_
#define _TOPOI_H_

#include <string>
#include <algorithm>
#include <vector>

//std::string toPoi(std::string base64Code);
//std::string fromPoi(std::string poiText);

std::string toPoi2(std::vector<unsigned char> byteCode);
std::vector<unsigned char> fromPoi2(std::string poiText);

#endif