#include "pw_gdb_chunks.h"
#include <malloc.h>
#include <assert.h>
#include <iostream>
#include <memory.h>

namespace gdb
{
//	pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
	int64 g_chunk_size = 0;

	void SChunk::FreeChain(SChunk* writebuffer)
	{
// 		pthread_mutex_lock(&g_mutex);

		SChunk* wb = writebuffer;
		while(wb != 0)
		{
			SChunk* next = wb->next;
// 			g_chunk_size -= wb->capacity;
			free(wb);
			wb = next;
		}

// 		pthread_mutex_unlock(&g_mutex);
	}

	SChunk* SChunk::MallocBuffer(size_t size)
	{
		if(size == 0)
			size = 64*1024;

		SChunk* result = (SChunk*)malloc(sizeof(SChunk) + size - 1);
		result->size = 0;
		result->next = 0;
		result->rpos = 0;
		result->spos = 0;
		result->capacity = size;
#ifdef _DEBUG
		memset(result->data,0xcdcdcdcd,size);
#endif

// 		pthread_mutex_lock(&g_mutex);
// 		g_chunk_size += size;
// 		pthread_mutex_unlock(&g_mutex);

		return result;
	}

	ChunksWriter::ChunksWriter(size_t chunkSize)
		: m_pHead(0)
		, m_pCurr(0)
		, m_nChunkSize(chunkSize)
	{
	}

	ChunksWriter::~ChunksWriter()
	{
		SChunk::FreeChain(m_pHead);
		
		m_pHead = 0;
		m_pCurr = 0;
	}

	void ChunksWriter::Write( const void* data,size_t size )
	{
		this->AllocSpace(size);

		const char* cbuf = (const char*)data;

		while(size > 0)
		{
			size_t space = m_pCurr->capacity - m_pCurr->size;
			size_t writelen = std::min(space,size);
			if(writelen > 0)
			{
				memcpy(&m_pCurr->data[m_pCurr->size],cbuf,writelen);
				m_pCurr->size += writelen;
				size -= writelen;
				cbuf += writelen;
			}

			if(m_pCurr->capacity == m_pCurr->size && size > 0)
			{
				assert(m_pCurr->next != 0);
				m_pCurr = m_pCurr->next;
			}			
		}
	}

	void ChunksWriter::Write( SChunk* writebuffer )
	{
		SChunk* wb = writebuffer;
		while(wb != 0)
		{
			this->Write(wb->data,wb->size);
			wb = wb->next;
		}
	}

	void ChunksWriter::AllocSpace( size_t len )
	{
		size_t space = this->Space();

		SChunk* current = m_pCurr;

		while(space < len)
		{
			SChunk* chunk = SChunk::MallocBuffer(m_nChunkSize);

			if(current == 0)
			{
				m_pHead = chunk;
				m_pCurr = chunk;
				current = chunk;
			}
			else
			{
				current->next = chunk;
				current = chunk;
			}
			space += chunk->capacity;			
		}

		while(m_pCurr->capacity == m_pCurr->size)
			m_pCurr = m_pCurr->next;
	}


	void ChunksWriter::NextWriteBuffer( SBuffer& r)
	{
		if(m_pCurr != 0)
		{
			while(m_pCurr->capacity == m_pCurr->size && m_pCurr->next != 0)
				m_pCurr = m_pCurr->next;

			r.data = &m_pCurr->data[m_pCurr->size];
			r.size = m_pCurr->capacity - m_pCurr->size;
		}
		else
		{
			memset(&r,0,sizeof(SBuffer));
		}
	}

	size_t ChunksWriter::Length()
	{
		size_t result = 0;
		SChunk* wb = m_pHead;
		while(wb != 0)
		{
			result += wb->size;
			wb = wb->next;
		}
		return result;
	}

	size_t ChunksWriter::Skip( size_t size )
	{
		size_t bytes = size;

		this->AllocSpace(size);

		while(size > 0)
		{
			size_t space = m_pCurr->capacity - m_pCurr->size;
			size_t writelen = std::min(space,size);

			m_pCurr->size += writelen;
			size -= writelen;
			bytes += writelen;

			if(m_pCurr->capacity == m_pCurr->size && size > 0)
			{
				if(m_pCurr->next == 0)
					break;
				m_pCurr = m_pCurr->next;
			}
		}

		return bytes;
	}

	void ChunksWriter::PushBuffer( SChunk* writebuffer )
	{
		if(writebuffer->size <= 0)
		{
			SChunk::FreeChain(writebuffer);
			return ;
		}

		if(m_pHead != 0)
		{
			m_pCurr->next = writebuffer;
			m_pCurr = writebuffer;
		}
		else
		{
			m_pHead = writebuffer;
			m_pCurr = writebuffer;
		}
	}

	SChunk* ChunksWriter::PeekBuffer( bool pop )
	{
		if(m_pHead == 0)
			return 0;

		SChunk* head = m_pHead;
		if(pop)
		{
			SChunk* tmp = 0;
			std::swap(tmp,m_pHead->next);
			m_pHead = tmp;
			if(m_pHead == 0)
				m_pCurr = 0;
		}
		return head;
	}

	void ChunksWriter::Clear()
	{
		SChunk::FreeChain(Detach());
	}

	// -----------------------------------------------------------------------------

	ChunksReader::ChunksReader( SChunk* head )
		: m_pContinuous(0)
		, m_nPosition(0)
		, m_nFreePosition(0)
		, m_nAvialable(0)
#ifdef _DEBUG
		, m_cMalloc(0)
#endif
	{
		size_t position = 0;

		SChunk* h = head;
		while(h != 0)
		{
			h->spos = position;
			m_nAvialable += h->size;
			position += h->size; 
			SChunk* tmp = h->next;
			h->next = 0;
			m_vBufs.push_back(h);
			h = tmp;
		}
	}

	ChunksReader::~ChunksReader()
	{
		SChunk::FreeChain(m_pContinuous);

		while(!m_vBufs.empty())
		{
			SChunk::FreeChain(m_vBufs.front());
			m_vBufs.pop_front();
		}

		while(!m_vFree.empty())
		{
			SChunk::FreeChain(m_vFree.front());
			m_vFree.pop_front();
		}
	}

	size_t ChunksReader::i_Read( void* data,size_t size )
	{
		size_t bytes = 0;

		char* wbuf = (char*)data;

		if(size > 0 && m_pContinuous != 0 && m_pContinuous->rpos < m_pContinuous->size)
		{
			size_t asize = std::min(size,m_pContinuous->size - m_pContinuous->rpos);
			if(asize > 0)
			{
				if(data != 0)
				{
					memcpy(wbuf,&m_pContinuous->data[m_pContinuous->rpos],asize);
					wbuf += asize;
				}
				m_pContinuous->rpos += asize;
				size -= asize;
				bytes += asize;
			}

			if(m_pContinuous->rpos != m_pContinuous->size)
			{
				assert(size == 0);
				return bytes;
			}
			m_vFree.push_back(m_pContinuous);
			m_pContinuous = 0;
		}

		while(!m_vBufs.empty())
		{
			SChunk* head = m_vBufs.front();

			size_t bsize = std::min(size,head->size - head->rpos);
			if(bsize > 0)
			{
				if(data != 0)
				{
					memcpy(wbuf,&head->data[head->rpos],bsize);
					wbuf += bsize;
				}
				head->rpos += bsize;
				size -= bsize;
				bytes += bsize;
			}

			if(head->rpos != head->size)
			{
				assert(size == 0);
				break;
			}

			m_vFree.push_back(head);
			m_vBufs.pop_front();
		}
		
		return bytes;
	}

	size_t ChunksReader::Length()
	{
		return m_nAvialable;
	}

	void ChunksReader::Peek( SConstBuffer& r)
	{
		SChunk* curr = m_pContinuous;
		if(curr == NULL && m_vBufs.size() > 0)
			curr = m_vBufs.front();

		if(curr != 0 && curr->size > curr->rpos)
		{
			r.data = &curr->data[curr->rpos];
			r.size = curr->size - curr->rpos;
		}
		else
		{
			memset(&r,0,sizeof(SConstBuffer));
		}
	}

	void ChunksReader::Free( size_t size )
	{
		if(size == 0)
		{
			assert(m_nPosition >= m_nFreePosition);
			size = m_nPosition - m_nFreePosition;
		}

		if(size <= 0)
			return ;

		assert((m_nFreePosition + size) <= m_nPosition);
		m_nFreePosition += size;

		while(!m_vFree.empty())
		{
			SChunk* h = m_vFree.front();
			if((h->spos + h->size) > m_nFreePosition)
				break;
			SChunk::FreeChain(h);
			m_vFree.pop_front();
		}
	}

	bool ChunksReader::InsureContinuous( size_t size )
	{
		if(m_nAvialable < size)
			return false;

		SConstBuffer tmpbuf;
		this->Peek(tmpbuf);

		if(tmpbuf.size >= size)
			return true;

#ifdef _DEBUG
		++m_cMalloc;
#endif
		SChunk* cbuf = SChunk::MallocBuffer(size);
		cbuf->size = this->i_Read(cbuf->data,cbuf->capacity);
		cbuf->spos = m_nPosition;
		this->i_ReplaceContinuous(cbuf);
		assert(cbuf->size == cbuf->capacity);

		return true;
	}

	size_t ChunksReader::Skip( size_t len )
	{
		size_t bytes = this->i_Read(0,len);
		m_nPosition += bytes;
		m_nAvialable -= bytes;
		return bytes;
	}

	void ChunksReader::i_ReplaceContinuous( SChunk* buf )
	{
		if(m_pContinuous != 0)
			m_vFree.push_back(m_pContinuous);
		m_pContinuous = buf;
	}

	void ChunksReader::PushChunk( SChunk* chunk )
	{
		chunk->spos = m_nPosition + m_nAvialable;
		m_nAvialable += chunk->size;

		m_vBufs.push_back(chunk);
	}

	void ChunksReader::RebuildStream()
	{
		this->Free(0);

		if(m_nPosition == m_nFreePosition && m_nAvialable == 0)
		{
			m_nPosition = 0;
			m_nFreePosition = 0;
			m_nAvialable = 0;
		}
	}
/*
	extern void test_bufferreader()
	{
		ChunksWriter writer(500);
		for(size_t i = 0; i < 137; ++i)
			writer.Write("abcdefghijklmnopqrstuvwxyz",26);

		ChunksReader reader(writer.Detach());

		unsigned int adf = 43657;
		::srand(adf);

		size_t size = 0;
		while(reader.Length() > 0)
		{
			size_t avialable_size = reader.Length();
			size_t r = rand() % (avialable_size + 1);

			if(r == 0)
				std::cout << " r = 0" << std::endl;

			if((r % 5) == 0)
			{
				SChunk* s = SChunk::MallocBuffer(100);
				memcpy(s->data,"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",100);
				s->size = 100;
				reader.PushChunk(s);
			}

			reader.InsureContinuous(r);
			SConstBuffer tmpbuf;
			reader.Peek(tmpbuf);
			std::cout << std::string(tmpbuf.data,tmpbuf.size) << std::endl;
			reader.Skip(tmpbuf.size);
			size += tmpbuf.size;
		}

		reader.Free(size);
	}
*/

}
