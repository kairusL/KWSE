#pragma once
#include "MeshTypes.h"

namespace KWSE::Graphics::MeshIO
{
	void Write(FILE* file, const SkinnedMesh& mesh);
	void Read(FILE* file, SkinnedMesh& mesh);
}
