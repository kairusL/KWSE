#pragma once
#include"Camera.h"
#include"ConstantBuffer.h"
#include "DepthStencilState.h"
#include "MeshBuffer.h"
#include "Texture.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RasterizerState.h"
#include"Sampler.h"

namespace KWSE::Graphics
{

	class Skybox
	{
	public:
		// Const Ref
		void Initialize(const std::filesystem::path &filePath) ;
		void Terminate();
		void Render(Camera camera);
	private:
		Texture mSkyboxTexture;
		MeshBuffer mSkyboxMeshBuffer;
		DepthStencilState mSkyboxDepthStencilState;
		PixelShader			mSkyboxPixelShader;
		VertexShader		mSkyboxVertexShader;
		RasterizerState		mSkyboxRasterizerState;

		struct TransformData
		{
			KWSE::Math::Matrix4 wvp;
		};

		using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;


		TransformBuffer mTransformBuffer;
		Sampler mSampler;
	};

}
