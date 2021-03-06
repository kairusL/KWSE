#pragma once

#include "Animation.h"
namespace KWSE::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& SetTime(float time);
		AnimationBuilder& AdvanceTime(float time);

		AnimationBuilder& AddPositionKey(const Math::Vector3& position);
		AnimationBuilder& AddRotationKey(const Math::Quaternion& rotation);
		AnimationBuilder& AddScaleKey(const Math::Vector3& scale);

		AnimationBuilder& AddPositionKey(const Math::Vector3& position , float time);
		AnimationBuilder& AddRotationKey(const Math::Quaternion& rotation, float time);
		AnimationBuilder& AddScaleKey(const Math::Vector3& scale, float time);

		AnimationBuilder& SetLooping(bool looping);


		Animation Get();
	private:
		Animation mTemp;
		float mTime = 0.0f;
	};

}