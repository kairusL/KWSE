#pragma once
#include "TypeIds.h"
namespace KWSE
{
	class GameObject;
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual uint32_t GetTypeId()const = 0;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update(float deltaTime) {}
		virtual void DebugUI(){}

		//Make sure when gameobject created , pass it to the owner directly. 
		// & not * 
		// * means it can be null -> but we guarantee it won't be null
		// so we de-reference it ahead of time and give you a reference.
		GameObject& GetOwner() { return *mOwner; }
		const GameObject& GetOwner() const { return *mOwner; }


	private:
			friend class GameObject;
			GameObject* mOwner = nullptr;


	};
}