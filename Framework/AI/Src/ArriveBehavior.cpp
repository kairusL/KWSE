#include "Precompiled.h"
#include "ArriveBehavior.h"

#include "Agent.h"

using namespace KWSE::AI;

KWSE::Math::Vector2 ArriveBehavior::Calculate(Agent& agent)
{
	return Arrive(agent, agent.destination);
}

KWSE::Math::Vector2 KWSE::AI::ArriveBehavior::Arrive(KWSE::AI::Agent & agent, KWSE::Math::Vector2 destination)
{
	auto posToDest = destination - agent.position;
	auto distance = KWSE::Math::Magnitude(posToDest);
	if (distance <= 0.0f)
		return {};

	auto speed = KWSE::Math::Min(agent.maxSpeed, distance);
	auto desiredVelocity = posToDest / distance * speed;

	return desiredVelocity - agent.velocity;
}
