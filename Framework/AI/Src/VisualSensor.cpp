#include "Precompiled.h"
#include"VisualSensor.h"
#include "Agent.h"
#include "AIWorld.h"
#include "MemoryRecord.h"

void KWSE::AI::VisualSensor::Update(Agent& agent, MemoryRecords & memory, float deltaTime)
{
	/////          X::Math::Circle ->check agent pos and the range for neighbor.      -- check which neighbot type you looking for. 
	auto neighbors = agent.world.GetNeighborhood({ agent.position,viewRange*2 }, neighborTypeId);
	for (auto neighbor : neighbors)
	{
		// its outside the range
		if (KWSE::Math::Distance(neighbor->position,agent.position) > viewRange)
		{
			continue;
		}
		//						(direction to neighbor.       where agent is facing now)  check dot(cos)  if in range will return 1 if not will return 0;
		//check if the neighbor is in the FOV.
		if (KWSE::Math::Dot(KWSE::Math::Normalize(neighbor->position-agent.position),agent.heading)< cosf(KWSE::Math::Constants::DegToRad*viewAngle))
		{
			continue;
		}
		//check is wall or obstacle between the agent and neighbor.
		if (!agent.world.HasLineOfSight(agent.position,neighbor->position))
		{
			continue;
		}
		//check this neighbor is in the memoryRecord, if not  creat one.
		MemoryRecord& checkRecord = FindOrCreate(memory, neighbor->GetUniqurId());
		//save  key ["lastSeenPosition"] as vector2(neighbor position)  to propertieslist
		checkRecord.properties["lastSeenPosition"] = neighbor->position;
		checkRecord.lastRecordedTime = KWSE::Core::TimeUtil::GetTime();
		
	}

}
