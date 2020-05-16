#pragma once


namespace KWSE::Graphics
{
	class PixelShader
	{
	public:
		PixelShader() = default;
		~PixelShader();

		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void Bind() const;

	private:
		ID3D11PixelShader* mPixelShader = nullptr;
	};
}
