#include"Precompiled.h"
#include"TransformComponent.h"

using namespace KWSE;

//#define MEMPOOL_DEFINE(Class,Capacity)\
//	KWSE::Core::BlockAllocator Class::sAllocator(sizeof(Class),Capacity);\
//	void* Class::operator new(std::size_t size)\
//	{\
//		return sAllocator.Allocate(); \
//	}\
//	void Class::operator delete(void* ptr)\
//	{\
//		sAllocator.Free(ptr);\
//	}
//
MEMPOOL_DEFINE(TransformComponent, 1000);
//#define MEMPOOL_DEFINE(Class <-TransformComponent ,Capacity <-1000)\
// Creating BlockAllocator inside transform component class -> initialize to take Transform component as block size , and 1000 capacity
//	KWSE::Core::BlockAllocator TransformComponent::sAllocator(sizeof(TransformComponent),1000);\
//	void* TransformComponent::operator new(std::size_t size)
//	{
//   tell the allocator to new
//		return sAllocator.Allocate(); 
//	}
//	void TransformComponent::operator delete(void* ptr)
//	{
//   tell the allocator to free
//		sAllocator.Free(ptr);
//	}

void TransformComponent::DebugUI()
{
	
	Graphics::SimpleDraw::AddLine(mPosition, mPosition + Math::Vector3::XAxis, Graphics::Colors::Red);
	Graphics::SimpleDraw::AddLine(mPosition, mPosition + Math::Vector3::YAxis, Graphics::Colors::Green);
	Graphics::SimpleDraw::AddLine(mPosition, mPosition + Math::Vector3::ZAxis, Graphics::Colors::Blue
	);
}