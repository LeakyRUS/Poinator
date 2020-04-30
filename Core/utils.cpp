#include "utils.h"
#include <cmath>

unsigned Poinator::Core::Utils::findFibonacci(unsigned n)
{
	unsigned prev = 1, res = 1;

	for (unsigned i = 3; i <= n; ++i)
	{
		unsigned v = res + prev;
		prev = res;
		res = v;
	}

	return res;
}

unsigned Poinator::Core::Utils::findFibNbigger(unsigned number, unsigned max)
{
	unsigned p = 1, r = 1;

	for (unsigned i = 3; i <= max; ++i)
	{
		unsigned v = r + p;
		p = r;
		r = v;

		if (r >= number) return i;
	}

	return max;
}
