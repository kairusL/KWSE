#include "Precompiled.h"
#include "HideBehavior.h"
#include "AIWorld.h"

#include "Agent.h"

KWSE::Math::Vector2 KWSE::AI::HideBehavior::Calculate(KWSE::AI::Agent & agent)
{
	std::vector<KWSE::Math::Circle> Obstacles = agent.world.GetObstacles();
	float disToClosest = FLT_MAX;


	KWSE::Math::Vector2 bestHidingSpot;
	KWSE::Math::Vector2 HidingSpot;


	for (auto obs : Obstacles)
	{
		float distanceFromBoundary = 30.0f;
		float disAway = obs.radius + distanceFromBoundary;
		KWSE::Math::Vector2 toObject = KWSE::Math::Normalize(obs.center - agent.threat->position);

		HidingSpot = (toObject* disAway) + obs.center;
		float dis = KWSE::Math::DistanceSqr(HidingSpot, agent.position);

		if (dis<disToClosest)
		{
			disToClosest = dis;
			bestHidingSpot = HidingSpot;
		}
		
	}

	if (disToClosest ==FLT_MAX)
	{
		return KWSE::Math::Vector2();
	}
	return Arrive(agent,bestHidingSpot);
}

