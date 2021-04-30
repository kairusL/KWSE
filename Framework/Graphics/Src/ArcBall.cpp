#include "Precompiled.h"

#include "ArcBall.h"
#include "GraphicsSystem.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;

void ArcBall::Update(const Camera& camera)
{
	const auto& inputSystem = InputSystem::Get();
	const auto& graphicsSystem = GraphicsSystem::Get();

	if (!mDrag)
	{
		if (inputSystem->IsMousePressed(MouseButton::LBUTTON))
		{
			float distance;
			Ray ray = camera.ScreenPointToRay(
				inputSystem->GetMouseScreenX()
				, inputSystem->GetMouseScreenY()
				, graphicsSystem->GetBackBufferWidth()
				, graphicsSystem->GetBackBufferHeight());
			if (Intersect(ray, Sphere{ mPosition, mRadius }, distance))
			{
				mDragFromPos = ray.GetPoint(distance);
				mDrag = true;
			}
		}
	}
	if (inputSystem->IsMouseDown(MouseButton::LBUTTON))
	{
		float distance;
		Ray ray = camera.ScreenPointToRay(
			inputSystem->GetMouseScreenX()
			, inputSystem->GetMouseScreenY()
			, graphicsSystem->GetBackBufferWidth()
			, graphicsSystem->GetBackBufferHeight());

		if (Intersect(ray, Sphere{ mPosition, mRadius }, distance))
		{
			const Vector3 dragPosition = ray.GetPoint(distance);
			if (DistanceSqr(dragPosition, mDragFromPos) > 0.0f)
			{
				const Vector3 from = Normalize(mDragFromPos - mPosition);
				const Vector3 to = Normalize(dragPosition - mPosition);
				const Quaternion rotation = Quaternion::RotationFromTo(from, to);
				mRotation = rotation * mRotation;
				mDragFromPos = dragPosition;
			}
		}
	}
	else
	{
		mDrag = false;
	}
}