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
		const Graphics::Model& GetModel() const { return mModel; }

	private:
		std::string mFileName;
		Graphics::Model mModel;
	};
}