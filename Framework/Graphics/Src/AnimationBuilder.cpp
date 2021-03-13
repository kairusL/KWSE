#include "Precompiled.h"
#include "AnimationBuilder.h"


using namespace KWSE::Graphics;

AnimationBuilder & KWSE::Graphics::AnimationBuilder::SetTime(float time)
{
	mTime = time;
	mTemp.mStartFrame = time;
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::AdvanceTime(float time)
{
	mTime += time;
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::AddPositionKey(const Math::Vector3 & position)
{
	ASSERT(mTemp.mPositionKeys.empty() || mTemp.mPositionKeys.back().time < mTime, "PositionKey is Empty");
	mTemp.mPositionKeys.push_back({ position,mTime });
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::AddRotationKey(const Math::Quaternion & rotation)
{
	ASSERT(mTemp.mRotationKeys.empty() || mTemp.mRotationKeys.back().time < mTime, "RositionKeys is Empty");
	mTemp.mRotationKeys.push_back({ rotation,mTime });
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::AddScaleKey(const Math::Vector3 & scale)
{
	ASSERT(mTemp.mScaleKeys.empty() || mTemp.mScaleKeys.back().time < mTime, "ScaleKeys is Empty");
	mTemp.mScaleKeys.push_back({ scale,mTime });
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::AddPositionKey(const Math::Vector3 & position, float time)
{

	ASSERT(mTemp.mPositionKeys.empty() || mTemp.mPositionKeys.back().time < time, "PositionKey is Empty");
	mTemp.mPositionKeys.push_back({ position,time });
	mTime = time;
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::AddRotationKey(const Math::Quaternion & rotation, float time)
{
	ASSERT(mTemp.mRotationKeys.empty() || mTemp.mRotationKeys.back().time < time, "RositionKeys is Empty");
	mTemp.mRotationKeys.push_back({ rotation,time });
	mTime = time;
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::AddScaleKey(const Math::Vector3 & scale, float time)
{
	ASSERT(mTemp.mScaleKeys.empty() || mTemp.mScaleKeys.back().time < time, "ScaleKeys is Empty");
	mTemp.mScaleKeys.push_back({ scale,time });
	mTime = time;
	return *this;
}

AnimationBuilder & KWSE::Graphics::AnimationBuilder::SetLooping(bool looping)
{
	mTemp.mLooping = looping;
	return *this;
}

Animation KWSE::Graphics::AnimationBuilder::Get()
{
	mTemp.mEndFrame = mTime;
	mTemp.mTotalDuration = mTemp.mEndFrame - mTemp.mStartFrame;
	mTime = 0.0f;
	return std::move(mTemp);	
}
