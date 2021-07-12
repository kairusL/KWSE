#include "Precompiled.h"

#include "Animator.h"
#include "ModelLoader.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Math;

void KWSE::Graphics::Animator::PlayAnimation(int clipIndex)
{
	if (clipIndex!= mAnimClipIndex&& clipIndex < mModel->animSet.size())
	{
		mAnimationTimer = 0.0f;
	}
	 mAnimClipIndex = clipIndex < mModel->animSet.size() ? clipIndex : mAnimClipIndex; 
}
void KWSE::Graphics::Animator::PlayAnimation(std::string name)
{
	for (int i=0;i<mModel->animSet.size();++i)
	{
		if (mModel->animSet[i]->name ==name)
		{
			clip = i;
			
		}
	}
	if (clip != mAnimClipIndex && clip < mModel->animSet.size())
	{
		mAnimationTimer = 0.0f;
	}
	mAnimClipIndex = clip < mModel->animSet.size() ? clip : mAnimClipIndex;

}

void Animator::Update(float deltaTime)
{
	if (mAnimate)
	{
		auto& animationClip = mModel->animSet[mAnimClipIndex];
		mAnimationTimer += deltaTime;
		if (mAnimationTimer > animationClip->duration / animationClip->ticksPerSecond)
		{
			if (mLooping)
				mAnimationTimer -= animationClip->duration / animationClip->ticksPerSecond;
			else
				mAnimationTimer = animationClip->duration / animationClip->ticksPerSecond;
		}
		mToLocalTransform = KWSE::Graphics::CalculateSkinningMatrices(*(mModel->skeleton), *animationClip, mAnimationTimer * mAnimationSpeed);
		mSkeletonTransform = CalculateBoneMatrices(*(mModel->skeleton), *animationClip, mAnimationTimer * mAnimationSpeed);
	}
	else
	{
		mToLocalTransform = KWSE::Graphics::CalculateSkinningMatrices(*(mModel->skeleton));
		mSkeletonTransform = CalculateBoneMatrices(*(mModel->skeleton));
	}

	auto& bones = mModel->skeleton.get()->bones;
	for (auto& bone : bones)
		mToLocalTransform[bone->index] = bone->offsetTransform * mToLocalTransform[bone->index];
}