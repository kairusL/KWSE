#pragma once
#include"Component.h"

namespace KWSE
{
	class TransformComponent final :public Component
	{

	public:
		// had the macro for ( get component to get a specific thing ) mechanism.
		SET_TYPE_ID(ComponentId::Transform);
		// define
		//		want to have a static allocator
		// 	static KWSE::Core::BlockAllocator sAllocator;\
		//		want to have new and delete operator overloading.
		// 	static void* operator new(std::size_t size);\
		// 	static void operator delete(void* ptr);
		MEMPOOL_DECLARE;


		TransformComponent() = default;
		void DebugUI() override;

		void SetPosition(const Math::Vector3& position) { mPosition = position; }
		const Math::Vector3& GetPosition() const { return mPosition; }

		void SetRotation(const Math::Quaternion& rotation) { mRotation = rotation; }
		const Math::Quaternion& GetRotation() const { return mRotation; }
	private:
		Math::Vector3 mPosition;
		Math::Quaternion mRotation;
	};
}