#ifndef _pw_bitset_utils_
#define _pw_bitset_utils_

#include "pw_logger.h"

namespace pwutils
{
	struct BitsetUtils
	{
		void Set(size_t index,bool setItTrue = true)
		{
			pwassert(index < bitsNum);

			int bit = index % 32;
			int idx = index / 32;

			if(setItTrue)
				bits[idx] |= (1 << bit);
			else
				bits[idx] &= ~(1 << bit);
		}

		bool Get(size_t index)
		{
			pwassertn(index < bitsNum);
			int bit = index % 32;
			int idx = index / 32;

			return bits[idx] & (1 << bit);
		}

		BitsetUtils()
			: bits(0)
			, bitsNum(0)
		{
		}

		uint32* bits;
		size_t  bitsNum;
	};
}

#endif // _pw_bitset_utils_