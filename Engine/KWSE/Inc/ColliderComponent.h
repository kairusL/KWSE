#pragma once
#include"Component.h"
namespace KWSE
{

	class TransformComponent;
	
	class ColliderComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Collider);
		MEMPOOL_DECLARE;
		ColliderComponent() = default;

		void Initialize() override;
		void DebugUI() override;

		void SetCenter(const Math::Vector3& center) { mCenter = center; }
		void SetExtend(const Math::Vector3& extend) { mExtend = extend; }

		Math::AABB GetAABB() const;
		
	private:
		// const -> meaning that collider would not move the game object.
		// merely just want to know where it is.
		const TransformComponent* mTransformComponent = nullptr;
		Math::Vector3 mCenter = Math::Vector3::Zero;
		Math::Vector3 mExtend= Math::Vector3::One;
	};
}