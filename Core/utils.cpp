#include "utils.h"
#include <cmath>

namespace Poinator
{
	namespace Core
	{
		namespace Utils
		{
			unsigned findFibonacci(unsigned n)
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

			unsigned findFibNbigger(unsigned number, unsigned max = 31)
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
		}
	}
}