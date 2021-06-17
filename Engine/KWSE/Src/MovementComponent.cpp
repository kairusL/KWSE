#include "Precompiled.h"
#include "MovementComponent.h"

#include "GameObject.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "RenderService.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;

MEMPOOL_DEFINE(MovementComponent, 1000)

void MovementComponent::Initialize()
{
	mAnimatorComponent = GetOwner().GetComponent< AnimatorComponent>();
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mAnimatorComponent->Initialize();
	mTransformComponent->Initialize();
}

void MovementComponent::Update(float deltaTime)
{
	auto input = InputSystem::Get();
	auto pos = mTransformComponent->GetPosition();
	auto rot = mTransformComponent->GetRotation();
	bool play = true;
	bool stop = false;
	auto horCamDir = Math::Vector3{ 0.99f,0.0049f, 0.019f };
	auto camDir = Math::Vector3{ 0.036f,-0.17f, 0.983f };
	auto speed = mAnimatorComponent->GetAnimator().GetAnimationSpeed();
	if (mPos ==pos)
	{
		mAnimatorComponent->GetAnimator().SetLooping(stop);
	}
	if (input->IsKeyDown(KeyCode::RIGHT))
	{
		mPos = pos;
		mPos.x += speed *deltaTime;
		mAnimatorComponent->GetAnimator().PlayAnimation(1);
		mAnimatorComponent->GetAnimator().SetLooping(play);
		mTransformComponent->SetPosition(mPos);
		Math::Vector3 dir = Math::Normalize( pos-mPos);
		mTransformComponent->SetRotation(rot.RotationLook(-horCamDir, Math::Vector3::YAxis));
	}
	if (input->IsKeyDown(KeyCode::LEFT))
	{
		mPos = pos;
		mPos.x -= speed *deltaTime;
		mAnimatorComponent->GetAnimator().PlayAnimation(1);
		mAnimatorComponent->GetAnimator().SetLooping(play);
		mTransformComponent->SetPosition(mPos);

		mTransformComponent->SetRotation(rot.RotationLook(horCamDir, Math::Vector3::YAxis));
	}
	if (input->IsKeyDown(KeyCode::UP))
	{
		mPos = pos;
		mPos.z += speed *deltaTime;
		mAnimatorComponent->GetAnimator().PlayAnimation(1);
		mAnimatorComponent->GetAnimator().SetLooping(play);
		mTransformComponent->SetPosition(mPos);
		//mTransformComponent->SetRotation(rot.RotationLook(dir,Math::Vector3::YAxis));
		mTransformComponent->SetRotation(rot.RotationLook(-camDir, Math::Vector3::YAxis));
	}
	if (input->IsKeyDown(KeyCode::DOWN))
	{
		mPos = pos;
		mPos.z -= speed *deltaTime;
		mAnimatorComponent->GetAnimator().PlayAnimation(1);
		mAnimatorComponent->GetAnimator().SetLooping(play);
		mTransformComponent->SetPosition(mPos);
		mTransformComponent->SetRotation(rot.RotationLook(camDir,Math::Vector3::YAxis));
	}
	if (input->IsKeyDown(KeyCode::SPACE))
	{
		mAnimatorComponent->GetAnimator().PlayAnimation(2);
		mAnimatorComponent->GetAnimator().SetLooping(play);
	}



}
