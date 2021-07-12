#include "Precompiled.h"
#include "GameWorld.h"
#include"GameObjectIO.h"


void GameWorld::Initialize(uint32_t capacity)
{
	ASSERT(!mInitialized, "GameWorld - Already initialized.");
	for (auto& service : mServices)
	{
		service->Initialize();
	}
	mGameObjectSlots.resize(capacity);
	mFreeSlots.resize(capacity);
	std::iota(mFreeSlots.begin(), mFreeSlots.end(), 0);
	mInitialized = true;
}
void GameWorld::Terminate()
{
	ASSERT(!mUpdating, "GameWorld - Cannot terminate world during update.");
	if (!mInitialized)
	{
		return;
	}
	// Destory all remaining game objects
	for ( auto gameObject : mUpdateList)
	{
		Destory(gameObject->GetHandle());
	}
	ProcessDestoryList();
	ASSERT(mUpdateList.empty(), "GameWorld - Failed to clean up game objects.");
	for (auto& service : mServices)
	{
		service->Terminate();
	}
	mInitialized = false;
}
void GameWorld::Update(float deltaTime)
{
	ASSERT(!mUpdating, "GameWorld - Already updating the world.");

	// This defers game object destruction
	mUpdating = true;

	for (auto& service : mServices)
	{
		service->Update(deltaTime);
	}
	for (size_t i = 0; i < mUpdateList.size(); ++i)
	{
		GameObject* gameObject = mUpdateList[i];
		if (IsValid(gameObject->GetHandle()))
		{
			gameObject->Update(deltaTime);
		}
	}

	//for (auto& gameObject : mUpdateList)
	//{
	//	gameObject->Update(deltaTime);
	//}

	// Allow game object destructions
	mUpdating = false;
	ProcessDestoryList();

}
void GameWorld::Render()
{
	for (auto& service : mServices)
	{
		service->Render();
	}
}
void GameWorld::DebugUI()
{
	for (auto& service : mServices)
	{
		service->DebugUI();
	}
	for (auto& gameObject : mUpdateList)
	{
		gameObject->DebugUI();
	}
}

GameObject* KWSE::GameWorld::CreateGameObject(const std::filesystem::path & templateFileName, std::string name)
{
	ASSERT(mInitialized, "GameWorld world must be initialized first before creating game objects.");

	GameObjectHandle handle;

	// if empty then exit. run out space
	if (mFreeSlots.empty())
	{
		return nullptr;
	}
	// Open file
	FILE* file = nullptr;
	auto err = fopen_s(&file, templateFileName.u8string().c_str(), "r");
	//if can not open file ,then exit.
	if (err != 0 || file == nullptr)
	{
		//ASSERT(file, "CreateGameObject - Failed to open template file %s.", templateFileName.u8string().c_str());
		LOG("CreateGameObject - Failed to open template file %s.", templateFileName.u8string().c_str());
		return nullptr;
	}
	//Open file

	uint32_t freeslot = mFreeSlots.back();
	mFreeSlots.pop_back();

	auto& slot = mGameObjectSlots[freeslot];
	auto& newObject = slot.gameObject;
	newObject = std::make_unique<GameObject>();

	// Start read file;
	GameObjectIO::Read(file, *newObject);
	//Close file
	fclose(file);
	
	//Initialize handle
	handle.mIndex = freeslot;
	handle.mGeneration = slot.generation;

	// Initialize game object
	newObject->mWorld = this;
	newObject->mHandle = handle;
	newObject->mName = name;
	newObject->Initialize();

	// Add game object to update list
	mUpdateList.push_back(newObject.get());
	return newObject.get();
}

GameObject * KWSE::GameWorld::GetGameObject(GameObjectHandle handle)
{
	if (IsValid(handle))
	{
		auto& slot = mGameObjectSlots[handle.mIndex];
		if (slot.generation == handle.mGeneration)
		{
			return slot.gameObject.get();
		}
	}
	return nullptr;
}
GameObject* GameWorld::FindGameObject(const std::string& name)
{
	auto iter = std::find_if(mUpdateList.begin(), mUpdateList.end(), [&](auto gameObject)
	{
		return gameObject->GetName() == name;
	});
	return iter == mUpdateList.end() ? nullptr : *iter;


}

void GameWorld::Destory(GameObjectHandle handle)
{

	ASSERT(mInitialized, "GameWorld - World must be initialized first before destorying game objects.");

	if (!IsValid(handle))
	{
		return;
	}
	auto& slot = mGameObjectSlots[handle.mIndex];
	if (slot.generation != handle.mGeneration)
	{
		return;
	}
	slot.generation++; // This invalidates all existing handles to the slot
	mToBeDestoryed.push_back(handle.mIndex);







}

bool GameWorld::IsValid(GameObjectHandle handle) const
{
	return
		handle.mIndex >= 0 &&
		handle.mIndex < mGameObjectSlots.size() &&
		mGameObjectSlots[handle.mIndex].generation == handle.mGeneration;
	
}


void  GameWorld::ProcessDestoryList()
{
	ASSERT(!mUpdating, "GameWorld - Cannot destory game objects during update.");

	for (auto index:mToBeDestoryed)
	{
		auto& slot = mGameObjectSlots[index];
	
		GameObject* gameObject = slot.gameObject.get();
		ASSERT(!IsValid(gameObject->GetHandle()), "GameWorld - Game object is still valid.");

		// Remove game object from update list
		mUpdateList.erase(std::remove(mUpdateList.begin(), mUpdateList.end(), gameObject)); // Erase- Remove Idiom
		
		// Terminate game object
		gameObject->Terminate();
		
		// Delete the game object and recycle the slot
		slot.gameObject.reset();
		mFreeSlots.push_back(index);	
	}
	mToBeDestoryed.clear();



}