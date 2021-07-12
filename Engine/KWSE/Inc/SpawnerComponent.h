#pragma once

#include "Component.h"

namespace KWSE
{
	class TransformComponent;

	class SpawnerComponent final : public Component
	{

	public:
		SET_TYPE_ID(ComponentId::Spawner);
		MEMPOOL_DECLARE;

		SpawnerComponent() = default;

		void Initialize() override;

		void Update(float deltaTime) override;

		void SetTemplateFileName(std::string templateFileName) { mTemplateFileName = templateFileName; }
		void SetSpawnObjectName(std::string spawnObjectName) { mSpawnObjectName = spawnObjectName; }
		void SetSpawnAmount(int spawnAmount) { mSpawnAmount = spawnAmount; }
		void SetSpawnWaitTime(float spawnWaitTime) { mNextSpawnTime = spawnWaitTime; }
		void SetMaxAmount(int maxSpawnAmount) { mMaxSpawnAmount = maxSpawnAmount; }

		void SetSpawnPath(bool spawnPath) { mSpawnPath = spawnPath; }
		void SetPath(float deltaTime);
		void SetJumpActive(bool jumpActive) { mJumpActive = jumpActive; }
		void SetBackflipAreaActive(bool backflipAreaActive) { mSpawnBackflipAreaActive = backflipAreaActive; }
		void SetBackflipArea();
		void SetJump();
		void Terminate(float deltaTime);
	private:
		const TransformComponent* mTransformComponent = nullptr;

		std::string mTemplateFileName;
		std::string mSpawnObjectName;
		int mSpawnAmount=0;
		int mMaxSpawnAmount=0;
		float mNextSpawnTime=0.0f;
		int mSpawnId=0;
		float mTimer=0.0f;
		bool mSpawnPath=false;
		bool mJumpActive = false;
		bool mSpawnBackflipAreaActive = false;
		bool mStartTerminate = false;
		bool mCleared = false;
	};
}