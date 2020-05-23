#pragma once

namespace KWSE::Graphics
{
	class ConstantBuffer
	{
	public:
		~ConstantBuffer();
		void Initialize(uint32_t constantBufferSize);
		void Terminate();

		void Set(const void* data);
		void Bind();

	private:
		ID3D11Buffer* mConstantBuffer = nullptr;

	};

}