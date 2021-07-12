#pragma once

#include "Component.h"

namespace KWSE
{
	class ModelComponent;

	class StateComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::State);
		MEMPOOL_DECLARE;

		StateComponent() = default;

		void Initialize() override;

		void Update(float deltaTime) override;


	private:
	
	};
}