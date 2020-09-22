#include "Precompiled.h"
#include "SeekBehavior.h"

#include "Agent.h"

using namespace KWSE::AI;

KWSE::Math::Vector2 SeekBehavior::Calculate(Agent& agent)
{
	return Seek(agent ,agent.destination - agent.position);
}

KWSE::Math::Vector2 KWSE::AI::SeekBehavior::Seek(KWSE::AI::Agent & agent, KWSE::Math::Vector2 destination)
{
	auto posToDest = destination - agent.position;
	auto desiredVelocity = KWSE::Math::Normalize(posToDest) * agent.maxSpeed;
	return desiredVelocity - agent.velocity;
}
