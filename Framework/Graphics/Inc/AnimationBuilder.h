#pragma once

#include "Animation.h"
namespace KWSE::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& SetTime(float time);
		AnimationBuilder& AdvanceTime(float time);

		AnimationBuilder& AddPosition(const Math::Vector3& position);
		AnimationBuilder& AddRotationKey(const Math::Quaternion& rotation);
		AnimationBuilder& AddScaleKey(const Math::Vector3& scale);

		AnimationBuilder& SetLooping(bool looping);


		Animation Get();
	private:
		Animation mTemp;
		float mTime = 0.0f;
	};

}