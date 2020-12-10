#pragma once


namespace KWSE::Graphics
{
	class VertexShader
	{
	public:
		VertexShader() = default;
		~VertexShader();

		VertexShader(const VertexShader&) = delete;
		VertexShader& operator=(const VertexShader&) = delete;

		void Initialize(const std::filesystem::path& filePath, uint32_t vertexFormat, const char* shaderName="VS");
		void Terminate();

		void Bind() const;

	private:
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
	};
}
