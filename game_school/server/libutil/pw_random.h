#ifndef _pw_random_
#define _pw_random_

#ifdef _MSC_VER
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <wincrypt.h>
#endif

#include "pw_def.h"

namespace pwutils
{
#ifdef _MSC_VER
	class RandomGenerator
	{
	public:
		RandomGenerator();
		~RandomGenerator();
	public:
		int64 Gen();
	private:
		HCRYPTPROV m_hProv;
	};
#else
	class RandomGenerator
	{
	public:
		RandomGenerator();
		~RandomGenerator();
	public:
		int64 Gen();
	private:
		FILE* m_pFile;
	};
#endif

	extern RandomGenerator g_objRandomGenerator;

}
#endif // _pw_random

