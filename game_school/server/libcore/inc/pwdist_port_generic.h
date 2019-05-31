#ifndef _pwdist_port_generic_
#define _pwdist_port_generic_

#include "pwdist_port.h"

namespace pwdist
{
	class GenericPort : public PortBase
	{
	public:
		GenericPort();
	public:
		static Port* self();
	public:
		void MakeCall(MsgCall& call,ICallableObject* caller,const_char_ptr method)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def);
			GenCallMsg(call,caller,msgid_rpc,method,def);
			pwdist::CallParameterHelper::MakeParams(call.params);
			i_SetCall(call);
		}
		template<class P1> void MakeCall(MsgCall& call,ICallableObject* caller,const_char_ptr method,P1 v1)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1);
			GenCallMsg(call,caller,msgid_rpc,method,def);
			pwdist::CallParameterHelper::MakeParams(call.params,v1);
			i_SetCall(call);
		}
		template<class P1,class P2> void MakeCall(MsgCall& call,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2);
			GenCallMsg(call,caller,msgid_rpc,method,def);
			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2);
			i_SetCall(call);
		}
		template<class P1,class P2,class P3> void MakeCall(MsgCall& call,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3);
			GenCallMsg(call,caller,msgid_rpc,method,def);
			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3);
			i_SetCall(call);
		}
		template<class P1,class P2,class P3,class P4> void MakeCall(MsgCall& call,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3,v4);
			GenCallMsg(call,caller,msgid_rpc,method,def);
			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4);
			i_SetCall(call);
		}
		template<class P1,class P2,class P3,class P4,class P5> void MakeCall(MsgCall& call,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3,v4,v5);
			GenCallMsg(call,caller,msgid_rpc,method,def);
			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4,v5);
			i_SetCall(call);
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6> void MakeCall(MsgCall& call,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5,P6 v6)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3,v4,v5,v6);
			GenCallMsg(call,caller,msgid_rpc,method,def);
			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4,v5,v6);
			i_SetCall(call);
		}
	public:
		size_t MakeCall(char* buf,size_t len,ICallableObject* caller,const_char_ptr method)
		{
			MsgCall call = {0};
			MakeCall(call,caller,method);

			size_t n = call.Bytes();
			assert(n <= len);

			call.Save(buf,n);

			return n;
		}

		template<class P1> size_t MakeCall(char* buf,size_t len,ICallableObject* caller,const_char_ptr method,P1 v1)
		{
			MsgCall call = {0};
			MakeCall(call,caller,method,v1);

			size_t n = call.Bytes();
			assert(n <= len);

			call.Save(buf,n);

			return n;
		}

		template<class P1,class P2> size_t MakeCall(char* buf,size_t len,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2)
		{
			MsgCall call = {0};
			MakeCall(call,caller,method,v1,v2);

			size_t n = call.Bytes();
			assert(n <= len);

			call.Save(buf,n);

			return n;
		}

		template<class P1,class P2,class P3> size_t MakeCall(char* buf,size_t len,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3)
		{
			MsgCall call = {0};
			MakeCall(call,caller,method,v1,v2,v3);

			size_t n = call.Bytes();
			assert(n <= len);

			call.Save(buf,n);

			return n;
		}

		template<class P1,class P2,class P3,class P4> size_t MakeCall(char* buf,size_t len,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4)
		{
			MsgCall call = {0};
			MakeCall(call,caller,method,v1,v2,v3,v4);

			size_t n = call.Bytes();
			assert(n <= len);

			call.Save(buf,n);

			return n;
		}

		template<class P1,class P2,class P3,class P4,class P5> size_t MakeCall(char* buf,size_t len,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5)
		{
			MsgCall call = {0};
			MakeCall(call,caller,method,v1,v2,v3,v4,v5);

			size_t n = call.Bytes();
			assert(n <= len);

			call.Save(buf,n);

			return n;
		}

		template<class P1,class P2,class P3,class P4,class P5,class P6> size_t MakeCall(char* buf,size_t len,ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5,P6 v6)
		{
			MsgCall call = {0};
			MakeCall(call,caller,method,v1,v2,v3,v4,v5,v6);

			size_t n = call.Bytes();
			assert(n <= len);

			call.Save(buf,n);

			return n;
		}
	public:
		int DispatchChunk(ICallableObject* obj,char* buf,size_t len);
	public:
		int Call(ICallableObject* caller,const_char_ptr method)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def);

			MsgCall call = {0};
			GenCallMsg(call,caller,msgid_rpc,method,def);

			pwdist::CallParameterHelper::MakeParams(call.params);

			return this->i_Call(call);
		}

		template<class P1> int Call(ICallableObject* caller,const_char_ptr method,P1 v1)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1);

			MsgCall call = {0};
			GenCallMsg(call,caller,msgid_rpc,method,def);

			pwdist::CallParameterHelper::MakeParams(call.params,v1);

			return this->i_Call(call);
		}

		template<class P1,class P2> int Call(ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2);

			MsgCall call = {0};
			GenCallMsg(call,caller,msgid_rpc,method,def);

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2);

			return this->i_Call(call);
		}

		template<class P1,class P2,class P3> int Call(ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3);

			MsgCall call = {0};
			GenCallMsg(call,caller,msgid_rpc,method,def);

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3);

			return this->i_Call(call);
		}

		template<class P1,class P2,class P3,class P4> int Call(ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3,v4);

			MsgCall call = {0};
			GenCallMsg(call,caller,msgid_rpc,method,def);

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4);

			return this->i_Call(call);
		}

		template<class P1,class P2,class P3,class P4,class P5> int Call(ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3,v4,v5);

			MsgCall call = {0};
			GenCallMsg(call,caller,msgid_rpc,method,def);

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4,v5);

			return this->i_Call(call);
		}

		template<class P1,class P2,class P3,class P4,class P5,class P6> int Call(ICallableObject* caller,const_char_ptr method,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5,P6 v6)
		{
			char def[cst_max_def_len];
			CallHelper::MakeDef(def,v1,v2,v3,v4,v5,v6);

			MsgCall call = {0};
			GenCallMsg(call,caller,msgid_rpc,method,def);

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4,v5,v6);

			return this->i_Call(call);
		}
	public:
		int Return()
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");
			return this->i_Return(call);
		}

		template<class P1> int Return(P1 v1)
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");

			pwdist::CallParameterHelper::MakeParams(call.params,v1);

			return this->i_Return(call);
		}

		template<class P1,class P2> int Return(P1 v1,P2 v2)
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2);

			return this->i_Return(call);
		}

		template<class P1,class P2,class P3> int Return(P1 v1,P2 v2,P3 v3)
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3);

			return this->i_Return(call);
		}

		template<class P1,class P2,class P3,class P4> int Return(P1 v1,P2 v2,P3 v3,P4 v4)
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4);

			return this->i_Return(call);
		}

		template<class P1,class P2,class P3,class P4,class P5> int Return(P1 v1,P2 v2,P3 v3,P4 v4,P5 v5)
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4,v5);

			return this->i_Return(call);
		}

		template<class P1,class P2,class P3,class P4,class P5,class P6> int Return(P1 v1,P2 v2,P3 v3,P4 v4,P5 v5,P6 v6)
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");

			pwdist::CallParameterHelper::MakeParams(call.params,v1,v2,v3,v4,v5,v6);

			return this->i_Return(call);
		}
	public:
		template<class P1> int AsyncReturn(int64 pid,P1 v1)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1);
			return AsyncReturnValues(pid,params);
		}
		template<class P1,class P2> int AsyncReturn(int64 pid,P1 v1,P2 v2)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2);
			return AsyncReturnValues(pid,params);
		}
		template<class P1,class P2,class P3> int AsyncReturn(int64 pid,P1 v1,P2 v2,P3 v3)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3);
			return AsyncReturnValues(pid,params);
		}
		template<class P1,class P2,class P3,class P4> int AsyncReturn(int64 pid,P1 v1,P2 v2,P3 v3,P4 v4)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3,v4);
			return AsyncReturnValues(pid,params);
		}
		template<class P1,class P2,class P3,class P4,class P5> int AsyncReturn(int64 pid,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3,v4,v5);
			return AsyncReturnValues(pid,params);
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6> int AsyncReturn(int64 pid,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5,P6 v6)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3,v4,v5,v6);
			return AsyncReturnValues(pid,params);
		}
	public:
		template<class P1> int AsyncReturnEx(int64 pid,bool removeCaller,P1 v1)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1);
			return AsyncReturnValues(pid,params,removeCaller);
		}
		template<class P1,class P2> int AsyncReturnEx(int64 pid,bool removeCaller,P1 v1,P2 v2)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2);
			return AsyncReturnValues(pid,params,removeCaller);
		}
		template<class P1,class P2,class P3> int AsyncReturnEx(int64 pid,bool removeCaller,P1 v1,P2 v2,P3 v3)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3);
			return AsyncReturnValues(pid,params,removeCaller);
		}
		template<class P1,class P2,class P3,class P4> int AsyncReturnEx(int64 pid,bool removeCaller,P1 v1,P2 v2,P3 v3,P4 v4)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3,v4);
			return AsyncReturnValues(pid,params,removeCaller);
		}
		template<class P1,class P2,class P3,class P4,class P5> int AsyncReturnEx(int64 pid,bool removeCaller,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3,v4,v5);
			return AsyncReturnValues(pid,params,removeCaller);
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6> int AsyncReturnEx(int64 pid,bool removeCaller,P1 v1,P2 v2,P3 v3,P4 v4,P5 v5,P6 v6)
		{
			Parameters params = {0};
			pwdist::CallParameterHelper::MakeParams(params,v1,v2,v3,v4,v5,v6);
			return AsyncReturnValues(pid,params,removeCaller);
		}
	};

	class Port : public GenericPort {};
}

#endif // _pwdist_port_generic_