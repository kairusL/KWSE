#pragma once

#include "Keyframe.h"

namespace KWSE::Graphics
{


	class Animation
	{
	public:
		Math::Vector3 GetPosition(float time) const;
		Math::Quaternion GetRotation(float time)const;
		Math::Vector3 GetScale(float time) const;


	private:
		friend class AnimationBuilder;

		float AdjustTime(float time,float totalDuration);

		PositionKeys mPositionKeys;
		RotationKeys mRotationKeys;
		ScaleKeys mScaleKeys;
		float mStartFrame = 0.0f;
		float mEndFrame = 0.0f;
		float mTotalDuration = 0.0f;
		bool mLooping = false;
	};
}