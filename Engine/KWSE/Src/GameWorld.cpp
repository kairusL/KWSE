#include "Precompiled.h"
#include "GameWorld.h"
#include"GameObjectIO.h"


void GameWorld::Initialize(uint32_t capacity)
{
	for (auto& service : mServices)
	{
		service->Initialize();
	}
	mGameObjectSlots.resize(capacity);
	mFreeSolts.resize(capacity);
	std::iota(mFreeSolts.begin(), mFreeSolts.end(), 0);
}
void GameWorld::Terminate()
{
	for (auto& service : mServices)
	{
		service->Terminate();
	}
}
void GameWorld::Update(float deltaTime)
{
	for (auto& service : mServices)
	{
		service->Update(deltaTime);
	}
	for (auto& gameObject : mUpdateList)
	{
		gameObject->Update(deltaTime);
	}

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
}

GameObjectHandle KWSE::GameWorld::CreateGameObject(const std::filesystem::path & templateFileName, std::string name)
{
	GameObjectHandle handle;

	// if empty then exit. run out space
	if (mFreeSolts.empty())
	{
		return handle;
	}
	// Open file
	FILE* file = nullptr;
	auto err = fopen_s(&file, templateFileName.u8string().c_str(), "r");
	//if can not open file ,then exit.
	if (err != 0 || file == nullptr)
	{
		//ASSERT(file, "CreateGameObject - Failed to open template file %s.", templateFileName.u8string().c_str());
		LOG("CreateGameObject - Failed to open template file %s.", templateFileName.u8string().c_str());
		return handle;
	}
	//Open file

	uint32_t freeslot = mFreeSolts.back();
	mFreeSolts.pop_back();

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
	return handle;
}

GameObject * KWSE::GameWorld::GetGameObject(GameObjectHandle handle)
{
	if (handle.mIndex >= 0 && handle.mIndex < mGameObjectSlots.size())
	{
		auto& slot = mGameObjectSlots[handle.mIndex];
		if (slot.generation == handle.mGeneration)
		{
			return slot.gameObject.get();
		}
	}
	return nullptr;
}


