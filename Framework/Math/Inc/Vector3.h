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




		// HomeWork:
		// Add operator overloads for +,-,*,/ etc 
	};
}