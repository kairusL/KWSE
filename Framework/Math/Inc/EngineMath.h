#pragma once
#include "Common.h"

//Vector
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

//Matrix
#include "Matrix3.h"
#include "Matrix4.h"

#include"Constants.h"


namespace KWSE::Math
{

	template <class T>
	constexpr T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <class T>
	constexpr T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template <class T>
	constexpr T Clamp(T value, T min, T max)
	{
		return Max(min, Min(max, value));
	}

	template <class T>
	constexpr T Lerp(T a, T b, float t)
	{
		return a + (b - a) * t;
	}

	constexpr float Abs(float value)
	{
		return value >= 0.0f ? value : -value;
	}

	constexpr float Sqr(float value)
	{
		return value * value;
	}



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
		//ASSERT(Magnitude(v) != 0," Tring to / length , length is 0 !!! ");
		if (Magnitude(v) == 0.0f)
		{
			return v;
		}
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
	
	


	constexpr Matrix4 Transpose(const Matrix4& m)
	{
		return {
			m._11, m._21, m._31, m._41,
			m._12, m._22, m._32, m._42,
			m._13, m._23, m._33, m._43,
			m._14, m._24, m._34, m._44
		};
	}

	constexpr float Determinant(const Matrix4& m)
	{
		float det = 0.0f;
		det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
		det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
		det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
		det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
		return det;
	}

	constexpr Matrix4 Adjoint(const Matrix4& m)
	{
		return
		{
			+(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
			-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
			+(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
			-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

			-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
			+(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
			-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
			+(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

			+(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
			-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
			+(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
			-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

			-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
			+(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
			-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
			+(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
		};
	}

	constexpr Matrix4 Inverse(const Matrix4& m)
	{
		const float determinant = Determinant(m);
		const float invDet = 1.0f / determinant;
		return Adjoint(m) * invDet;
	}

	constexpr Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	{
		const float w = (v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (1.0f * m._44);
		return {
			((v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (1.0f * m._41)) / w,
			((v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (1.0f * m._42)) / w,
			((v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (1.0f * m._43)) / w
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


	//constexpr Vector3 GetUp(const Matrix4& m)
	//{
	//	return { m._21, m._22, m._23 };
	//}

	//constexpr Vector3 GetLook(const Matrix4& m)
	//{
	//	return { m._31, m._32, m._33 };
	//}

	//constexpr Vector3 GetTranslation(const Matrix4& m)
	//{
	//	return { m._41, m._42, m._43 };
	//}




	//constexpr Matrix4 Transpose(const Matrix4& m)
	//{
	//	return {
	//		m._11, m._21, m._31, m._41,
	//		m._12, m._22, m._32, m._42,
	//		m._13, m._23, m._33, m._43,
	//		m._14, m._24, m._34, m._44
	//	};
	//}

	//constexpr float Determinant(const Matrix4& m)
	//{
	//	float det = 0.0f;
	//	det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	//	det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	//	det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	//	det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	//	return det;
	//}

	//constexpr Matrix4 Adjoint(const Matrix4& m)
	//{
	//	return
	//	{
	//		+(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
	//		-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
	//		+(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
	//		-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),
	//
	//		-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
	//		+(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
	//		-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
	//		+(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),
	//
	//		+(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
	//		-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
	//		+(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
	//		-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),
	//
	//		-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
	//		+(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
	//		-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
	//		+(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
	//	};
	//}

	//constexpr Matrix4 Inverse(const Matrix4& m)
	//{
	//	const float determinant = Determinant(m);
	//	const float invDet = 1.0f / determinant;
	//	return Adjoint(m) * invDet;
	//}

	//constexpr Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	//{
	//	const float w = (v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (1.0f * m._44);
	//	return {
	//		((v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (1.0f * m._41)) / w,
	//		((v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (1.0f * m._42)) / w,
	//		((v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (1.0f * m._43)) / w
	//	};
	//}

	//constexpr Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
	//{
	//	return {
	//		(v.x * m._11) + (v.y * m._21) + (v.z * m._31),
	//		(v.x * m._12) + (v.y * m._22) + (v.z * m._32),
	//		(v.x * m._13) + (v.y * m._23) + (v.z * m._33)
	//	};
	//}

	//constexpr Vector3 GetRight(const Matrix4& m)
	//{
	//	return { m._11, m._12, m._13 };
	//}

	//constexpr Vector3 GetUp(const Matrix4& m)
	//{
	//	return { m._21, m._22, m._23 };
	//}

	//constexpr Vector3 GetLook(const Matrix4& m)
	//{
	//	return { m._31, m._32, m._33 };
	//}

	//constexpr Vector3 GetTranslation(const Matrix4& m)
	//{
	//	return { m._41, m._42, m._43 };
	//}






	//Inline
	//Constexpr



}