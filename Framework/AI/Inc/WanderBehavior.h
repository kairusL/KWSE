#ifndef INCLUDED_AI_WANDERBEHAVIOR_H
#define INCLUDED_AI_WANDERBEHAVIOR_H

#include "SeekBehavior.h"


namespace KWSE::AI
{

	class WanderBehavior :public SeekBehavior
	{
	public:
		KWSE::Math::Vector2 Calculate(AI::Agent& agent) override;
		void SetParama(float radius, float distance, float jitter);

	//private:
		float mWanderRadius = 20.0f;
		float mWanderDistance = 50.0f;
		float mWanderJitter = 10.0f;
		KWSE::Math::Vector2 mWanderPoint = {0.0f,0.0f};
		KWSE::Math::Vector2 mRenderPoint;

	};

} 

#endif // #include INCLUDED_AI_WANDERBEHAVIOR_H