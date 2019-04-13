#pragma once

class ZlibLink
{
	bool isInit;
public:
	ZlibLink();
	~ZlibLink();
	int compress2(unsigned char *dest, unsigned long int *destLen,
		const unsigned char *source, unsigned long int sourceLen,
		int level);
	int uncompress2(unsigned char *dest, unsigned long int *destLen,
		const unsigned char *source, unsigned long int *sourceLen);
};

