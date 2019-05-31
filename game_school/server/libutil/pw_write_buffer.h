#ifndef PW_WRITE_BUFFER_H
#define PW_WRITE_BUFFER_H

#include <string.h>

namespace pwutils
{
    class WriteBuffer
    {
    public:
        WriteBuffer(size_t defaultChunkSize = 256*1024);
        ~WriteBuffer();
    public:
        struct Chunk
        {
            Chunk* next;
            size_t capacity;
            size_t length;
            char buffer[1];
        };
    public:
        void Push(WriteBuffer* wb);
        void Write(const void* buf,size_t len);
    public:
        inline size_t GetLength()
        {
            return m_nLength;
        }

        inline Chunk* GetHead()
        {
            return m_pHead;
        }
    public:
        void Cleanup();
    protected:
        Chunk* AllocateChunk();
    protected:
        size_t m_nDefaultChunkSize;
        size_t m_nLength;
        Chunk* m_pHead;
        Chunk* m_pTail;
    };


}

#endif // PW_WRITE_BUFFER_H
