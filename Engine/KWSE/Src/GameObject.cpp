#include"Precompiled.h"
#include "GameObject.h"
//#include "GameObject.h"
//
#include"Component.h"

using namespace KWSE;

MEMPOOL_DEFINE(GameObject, 1000);

void KWSE::GameObject::Initialize()
{
	ASSERT(!mInitialized, "GameObject - Already initialized.");

	for (auto& component : mComponents)
	{
		component->Initialize();
	}
	mInitialized = true;
}

void KWSE::GameObject::Terminate()
{
	for (auto& component : mComponents)
	{
		component->Terminate();
	}
}

void KWSE::GameObject::Update(float deltaTime)
{
	for (auto& component : mComponents)
	{
		component->Update(deltaTime);
	}
}

//void KWSE::GameObject::Render()
//{
//	for (auto& component : mComponents)
//	{
//		component->Render();
//	}
//}

void KWSE::GameObject::DebugUI()
{
	for (auto& component : mComponents)
	{
		component->DebugUI();
	}
}



//void KWSE::GameObject::AddComponent(Component * newComponent)
//{
//	mComponents.emplace_back(newComponent);
//}
