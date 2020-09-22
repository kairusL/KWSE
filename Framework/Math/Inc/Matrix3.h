#pragma once

namespace KWSE::Math
{
	struct Matrix3
	{
		union // Can access the data either from _11 or v[0]  // _11 and v[0] are the same . 
		{
			struct // 
			{
				float	_11, _12, _13;
				float	_21, _22, _23;
				float	_31, _32, _33;
			};

			std::array<float, 9> v;
		};



		//Identity
		const static Matrix3 Identity;

		//Assignment operator
		constexpr Matrix3& operator=(const Matrix3& other)
		{
			// Check if object is same
			if (this == &other)
				return *this;
			v[0] = other.v[0];
			v[1] = other.v[1];
			v[2] = other.v[2];
			v[3] = other.v[3];
			v[4] = other.v[4];
			v[5] = other.v[5];
			v[6] = other.v[6];
			v[7] = other.v[7];
			v[8] = other.v[8];
			return *this;
		}

		constexpr Matrix3 operator+(const   Matrix3& other) const
		{
			return
			{
				(_11 + other._11) , (_12 + other._12) , (_13 + other._13),
				(_21 + other._21) , (_22 + other._22) , (_23 + other._23),
				(_31 + other._31) , (_32 + other._32) , (_33 + other._33)
			};
		}
		constexpr Matrix3& operator+=(const Matrix3& other)
		{
			(_11 += other._11) ; (_12 += other._12) ; (_13 += other._13);
			(_21 += other._21) ; (_22 += other._22) ; (_23 += other._23);
			(_31 += other._31) ; (_32 += other._32) ; (_33 += other._33);
			return *this;
		}
		constexpr Matrix3 operator-(const   Matrix3& other) const
		{
			return
			{
				(_11 - other._11) , (_12 - other._12) , (_13 - other._13),
				(_21 - other._21) , (_22 - other._22) , (_23 - other._23),
				(_31 - other._31) , (_32 - other._32) , (_33 - other._33)
			};
		}
		constexpr Matrix3& operator-=(const Matrix3& other)
		{
			(_11 -= other._11); (_12 -= other._12); (_13 -= other._13);
			(_21 -= other._21); (_22 -= other._22); (_23 -= other._23);
			(_31 -= other._31); (_32 -= other._32); (_33 -= other._33);
			return *this;
		}

		constexpr Matrix3 operator*(const Matrix3& other)const
		{
			return
			{
				(_11 * other._11) + (_12 * other._21) + (_13 * other._31),
				(_11 * other._12) + (_12 * other._22) + (_13 * other._32),
				(_11 * other._13) + (_12 * other._23) + (_13 * other._33),

				(_21 * other._11) + (_22 * other._21) + (_23 * other._31),
				(_21 * other._12) + (_22 * other._22) + (_23 * other._32),
				(_21 * other._13) + (_22 * other._23) + (_23 * other._33),

				(_31 * other._11) + (_32 * other._21) + (_33 * other._31),
				(_31 * other._12) + (_32 * other._22) + (_33 * other._32),
				(_31 * other._13) + (_32 * other._23) + (_33 * other._33)
			};
		}

		constexpr Matrix3 operator*(const float scalar)const
		{
			return
			{
				(_11 * scalar) , (_12 * scalar) , (_13 * scalar),
				(_21 * scalar) , (_22 * scalar) , (_23 * scalar),
				(_31 * scalar) , (_32 * scalar) , (_33 * scalar)
			};
		}
		constexpr Matrix3 operator*=(const float scalar)
		{
			(_11 *= scalar) ; (_12 *= scalar) ; (_13 *= scalar);
			(_21 *= scalar) ; (_22 *= scalar) ; (_23 *= scalar);
			(_31 *= scalar) ; (_32 *= scalar) ; (_33 *= scalar);
			return *this;
			
		}
		constexpr Matrix3 operator/(const float scalar)const
		{
			return
			{
				(_11 / scalar) , (_12 / scalar) , (_13 / scalar),
				(_21 / scalar) , (_22 / scalar) , (_23 / scalar),
				(_31 / scalar) , (_32 / scalar) , (_33 / scalar)
			};
		}
		constexpr Matrix3 operator/=(const float scalar)
		{
			(_11 /= scalar); (_12 /= scalar); (_13 /= scalar);
			(_21 /= scalar); (_22 /= scalar); (_23 /= scalar);
			(_31 /= scalar); (_32 /= scalar); (_33 /= scalar);
			return *this;
		}

		//Rotation
		static Matrix3 RotationX(float radian)
		{
			const float c = cos(radian);
			const float s = sin(radian);
			return
			{
				1.0f  ,0.0f,0.0f,
				0.0f  ,c   ,-s  ,
				0.0f  ,s   ,c
			};
		}
		static Matrix3 RotationY(float radian)
		{
			const float c = cos(radian);
			const float s = sin(radian);
			return
			{
				c   ,0.0f,s   ,
				0.0f,1.0f,0.0f,
				-s  ,0.0f,c
			};
		}
		static Matrix3 RotationZ(float radian)
		{
			const float c = cos(radian);
			const float s = sin(radian);
			return
			{
				c  ,-s  ,0.0f,
				s  ,c   ,0.0f,
				0.0f,0.0f,1.0f
			};
		}

		//Translation
		static Matrix3 Translation(const Vector2& d)
		{
			return
			{
				1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				d.x ,d.y ,1.0f
			};
		}
		static Matrix3 Translation(const float x, const float y)
		{
			return
			{
				1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				x   ,y   ,1.0f
			};
		}

		static Matrix3 Scaling(const Vector3& scale)
		{
			return Matrix3
			{
				(scale.x)  , (0.0f)   , (0.0f)   ,
				(0.0f)     , (scale.y), (0.0f)   ,
				(0.0f)     , (0.0f)   , (scale.z)
			};
		}
		
		constexpr Matrix3 Transpose(const Matrix3 m);
		constexpr Matrix3 Invserse(const Matrix3& m); 
		constexpr float Determinant(const Matrix3& m);
		constexpr Matrix3 Adjoint(const Matrix3& m);

	};

}