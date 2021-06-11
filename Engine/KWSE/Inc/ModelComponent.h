#pragma once

#include "Component.h"

namespace KWSE
{
	class ModelComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Model);
		MEMPOOL_DECLARE;

		ModelComponent() = default;

		void Initialize() override;
		void Terminate() override;

		void SetFileName(const char* fileName) { mFileName = fileName; }
		void SetAnimationFileName(const char* animationFileName) { mAnimationFileName = animationFileName; }
		const Graphics::Model& GetModel() const;

	private:
		std::string mFileName;
		std::string mAnimationFileName;
		Graphics::ModelId mModelId = 0;
	};
}