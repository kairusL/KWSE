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
		void SetAnimationFileName(const char* fileName ) { mAnimationFileName.push_back(fileName); }
		void SetAnimationCount(const size_t count ) { mAnimationFileCount = count; }
		const Graphics::Model& GetModel() const;

	private:
		std::string mFileName;
		std::vector<std::string> mAnimationFileName;
		size_t mAnimationFileCount;

		Graphics::ModelId mModelId = 0;
	};
}