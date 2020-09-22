#pragma once

//Vector
#include "Vector2.h"

namespace KWSE::Math
{
	struct LineSegment
	{
		Vector2 from;
		Vector2 to;

		LineSegment() : from(0.0f, 0.0f), to(0.0f, 0.0f) {} 
		LineSegment(float x0, float y0, float x1, float y1) : from(x0, y0), to(x1, y1) {} // Pass by value , the origin data wont be change even the values been modified 
		LineSegment(const Vector2& v0, const Vector2& v1):from(v0),to(v1) {}// ref -> (better for performance) allow to use the ref values and wont make a copy. const ref -> make use no one else can modify the ref value. 
	};

	struct Rect
	{
		union                    //topleft corner 
		{										  
			struct { float left, top; };		  
			Vector2 min;						  
		};										  
		union                    //bottomright corner 
		{
			struct { float right, bottom; };
			Vector2 max;
		};

		constexpr Rect() : Rect{ 0.0f, 0.0f, 1.0f, 1.0f } {}
		constexpr Rect(float left, float top, float right, float bottom) : left{ left }, top{ top }, right{ right }, bottom{ bottom } {}
		constexpr Rect(const Vector2& v0, const Vector2& v1) :min(v0), max(v1) {}
	};

	struct Circle
	{
		Math::Vector2 center;
		float radius;

		Circle() : center(0.0f, 0.0f), radius(1.0f) {}
		Circle(float x, float y, float radius) : center(x, y), radius(radius) {}
		Circle(const Math::Vector2& center, float radius) : center(center), radius(radius) {}
	};



}