#ifndef INCLUDED_AI_SEEKBEHAVIOR_H
#define INCLUDED_AI_SEEKBEHAVIOR_H

#include "SteeringBehavior.h"

namespace KWSE::AI {

class SeekBehavior : public SteeringBehavior
{
public:
	KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
	KWSE::Math::Vector2 Seek(AI::Agent& agent, KWSE::Math::Vector2 destination);
};

} // namespace AI

#endif // #include INCLUDED_AI_SEEKBEHAVIOR_H