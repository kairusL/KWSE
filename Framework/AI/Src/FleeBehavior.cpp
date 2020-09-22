#include "Precompiled.h"
#include "FleeBehavior.h"

#include "Agent.h"

using namespace KWSE::AI;

KWSE::Math::Vector2 FleeBehavior::Calculate(Agent& agent)
{
	return Flee(agent, agent.destination);
}

KWSE::Math::Vector2 KWSE::AI::FleeBehavior::Flee(AI::Agent & agent, KWSE::Math::Vector2 destination)
{
	auto posToDest =agent.position- destination ;


	auto desiredVelocity = KWSE::Math::Normalize( posToDest)*agent.maxSpeed ;

	return desiredVelocity - agent.velocity;
}
