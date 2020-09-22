#include "Precompiled.h"
#include "SteeringModule.h"

using namespace KWSE::AI;

SteeringModule::SteeringModule(Agent& agent)
	: mAgent(agent)
{}

KWSE::Math::Vector2 SteeringModule::Calculate()
{
	KWSE::Math::Vector2 total;
	for (auto& [name, behavior] : mBehaviors)
	{
		if (behavior->IsActive())
			total += behavior->Calculate(mAgent);
	}

	return total;
}