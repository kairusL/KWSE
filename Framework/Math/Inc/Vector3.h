#pragma once


namespace KWSE::Math

{
	struct Vector3
	{
		union
		{
			struct { float x, y, z; };
			std::array<float, 3> v;
		};

		constexpr Vector3() noexcept : Vector3 {0.0f} {}
		explicit constexpr Vector3(float f) : Vector3{ f,f,f } {}
		constexpr Vector3(float x, float y, float z) noexcept : x{ x }, y{y},z{z}{}




		// Assignment Operator = 
		Vector3 operator=(const Vector3& other)
		{
			// Check if object is same
			if (this == &other)
				return *this;
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		// Equal Operator 
		const bool operator==(const Vector3& other) const 
		{
			// Check if object is same
			if (x == other.x&&
				y == other.y&&
				z == other.z)
			{
				return true;
			}
			return false;
		}


		// Negative Operator  
		Vector3 operator-() const { return Vector3(-x, -y, -z); };
		// Operator overloads for +,-,*,/
		Vector3 operator+ (const Vector3& otherVec) const  {return Vector3(x + otherVec.x, y + otherVec.y, z + otherVec.z);}
		Vector3 operator-(const Vector3& otherVec) const { return Vector3(x - otherVec.x, y - otherVec.y, z - otherVec.z); };
		Vector3 operator*(float scalar)const { return Vector3( x * scalar, y * scalar, z * scalar ); };
		Vector3 operator/(float scalar)const { return Vector3(x / scalar, y / scalar, z / scalar); };
		// Operator overloads for += , -= , *= ,/=  
		Vector3& operator+=(const Vector3& vector) { x += vector.x; y += vector.y; z += vector.z; return *this; };
		Vector3& operator-=(const Vector3& vector) { x -= vector.x; y -= vector.y; z -= vector.z; return *this; };
		Vector3& operator*=(float scalar) {x *= scalar; y *= scalar; z *= scalar; return *this; };
		Vector3& operator/=(float scalar) {x /= scalar; y /= scalar; z /= scalar; return *this; };


	};
}