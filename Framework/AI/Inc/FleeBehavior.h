#ifndef INCLUDED_AI_FLEEBEHAVIOR_H
#define INCLUDED_AI_FLEEBEHAVIOR_H

#include "SteeringBehavior.h"

namespace KWSE::AI {

class FleeBehavior : public SteeringBehavior
{
public:
	KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
	KWSE::Math::Vector2 Flee(AI::Agent& agent, KWSE::Math::Vector2 destination);
	
};

} // namespace AI

#endif // #include INCLUDED_AI_ARRIVEBEHAVIOR_H