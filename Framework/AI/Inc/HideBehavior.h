#ifndef INCLUDE_NFGE_AI_HIDEBEHAVIOR_H
#define INCLUDE_NFGE_AI_HIDEBEHAVIOR_H

#include "ArriveBehavior.h"

namespace KWSE::AI
{
	class HideBehavior : public ArriveBehavior
	{
	public:
		KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
		
	};

}

#endif // !INCLUDE_NFGE_AI_HIDEPOSEBEHAVIOR_H