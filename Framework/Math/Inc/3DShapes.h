
#pragma once

//Vector
#include "Vector3.h"

namespace KWSE::Math
{
	struct AABB
	{
		Vector3 center;
		Vector3 extend;

		AABB() : center(0.0f, 0.0f, 0.0f), extend(0.0f, 0.0f, 0.0f) {}
		AABB(const Vector3& center, const Vector3& extend) : center(center), extend(extend) {}
	};

	//----------------------------------------------------------------------------------------------------


	//----------------------------------------------------------------------------------------------------

	struct Sphere
	{
		Vector3 center;
		float radius;

		Sphere() : center(0.0f, 0.0f, 0.0f), radius(1.0f) {}
		Sphere(float x, float y, float z, float radius) : center(x, y, z), radius(radius) {}
		Sphere(const Vector3& center, float radius) : center(center), radius(radius) {}
	};

	//----------------------------------------------------------------------------------------------------

	struct Ray
	{
		Vector3 org;
		Vector3 dir;

		Ray() : org(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, 1.0f) {}
		Ray(float x, float y, float z, float dx, float dy, float dz) : org(x, y, z), dir(dx, dy, dz) {}
		Ray(const Vector3& org, const Vector3& dir) : org(org), dir(dir) {}

		Vector3 GetPoint(float distance) { return org + (dir * distance); }
	};

	//----------------------------------------------------------------------------------------------------

	struct Plane
	{
		Vector3 n;
		float d;

		Plane() : n(0.0f, 1.0f, 0.0f), d(0.0f) {}
		Plane(float a, float b, float c, float d) : n(a, b, c), d(d) {}
	};


}