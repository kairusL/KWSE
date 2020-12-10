#pragma once

#include "Colors.h"

namespace KWSE::Graphics
{

	struct DirectionalLight
	{
		Math::Vector3 direction; // Vect3 -> 12bytes
		float padding;  // 4 bytes
		Color ambient;  // Vect4 -> 16bytes
		Color diffuse;  // Vect4 -> 16bytes
		Color specular;	// Vect4 -> 16bytes
	};

}