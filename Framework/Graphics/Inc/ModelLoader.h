#pragma once

#include "MeshTypes.h"

namespace KWSE::Graphics
{
	class ModelLoader
	{
	public:
		static void LoadObj(std::filesystem::path fileName, float scale, MeshPX& mesh);
	};
}