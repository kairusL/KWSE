#ifndef INCLUDE_NFGE_AI_OBSTACLEAVOIDBEHAVIOR_H
#define INCLUDE_NFGE_AI_OBSTACLEAVOIDBEHAVIOR_H

#include "SteeringBehavior.h"

namespace KWSE::AI
{
	class ObstacleAvoidBehavior : public SteeringBehavior
	{
	public:
		KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
		void SetBox(KWSE::Math::Vector2 miniumBox) {
			mMiniumBox = miniumBox; };
	private:

		KWSE::Math::Vector2 mMiniumBox;
		//float boxRadiusX;
		//float boxRadiusY;
	};


}

#endif // !INCLUDE_NFGE_AI_OBSTACLEAVOIDBEHAVIOR_H