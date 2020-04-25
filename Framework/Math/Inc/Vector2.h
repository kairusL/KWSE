#pragma once


namespace KWSE::Math

{
	struct Vector2
	{
		union
		{
			struct { float x, y; };
			std::array<float, 2> v;
		};

		constexpr Vector2() noexcept : Vector2{ 0.0f } {}
		explicit constexpr Vector2(float f) : Vector2{ f,f } {}
		constexpr Vector2(float x, float y) noexcept : x{ x }, y{ y }{}

		const static Vector2 Zero;
		const static Vector2 One;
		const static Vector2 XAxis;
		const static Vector2 YAxis;

		// Assignment Operator = 
		constexpr Vector2 operator=(const Vector2& other)
		{
			// Check if object is same
			if (this == &other)
				return *this;
			x = other.x;
			y = other.y;
			return *this;
		}
		// Equal Operator 
		constexpr const bool operator==(const Vector2& other) const
		{
			// Check if object is same
			if (x == other.x&&
				y == other.y)
			{
				return true;
			}
			return false;
		}


		// Negative Operator  
		constexpr Vector2 operator-() const { return Vector2(-x, -y); };
		// Operator overloads for +,-,*,/
		constexpr Vector2 operator+ (const Vector2& otherVec) const { return Vector2(x + otherVec.x, y + otherVec.y); }
		constexpr Vector2 operator-(const Vector2& otherVec) const { return Vector2(x - otherVec.x, y - otherVec.y); };
		constexpr Vector2 operator*(float scalar)const { return Vector2(x * scalar, y * scalar); };
		constexpr Vector2 operator/(float scalar)const { return Vector2(x / scalar, y / scalar); };
		// Operator overloads for += , -= , *= ,/=  
		constexpr Vector2& operator+=(const Vector2& vector) { x += vector.x; y += vector.y; return *this; };
		constexpr Vector2& operator-=(const Vector2& vector) { x -= vector.x; y -= vector.y; return *this; };
		constexpr Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; };
		constexpr Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; };


	};
}