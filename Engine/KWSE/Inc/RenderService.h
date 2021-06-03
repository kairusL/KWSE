#pragma once
#include "Service.h"

namespace KWSE
{
	class RenderService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Render);



		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override; 
		void DebugUI() override; 

	private:


	};
}