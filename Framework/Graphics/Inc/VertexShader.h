#pragma once


namespace KWSE::Graphics
{
	class VertexShader
	{
	public:
		VertexShader() = default;
		~VertexShader();

		void Initialize(const std::filesystem::path& filePath);
		void Terminate();

		void Bind() const;

	private:
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
	};
}
