#pragma once
#include "Common.h"

#include "Vector3.h"

namespace KWSE::Math
{
	constexpr float Dot(const Vector3& v0, const Vector3& v1)
	{
		return 0.0f;
	}
	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return 0.0f;
	}

	inline float Magnitude(const Vector3& v)
	{
		return 0.0f;
	}
	constexpr float DistanceSqr(const Vector3& v0, const Vector3 & v1)
	{
		return 0.0f;
	}
	inline float Distance(const Vector3& v0, const Vector3 &v1)
	{
		return 0.0f;
	}
	inline Vector3 Normalize(const Vector3& v)
	{
		return {};
	}
	constexpr Vector3 Cross(const Vector3& u, const Vector3& v)
	{
		return {};
	}

}