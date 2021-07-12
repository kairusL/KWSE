#pragma once

#include "Component.h"

namespace KWSE
{
	class AnimatorComponent;
	class TransformComponent;
	class RenderService;
	class GameWorld;

	class MovementComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Movement);
		MEMPOOL_DECLARE;

		MovementComponent() = default;

		void Initialize() override;

		void Update(float deltaTime) override;

		void TargetColliderCheck(Math::AABB aabb, std::string areaname);
	private:
		GameWorld* mWorld;
		RenderService* mRenderService;
		AnimatorComponent* mAnimatorComponent = nullptr;
		TransformComponent* mTransformComponent = nullptr;
		Math::Vector3 mPos = Math::Vector3(0.0f);
	};
}