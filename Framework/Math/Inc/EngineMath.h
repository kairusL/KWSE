#pragma once
#include "Common.h"

//Vector
#include "Vector2.h"
#include "Vector3.h"

//Matrix
#include "Matrix3.h"
#include "Matrix4.h"


namespace KWSE::Math
{
	//Vector2
	const Vector2 Vector2::XAxis{ 1.0f,0.0f };
	const Vector2 Vector2::YAxis{0.0f,1.0f};

	const Vector2 Vector2::Zero{0.0f};
	const Vector2 Vector2::One{1.0f };


	//Vector3
	const Vector3 Vector3::XAxis{ 1.0f,0.0f ,0.0f};
	const Vector3 Vector3::YAxis{ 0.0f,1.0f,0.0f };
	const Vector3 Vector3::ZAxis{ 0.0f,0.0f,1.0f };

	const Vector3 Vector3::Zero{ 0.0f };
	const Vector3 Vector3::One{ 1.0f };

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
	
	//
	// Dot 
	constexpr float Dot(const Vector2& v0, const Vector2& v1)
	{
		return (v0.x * v1.x) + (v0.y * v1.y);
	}
	constexpr float Dot(const Vector3& v0, const Vector3& v1)
	{
		return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
	}

	// MagnitudeSqr
	constexpr float MagnitudeSqr(const Vector2& v)
	{
		return Dot(v, v);
	}
	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return (v.x*v.x) + (v.y*v.y) + (v.z*v.z);
	}

	// Magnitude
	inline float Magnitude(const Vector2& v)
	{
		return sqrt(MagnitudeSqr(v));
	}
	inline float Magnitude(const Vector3& v)
	{
		return sqrt(MagnitudeSqr(v));
	}

	// Normalize
	inline Vector2 Normalize(const Vector2& v)
	{
		return v / Magnitude(v);
	}
	inline Vector3 Normalize(const Vector3& v)
	{
		ASSERT(Magnitude(v) != 0," Tring to / length , length is 0 !!! ");
		return v / Magnitude(v);
	}
	
	// DistanceSqr
	constexpr float DistanceSqr(const Vector3& v0, const Vector3 & v1)
	{
		float x = v0.x - v1.x;
		float y = v0.y - v1.y;
		float z = v0.z - v1.z;

		return (x*x + y * y + z * z);
	}
	// Distance
	inline float Distance(const Vector3& v0, const Vector3 &v1)
	{
		float x = v0.x - v1.x;
		float y = v0.y - v1.y;
		float z = v0.z - v1.z;

		return sqrtf(x*x + y * y + z * z);
	}

	// Cross
	constexpr Vector3 Cross(const Vector3& u, const Vector3& v)
	{
		return  Vector3((u.y*v.z - u.z*v.y),
						(u.z*v.x - u.x*v.z),
						(u.x*v.y - u.y*v.x));
	}

	// Transform
	constexpr Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	{
		return {
			(v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (1.0f * m._41),
			(v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (1.0f * m._42),
			(v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (1.0f * m._43)
		};
	}
	constexpr Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
	{
		return {
			(v.x * m._11) + (v.y * m._21) + (v.z * m._31),
			(v.x * m._12) + (v.y * m._22) + (v.z * m._32),
			(v.x * m._13) + (v.y * m._23) + (v.z * m._33)
		};
	}

	// GetRight
	constexpr Vector3 GetRight(const Matrix4& m)
	{
		return { m._11, m._12, m._13 };
	}

	// GetUp
	constexpr Vector3 GetUp(const Matrix4& m)
	{
		return { m._21, m._22, m._23 };
	}

	// GetLook
	constexpr Vector3 GetLook(const Matrix4& m)
	{
		return { m._31, m._32, m._33 };
	}

	// GetTranslation
	constexpr Vector3 GetTranslation(const Matrix4& m)
	{
		return { m._41, m._42, m._43 };
	}

	// Lerp
	constexpr float Lerp(float a, float b, float t)
	{
		return a + ((b - a) * t);
	}
	constexpr Vector3 Lerp(const Vector3& v0, const Vector3& v1, float t)
	{
		return v0 + ((v1 - v0) * t);
	}

	// Transpose
	constexpr Matrix3 Transpose(const Matrix3& m)
	{
		return
		{
		m._11,m._21,m._31,
		m._12,m._22,m._32,
		m._13,m._23,m._33
		};
	}

	// Determinant
	constexpr float Determinant(const Matrix3& m)
	{
		//11a, 12b, 13c
		//21d, 22e, 23f
		//31g, 32h, 33i
		//aei + bfg + cdh - ceg - bdi - afh
		return
		{
			(m._11*m._22*m._33) + (m._12*m._23*m._31) + (m._13*m._21*m._32)
			-
			(m._13*m._22*m._31) - (m._12*m._21*m._33) - (m._11*m._23*m._32)
		}
			;
	}
	// Adjoint
	constexpr Matrix3 Adjoint(const Matrix3& m)
	{
		return Matrix3
		{
			+((m._22*m._33)-(m._23*m._32)), 
			-((m._21*m._33)-(m._23*m._31)), 
			+((m._21*m._32)-(m._22*m._31)), 

			-((m._12*m._33)-(m._13*m._32)),
			+((m._11*m._33)-(m._13*m._31)),
			-((m._11*m._32)-(m._12*m._31)),

			+((m._12*m._23)-(m._13*m._22)),
			-((m._11*m._23)-(m._13*m._21)),
			+((m._11*m._22)-(m._12*m._21))
		};
	}
	// Inverse
	constexpr Matrix3 Inverse(const Matrix3& m)
	{
		const float determinant = Determinant(m);
		const float inverseDeterminant = 1.0f / determinant;
		return Adjoint(m) *inverseDeterminant;
	}
	
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



	//Inline
	//Constexpr



}