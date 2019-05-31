#ifndef _pw_hmodule_
#define _pw_hmodule_

#include "pw_def.h"
#include "pw_any_ptr.h"
#include "pw_autoptr.h"

namespace pwutils
{
	class HModuleManager;
	class HModuleConstructor;
	class HPersistentStream;
	class DynamicModule;

	typedef size_t HCtorId;
	typedef void (*fnModuleConstructor)(HModuleManager* manager,void* context);

	struct HARGS : public std::vector<pwutils::any_ref>
	{
	public:
		template<class T> T castp(size_t i)
		{
			if(i >= this->size())
				return NULL;
			return this->at(i).cast<T>();
		}

		template<class T> T castv(size_t i)
		{
			if(i >= this->size())
				return T();
			return this->at(i).cast<T>();
		}
	};
	typedef std::vector<pwutils::any_ptr> HRETS;

	/*
	 @class HModule
	 @author cbh
	 @date 2014/5/22 15:09:25
	 @file pw_hmodule.h
	 @brief 热加载模块
		
	************************************************************
	 1)所有函数必须为虚函数
	 2)所有数据成员不可被外界直接访问(必须通过函数访问)
	 3)对象不能被Owner以外的对象持有指针
	 4)替换对象的so,不能修改类接口，只能变更实现代码
	************************************************************
	*/
	class HModule
	{
		friend class HModuleConstructor;
	public:
		HModule();
		virtual ~HModule();
	public:
		virtual void HInit(void* context) {};
		virtual void HSave(HPersistentStream& stream) = 0;
		virtual void HLoad(HPersistentStream& stream) = 0;
		virtual void HExec(int64 code,HARGS* pparams,HRETS* presults) {}
	public:
		virtual void* HGetUpdateContext()
		{
			return NULL;
		}
	public:
		inline HCtorId HGetCtorId()
		{
			return m_nCtorId;
		}
	private:
		HCtorId m_nCtorId;
	};

	/*
	 @class 热加载模块观察者
	 @author cbh
	 @date 2014/5/22 15:09:37
	 @file pw_hmodule.h
	 @brief 
	*/
	class HModuleObserve
	{
	public:
		HModuleObserve(HModuleManager* mgr = NULL);
		virtual ~HModuleObserve();
	public:
		virtual size_t OnCtorUpdated(HModuleConstructor* ctor) = 0;
	private:
		HModuleManager* m_pHMgr;
	};

	/*
	 @class 模块构造器
	 @author cbh
	 @date 2014/5/22 15:09:54
	 @file pw_hmodule.h
	 @brief 
	*/
	class HModuleConstructor
	{
		friend class HModuleManager;
	public:
		HModuleConstructor();
		virtual ~HModuleConstructor();
	public:
		virtual HModule* Create(void* context);
		virtual HModule* Update(HModule* m,void* context = NULL);
	public:
		inline HCtorId GetId()
		{
			return m_nCtorId;
		}

		inline void SetId(HCtorId id)
		{
			assert(m_nCtorId == (HCtorId)-1);
			m_nCtorId = id;
		}

		inline const std::string& GetName()
		{
			return m_sCtorName;
		}

		inline void SetName(const std::string& name)
		{
			assert(m_sCtorName.length() == 0);
			m_sCtorName = name;
		}
	public:
		HModule* HInit(HModule* m,void* context)
		{
			m->m_nCtorId = m_nCtorId;
			m->HInit(context);
			return m;
		}
	protected:
		HCtorId m_nCtorId;
		std::string m_sCtorName;
	};

	/*
	 @class 热加载模块管理器(每线程一个)
	 @author cbh
	 @date 2014/5/22 15:10:08
	 @file pw_hmodule.h
	 @brief 
	*/
	class HModuleManager
	{
	public:
		HModuleManager();
		~HModuleManager();
	public:
		void LoadModule(const char* name);
		void LoadModuleDelay(const char* name);
	public:
		HModule* CreateModule(HCtorId ctorid,void* context = NULL);
		HModule* CreateModule(const std::string& name,void* context = NULL);
	public:
		HModuleConstructor* Get(HCtorId id);
		HModuleConstructor* Get(const std::string& name);
		HCtorId GetCtorId(const std::string& name);
	public:
		void Add(HModuleObserve* observe);
		void Del(HModuleObserve* observe);
	public:
		bool Add(HModuleConstructor* ctor);
		bool DoModuleLoaded(HModuleConstructor* ctor);
		bool Replace(HModuleConstructor* ctor);
	public:
		size_t DoConstructorUpdated(HModuleConstructor* ctor);
	public:
		void Tick(int64 curr);
		void Sync(HModuleManager* mgr = NULL);
	public:
		typedef std_unordered_set<HModuleObserve*> CollectionObservesT;
		typedef std_unordered_map<std::string,HCtorId> CollectionCtorNamesT;
		typedef std::vector<HModuleConstructor*> CollectionCtorIndeicesT;
		typedef std_unordered_map<std::string,DynamicModule*> CollectionModulesT;
		typedef std::vector<HModuleManager*> CollectionManagersT;
		typedef std::list<std::string> CollectionDelayedModuelsT;
	public:
		typedef tbb::concurrent_queue<HModuleConstructor*> CollectionDispatchCtorsT;
		typedef tbb::concurrent_queue<HModuleManager*> CollectionDispatchManagersT;
	private:
		CollectionObservesT m_vObserves;
		CollectionCtorNamesT m_vCtorNames;
		CollectionCtorIndeicesT m_vCtors;
		CollectionModulesT m_vDynamicModules;
		CollectionDelayedModuelsT m_lDelayedModuels;
	private:
		CollectionDispatchCtorsT m_vDispatchedCtors;
		CollectionDispatchManagersT m_vDispatchedMgrs;
	private:
// 		pthread_rwlock_t m_vManagerLock;
		CollectionManagersT m_vManagers;
	private:
		int64 m_nLastCheckTick;
		int64 m_nLastLoadDelayTick;
	};

	/*
	 @class HPersistentStream
	 @author cbh
	 @date 2014/5/22 15:57:27
	 @file pw_hmodule.h
	 @brief 持久化流
	*/
	class HPersistentStream
	{
		template<class T> struct IsPointerType
		{
			enum { Result = 0, };
		};

		template<class T> struct IsPointerType<T*>
		{
			enum { Result = 1, };
		};
	public:
		HPersistentStream();
	public:
		template<class T> void save(const T& v)
		{
			assert(!IsPointerType<T>::Result && "unsupport pointer type");
			m_vObjects.push_back(v);
		}
	public:
		template<class T> bool load(T& v)
		{
			assert(!IsPointerType<T>::Result && "unsupport pointer type");

			if(m_nPosition >= m_vObjects.size())
				return false;

			if(T* p = m_vObjects[m_nPosition].castp<T>())
			{
				v = *p;
				++m_nPosition;
				return true;
			}
			return false;
		}

		void reset()
		{
			m_nPosition = 0;
			m_vObjects.clear();
		}
	private:
		typedef std::vector<pwutils::any_ref> CollectionObjectsT;
	private:
		size_t m_nPosition;
		CollectionObjectsT m_vObjects;
	};

	// **************************************************************************************

	/*
	 @class HModuleContainer
	 @author cbh
	 @date 2014/5/22 15:57:27
	 @file pw_hmodule.h
	 @brief 热更新模块容器
	*/
	class HModuleContainer : public HModuleObserve
	{
	public:
		virtual ~HModuleContainer();
	public:
		virtual size_t OnCtorUpdated(HModuleConstructor* ctor);
	public:
		HModule* Get(HCtorId id);
		HModule* Add(HCtorId id,void* context = NULL);
		bool	 Del(HCtorId id);
	public:
		template<class T> HModule* Get()
		{
			return this->Get(T::GetClassId());
		}
		template<class T> HModule* Add(void* context = NULL)
		{
			return this->Add(T::GetClassId(),context);
		}
		template<class T> bool     Del()
		{
			return this->Del(T::GetClassId());
		}
	protected:
		struct SModuleInfo
		{
			HCtorId  ctorid;
			HModule* module;
		};
	protected:
		typedef std::vector<SModuleInfo> CollectionModulesT;
	protected:
		CollectionModulesT m_vModules;
	};


	// **************************************************************************************

	extern HModuleManager* GetCurrHModuleMgr();
	extern HModuleManager* GetMainHModuleMgr();

	// **************************************************************************************

#define HMODULE_IMPL_NAME(T) T##Impl
#define HMODULE_CTOR_NAME(T) T##HModuleConstructor
#define HMODULE_CTORID(T) T##HModuleConstructor::GetClassId()
#define HMODULE_NAME(T) #T
#define HMODULE_CTOR_CLASS_DECL(T) class T##HModuleConstructor : public pwutils::HModuleConstructor \
	{\
	public:\
		T##HModuleConstructor() { m_sCtorName = HMODULE_NAME(T); } \
		virtual pwutils::HModule* Create(void* context) { T* v = new T(); return this->HInit(v,context); };\
	public:\
		static pwutils::HCtorId GetClassId();\
	}

#define HMODULE_CTOR_CLASS_IMPL(T) \
	pwutils::HCtorId T##HModuleConstructor::GetClassId()\
	{\
		static pwutils::HCtorId s_ctorid = -1;\
		if(s_ctorid == -1) s_ctorid = pwutils::GetCurrHModuleMgr()->GetCtorId(HMODULE_NAME(T));\
		return s_ctorid;\
	}

#define HMODULE_DECL(T) public: static pwutils::HCtorId GetClassId();\
						private:\
							class Impl;\
							friend class Impl;\
							Impl* m_pImpl

#ifdef _MSC_VER
	#define HMODULE_IMPL(T)
#else
	#define HMODULE_IMPL(T) extern "C" void hinit(pwutils::HModuleManager* manager,void* context)\
		{\
			pwutils::HModuleConstructor* ctor = new HMODULE_CTOR_NAME(T)();\
			manager->DoModuleLoaded(ctor);\
			manager->DoConstructorUpdated(ctor);\
		}
#endif

#ifdef _MSC_VER
	#define HMODULE_REGISTER(mgr,T) \
			mgr->Add(new HMODULE_CTOR_NAME(T)());\
			HMODULE_CTOR_NAME(T)::GetClassId()
#else
	#define HMODULE_REGISTER(mgr,T) \
			HMODULE_CTOR_NAME(T)::GetClassId()
#endif

}


#endif // _pw_hmodule_