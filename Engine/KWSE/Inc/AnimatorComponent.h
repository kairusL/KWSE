#pragma once

#include "Component.h"

namespace KWSE
{
	class ModelComponent;

	class AnimatorComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Animator);
		MEMPOOL_DECLARE;

		AnimatorComponent() = default;

		void Initialize() override;

		void Update(float deltaTime) override;

		Graphics::Animator& GetAnimator() { return mAnimator; }

	private:
		const ModelComponent* mModelComponent = nullptr;
		Graphics::Animator mAnimator;
	};
}