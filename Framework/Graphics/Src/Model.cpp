#include "Precompiled.h"
#include "Model.h"
#include "ModelLoader.h"

using namespace KWSE;
using namespace KWSE::Graphics;

void KWSE::Graphics::Model::Initialize(const std::filesystem::path & fileName)
{
	ModelLoader::LoadModel(fileName,*this);

	//Initialize meshBuffers
	for (const auto& mesh : meshData)
	{
		mesh->meshBuffer.Initialize(mesh->mesh);
	}
}

void KWSE::Graphics::Model::Terminate()
{
	for (const auto& mesh : meshData)
	{
		mesh->meshBuffer.Terminate();
	}
}
