#pragma once
#include "Component.h"
#include "GameObjectHandle.h"
namespace KWSE
{
	class GameWorld;

	class GameObject final
	{
	public:
		MEMPOOL_DECLARE;

		GameObject() = default;

		void Initialize();
		void Terminate();

		void Update(float deltaTime);
		void DebugUI();
		
		template <class ComponentType>
		//take that component back for convenience
		ComponentType* AddComponent()
		{
			ASSERT(!mInitialized, "GameObject - Can only add components before object is initialized.");
			//construct a component ourselves -> make unique 
			// emplace_back is updated 
			// -> so it will return whatever you just add by reference
			// in this case return a reference to a unique pointer.
			auto& newComponent = mComponents.emplace_back(std::make_unique<ComponentType>());
			// emplace_back added new object, and this object belongs to me.
			newComponent->mOwner = this;
			return static_cast<ComponentType*>(newComponent.get());
		}

		

		template <class ComponentType>
		// get component to get a specific thing
		ComponentType* GetComponent()
		{
			auto constMe = static_cast<const GameObject*>(this);
			return const_cast<ComponentType*>(constMe->GetComponent<ComponentType>());
		}

		template <class ComponentType>
		// get component to get a specific thing
		const ComponentType* GetComponent() const
		{
			// because it is a unique pointer , can not make a copy of it.
			// make sure it is reference.
			for (auto& component : mComponents)
			{
				// use instance get type check if is match the static get type
				// make sure instance id matching the class types id  
				if (component->GetTypeId() == ComponentType::StaticGetTypeId())
				{
					//then this instance is that particular component.
					// cast the bast pointer (component ) back to the actual template pointer.

					// can not convent unique pointer to component type.
					// *return static_cast<ComponentType*>(component);
					return static_cast<ComponentType*>(component.get());
				}
			}
			return nullptr;
		}

		GameWorld& GetWorld() { return *mWorld; }
		const GameWorld& GetWorld() const{ return *mWorld; }

		GameObjectHandle GetHandle() const { return mHandle; }

		void SetName(const char* name) { mName = name; }
		const std::string& GetName() const { return mName; }
	private:
		friend class GameWorld;

		//using Components = std::vector<std::unique_ptr<Component*>>;
		using Components = std::vector < std::unique_ptr<Component> > ;

		GameWorld *mWorld = nullptr;
		Components mComponents;
		GameObjectHandle mHandle;
		std::string mName = "NoName";
		bool mInitialized = false;


	};
}