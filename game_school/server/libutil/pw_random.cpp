#include "pw_random.h"

namespace pwutils
{
	RandomGenerator g_objRandomGenerator;

#ifdef _MSC_VER
	RandomGenerator::RandomGenerator()
	{
		m_hProv = NULL;
		if(!CryptAcquireContext(&m_hProv, NULL, NULL, PROV_RSA_FULL, 0)) 
		{
			if( !CryptAcquireContext(&m_hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET) ) 
				assert(false && "CryptAcquireContext Failed. \n");
		}
	}

	RandomGenerator::~RandomGenerator()
	{
		if(m_hProv != NULL)
			CryptReleaseContext(m_hProv,0);
	}

	int64 RandomGenerator::Gen()
	{
		if( m_hProv != NULL)
		{
			int64 result = 0;
			if(CryptGenRandom( m_hProv, sizeof(result), (BYTE*)&result)) 
			{
				return result;
			}
		}
		return ((int64)rand() << 32) + rand();
	}
#else
	RandomGenerator::RandomGenerator()
	{
		m_pFile = fopen("/dev/urandom","r");
		assert(m_pFile && "can't open urandom");
	}

	RandomGenerator::~RandomGenerator()
	{
		fclose(m_pFile);
	}
	
	int64 RandomGenerator::Gen()
	{
		int64 result = 0;
		fread(&result,sizeof(result),1,m_pFile);
		return result;
	}

#endif

}