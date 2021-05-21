#include"Precompiled.h"
#include"ColliderComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"
using namespace KWSE;

MEMPOOL_DEFINE(ColliderComponent, 1000);
void ColliderComponent::Initialize()
{
	// ColliderComponent needs to reference to transform component.
	// get component cast that pointer
	 mTransformComponent= GetOwner().GetComponent<TransformComponent>();
}

void ColliderComponent::DebugUI()
{
	const auto aabb = GetAABB();
	Graphics::SimpleDraw::AddAABB(aabb.center, aabb.extend, Graphics::Colors::Green,false);
}

Math::AABB ColliderComponent::GetAABB() const
{
	Math::AABB aabb;
	// where the transform component is + offset 
	aabb.center = mTransformComponent->GetPosition() + mCenter;
	// + extent from that position
	aabb.extend = mExtend;
	return aabb;
}