#include "pw_write_buffer.h"
#include <malloc.h>
#include <algorithm>

namespace pwutils
{
    WriteBuffer::WriteBuffer(size_t defaultChunkSize)
        : m_nDefaultChunkSize(defaultChunkSize)
        , m_nLength(0)
        , m_pHead(NULL)
        , m_pTail(NULL)
    {

    }

    WriteBuffer::~WriteBuffer()
    {
        this->Cleanup();
    }

    void WriteBuffer::Push(WriteBuffer* wb)
    {
        if(wb->m_pHead == NULL)
            return ;

        if(m_pHead == NULL)
        {
            std::swap(m_pHead,wb->m_pHead);
            std::swap(m_pTail,wb->m_pTail);
            std::swap(m_nLength,wb->m_nLength);
        }
        else
        {
            m_pTail->next = wb->m_pHead;
            m_pTail = wb->m_pTail;
            m_nLength += wb->m_nLength;

            wb->m_pHead = NULL;
            wb->m_pTail = NULL;
            wb->m_nLength = 0;
        }
    }

    void WriteBuffer::Write(const void* buf,size_t len)
    {
        const char* chb = (const char*)buf;

        if(m_pHead == NULL)
        {
            m_pHead = this->AllocateChunk();
            m_pTail = m_pHead;
        }

        while(len > 0)
        {
            Chunk* last = m_pTail;
            size_t bytes = std::min(last->capacity - last->length,len);
            if(bytes == 0)
            {
                m_pTail->next = this->AllocateChunk();
                m_pTail = m_pTail->next;
                continue;
            }
            memcpy(&last->buffer[last->length],chb,bytes);
            chb += bytes;
            len -= bytes;
            last->length += bytes;
            m_nLength += bytes;
        }
    }

    WriteBuffer::Chunk* WriteBuffer::AllocateChunk()
    {
        WriteBuffer::Chunk* result = (WriteBuffer::Chunk*)malloc(sizeof(WriteBuffer::Chunk) + m_nDefaultChunkSize - 1);
        result->capacity = m_nDefaultChunkSize;
        result->length = 0;
        result->next = NULL;
        return result;
    }

    void WriteBuffer::Cleanup()
    {
        Chunk* c = m_pHead;
        while( c != NULL )
        {
            Chunk* tmp = c->next;
            free(c);
            c = tmp;
        }
    }
}
