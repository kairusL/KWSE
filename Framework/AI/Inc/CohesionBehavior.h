#ifndef INCLUDE_NFGE_AI_COHESIONBEHAVIOR_H
#define INCLUDE_NFGE_AI_COHESIONBEHAVIOR_H

#include "SeekBehavior.h"

namespace KWSE::AI
{
	class CohesionBehavior : public SeekBehavior
	{
	public:
		KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
		
	};

}

#endif 