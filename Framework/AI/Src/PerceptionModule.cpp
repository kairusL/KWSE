#include"Precompiled.h"
#include "PerceptionModule.h"

KWSE::AI::PerceptionModule::PerceptionModule(Agent & agent, ImportanceCalculator importanceCalculator)
	:mAgent(agent)
	,mImportanceCalculator(std::move(importanceCalculator))
{
}

void KWSE::AI::PerceptionModule::Update(float deltaTime)
{
	//UPdate sensors and refresh/add memory records;
	for (auto& [name, sensor] : mSensors)
	{
		sensor->Update(mAgent, mMemory, deltaTime);
	}

	//Remove any records older than memory span
	for (auto iter = mMemory.begin(); iter != mMemory.end();)
	{
		if (iter->lastRecordedTime + mMemorySpan < KWSE::Core::TimeUtil::GetTime())
		{
			iter = mMemory.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	//Calculator importance on new records
	for (auto& m : mMemory)
	{
		mImportanceCalculator(mAgent, m);
	}

	//Sort records by importance
	mMemory.sort([](const MemoryRecord& a, const MemoryRecord& b)
	{
		return a.importance > b.importance;
	});
}
