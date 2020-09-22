#include "Precompiled.h"
#include "SeperationBehavior.h"
#include "AIWorld.h"

#include "Agent.h"

KWSE::Math::Vector2 KWSE::AI::SeperationBehavior::Calculate(KWSE::AI::Agent & agent)
{
	KWSE::Math::Vector2 totalForce;
	for (auto& neighbor :agent.neighbors)
	{
		auto neighborToAgent = agent.position - neighbor->position;
		auto distanceToAgent = KWSE::Math::Magnitude(neighborToAgent);
		if (distanceToAgent<=0.0)
		{
			totalForce += agent.heading*agent.maxSpeed;
		}
		else
		{
		auto seperationDirection = neighborToAgent / distanceToAgent;
		auto seperationForce = agent.maxSpeed*(1.0f - KWSE::Math::Min(distanceToAgent, 100.0f) / 100.0f);
		totalForce += seperationDirection * seperationForce;
		}
	}
	return totalForce;
}

