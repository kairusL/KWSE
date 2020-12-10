#include"Precompiled.h"
#include"ConstantBuffer.h"
#include "GraphicsSystem.h"

KWSE::Graphics::ConstantBuffer::~ConstantBuffer()
{
	ASSERT(mConstantBuffer == nullptr, "ConstantBuffer -- Constant buffer not released!");
}

void KWSE::Graphics::ConstantBuffer::Initialize(uint32_t constantBufferSize)
{
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = constantBufferSize;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


	auto device = GraphicsSystem::Get()->GetDevice();
	HRESULT hr = device->CreateBuffer(&bufferDesc, nullptr, &mConstantBuffer);
	ASSERT(SUCCEEDED(hr), "ConstantBuffer - Failed to create constant buffer.");
}

void KWSE::Graphics::ConstantBuffer::Terminate()
{
	SafeRelease(mConstantBuffer);
}

void KWSE::Graphics::ConstantBuffer::Update(const void * data)const
{
	GraphicsSystem::Get()->GetContext()->UpdateSubresource(mConstantBuffer, 0, nullptr, data, 0, 0);
}

void KWSE::Graphics::ConstantBuffer::BindVS(uint32_t slot) const
{
	//UINT slot = 0; // This needs to match the shader register index.
	GraphicsSystem::Get()->GetContext()->VSSetConstantBuffers(slot, 1, &mConstantBuffer);
}

void KWSE::Graphics::ConstantBuffer::BindPS(uint32_t slot) const
{
	GraphicsSystem::Get()->GetContext()->PSSetConstantBuffers(slot, 1, &mConstantBuffer);
}
