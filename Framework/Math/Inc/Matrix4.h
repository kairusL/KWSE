#pragma once

namespace KWSE::Math
{
	struct Matrix4
	{
		union
		{
			struct // 
			{
				float	_11, _12, _13,_14;
				float	_21, _22, _23,_24;
				float	_31, _32, _33,_34;
				float	_41, _42, _43,_44;
			};
			std::array<float, 16> v;
		};



		//Identity
		const static Matrix4 Identity;

		static Matrix4 RotationAxis(const Vector3& axis, float radian);

		//Assignment operator
		constexpr Matrix4& operator=(const Matrix4& other)
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
			v[8] = other.v[9];
			v[8] = other.v[10];
			v[8] = other.v[11];
			v[8] = other.v[12];
			v[8] = other.v[13];
			v[8] = other.v[14];
			v[8] = other.v[15];
			return *this;
		}

		constexpr Matrix4 operator+(const   Matrix4& other) const
		{
			return
			{
				(_11 + other._11) , (_12 + other._12) , (_13 + other._13),(_14 + other._14),
				(_21 + other._21) , (_22 + other._22) , (_23 + other._23),(_24 + other._24),
				(_31 + other._31) , (_32 + other._32) , (_33 + other._33),(_34 + other._34),
				(_41 + other._41) , (_42 + other._42) , (_43 + other._43),(_44 + other._44)
			};
		}
		constexpr Matrix4& operator+=(const Matrix4& other)
		{
				(_11 += other._11); (_12 += other._12); (_13 += other._13); (_14 += other._14);
				(_21 += other._21); (_22 += other._22); (_23 += other._23); (_24 += other._24);
				(_31 += other._31); (_32 += other._32); (_33 += other._33); (_34 += other._34);
				(_41 += other._41); (_42 += other._42); (_43 += other._43); (_44 += other._44);
			return *this;
		}
		constexpr Matrix4 operator-(const   Matrix4& other) const
		{
			return
			{
				(_11 - other._11) , (_12 - other._12) , (_13 - other._13),(_14 - other._14),
				(_21 - other._21) , (_22 - other._22) , (_23 - other._23),(_24 - other._24),
				(_31 - other._31) , (_32 - other._32) , (_33 - other._33),(_34 - other._34),
				(_41 - other._41) , (_42 - other._42) , (_43 - other._43),(_44 - other._44)
			};
		}
		constexpr Matrix4& operator-=(const Matrix4& other)
		{
			(_11 -= other._11); (_12 -= other._12); (_13 -= other._13); (_14 -= other._14);
			(_21 -= other._21); (_22 -= other._22); (_23 -= other._23); (_24 -= other._24);
			(_31 -= other._31); (_32 -= other._32); (_33 -= other._33); (_34 -= other._34);
			(_41 -= other._41); (_42 -= other._42); (_43 -= other._43); (_44 -= other._44);
			return *this;
		}

		constexpr Matrix4 operator*(const Matrix4& other)const
		{
			return
			{
				(_11 * other._11) + (_12 * other._21) + (_13 * other._31) + (_14 * other._31),
				(_11 * other._12) + (_12 * other._22) + (_13 * other._32) + (_14 * other._32),
				(_11 * other._13) + (_12 * other._23) + (_13 * other._33) + (_14 * other._33),
				(_11 * other._14) + (_12 * other._24) + (_13 * other._34) + (_14 * other._34),

				(_21 * other._11) + (_22 * other._21) + (_23 * other._31) + (_24 * other._31),
				(_21 * other._12) + (_22 * other._22) + (_23 * other._32) + (_24 * other._32),
				(_21 * other._13) + (_22 * other._23) + (_23 * other._33) + (_24 * other._33),
				(_21 * other._14) + (_22 * other._24) + (_23 * other._34) + (_24 * other._34),

				(_31 * other._11) + (_32 * other._21) + (_33 * other._31) + (_34 * other._31),
				(_31 * other._12) + (_32 * other._22) + (_33 * other._32) + (_34 * other._32),
				(_31 * other._13) + (_32 * other._23) + (_33 * other._33) + (_34 * other._33),
				(_31 * other._14) + (_32 * other._24) + (_33 * other._34) + (_34 * other._34),

				(_41 * other._11) + (_42 * other._21) + (_43 * other._31) + (_44 * other._31),
				(_41 * other._12) + (_42 * other._22) + (_43 * other._32) + (_44 * other._32),
				(_41 * other._13) + (_42 * other._23) + (_43 * other._33) + (_44 * other._33),
				(_41 * other._14) + (_42 * other._24) + (_43 * other._34) + (_44 * other._34)
			};
		}

		constexpr Matrix4 operator*(const float scalar)const
		{
			return
			{
				(_11 * scalar) , (_12 * scalar) , (_13 * scalar) , (_14 * scalar) ,
				(_21 * scalar) , (_22 * scalar) , (_23 * scalar) , (_24 * scalar) ,
				(_31 * scalar) , (_32 * scalar) , (_33 * scalar) , (_34 * scalar) ,
				(_41 * scalar) , (_42 * scalar) , (_43 * scalar) , (_44 * scalar) 
			};													 
		}
		constexpr Matrix4 operator*=(const float scalar)
		{
			(_11 *= scalar); (_12 *= scalar); (_13 *= scalar); (_14 *= scalar);
			(_21 *= scalar); (_22 *= scalar); (_23 *= scalar); (_24 *= scalar);
			(_31 *= scalar); (_32 *= scalar); (_33 *= scalar); (_34 *= scalar);
			(_41 *= scalar); (_42 *= scalar); (_43 *= scalar); (_44 *= scalar);

			return *this;

		}
		constexpr Matrix4 operator/(const float scalar)const
		{
			return
			{
				(_11 / scalar) , (_12 / scalar) , (_13 / scalar) , (_14 / scalar) ,
				(_21 / scalar) , (_22 / scalar) , (_23 / scalar) , (_24 / scalar) ,
				(_31 / scalar) , (_32 / scalar) , (_33 / scalar) , (_34 / scalar) ,
				(_41 / scalar) , (_42 / scalar) , (_43 / scalar) , (_44 / scalar)
			};
		}
		constexpr Matrix4 operator/=(const float scalar)
		{
			(_11 /= scalar); (_12 /= scalar); (_13 /= scalar); (_14 /= scalar);
			(_21 /= scalar); (_22 /= scalar); (_23 /= scalar); (_24 /= scalar);
			(_31 /= scalar); (_32 /= scalar); (_33 /= scalar); (_34 /= scalar);
			(_41 /= scalar); (_42 /= scalar); (_43 /= scalar); (_44 /= scalar);
			return *this;
		}

		//Rotation
		static Matrix4 RotationX(float radian)
		{
			const float c = cos(radian);
			const float s = sin(radian);
			return
			{
				1.0f ,0.0f,0.0f,0.0f,
				0.0f ,c   ,-s  ,0.0f,
				0.0f ,s   ,c   ,0.0f,
				0.0f ,0.0f,0.0f,1.0f
			};
		}
		static Matrix4 RotationY(float radian)
		{
			const float c = cos(radian);
			const float s = sin(radian);
			return
			{
				c   ,0.0f,-s  ,0.0f,
				0.0f,1.0f,0.0f,0.0f,
				s   ,0.0f,c   ,0.0f,
				0.0f,0.0f,0.0f,1.0f
			};
		}
		static Matrix4 RotationZ(float radian)
		{
			const float c = cos(radian);
			const float s = sin(radian);
			return
			{
				c  ,-s   ,0.0f,0.0f,
				s  ,c    ,0.0f,0.0f,
				0.0f,0.0f,1.0f,0.0f,
				0.0f,0.0f,0.0f,1.0f
			};
		}

		//Translation
		static Matrix4 Translation(const Vector3& d)
		{
			return
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				d.x , d.y , d.z , 1.0f
			};
		}
		static Matrix4 Translation(const float x, const float y,const float z)
		{
			return
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				x   , y   , z   , 1.0f
			};
		}

		static Matrix4 Scaling(const Vector3& scale)
		{
			return Matrix4
			{
				(scale.x)  , (0.0f)   , (0.0f)   , (0.0f)   ,
				(0.0f)     , (scale.y), (0.0f)   , (0.0f)   ,
				(0.0f)     , (0.0f)   , (scale.z), (0.0f)   ,
				(0.0f)     , (0.0f)   , (0.0f)   , (1.0f)
			};
		}

		constexpr Matrix3 Transpose(const Matrix3 m);
		constexpr Matrix3 Invserse(const Matrix3& m);
		constexpr float Determinant(const Matrix3& m);
		constexpr Matrix3 Adjoint(const Matrix3& m);

	};

}