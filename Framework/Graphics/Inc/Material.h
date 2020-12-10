#pragma once

#include "Colors.h"

namespace KWSE::Graphics
{

	struct Material
	{
		Color ambient;  // Vect4 -> 16bytes
		Color diffuse; 	// Vect4 -> 16bytes
		Color specular;	// Vect4 -> 16bytes
		float power;     // 4bytes
		float padding[3]; // 12 bytes 

	};

}