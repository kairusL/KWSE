#include "Precompiled.h"
#include "Model.h"
#include "ModelLoader.h"

using namespace KWSE;
using namespace KWSE::Graphics;

void KWSE::Graphics::Model::Initialize(const std::filesystem::path & fileName)
{

	//This is the opposite of SaveModel in ModelImporter
	ModelLoader::LoadModel(fileName,*this);

	//Initialize meshBuffers
	for (const auto& mesh : meshData)
	{
		mesh->meshBuffer.Initialize(mesh->mesh);
	}


	// Load Texture
	ModelLoader::LoadMaterial(fileName, *this);

	const std::string parentPath = fileName.parent_path().generic_string();

	// Initialize Textures
	for (auto& data : materialData)
	{
		data.diffuseMap = std::make_unique<Texture>();
		if (!data.diffuseMapName.empty())
			data.diffuseMap->Initialize(parentPath + "/" + data.diffuseMapName);

		data.specularMap = std::make_unique<Texture>();
		if (!data.specularMapName.empty())
			data.specularMap->Initialize(parentPath + "/" + data.specularMapName);

		data.normalMap = std::make_unique<Texture>();
		if (!data.normalMapName.empty())
			data.normalMap->Initialize(parentPath + "/" + data.normalMapName);
	}

	ModelLoader::LoadSkeleton(fileName, *this);
	//Relink all the bones to form the skeleton again...
	for (auto& bone : skeleton->bones)
	{
		if (bone.get() != skeleton->root)
			bone->parent = skeleton->bones[bone->parentIndex].get();

		for (auto& childIndex : bone->childrenIndices)
			bone->children.push_back(skeleton->bones[childIndex].get());
	}
}

void KWSE::Graphics::Model::Terminate()
{
	for (const auto& mesh : meshData)
	{
		mesh->meshBuffer.Terminate();
	}
	for (auto& data : materialData)
	{
		data.diffuseMap->Terminate();
		data.specularMap->Terminate();
		data.normalMap->Terminate();
	}
}
