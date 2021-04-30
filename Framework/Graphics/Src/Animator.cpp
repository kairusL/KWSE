#include "Precompiled.h"

#include "Animator.h"
#include "ModelLoader.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Math;

Animator::~Animator()
{
	ASSERT(mModel == nullptr, "Animator -- Terminate must be called before destruction.");
}

void KWSE::Graphics::Animator::Terminate()
{
	if (mModel)
	{
		mModel = nullptr;
		delete mModel;
	}
}

void Animator::AddClip(std::filesystem::path fileName)
{
	ModelLoader::LoadAnimation(fileName, *mModel);
}

void KWSE::Graphics::Animator::PlayAnimation(int clipIndex)
{
	if (clipIndex!= mAnimClipIndex&& clipIndex < mModel->animSet.size())
	{
		mAnimationTimer = 0.0f;
	}
	 mAnimClipIndex = clipIndex < mModel->animSet.size() ? clipIndex : mAnimClipIndex; 
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

const std::vector<KWSE::Math::Matrix4> KWSE::Graphics::Animator::GetSkeletonTransform(const KWSE::Math::Matrix4 matWorld)
{
	
		for (auto& matrix : mSkeletonTransform)
			matrix = matrix * matWorld;

		return mSkeletonTransform;
	
}
