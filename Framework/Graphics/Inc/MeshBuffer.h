#pragma once
#include "MeshTypes.h"

namespace KWSE::Graphics
{
	class MeshBuffer
	{
	public:
		enum class Topology {Points, Lines,Triangles};

		MeshBuffer() = default;
		~MeshBuffer();

		MeshBuffer(const MeshBuffer&) = delete;
		MeshBuffer& operator=(const MeshBuffer&) = delete;


		template <class MeshT>
		void Initialize(const MeshT& mesh, bool dynamic = false) // dynamic -> allow the shader to updated new vertices.  
		{
			Initialize(
				mesh.vertices.data(),
				static_cast<uint32_t>(sizeof(MeshT::VertexType)), //verticesSize  //<--- Geting from MeshTypes.h
				static_cast<uint32_t>(mesh.vertices.size()),      //verticesCount //<--- Geting from MeshTypes.h 
				mesh.indices.data(),											  //<--- Geting from MeshTypes.h
				static_cast<uint32_t>(mesh.indices.size()),                      //<--- Geting from MeshTypes.h
				dynamic
	   
			);
			
		}

		void Initialize(const void* vertexData, uint32_t vertexSize, uint32_t verticesCount, bool dynamic );
		void Initialize(const void* vertexData, uint32_t vertexSize,uint32_t verticesCount,
						const uint32_t* indexData, uint32_t indexCount,bool dynamic);
		void Terminate();

		void SetTopology(Topology topology);
		
		//template <class VertexT>
		//void Update(const VertexT* vertices, uint32_t numVertices)
		//{
		//	ASSERT(sizeof(VertexT) == mVertexSize);
		//	Update(static_cast<const void*>(vertices), numVertices);
		//}
		void Update(const  void* vertices, uint32_t numVertices);


		void Render();

	private:
		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;

		D3D11_PRIMITIVE_TOPOLOGY mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // Return the default topology to draw triangele.

		uint32_t mVertexSize;
		uint32_t mVertexCount;
		uint32_t mIndexCount;
	};



}