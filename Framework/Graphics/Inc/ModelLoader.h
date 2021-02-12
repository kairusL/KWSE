#pragma once

#include "MeshTypes.h"

namespace KWSE::Graphics
{
	class ModelLoader
	{
	public:
		static void LoadObjPX(std::filesystem::path fileName, float scale, MeshPX& mesh); // position and texture coordinate
		static void LoadObj(std::filesystem::path fileName, float scale, Mesh& mesh); // position and texture coordinate
		static void LoadModel(std::filesystem::path fileName, Model& model); // position and texture coordinate
	};
}