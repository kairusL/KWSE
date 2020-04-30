#include "Precompiled.h"
#include "EngineMath.h"

using namespace KWSE;
using namespace KWSE::Math;

//Vector2
const Vector2 Vector2::XAxis{ 1.0f, 0.0f };
const Vector2 Vector2::YAxis{ 0.0f, 1.0f };

//Vector3
const Vector3 Vector3::Zero{ 0.0f };
const Vector3 Vector3::One{ 1.0f };
const Vector3 Vector3::XAxis{ 1.0f, 0.0f, 0.0f };
const Vector3 Vector3::YAxis{ 0.0f, 1.0f, 0.0f };
const Vector3 Vector3::ZAxis{ 0.0f, 0.0f, 1.0f };
//Matrix
const Matrix3 Matrix3::Identity
{
	1.0f , 0.0f , 0.0f,
	0.0f , 1.0f , 0.0f,
	0.0f , 0.0f , 1.0f
};
const Matrix4 Matrix4::Identity
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f,
};

// RotationAxis  
Matrix4 Matrix4::RotationAxis(const Vector3& axis, float radian)
{
	const Vector3 u = Normalize(axis);
	const float x = u.x;
	const float y = u.y;
	const float z = u.z;
	const float s = sin(radian);
	const float c = cos(radian);

	return {
		c + (x * x * (1.0f - c)),
		x * y * (1.0f - c) + z * s,
		x * z * (1.0f - c) - y * s,
		0.0f,

		x * y * (1.0f - c) - z * s,
		c + (y * y * (1.0f - c)),
		y * z * (1.0f - c) + x * s,
		0.0f,

		x * z * (1.0f - c) + y * s,
		y * z * (1.0f - c) - x * s,
		c + (z * z * (1.0f - c)),
		0.0f,

		0.0f, 0.0f, 0.0f, 1.0f
	};
}