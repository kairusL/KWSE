#pragma once
#include "TypeIds.h"

namespace KWSE
{
	class GameWorld;
	class Service
	{
	public:
		Service() = default;
		virtual ~Service() = default;

		virtual uint32_t GetTypeId()const = 0;

		virtual void Initialize() {}
		virtual void Terminate() {}

		virtual void Update(float deltaTime) {}
		virtual void Render() {}
		virtual void DebugUI() {}

		//Make sure when gameobject created , pass it to the owner directly. 
		// & not * 
		// * means it can be null -> but we guarantee it won't be null
		// so we de-reference it ahead of time and give you a reference.
		GameWorld& GetWorld() { return *mWorld; }
		const GameWorld& GetWorld() const { return *mWorld; }


	private:
		friend class GameWorld;
		GameWorld* mWorld = nullptr;


	};
}