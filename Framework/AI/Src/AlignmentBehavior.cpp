#include "Precompiled.h"
#include "AlignmentBehavior.h"
#include "AIWorld.h"

#include "Agent.h"

KWSE::Math::Vector2 KWSE::AI::AlignmentBehavior::Calculate(KWSE::AI::Agent & agent)
{
	KWSE::Math::Vector2 averageHeading = agent.heading;
	for (auto& neighbor : agent.neighbors)
	{
		averageHeading += neighbor->heading;
	}
	averageHeading /= (agent.neighbors.size() + 1.0f);
	return averageHeading - agent.heading;
}

