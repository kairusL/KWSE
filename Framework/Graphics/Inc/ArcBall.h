#pragma once
#include "Camera.h"

using namespace KWSE;
using namespace KWSE::Graphics;

namespace KWSE::Graphics
{
	class ArcBall
	{
	public:
		void Update(const Camera& camera);

		void SetPosition(Math::Vector3 pos) { mPosition = pos; }
		void SetRadius(float radius) { mRadius = radius; }

		const Math::Vector3& GetPosition() const { return mPosition; }
		const Math::Quaternion& GetRoration() const { return mRotation; }
		const float GetRadius() const { return mRadius; }
	private:
		Math::Vector3 mDragFromPos = Math::Vector3::Zero;
		Math::Vector3 mPosition = Math::Vector3::Zero;
		Math::Quaternion mRotation = Math::Quaternion::Identity;

		float mRadius = 0.0f;
		bool mDrag = false;
	};

}