#ifndef INCLUDE_NFGE_AI_SEPERATIONBEHAVIOR_H
#define INCLUDE_NFGE_AI_SEPERATIONBEHAVIOR_H

#include "SteeringBehavior.h"

namespace KWSE::AI
{
	class SeperationBehavior : public SteeringBehavior
	{
	public:
		KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
		
	};

}

#endif // !INCLUDE_NFGE_AI_HIDEPOSEBEHAVIOR_H