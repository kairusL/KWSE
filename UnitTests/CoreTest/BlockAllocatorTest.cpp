#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace KWSE::Core;

namespace CoreTest
{
	TEST_CLASS(BlockAllocatorTest)
	{
	public:

		TEST_METHOD(OneBlockTest)
		{
			BlockAllocator blockAllocator(16,1);

			void* ptr1 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr1);

			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNull(ptr2);
		}

		TEST_METHOD(TwoBlockTest)
		{
			BlockAllocator blockAllocator(16, 2);

			void* ptr1 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr1);

			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr2);

			Assert::IsTrue(ptr1!=ptr2);

			// ptrdiff_t -> just integer -> use to subtract two pointer.
			// use it to make sure have long enough integer to store pointer addresses differences.
			// the block needs to be 16 bytes apart -> these two pointer should be one block away.
			ptrdiff_t diff = static_cast<uint8_t*>(ptr1) - static_cast<uint8_t*>(ptr2);
			Assert::IsTrue(abs(diff) >= 16);

			void* ptr3 = blockAllocator.Allocate();
			Assert::IsNull(ptr3);

		}

		TEST_METHOD(FreeTest)
		{
			// Initialize with 1 block of 16
			BlockAllocator blockAllocator(16,1);

			// Allocate the block to ptr1
			// Check ptr1 to be not nillptr
			void* ptr1 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr1);

			// Allocate another block to ptr2
			// Check ptr2 to be nullptr
			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNull(ptr2);

			// Free pte1, dont clear ptr1!
			blockAllocator.Free(ptr1);

			// Allocate block to ptr2
			// Check ptr2 to be not nullptr
			ptr2 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr2);

			Assert::IsTrue(ptr1 == ptr2);
			// Check that ptr2 got the same address as ptr1.
			//ptrdiff_t diff = static_cast<uint8_t*>(ptr1) - static_cast<uint8_t*>(ptr2);
			//Assert::IsTrue(abs(diff) == 0);
		}
		TEST_METHOD(FreeTestT)
		{
			BlockAllocator blockAllocator(16,4);
		
			void* ptr1 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr1);
			void* ptr2 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr2);
			void* ptr3 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr3);
			void* ptr4 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr4);
			void* ptr5 = blockAllocator.Allocate();
			Assert::IsNull(ptr5);
		
			blockAllocator.Free(ptr1);
		
		
		
			ptr5 = blockAllocator.Allocate();
			Assert::IsNotNull(ptr5);
		
			Assert::IsTrue(ptr5 == ptr1);
		
		}



	};
}
