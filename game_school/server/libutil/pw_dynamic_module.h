#ifndef _pw_dynamic_module_
#define _pw_dynamic_module_

namespace pwutils
{
	class DynamicModule
	{
	public:
		DynamicModule();
		virtual ~DynamicModule();
	public:
		bool  Dlopen(const char* filename);
		void  Dlclose();
		void* Dlsym(const char* name);
	protected:
		void* m_hModule;
	};
}


#endif // _pw_dynamic_module_