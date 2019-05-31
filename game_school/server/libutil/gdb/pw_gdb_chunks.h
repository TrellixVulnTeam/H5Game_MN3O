#ifndef _pw_gdb_chunks_
#define _pw_gdb_chunks_

#include "pw_gdb_reader_writer.h"
#include <deque>
#include "pw_gdb_stdint.h"

namespace gdb
{
	struct SChunk
	{
		SChunk* next;
		size_t capacity;
		size_t rpos; // readed pos
		size_t spos; // stream position
		size_t size;
		char   data[1];

		static void FreeChain(SChunk* writebuffer);
		static SChunk* MallocBuffer(size_t size);
	};

	class ChunksWriter : public Writer
	{
	public:
		ChunksWriter(size_t chunkSize = 64*1024);
		virtual ~ChunksWriter();
	public:
		void	Write(const void* data,size_t size); // override
		void	Write(SChunk* writebuffer);
		void	PushBuffer(SChunk* writebuffer);
		SChunk* PeekBuffer(bool pop);
	public:
		virtual void NextWriteBuffer(SBuffer&);
	public:
		virtual size_t Skip(size_t size);
		virtual size_t Length();
	public:
		inline size_t Space()
		{
			size_t result = 0;
			SChunk* wb = m_pCurr;
			while(wb != 0)
			{
				result += wb->capacity - wb->size;
				wb = wb->next;
			}
			return result;
		}

		inline SChunk* GetChain()
		{
			return m_pHead;
		}

		inline SChunk* Detach()
		{
			m_pCurr = 0;
			SChunk* r = m_pHead;
			m_pHead = 0;
			return r;
		}
	public:
		void Clear();
	public:
		void AllocSpace(size_t len);
	protected:
		SChunk* m_pHead;
		SChunk* m_pCurr;
	protected:
		size_t m_nChunkSize;
	};

	class ChunksReader : public Reader
	{
	public:
		ChunksReader(SChunk* head);
		virtual ~ChunksReader();
	public:
		virtual void Peek(SConstBuffer&);
		virtual bool InsureContinuous(size_t size);
		virtual void Free(size_t size);
	public:
		virtual size_t Skip(size_t size);
		virtual size_t Length();
	public:
		void	PushChunk(SChunk* chunk);
		void	RebuildStream();
	protected:
		size_t	i_Read(void* data,size_t size);
		void	i_ReplaceContinuous(SChunk* buf);
	protected:
		typedef std::deque<SChunk*> CollectionChunksT;
	protected:
		SChunk* m_pContinuous;
	protected:
		CollectionChunksT m_vBufs;
		CollectionChunksT m_vFree;
	protected:
		size_t  m_nPosition;
		size_t  m_nFreePosition;
		size_t	m_nAvialable;
#ifdef _DEBUG
		size_t	m_cMalloc;
#endif
	};


	extern void test_bufferreader();
	extern int64 g_chunk_size;
}

#endif // _pw_gdb_chunks_