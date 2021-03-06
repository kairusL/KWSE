#pragma once
#include "AnimationClip.h"
#include "Material.h"
#include "MeshBuffer.h"
#include "MeshTypes.h"
#include "Skeleton.h"
#include "Texture.h"

namespace KWSE::Graphics
{
	class Model
	{
	public:
		void Initialize(const std::filesystem::path& fileName);
		void Terminate();
	public:
		struct MeshData
		{
			SkinnedMesh mesh;
			uint32_t materialIndex = 0;
			MeshBuffer meshBuffer;
		};
		struct MaterialData
		{
			Material material;
			std::string diffuseMapName;
			std::string specularMapName;
			std::string normalMapName;
			std::unique_ptr<Texture> diffuseMap;
			std::unique_ptr<Texture> specularMap;
			std::unique_ptr<Texture> normalMap;
		};
		std::vector<std::unique_ptr<MeshData>> meshData;
		std::vector<MaterialData> materialData;
		std::unique_ptr<Skeleton> skeleton; // not all model has skeleton, so use unique.
		std::vector<std::unique_ptr<AnimationClip>> animSet;
	};

}