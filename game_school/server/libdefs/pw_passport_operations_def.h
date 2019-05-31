/*
#ifndef _pw_passport_operations_def_
#define _pw_passport_operations_def_

namespace pwngs
{
	namespace passport_operations
	{
		// ***********************************************************
		//以下结构,不允许升级,更改后必须作为一个新结构去执行操作
		// ***********************************************************
		struct SOperationCharge
		{
			int64	gold;
		};

		// ***********************************************************
		//此枚举 不能删除,不能插入
		// ***********************************************************
		enum
		{
			Charge,


			Num,
		};

		// ***********************************************************
		// 最大的operation size
		// ***********************************************************
		const size_t cst_max_operation_bufsize = __max(0,sizeof(SOperationCharge));
	}
}

#endif // _pw_passport_operations_def_
*/