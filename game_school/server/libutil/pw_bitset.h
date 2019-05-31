#ifndef _pw_bitset_
#define _pw_bitset_

#include "pw_def.h"
#include "pw_logger.h"


namespace pwngs
{
	template<int N = 16> class TwoBitSet
	{
	public:
		TwoBitSet()
		{
			memset(m_nStates,0,sizeof(m_nStates));
		}
	public:
		inline uint8 Get(int index)
		{
			pwassertn(index < N);
			int idx = index >> 4;
			int bit = (index & 0xf) << 1;

			return (m_nStates[idx] >> bit) & 0x3;
		}

		inline void Set(int index,uint8 set)
		{
			pwassert(index < N);
			int idx = index >> 4;
			int bit = (index & 0xf) << 1;

			m_nStates[idx] &= ~(0x3 << bit);
			m_nStates[idx] |= (set & 0x3) << bit;
		}

		inline void Clean()
		{
			memset(m_nStates,0,sizeof(m_nStates));
		}

		inline bool IsZero()
		{
			for(int i = 0; i < _countof(m_nStates); ++i)
			{
				if(m_nStates[i] != 0)
					return false;
			}
			return true;
		}
	private:
		uint32 m_nStates[N*2/32];
	};

	/**
	 * @class Bitset
	 * @author cbh
	 * @date 2011年09月21日
	 * @file pw_bitset.h
	 * @brief bitset
	 */
	template<int N = 32> class Bitset
	{
	public:
		Bitset()
		{
			memset(m_nStates,0,sizeof(m_nStates));
		}
	public:
		inline int GetBitsNum()
		{
			return N;
		}
		inline bool Get(int index)
		{
			pwassertn(index < (N*32));
			int bit = index % 32;
			int idx = index / 32;

			return m_nStates[idx] & (1 << bit);
		}

		inline void Set(int index,bool set)
		{
			pwassert(index < (N*32));
			int bit = index % 32;
			int idx = index / 32;

			if(set)
				m_nStates[idx] |= (1 << bit);
			else
				m_nStates[idx] &= ~(1 << bit);
		}

		inline void SetAll()
		{
			for(int i = 0; i < _countof(m_nStates); ++i)
			{
				m_nStates[i] = 0xffffffff;
			}
		}
		
		inline void Clean()
		{
			memset(m_nStates,0,sizeof(m_nStates));
		}

		inline bool IsZero()
		{
			for(int i = 0; i < _countof(m_nStates); ++i)
			{
				if(m_nStates[i] != 0)
					return false;
			}
			return true;
		}
	public:
		inline void* GetBuf()
		{
			return m_nStates;
		}

		inline size_t GetLen()
		{
			return sizeof(m_nStates);
		}
	public:
		inline uint32* GetInternalUint()
		{
			return m_nStates;
		}

		inline size_t GetInternalUintNum()
		{
			return _countof(m_nStates);
		}
	private:
		uint32 m_nStates[N/32];
	};

	template<int N = 10,typename T = unsigned char> class BitsetEx
	{
	public:
		BitsetEx()
		{
			memset(m_nBits,0,sizeof(m_nBits));
		}

		inline int Set(size_t i, bool addOrDec)
		{
			pwassertn(i >= 0 && i < N);

			if(addOrDec)
			{
				++ m_nBits[i];
			}
			else
			{
				pwreportvars(m_nBits[i] > 0,i);
				pwassertn(m_nBits[i] > 0);
				-- m_nBits[i];
			}
			return 0;
		}

		inline int Get(size_t i)
		{
			pwassertn(i >= 0 && i < N);
			return m_nBits[i] > 0;
		}
		
		inline void Clean()
		{
			memset(m_nBits,0,sizeof(m_nBits));
		}

		inline bool IsZero()
		{
			for(int i = 0; i < _countof(m_nBits); ++i)
			{
				if(m_nBits[i] != 0)
					return false;
			}
			return true;
		}
	private:
		T m_nBits[N];
	};

}


#endif // _pw_bitset_
