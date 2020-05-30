#pragma once
#include "MeshTypes.h"

namespace KWSE::Graphics
{
	class MeshBuffer
	{
	public:
		MeshBuffer() = default;
		~MeshBuffer();

		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;


		template <class MeshT>
		void Initialize(const MeshT& mesh)
		{
			Initialize(
				mesh.vertices.data(),
				static_cast<uint32_t>(sizeof(MeshT::VertexType)), //verticesSize  //<--- Geting from MeshTypes.h
				static_cast<uint32_t>(mesh.vertices.size()),      //verticesCount //<--- Geting from MeshTypes.h 
				mesh.indices.data(),											  //<--- Geting from MeshTypes.h
				static_cast<uint32_t>(mesh.indices.size())						  //<--- Geting from MeshTypes.h
	   
			);
			
		}

		void Initialize(const void* vertexData, uint32_t vertexSize, uint32_t verticesCount);
		void Initialize(const void* vertexData, uint32_t vertexSize,uint32_t verticesCount,
						const uint32_t* indexData, uint32_t indexCount);
		void Terminate();

		void Render();

	private:
		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
		uint32_t mVertexSize;
		uint32_t mVertexCount;
		uint32_t mIndexCount;
	};

}