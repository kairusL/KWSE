#pragma once
#include "Common.h"

//Vector
#include "Vector2.h"
#include "Vector3.h"

//Matrix
#include "Matrix3.h"


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

	//Matrix3
	const Matrix3 Matrix3::Identity
	{
		1.0f , 0.0f , 0.0f,
		0.0f , 1.0f , 0.0f,
		0.0f , 0.0f , 1.0f
	};

	constexpr Matrix3 Transpose(const Matrix3& m)
	{
		return
		{
		m._11,m._21,m._31,
		m._12,m._22,m._32,
		m._13,m._23,m._33
		};
	}
	



	constexpr float Dot(const Vector3& v0, const Vector3& v1)
	{
		return (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
	}
	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return (v.x*v.x) + (v.y*v.y) + (v.z*v.z);
	}

	//Inline
	//Constexpr

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
	constexpr Matrix3 Inverse(const Matrix3& m)
	{
		const float determinant = Determinant(m);
		const float inverseDeterminant = 1.0f / determinant;
		return Adjoint(m) *inverseDeterminant;
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