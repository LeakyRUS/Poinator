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

				for (unsigned i = 3; i <= n; i++)
				{
					unsigned v = res + prev;
					prev = res;
					res = v;
				}

				return res;
			}

			unsigned findFibNbigger(unsigned number)
			{
				constexpr unsigned n = 31;

				unsigned p = 1, r = 1;

				for (unsigned i = 3; i <= n; i++)
				{
					unsigned v = r + p;
					p = r;
					r = v;

					if (r >= number) return i;
				}

				return n;
			}
		}
	}
}