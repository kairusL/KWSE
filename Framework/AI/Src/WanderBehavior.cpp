#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace KWSE::AI;

KWSE::Math::Vector2 WanderBehavior::Calculate(Agent& agent)
{
	mWanderPoint = mWanderPoint + KWSE::Math::RandomUnitCircle(true) * mWanderJitter;
	mWanderPoint = KWSE::Math::Normalize(mWanderPoint) * mWanderRadius;
	//wanderPoint.y += wanderDistance;
	auto wanderTarget = mWanderPoint + KWSE::Math::Vector2{ 0.0f, mWanderDistance };
	auto localToWorld = agent.LocalToWorld();
	KWSE::Math::Vector2 destination = KWSE::Math::TransformCoord(wanderTarget, localToWorld);
	mRenderPoint = destination;
	agent.destination = destination;
	KWSE::Graphics::SimpleDraw::AddScreenCircle(KWSE::Math::TransformCoord(KWSE::Math::Vector2{ 0.0f, mWanderDistance }, agent.LocalToWorld()), mWanderRadius, KWSE::Graphics::Colors::LightBlue);
	KWSE::Graphics::SimpleDraw::AddScreenCircle(agent.destination, 5.0f, KWSE::Graphics::Colors::Green);
	KWSE::Graphics::SimpleDraw::AddScreenLine(agent.position, agent.destination, KWSE::Graphics::Colors::Cyan);

	return SeekBehavior::Calculate(agent);
}

void KWSE::AI::WanderBehavior::SetParama(float radius, float distance, float jitter)
{
	mWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}
