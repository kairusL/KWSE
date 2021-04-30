#include "Precompiled.h"
#include "Camera.h"
#include "GraphicsSystem.h"

using namespace KWSE; 
using namespace KWSE::Graphics;

void Camera::SetPosition(const Math::Vector3& position)
{
	mPosition = position;

}

void KWSE::Graphics::Camera::SetDirection(const Math::Vector3 & direction)
{
	// Prevent setting direction straight up or down.
	auto dir = Math::Normalize(direction);
	if (Math::Abs(Dot(dir,Math::Vector3::YAxis))< 0.995f)
	{
		mDirection = dir;
	}
}

const Math::Vector3& KWSE::Graphics::Camera::GetPosition() const
{
	return mPosition;
}

const Math::Vector3& KWSE::Graphics::Camera::GetDirection() const
{
	return mDirection;
}



void KWSE::Graphics::Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f*Math::Constants::DegToRad;
	constexpr float kMaxFov = 170.0f*Math::Constants::DegToRad;
	mFov = Math::Clamp(fov, kMinFov, kMaxFov);
}

void KWSE::Graphics::Camera::SetAspectRation(float ratio)
{
	mAspectRatio = ratio;
}

void KWSE::Graphics::Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void KWSE::Graphics::Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void KWSE::Graphics::Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}

void KWSE::Graphics::Camera::Strafe(float distance)
{
	const Math::Vector3 right 
		= 
		Math::Normalize(Cross(Math::Vector3::YAxis,mDirection));
	mPosition += right * distance;
}

void KWSE::Graphics::Camera::Rise(float distance)
{
	mPosition += Math::Vector3::YAxis*distance;
}

void KWSE::Graphics::Camera::Yaw(float radian)
{
	Math::Matrix4 matRotate = Math::Matrix4::RotationY(radian);
	mDirection = Math::TransformNormal(mDirection, matRotate);
}

void KWSE::Graphics::Camera::Pitch(float radian)
{
	const Math::Vector3 right
		=
		Math::Normalize(Cross(Math::Vector3::YAxis, mDirection));

	const Math::Matrix4 matRot= Math::Matrix4::RotationAxis(right,radian);
	const Math::Vector3 newLook = Math::TransformNormal(mDirection, matRot);
	// Check to prevent our new look direction from being colinear with the Y-Axis
	// Look Direction can not be same as Y-Axis(0,1,0)
	const float dot = Math::Dot(newLook, Math::Vector3::YAxis);
	if (Math::Abs(dot) < 0.995f)
		mDirection = newLook;
}

void KWSE::Graphics::Camera::Zoom(float amount)
{
	constexpr float minZoom = 170.0f * Math::Constants::DegToRad;
	constexpr float maxZoom = 10.0f * Math::Constants::DegToRad;
	mFov = Math::Clamp(mFov - amount,maxZoom,minZoom);

}

Math::Matrix4 KWSE::Graphics::Camera::GetViewMatrix() const
{
	const Math::Vector3 l = mDirection;
	const Math::Vector3 r = Math::Normalize(Math::Cross(Math::Vector3::YAxis, l));
	const Math::Vector3 u = Math::Normalize(Math::Cross(l, r));

	const float x = -Math::Dot(r, mPosition);
	const float y = -Math::Dot(u, mPosition);
	const float z = -Math::Dot(l, mPosition);

	return{

		r.x,u.x,l.x,0.0f,
		r.y,u.y,l.y,0.0f,
		r.z,u.z,l.z,0.0f,
		x,  y,  z ,  1.0f
	};
	

}

Math::Matrix4 KWSE::Graphics::Camera::GetProjectionMatrix() const
{
	const float a = (mAspectRatio == 0.0f) ? GraphicsSystem::Get()->GetBackBufferAspectRatio() : mAspectRatio;
	const float h = 1.0f / tan(mFov*0.5f);
	const float w = h / a;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float q = zf / (zf - zn);

	return{
		w,0.0f,0.0f,0.0f,
		0.0f,h,0.0f,0.0f,
		0.0f,0.0f,q,1.0f,
		0.0f,0.0f,-zn * q,0.0f
	};
}

Math::Ray KWSE::Graphics::Camera::ScreenPointToRay(int screenX, int screenY, uint32_t screenWidth, uint32_t screenHeight) const
{
	const float aspect = (float)screenWidth / (float)screenHeight;
	const float halfWidth = screenWidth * 0.5f;
	const float halfHeight = screenHeight * 0.5f;
	const float tanFOV = tanf(mFov * 0.5f);
	const float dx = tanFOV * ((float)screenX / halfWidth - 1.0f) * aspect;
	const float dy = tanFOV * (1.0f - (float)screenY / halfHeight);

	Math::Ray ray;
	ray.org = Math::Vector3::Zero;
	ray.dir = Normalize(Math::Vector3(dx, dy, 1.0f));

	Math::Matrix4 invMatView = Inverse(GetViewMatrix());
	ray.org = TransformCoord(ray.org, invMatView);
	ray.dir = TransformNormal(ray.dir, invMatView);
	return ray;
}
