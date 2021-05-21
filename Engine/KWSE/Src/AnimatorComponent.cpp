#include "Precompiled.h"
#include "AnimatorComponent.h"

#include "GameObject.h"
#include "ModelComponent.h"

using namespace KWSE;
using namespace KWSE::Graphics;

MEMPOOL_DEFINE(AnimatorComponent, 1000)

void AnimatorComponent::Initialize()
{
	mModelComponent = GetOwner().GetComponent<ModelComponent>();
	mAnimator.Initialize(const_cast<KWSE::Graphics::Model*>(&mModelComponent->GetModel()));
}

void AnimatorComponent::Update(float deltaTime)
{
	mAnimator.Update(deltaTime);
}
