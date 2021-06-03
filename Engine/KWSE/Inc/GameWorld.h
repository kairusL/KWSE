#pragma once
#include "GameObject.h"
#include"Service.h"
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

		template <class ServiceType>
		//take that component back for convenience
		ServiceType* AddService()
		{
			ASSERT(!mInitialized, "GameWorld - Can only add service before world is initialized.");
			//construct a component ourselves -> make unique 
			// emplace_back is updated 
			// -> so it will return whatever you just add by reference
			// in this case return a reference to a unique pointer.
			auto& newService = mServices.emplace_back(std::make_unique<ServiceType>());
			// emplace_back added new object, and this object belongs to me.
			newService ->mWorld = this;
			return static_cast<ServiceType*>(newService.get());
		}



		template <class ServiceType>
		// get component to get a specific thing
		ServiceType* GetService()
		{
			// because it is a unique pointer , can not make a copy of it.
			// make sure it is reference.
			for (auto& service : mServices)
			{
				// use instance get type check if is match the static get type
				// make sure instance id matching the class types id  
				if (service->GetTypeId() == ServiceType::StaticGetTypeId())
				{
					//then this instance is that particular component.
					// cast the bast pointer (component ) back to the actual template pointer.

					// can not convent unique pointer to component type.
					// *return static_cast<ComponentType*>(component);
					return static_cast<ServiceType*>(service.get());
				}
			}
			return nullptr;
		}



		GameObjectHandle CreateGameObject(const std::filesystem::path & templateFileName, std::string name);
		GameObject* GetGameObject(GameObjectHandle handle);
	private:
		struct Slot
		{
			std::unique_ptr<GameObject> gameObject;
			uint32_t generation = 0;
		};

		// we do own it so we want unique ptr
		using Services= std::vector<std::unique_ptr<Service>>;
		
		using GameObjectSlots = std::vector<Slot>;
		using GameObjectList = std::vector<GameObject*>;

		Services mServices;

		GameObjectSlots mGameObjectSlots;
		std::vector<uint32_t> mFreeSolts;

		GameObjectList mUpdateList;

		bool mInitialized = false;
	};
}