#include "Precompiled.h"
#include "CohesionBehavior.h"
#include "AIWorld.h"

#include "Agent.h"

KWSE::Math::Vector2 KWSE::AI::CohesionBehavior::Calculate(KWSE::AI::Agent & agent)
{
	KWSE::Math::Vector2 sumOfNeigborsPosition ;

	for (auto& neighbor : agent.neighbors)
	{
		sumOfNeigborsPosition += neighbor->position;
	}
	if (agent.neighbors.size() > 0)
	{
		KWSE::Math::Vector2 centerOfMass = sumOfNeigborsPosition / agent.neighbors.size();
		KWSE::Math::Vector2 Destination = centerOfMass - agent.position;

		if ((KWSE::Math::IsZero(Destination.x)) && (KWSE::Math::IsZero(Destination.y)))
			return KWSE::Math::Vector2();
		return Seek(agent,centerOfMass);

		//X::Math::Vector2 desiredVelocity = X::Math::Normalize(Destination) * agent.maxSpeed;
	}
	else
		return KWSE::Math::Vector2();
}

