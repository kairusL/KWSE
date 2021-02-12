#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/EngineMath.h>

#include <assimp/Importer.hpp>		// C++ importer interface
#include <assimp/scene.h>			// Output data structure
#include <assimp/postprocess.h>		// Post processing flags
#include <cstdio>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Math;
struct Arguments
{
	const char* inputFileName = nullptr;
	const char* outputFileName = nullptr;
	float scale = 1.0f;
	bool animOnly = false;
};

std::optional<Arguments> ParseArgs(int argc, char* argv[])
{
	// We need at least 3 arguments.
	if (argc < 3)
		return std::nullopt;

	Arguments args;
	args.inputFileName = argv[argc - 2];
	args.outputFileName = argv[argc - 1];

	for (int i = 1; i + 2 < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 's':
				args.scale = static_cast<float>(atof(argv[i + 1]));
				break;
			}
		}
	}
	return args;
}

void PrintUsage()
{
	printf(
		"== ModelImporter Help ==\n"
		"\n"
		"Usage:\n"
		"    ModelImporter.exe [Options] <InputFile> <OutputFile>\n"
		"\n"
		"Options:\n"
		"    -s    Scale applied to the model."
		"\n"
	);
}

inline Vector2 ConvertToV2(const aiVector3D& v)
{
	return
	{
		static_cast<float>(v.x),
		static_cast<float>(v.y)
	};
}

inline Vector3 ConvertToV3(const aiVector3D& v)
{
	return
	{
		static_cast<float>(v.x),
		static_cast<float>(v.y),
		static_cast<float>(v.z)
	};
}


void SaveModel(const Arguments& args, const Model& model)
{
	if (model.meshData.empty())
	{
		return;
	}
	printf("Saving model: %s...\n", args.outputFileName);

	FILE* file = nullptr;
	auto err = fopen_s(&file, args.outputFileName, "w");
	if (err !=0 || file ==nullptr)
	{
		printf("Error: failed to open file %s for saving. \n", args.outputFileName);
		return;
	}
	const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
	fprintf_s(file, "MeshCount: %d\n", meshCount);
	for (uint32_t i = 0; i < meshCount; ++i)
	{
		fprintf_s(file, "MaterialIndex: %d\n", model.meshData[i]->materialIndex);
		MeshIO::Write(file, model.meshData[i]->mesh);
	}

	fclose(file);
}
// Game.exe -o model.txt
 
// argc=3
// argv[0] = "Game.exe"
// argv[1] = "-o"
// argv[2] = "model.txt"
int main(int argc, char* argv[])
{
	const auto argsOpt = ParseArgs(argc, argv);
	if (!argsOpt.has_value())
	{
		PrintUsage();
		return -1;
	}
	const auto& args = argsOpt.value();

	// Create an instance of the importer class to do the parsing for us.
	Assimp::Importer importer;

	// Try to import the model into a scene.
	const uint32_t flags = aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded;
	const aiScene* scene = importer.ReadFile(args.inputFileName, flags);
	if (scene == nullptr)
	{
		printf("Error: %s\n", importer.GetErrorString());
		return -1;
	}

	Graphics::Model model;

	//Look for mesh data
	if (scene->HasMeshes())
	{
		printf("Reading mesh data...\n");
		const uint32_t numMeshes = scene->mNumMeshes;
		model.meshData.reserve(numMeshes);

		for (size_t meshIndex = 0; meshIndex < numMeshes; ++meshIndex)
		{
			const auto aiMesh = scene->mMeshes[meshIndex];
			const uint32_t numVertices = aiMesh->mNumVertices;
			const uint32_t numFaces = aiMesh->mNumFaces;
			const uint32_t numIndices = numFaces*3;

			auto& meshData = model.meshData.emplace_back(std::make_unique<Graphics::Model::MeshData>());
		
			printf("Reading material index...\n");
			
			meshData->materialIndex = aiMesh->mMaterialIndex;

			printf("Reading vertives ...\n");

			auto& mesh = meshData->mesh;
			//std::vector<Graphics::BoneVertex> vertices;
			mesh.vertices.reserve(numVertices);

			// Get positions, normals, tangents
			const aiVector3D* positions = aiMesh->mVertices;
			const aiVector3D* normals = aiMesh->mNormals;
			const aiVector3D* tangents = aiMesh->mTangents;
			const aiVector3D* texCoords = aiMesh->HasTextureCoords(0) ? aiMesh->mTextureCoords[0] : nullptr;
			for (uint32_t i = 0; i < numVertices; ++i)
			{
				auto& vertex = mesh.vertices.emplace_back(BoneVertex{});
				vertex.position = ConvertToV3(positions[i]) * args.scale;
				vertex.normal = ConvertToV3(normals[i]);
				vertex.tangent = ConvertToV3(tangents[i]);
				//vertex.uv = texCoords ? Vector2{ texCoords[i].x, texCoords[i].y } : Vector2::Zero;
				vertex.uv = texCoords ? ConvertToV2( texCoords[i] ) : Vector2::Zero;
			}

			printf("Reading indices ...\n");

			mesh.indices.reserve(numIndices);

			const auto aiFaces = aiMesh->mFaces;
			for (uint32_t i = 0; i < numFaces; ++i)
			{
				auto& aiFace = aiFaces[i];
				mesh.indices.push_back(aiFace.mIndices[0]);
				mesh.indices.push_back(aiFace.mIndices[1]);
				mesh.indices.push_back(aiFace.mIndices[2]);
			}
		}
	}

	SaveModel(args, model);

	printf("All done!\n");

	return 0;
}
