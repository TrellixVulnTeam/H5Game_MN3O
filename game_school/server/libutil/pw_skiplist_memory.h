#ifndef _skiplist_memory_
#define _skiplist_memory_

#include <vector>
#include <malloc.h>

namespace pwutils
{
	template<int HEIGHT> class SkipListMemory
	{
	public:
		SkipListMemory(size_t blockSize = 40960)
			: m_nBlockSize(blockSize)
			, m_nLastBlockSpace(0)
		{
			m_vBlocks.reserve(128);
			for(int i = 0; i < HEIGHT; ++i)
				m_vFreeNodes[i].reserve(1024);
		}

		~SkipListMemory()
		{
			for(size_t i = 0; i < m_vBlocks.size(); ++i)
				free(m_vBlocks[i]);
			m_vBlocks.clear();
		}
	public:
		char* allocate(size_t size,int height)
		{
			if(m_vFreeNodes[height].size() > 0)
			{
				char* result = m_vFreeNodes[height].back();
				m_vFreeNodes[height].pop_back();
				return result;
			}

			if(m_nLastBlockSpace < size)
				this->allocateBlock();

			char* memory = m_vBlocks.back();
			char* result = &memory[m_nBlockSize - m_nLastBlockSpace];
			m_nLastBlockSpace -= size;
			return result;
		}

		void deallocate(void* ptr,int height)
		{
			m_vFreeNodes[height].push_back((char*)ptr);
		}
	private:
		void allocateBlock()
		{
			char* block = (char*)malloc(m_nBlockSize);
			m_vBlocks.push_back(block);
			m_nLastBlockSpace = m_nBlockSize;
		}
	private:
		size_t m_nBlockSize;
		size_t m_nLastBlockSpace;
		std::vector<char*> m_vBlocks;
		std::vector<char*> m_vFreeNodes[HEIGHT];
	};
}


#endif // _skiplist_memory_