#pragma once
#include "Common.h"

#include "Vector3.h"

namespace KWSE::Math
{
	constexpr float Dot(const Vector3& v0, const Vector3& v1)
	{
		return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
	}
	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return (v.x*v.x) + (v.y*v.y) + (v.z*v.z);
	}

	inline float Magnitude(const Vector3& v)
	{
		return sqrtf(MagnitudeSqr(v));
	}
	constexpr float DistanceSqr(const Vector3& v0, const Vector3 & v1)
	{
		float x = v0.x - v1.x;
		float y = v0.y - v1.y;
		float z = v0.z - v1.z;

		return (x*x + y * y + z * z);
	}
	inline float Distance(const Vector3& v0, const Vector3 &v1)
	{
		float x = v0.x - v1.x;
		float y = v0.y - v1.y;
		float z = v0.z - v1.z;

		return sqrtf(x*x + y * y + z * z);
	}
	inline Vector3 Normalize(const Vector3& v)
	{
		float length = Magnitude(v);
		ASSERT(length != 0," Tring to / length , length is 0 !!! ");
		return { Vector3(v.x / length, v.y / length, v.z / length) };
	}
	constexpr Vector3 Cross(const Vector3& u, const Vector3& v)
	{
		return  Vector3((u.y*v.z - u.z*v.y),
						(u.z*v.x - u.x*v.z),
						(u.x*v.y - u.y*v.x));
	}

}