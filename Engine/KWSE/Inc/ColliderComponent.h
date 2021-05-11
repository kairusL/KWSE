#pragma once
#include"Component.h"
namespace KWSE
{
	class ColliderComponent final : public Component
	{
	public:
		SET_COMPONENT_ID(ComponentId::Collider)
			ColliderComponent() = default;

		
	private:
		Math::Vector3 mCenter;
		Math::Vector3 mExtend;
	};
}