#ifndef INCLUDED_AI_ARRIVEBEHAVIOR_H
#define INCLUDED_AI_ARRIVEBEHAVIOR_H

#include "SteeringBehavior.h"

namespace KWSE::AI
{

	class ArriveBehavior : public SteeringBehavior
	{
	public:
		KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
		KWSE::Math::Vector2 Arrive(AI::Agent& agent, KWSE::Math::Vector2 destination);
		
	};

} // namespace AI

#endif // #include INCLUDED_AI_ARRIVEBEHAVIOR_H