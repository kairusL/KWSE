#include"Precompiled.h"
#include"Animation.h"

using namespace KWSE;
using namespace KWSE::Math;
using namespace KWSE::Graphics;

Vector3 Animation::GetPosition(float time) const
{
	//if (mPositionKeys.empty())
	//	return Vector3::Zero;

	if (mLooping && (time > mPositionKeys.back().time))
	{
		time -= (static_cast<int>(time / mTotalDuration)*mTotalDuration);// -mPositionKeys.front().time;
	}
	if (mPositionKeys.back().time >time)
	{
		for (size_t i = 0; i < mPositionKeys.size(); ++i)
		{
			if (time < mPositionKeys[i].time)
			{
				int endFrame = i;
				int startFrame = i - 1;
				float duration = mPositionKeys[endFrame].time - mPositionKeys[startFrame].time;
				float percentage = (time - mPositionKeys[startFrame].time) / duration;
				return Lerp(mPositionKeys[startFrame].key, mPositionKeys[endFrame].key, percentage);
			}
		}
	}
	return mPositionKeys.back().key;
}

Quaternion Animation::GetRotation(float time) const
{

	//if (mRotationKeys.empty())
	//	return Quaternion::Identity;
	if (mLooping&&(time > mRotationKeys.back().time))
	{
		time -= (static_cast<int>(time / mTotalDuration)*mTotalDuration); //-mRotationKeys.front().time;
	}

	LOG("Ros time : %f", time);
	// If time is before the first frame, clamp and return the first key
	if (time < mRotationKeys.front().time)
		return mRotationKeys.front().key;
	if (mRotationKeys.back().time > time)
	{

		for (size_t i = 0; i < mRotationKeys.size(); ++i)
		{
			if (time < mRotationKeys[i].time)
			{
				int startFrame = i - 1;
				int endFrame = i;
				float duration = mRotationKeys[endFrame].time - mRotationKeys[startFrame].time;
				float percentage = (time - mRotationKeys[startFrame].time) / duration;
				return Slerp(mRotationKeys[startFrame].key, mRotationKeys[endFrame].key, percentage);
			}
		}
	}
	// If time is beyond the last frame, clamp and return the last key
	return mRotationKeys.back().key;
}

Vector3 Animation::GetScale(float time) const
{
	if (mScaleKeys.empty())
		return Vector3::One;
	if (mLooping&& (time > mScaleKeys.back().time))
	{
		time -= (static_cast<int>(time / mTotalDuration)*mTotalDuration);// -mScaleKeys.front().time;
	}
	if (mScaleKeys.back().time > time)
	{
		for (size_t i = 0; i < mScaleKeys.size(); ++i)
		{
			if (time < mScaleKeys[i].time)
			{
				int startFrame = i - 1;
				int endFrame = i;
				float duration = mScaleKeys[endFrame].time - mScaleKeys[startFrame].time;
				float percentage = (time - mScaleKeys[startFrame].time) / duration;
				return Lerp(mScaleKeys[startFrame].key, mScaleKeys[endFrame].key, percentage);
			}
		}
	}
		return mScaleKeys.back().key;
}

float Animation::AdjustTime(float time, float totalDuration)
{
	if (mLooping)
	{
			time -= totalDuration;
	}
	return time;
}