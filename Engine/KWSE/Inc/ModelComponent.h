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
		void SetAnimationFileName(const char* fileName) { mAnimationFileNames.push_back(fileName); }
		const Graphics::Model* GetModel() const;

	private:
		std::string mFileName;
		std::vector<std::string> mAnimationFileNames;

		Graphics::ModelId mModelId = 0;
	};
}