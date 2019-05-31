#include "pw_math.h"
#include <math.h>

namespace pwutils
{
/*
	FastSinCos g_objFastSinCos;
	static double twoPI = 6.28318531f;

	FastSinCos::FastSinCos()
	{
		this->initial();
	}

	void FastSinCos::initial()
	{
		m_fFactor = double(TABLE_SIZE)/twoPI;

		for(unsigned i = 0; i < TABLE_SIZE; ++i)
		{
			double angle = ((double)i / (double)TABLE_SIZE) * twoPI;
			m_fSinTable[i] = ::sin(angle);
			m_fCosTable[i] = ::cos(angle);
		}		
	}

	double FastSinCos::sin( double value )
	{
		if(value < 0.0f)
			value += twoPI;
		int index = (int)(value * m_fFactor);
		return m_fSinTable[index];
	}

	double FastSinCos::cos( double value )
	{
		if(value < 0.0f)
			value += twoPI;
		int index = (int)(value * m_fFactor);
		return m_fCosTable[index];
	}
*/

}