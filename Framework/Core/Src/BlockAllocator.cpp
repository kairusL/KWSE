#include "Precompiled.h"
#include "BlockAllocator.h"

#include "DebugUtil.h"

using namespace KWSE::Core;

KWSE::Core::BlockAllocator::BlockAllocator(std::size_t blockSize, std::size_t capacity)
	: mBlockSize(blockSize), mCapacity(capacity)
{
	//how many block(capacity) of data i need , each block containing (blockSize) bytes
	mData = std::malloc(blockSize*capacity);

	// Depends on how many block that created
	// Re- order same block size for the FreeSlots at the begining. 
	mFreeSlots.clear();
	mFreeSlots.reserve(capacity);
	// After order the size, added elements.
	for (size_t i = 0; i < capacity; ++i)
	{
		mFreeSlots.push_back(i);
	}

}


KWSE::Core::BlockAllocator::~BlockAllocator()
{
	std::free(mData);
}

void * KWSE::Core::BlockAllocator::Allocate()
{
	if (mFreeSlots.empty())
	{
		return nullptr;
	}
	// Run when have FreeSlot Taking one from the back each time.
	//Then pop the back , means this freesloat no longer exist.
	uint32_t nextSlot =mFreeSlots.back();
	mFreeSlots.pop_back();
	
	//^^^  nextSlot if is 2 , [xxxx] [xxxx] [nextSlot]  ^^^

	// mData always pointing to the begining of the pool
	// and i need to return the nextSlot address.
	return static_cast<uint8_t*>(mData) + (mBlockSize * nextSlot);
}

void KWSE::Core::BlockAllocator::Free(void * ptr)
{
	// Use this pointer address to subtract the begining address of the whole block.
	// diff geting begining byte of this block.
	// [0][1][2][3]    ->block size: 16
	// ^  ^  ^  ^
	// |  |  |  |
	// 0 16 32 48
	ptrdiff_t diff = static_cast<uint8_t*>(ptr) - mData;
	// if diff is 48 , meant we are trying to free block 3
	// so returnSlot 3 to the FreeSlot[] for the next use.
	std::size_t returnSlot = static_cast<std::size_t>(diff) / mBlockSize;
	mFreeSlots.push_back(returnSlot);
}
