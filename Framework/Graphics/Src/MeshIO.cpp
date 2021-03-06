#include "Precompiled.h"
#include "MeshIO.h"

void KWSE::Graphics::MeshIO::Write(FILE * file, const SkinnedMesh & mesh)
{
	const uint32_t verticesCount = static_cast<uint32_t>(mesh.vertices.size());
	const uint32_t indicesCount = static_cast<uint32_t>(mesh.indices.size());
	fprintf_s(file, "VertexCount: %d\n", verticesCount);
	fprintf_s(file, "IndicesCount: %d\n", indicesCount);
	for (auto& vertices : mesh.vertices)
	{
		fprintf_s(file, "\nposition : %f %f %f\n",
			vertices.position.x,
			vertices.position.y,
			vertices.position.z);
		fprintf_s(file,"normal : %f %f %f\n",
			vertices.normal.x,
			vertices.normal.y,
			vertices.normal.z);
		fprintf_s(file, "tangent : %f %f %f\n",
			vertices.tangent.x,
			vertices.tangent.y,
			vertices.tangent.z);
		fprintf_s(file, "uv : %f %f\n",
			vertices.uv.x,
			vertices.uv.y);
		fprintf_s(file, "boneIndices : %d %d %d %d\n",
			vertices.boneIndices[0],
			vertices.boneIndices[1],
			vertices.boneIndices[2],
			vertices.boneIndices[3]);
		fprintf_s(file, "boneWeights : %f %f %f %f\n",
			vertices.boneWeights[0],
			vertices.boneWeights[1],
			vertices.boneWeights[2],
			vertices.boneWeights[3]);
	}
	for (size_t i = 0; i < indicesCount; i +=3)
	{
		fprintf_s(file, "%d %d %d\n",
			mesh.indices[i],
			mesh.indices[i+1],
			mesh.indices[i+2]);
	}
	// fprintf_s(file, &mesh.vertices[0], verticesCount * sizeof(mesh.vertices));

}

void KWSE::Graphics::MeshIO::Read(FILE * file, SkinnedMesh & mesh)
{
	char buffer[255];
	uint32_t vertices = 0;
	uint32_t indices = 0;
	fscanf_s(file,"%s",buffer,(int)std::size(buffer));
	fscanf_s(file,"%d",&vertices);
	fscanf_s(file, "%s", buffer, (int)std::size(buffer));
	fscanf_s(file,"%d",&indices);
	mesh.vertices.reserve(vertices);
	mesh.indices.reserve(indices);
	//const uint32_t indicesCount = static_cast<uint32_t>(mesh.indices.size());
	for (int i= 0; i< vertices;++i)
	{
		auto& boneVertex = mesh.vertices.emplace_back();
		fscanf_s(file, "\nposition : %f %f %f\n",
			&boneVertex.position.x,
			&boneVertex.position.y,
			&boneVertex.position.z);
		fscanf_s(file, "normal : %f %f %f\n",
			&boneVertex.normal.x,
			&boneVertex.normal.y,
			&boneVertex.normal.z);
		fscanf_s(file, "tangent : %f %f %f\n",
			&boneVertex.tangent.x,
			&boneVertex.tangent.y,
			&boneVertex.tangent.z);
		fscanf_s(file, "uv : %f %f\n",
			&boneVertex.uv.x,
			&boneVertex.uv.y);
		fscanf_s(file, "boneIndices : %d %d %d %d\n",
			&boneVertex.boneIndices[0],
			&boneVertex.boneIndices[1],
			&boneVertex.boneIndices[2],
			&boneVertex.boneIndices[3]);
		fscanf_s(file, "boneWeights : %f %f %f %f\n",
			&boneVertex.boneWeights[0],
			&boneVertex.boneWeights[1],
			&boneVertex.boneWeights[2],
			&boneVertex.boneWeights[3]);
	}
	for (size_t i = 0; i < indices; i += 3)
	{
		int i1, i2, i3;
		fscanf_s(file, "%d %d %d\n", &i1, &i2, &i3);
		mesh.indices.push_back(i1);
		mesh.indices.push_back(i2);
		mesh.indices.push_back(i3);
	}
}

void KWSE::Graphics::MeshIO::WriteBinary(FILE * file, const SkinnedMesh & mesh)
{
	const uint32_t verticesCount = static_cast<uint32_t>(mesh.vertices.size());
	const uint32_t indicesCount = static_cast<uint32_t>(mesh.indices.size());

	fwrite(&verticesCount, sizeof(uint32_t), 1, file);
	fwrite(&indicesCount, sizeof(uint32_t), 1, file);

	fwrite(&mesh.vertices[0], sizeof(BoneVertex), verticesCount, file);
	fwrite(&mesh.indices[0], sizeof(uint32_t), indicesCount, file);
}

void KWSE::Graphics::MeshIO::ReadBinary(FILE * file, SkinnedMesh & mesh)
{
	uint32_t verticesCount;
	uint32_t indicesCount;
	fread(&verticesCount, sizeof(uint32_t), 1, file);
	fread(&indicesCount, sizeof(uint32_t), 1, file);

	mesh.vertices.resize(verticesCount);
	mesh.indices.resize(indicesCount);

	fread(&mesh.vertices[0], sizeof(BoneVertex), verticesCount, file);
	fread(&mesh.indices[0], sizeof(uint32_t), indicesCount, file);

	for (auto& data : mesh.vertices)
	{
		if (data.uv.x < 0.0) data.uv.x = data.uv.x + 1;
		if (data.uv.y < 0.0) data.uv.y = data.uv.y + 1;
	}
}
