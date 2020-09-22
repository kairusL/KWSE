#include "Precompiled.h"
#include "ObstacleAvoidBehavior.h"
#include "AIWorld.h"
#include"Agent.h"

using namespace KWSE::AI;


KWSE::Math::Vector2 KWSE::AI::ObstacleAvoidBehavior::Calculate(KWSE::AI::Agent & agent)
{
	KWSE::Math::Vector2 desiredVelocity;
	float speed = KWSE::Math::Magnitude(agent.velocity);

	float closestObsDist = FLT_MAX;
	KWSE::Math::Vector2 closestObs;
	float ClosestIntersectingObstacle;
	float boxLength = mMiniumBox.y + (speed / agent.maxSpeed)*mMiniumBox.y;

	auto Obstacles = agent.world.GetObstacles();
	for (auto& obs : Obstacles)
	{
		KWSE::Math::Vector2 obsLocalPos = KWSE::Math::TransformCoord(obs.center, KWSE::Math::Inverse(agent.LocalToWorld()));
		if (KWSE::Math::Distance(obs.center,agent.position)- obs.radius > boxLength)
			continue;

		KWSE::Math::Vector2 obsClosePoint = KWSE::Math::Normalize(-obsLocalPos) * obs.radius + obsLocalPos;
		if (obsLocalPos.y>= 0) 
		{
			float expandRadius = obs.radius + agent.radius;
			if (KWSE::Math::Abs(obsLocalPos.x) < expandRadius)
			{
				float sqrtpart = KWSE::Math::Sqrt(expandRadius*expandRadius - obsLocalPos.x*obsLocalPos.x);
				float insectionPoint = obsLocalPos.y - sqrtpart;

				if (insectionPoint <=0)
				{
					insectionPoint = obsLocalPos.y + sqrtpart;
				}
				
				//KWSE::Math::Vector2 worldPos = KWSE::Math::TransformCoord(insectionPoint, agent.LocalToWorld());
				if (closestObsDist > insectionPoint)
				{
					closestObs = obsLocalPos;
					ClosestIntersectingObstacle = expandRadius;
					closestObsDist = insectionPoint;
				}
			}
		}
	}

	KWSE::Math::Matrix3 localToWorld = agent.LocalToWorld();
	KWSE::Math::Vector2 boxExtendTLWorld = KWSE::Math::TransformCoord({ mMiniumBox.x*0.5f,0.0f }, localToWorld);
	KWSE::Math::Vector2 boxExtendTRWorld = KWSE::Math::TransformCoord({ mMiniumBox.x*0.5f , boxLength }, localToWorld);
	KWSE::Math::Vector2 boxExtendBLWorld = KWSE::Math::TransformCoord({ -mMiniumBox.x*0.5f,0.0f }, localToWorld);
	KWSE::Math::Vector2 boxExtendBRWorld = KWSE::Math::TransformCoord({ -mMiniumBox.x*0.5f ,  boxLength }, localToWorld);
	KWSE::Graphics::SimpleDraw::AddScreenLine({ boxExtendTLWorld }, { boxExtendTRWorld }, KWSE::Graphics::Colors::AliceBlue);
	KWSE::Graphics::SimpleDraw::AddScreenLine({ boxExtendBLWorld }, { boxExtendBRWorld }, KWSE::Graphics::Colors::AliceBlue);
	KWSE::Graphics::SimpleDraw::AddScreenLine({ boxExtendTLWorld }, { boxExtendBLWorld }, KWSE::Graphics::Colors::AliceBlue);
	KWSE::Graphics::SimpleDraw::AddScreenLine({ boxExtendTRWorld }, { boxExtendBRWorld }, KWSE::Graphics::Colors::AliceBlue);

	if (closestObsDist == FLT_MAX)
	{
		return KWSE::Math::Vector2();
	}
	else
	{
		float multiplier = 20.0f + (boxLength - closestObs.y) / boxLength;
		float SteeringForceY = (ClosestIntersectingObstacle - closestObs.x)* multiplier;
		float BrakingWeight = 0.8f;
		float SteeringForceX = (ClosestIntersectingObstacle - closestObs.y)* BrakingWeight;


		desiredVelocity = KWSE::Math::Vector2(SteeringForceX, SteeringForceY);
		return  KWSE::Math::TransformCoord(desiredVelocity, agent.LocalToWorld());// -agent.velocity);
	}

}



