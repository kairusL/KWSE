#pragma once
#include "GameObject.h"
namespace KWSE
{
	class GameWorld final
	{
	public:
		void Initialize(uint32_t capacity);
		void Terminate();

		void Update(float deltaTime);
		void Render();
		void DebugUI();

		GameObjectHandle CreateGameObject(const std::filesystem::path & templateFileName, std::string name);
		GameObject* GetGameObject(GameObjectHandle handle);
	private:
		struct Slot
		{
			std::unique_ptr<GameObject> gameObject;
			uint32_t generation = 0;
		};
		using GameObjectSlots = std::vector<Slot>;
		using GameObjectList = std::vector<GameObject*>;
		GameObjectSlots mGameObjectSlots;
		std::vector<uint32_t> mFreeSolts;
		std::vector<uint32_t> mGenerations;


		bool mInitialized = false;
	};
}