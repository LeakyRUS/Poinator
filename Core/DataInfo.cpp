#include "DataInfo.h"
#include <cstdint>
#ifdef _DEBUG
#include <iostream>
#endif

union Converter
{
	uint16_t p;
	unsigned char q[2];
};


void Poinator::Core::DataInfo::version(unsigned char value)
{
	subData.version = value;
}

unsigned char Poinator::Core::DataInfo::version() const
{
	return subData.version;
}

void Poinator::Core::DataInfo::decodedMultiplier(unsigned char value)
{
	subData.fibonacciDecodedMultiplier = value;
}

unsigned char Poinator::Core::DataInfo::decodedMultiplier() const
{
	return subData.fibonacciDecodedMultiplier;
}

void Poinator::Core::DataInfo::encodedMultiplier(unsigned char value)
{
	subData.fibonacciEncodedMultiplier = value;
}

unsigned char Poinator::Core::DataInfo::encodedMultiplier() const
{
	return subData.fibonacciEncodedMultiplier;
}

unsigned char* Poinator::Core::DataInfo::getData()
{
	uint16_t pac = 0;

#ifdef _DEBUG
	std::cout << "pac: " << std::hex << pac << std::endl;
#endif

	pac |= (uint16_t)subData.version;
#ifdef _DEBUG
	std::cout << "pac: " << std::hex << pac << std::endl;
#endif
	pac <<= 5;
#ifdef _DEBUG
	std::cout << "pac: " << std::hex << pac << std::endl;
#endif
	pac |= (uint16_t)subData.fibonacciDecodedMultiplier;
#ifdef _DEBUG
	std::cout << "pac: " << std::hex << pac << std::endl;
#endif
	pac <<= 5;
#ifdef _DEBUG
	std::cout << "pac: " << std::hex << pac << std::endl;
#endif
	pac |= (uint16_t)subData.fibonacciEncodedMultiplier;
#ifdef _DEBUG
	std::cout << "pac: " << std::hex << pac << std::endl;
	std::cout << std::dec
		<< "subData.version: " << (uint16_t)subData.version
		<< "\nsubData.fibonacciDecodedMultiplier: " << (uint16_t)subData.fibonacciDecodedMultiplier
		<< "\nsubData.fibonacciEncodedMultiplier: " << (uint16_t)subData.fibonacciEncodedMultiplier << std::endl;
#endif

	Converter h;

	h.p = pac;

	unsigned char* ret = new unsigned char[2];
	ret[0] = h.q[0];
	ret[1] = h.q[1];

	return ret;
}

void Poinator::Core::DataInfo::setData(unsigned char* data)
{
	Converter h;

	h.q[0] = data[0];
	h.q[1] = data[1];

	uint16_t pac = h.p;

	subData.version = pac >> 10;
	subData.fibonacciDecodedMultiplier = pac >> 5;
	subData.fibonacciEncodedMultiplier = pac;

#ifdef _DEBUG
	std::cout << "pac: " << std::hex << pac << std::endl;
	std::cout << std::dec
		<< "subData.version: " << (uint16_t)subData.version
		<< "\nsubData.fibonacciDecodedMultiplier: " << (uint16_t)subData.fibonacciDecodedMultiplier
		<< "\nsubData.fibonacciEncodedMultiplier: " << (uint16_t)subData.fibonacciEncodedMultiplier << std::endl;
#endif
}

size_t Poinator::Core::DataInfo::getDataSize() const
{
	return sizeof(unsigned char) * 2;
}
