/*

#ifndef _pw_operations_def_
#define _pw_operations_def_

#include "pw_def.h"
#include "kvorm/pw_orm_humanoperation.h"

namespace pwngs
{
	namespace operations
	{
		// ***********************************************************
		//以下结构,不允许升级,更改后必须作为一个新结构去执行操作
		// ***********************************************************
		struct SOperationTest
		{
		};

		// ***********************************************************
		//此枚举 不能删除,不能插入
		// ***********************************************************
		enum
		{
			TEST,


			HUMAN_OPERATION_NUM,
		};

		// ***********************************************************
		// 最大的operation size
		// ***********************************************************
		const size_t cst_max_operation_bufsize = __max(0,sizeof(SOperationTest));
	}
}

#endif // _pw_operations_def_
*/
