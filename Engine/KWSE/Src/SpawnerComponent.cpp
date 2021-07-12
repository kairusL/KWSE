#include "Precompiled.h"
#include "SpawnerComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "TransformComponent.h"

using namespace KWSE;

MEMPOOL_DEFINE(SpawnerComponent, 1000)


void SpawnerComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void SpawnerComponent::Update(float deltaTime)
{
	if (mSpawnPath)
	{
		SetPath(deltaTime);
	}
	if (mStartTerminate)
	{
		Terminate(deltaTime);
	}
}
void SpawnerComponent::SetPath(float deltaTime)
{
	mTimer += deltaTime;

	if (mTimer >= mNextSpawnTime && mMaxSpawnAmount >= mSpawnAmount)
	{
		auto pos = mTransformComponent->GetPosition();
		for (int i = 0; i < mSpawnAmount; ++i)
		{
			auto newObject = GetOwner().GetWorld().CreateGameObject(mTemplateFileName, mSpawnObjectName + std::to_string(mSpawnId++));
			pos.x += 0.5f*mSpawnId;
			pos.z += 0.5f*mSpawnId;
			auto newTransform = newObject->GetComponent<TransformComponent>();
			newTransform->SetPosition(pos);
		}

		mTimer -= mNextSpawnTime;
	}
	if (mMaxSpawnAmount <= mSpawnId)
	{
		mSpawnPath = false;
		if (mJumpActive)
		{
			SetJump();
		}
		if (mSpawnBackflipAreaActive)
		{
			SetBackflipArea();
		}
	}
}
void SpawnerComponent::Terminate(float deltaTime)
{
	mTimer += deltaTime;
	if (mTimer >= 2.0f)
	{
		auto pos = mTransformComponent->GetPosition();
		for (int i = 0; i <= mMaxSpawnAmount-1; )
		{
			auto newObject = GetOwner().GetWorld().FindGameObject(mSpawnObjectName + std::to_string(i++));
			
			GetOwner().GetWorld().Destory(newObject->GetHandle());
		}
		mTimer -= 2.0f;
		mCleared = true;
		mStartTerminate = false;
	}
}
void SpawnerComponent::SetJump()
{
	std::string jumpName= "Jump";
	auto jump = GetOwner().GetWorld().CreateGameObject(mTemplateFileName, jumpName);
	auto pos = mTransformComponent->GetPosition();
	pos.x += 0.5f*mSpawnId;
	pos.y += 1.0f;
	pos.z += 0.5f*mSpawnId;
	auto jumpTransform = jump->GetComponent<TransformComponent>();
	jumpTransform->SetPosition(pos);

	if (!mCleared)
	{
		mStartTerminate = true;

	}
}

void SpawnerComponent::SetBackflipArea()
{
	std::string backflipName = "Backflip";
	auto bf = GetOwner().GetWorld().CreateGameObject(mTemplateFileName, backflipName);
	auto pos = mTransformComponent->GetPosition();
	pos.x -= 0.5f*mSpawnId;
	pos.y += 1.0f;
	pos.z -= 0.5f*mSpawnId;
	auto bfTransform = bf->GetComponent<TransformComponent>();
	bfTransform->SetPosition(pos);

}