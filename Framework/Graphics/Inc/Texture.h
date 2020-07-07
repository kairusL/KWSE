#pragma once

namespace KWSE::Graphics
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		// Move Constructor
		// When use std vector needs a move constructor .
		// In the begining when delete the copy constructor
		// will also delete the move constructor
		// put a defaule move constructor here tells the compiler the program do wnat to use it.
		Texture( Texture&&) = default; 

		void Initialize(const std::filesystem::path& fileName);
		void Terminate();

		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;

	private:
		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
	};
}

