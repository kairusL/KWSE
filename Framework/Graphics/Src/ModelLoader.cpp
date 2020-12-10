#include"Precompiled.h"
#include"ModelLoader.h"

using namespace KWSE;
using namespace KWSE::Graphics;

void KWSE::Graphics::ModelLoader::LoadObjPX(std::filesystem::path fileName, float scale, MeshPX & mesh)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	std::vector<Math::Vector3> positions;
	std::vector<Math::Vector2> uvs;
	std::vector<uint32_t> positionIndices, uvIndices;

	while (true)
	{
		char buffer[256];
		int result = fscanf_s(file, "%s", buffer, (int)std::size(buffer));

		// If we reached the end of the file,we are done
		if (result == EOF)
		{
			break;
		}
		if (strcmp(buffer,"v")==0) //vertex
		{
			Math::Vector3 position;
			fscanf_s(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			positions.push_back(position * scale);
		}
		else if (strcmp(buffer, "vt") == 0) // uv vertex texture coordinate 
		{
			Math::Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back({ uv.x, 1.0f - uv.y });
		}
		else if (strcmp(buffer, "f") == 0) //face
		{

			uint32_t v[3], t[3], n[3];
			fgets(buffer, (int)std::size(buffer), file);
			if (sscanf_s
			(buffer, "%d/%d/%d %d/%d/%d %d/%d/%d\n", // triplet - > 3 in 1 set
				&v[0],&t[0], &n[0],
				&v[1], &t[1],&n[1],
				&v[2], &t[2],&n[2],
				&v[3], &t[3],&n[3] 
			)==9)
			{
				positionIndices.push_back(v[0]);
				positionIndices.push_back(v[1]);
				positionIndices.push_back(v[2]);
				uvIndices.push_back(t[0]);
				uvIndices.push_back(t[1]);
				uvIndices.push_back(t[2]);

				//positionIndices.push_back(v[0]);
				//positionIndices.push_back(v[2]);
				//positionIndices.push_back(v[3]);
				//uvIndices.push_back(t[0]);
				//uvIndices.push_back(t[2]);
				//uvIndices.push_back(t[3]);
			}
			//if (sscanf_s
			//(buffer, "%d/%d %d/%d %d/%d\n",
			//	&v[0], &t[0],
			//	&v[1], &t[1],
			//	&v[2], &t[2]
			//) == 6)
			//{
			//	positionIndices.push_back(v[0]);
			//	positionIndices.push_back(v[1]);
			//	positionIndices.push_back(v[2]);
			//	uvIndices.push_back(t[0]);
			//	uvIndices.push_back(t[1]);
			//	uvIndices.push_back(t[2]);
			//}

		}
	}

	fclose(file);

	// Reconstruct vertices
	std::vector<VertexPX> vertices;
	vertices.reserve(positionIndices.size());
	for (size_t i = 0; i < positionIndices.size(); ++i)
	{
		VertexPX vertex;
		vertex.position = positions[positionIndices[i] - 1];
		vertex.uv = uvs[uvIndices[i] - 1];
		vertices.push_back(vertex);
	}

	// Generate indices
	std::vector<uint32_t> indices;
	indices.resize(vertices.size());
	std::iota(indices.begin(), indices.end(), 0);

	//Initialize mesh
	mesh.vertices = std::move(vertices);
	mesh.indices = std::move(indices);

}

void KWSE::Graphics::ModelLoader::LoadObj(std::filesystem::path fileName, float scale, Mesh & mesh)
{

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	ASSERT(file, "ModelLoader - Failed to open model %s.", fileName.u8string().c_str());

	std::vector<Math::Vector3> positions;
	std::vector<Math::Vector3> normals;
	std::vector<Math::Vector2> uvs;
	std::vector<uint32_t> positionIndices, uvIndices,normalIndices;

	while (true)
	{
		char buffer[256];
		int result = fscanf_s(file, "%s", buffer, (int)std::size(buffer));

		// If we reached the end of the file,we are done
		if (result == EOF)
		{
			break;
		}
		if (strcmp(buffer, "v") == 0) //vertex
		{
			Math::Vector3 position;
			fscanf_s(file, "%f %f %f\n", &position.x, &position.y, &position.z);
			positions.push_back(position * scale);
		}
		else if (strcmp(buffer, "vn") == 0) // uv vertex texture coordinate 
		{
			Math::Vector3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y,&normal.z);
			normals.push_back({ normal.x, normal.y ,normal.z });
		}
		else if (strcmp(buffer, "vt") == 0) // uv vertex texture coordinate 
		{
			Math::Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back({ uv.x, 1.0f - uv.y });
		}
		else if (strcmp(buffer, "f") == 0) //face
		{

			uint32_t v[3], t[3], n[3];
			fgets(buffer, (int)std::size(buffer), file);
			if (sscanf_s
			(buffer, "%d/%d/%d %d/%d/%d %d/%d/%d\n", // triplet - > 3 in 1 set
				&v[0], &t[0], &n[0],
				&v[1], &t[1], &n[1],
				&v[2], &t[2], &n[2],
				&v[3], &t[3], &n[3]
			) == 9)
			{
				positionIndices.push_back(v[0]);
				positionIndices.push_back(v[1]);
				positionIndices.push_back(v[2]);
				uvIndices.push_back(t[0]);
				uvIndices.push_back(t[1]);
				uvIndices.push_back(t[2]);
				normalIndices.push_back(n[0]);
				normalIndices.push_back(n[1]);
				normalIndices.push_back(n[2]);

			}

		}
	}

	fclose(file);

	// Reconstruct vertices
	std::vector<Vertex> vertices;
	vertices.reserve(positionIndices.size());
	for (size_t i = 0; i < positionIndices.size(); ++i)
	{
		Vertex vertex;
		vertex.position = positions[positionIndices[i] - 1];
		vertex.uv = uvs[uvIndices[i] - 1];
		vertex.normal = normals[normalIndices[i] - 1];
		vertices.push_back(vertex);
	}

	// Generate indices
	std::vector<uint32_t> indices;
	indices.resize(vertices.size());
	std::iota(indices.begin(), indices.end(), 0);

	//Initialize mesh
	mesh.vertices = std::move(vertices);
	mesh.indices = std::move(indices);
}
