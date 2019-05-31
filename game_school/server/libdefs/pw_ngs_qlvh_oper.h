
#ifndef _pw_qlvh_oper_
#define _pw_qlvh_oper_

#include "pw_ngs_common.h"

namespace pwngs
{
	struct SGMCharacterOperator
	{
		int64 hash;
		std::string params;
		pwngs::SHumanQuery userinfo;
		int32 seconds; // optional
		int32 allzone;

		SGMCharacterOperator* Clone()
		{
			return new SGMCharacterOperator(*this);
		}
	};
}

#endif // _pw_qlvh_oper_