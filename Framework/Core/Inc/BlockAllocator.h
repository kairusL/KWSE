#pragma once
// Reason for use BlockAllocator
// Mixing large and small allocations can ca use memory fragnebtation
namespace KWSE::Core
{
	// Constant time allocate/ free  -> no search time
	// avoid fragmentation
	// Replaces malloc/free
	class BlockAllocator
	{
public:
	BlockAllocator(std::size_t blockSize,std::size_t capacity);
	~BlockAllocator();


	//make one bloakAllocator and thats the only one 
	BlockAllocator(const BlockAllocator&) = delete; // copy constructor
	BlockAllocator& operator=(const BlockAllocator&) = delete; // copy assignment operator

	BlockAllocator(BlockAllocator&&) = delete; // move constructor
	BlockAllocator& operator=(BlockAllocator&&) = delete; // move assignment operator

	void* Allocate();
	void Free(void* ptr);

	private:

		// we want constant time allication 
		//  -> containing array of the free slot. 
		//  -> easy use without search where is the empty slot that can be use. 
		//  -> one case that could case fail -> if all the slot are used up / out of free slot. 
		std::vector<uint32_t>mFreeSlots; 
		void* mData = nullptr; // begining of the block
		std::size_t mBlockSize = 0; // how many currently have in a vector
		std::size_t mCapacity = 0; // how much memory is reserved// how much you have in total 
	};

}