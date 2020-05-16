#include "Precompiled.h"
#include "MeshBuffer.h"
#include "GraphicsSystem.h"

using namespace KWSE::Graphics;

KWSE::Graphics::MeshBuffer::~MeshBuffer()
{

	ASSERT(mVertexBuffer == nullptr, "MeshBuffer -- Vertex buffer not released!");
	ASSERT(mIndexBuffer == nullptr, "MeshBuffer -- Index buffer not released!");

}

void KWSE::Graphics::MeshBuffer::Initialize(const void* vertexData, uint32_t vertexSize,uint32_t verticesCount, const uint32_t* indices, uint32_t indexCount)
{
	mVertexSize = vertexSize;
	mVertexCount = verticesCount;
	mIndexCount = indexCount;

	// Create vertex buffer
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = verticesCount *  vertexSize;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = vertexData;


	auto device = GraphicsSystem::Get()->GetDevice();

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer.");

	if (indices != nullptr && indexCount > 0)
	{
		// Create index buffer
		bufferDesc.ByteWidth = indexCount* sizeof(uint32_t);
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		initData.pSysMem = indices;

		hr = device->CreateBuffer(&bufferDesc, &initData, &mIndexBuffer);
		ASSERT(SUCCEEDED(hr), "Failed to create index buffer.");
	}
}

void KWSE::Graphics::MeshBuffer::Terminate()
{
	SafeRelease(mVertexBuffer);
	SafeRelease(mIndexBuffer);
}

void KWSE::Graphics::MeshBuffer::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();

	
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = (UINT)mVertexSize;
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//context->Draw((UINT)mVertexCount, 0);
	context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(mIndexCount, 0, 0);
}


