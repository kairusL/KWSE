#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/EngineMath.h>

#include <assimp/Importer.hpp>		// C++ importer interface
#include <assimp/scene.h>			// Output data structure
#include <assimp/postprocess.h>		// Post processing flags
#include <cstdio>

struct Arguments
{
	const char* inputFileName = nullptr;
	const char* outputFileName = nullptr;
	float scale = 1.0f;
	bool animOnly = false;
	bool foundMeshData = false;
	bool foundMaterialData = false;
	bool foundSkeletonData = false;
	bool foundAnimationData = false;
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


// Game.exe -o model.txt

// argc=3
// argv[0] = "Game.exe"
// argv[1] = "-o"
// argv[2] = "model.txt"
int main(int argc, char* argv[])
{
	auto argsOpt = ParseArgs(argc, argv);
	if (!argsOpt.has_value())
	{
		PrintUsage();
		return -1;
	}

	auto& args = argsOpt.value();

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

	return 0;
}
