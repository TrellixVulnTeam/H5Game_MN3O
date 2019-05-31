#include "pw_dynamic_module.h"
#include "pw_platform.h"
#include <iostream>

#ifdef __linux__
	#include <dlfcn.h>
#endif

namespace pwutils
{
	DynamicModule::DynamicModule()
		: m_hModule(NULL)
	{

	}

	DynamicModule::~DynamicModule()
	{
		if(m_hModule != NULL)
			this->Dlclose();
	}

#ifdef _MSC_VER
	
	bool DynamicModule::Dlopen( const char* filename )
	{
		HMODULE h = LoadLibraryA(filename);
		if(h == NULL || h == INVALID_HANDLE_VALUE)
			return false;
		m_hModule = (void*)h;
		return true;
	}

	void DynamicModule::Dlclose()
	{
		FreeLibrary((HMODULE)m_hModule);
		m_hModule =  NULL;
	}

	void* DynamicModule::Dlsym( const char* name )
	{
		return (void*)GetProcAddress((HMODULE)m_hModule,name);
	}

#else

	bool DynamicModule::Dlopen( const char* filename )
	{
		m_hModule = dlopen(filename,RTLD_NOW);
		if(m_hModule == NULL)
		{
			std::cout << __FUNCTION__ << " LoadSO:" << filename << " Failed,Error="  << dlerror() << std::endl;
		}
		return m_hModule != NULL;
	}

	void DynamicModule::Dlclose()
	{
		dlclose(m_hModule);
		m_hModule = NULL;
	}

	void* DynamicModule::Dlsym( const char* name )
	{
		return (void*)dlsym(m_hModule,name);
	}

#endif
}