#include "Precompiled.h"
#include "Skybox.h"
#include "MeshBuilder.h"

using namespace KWSE;
using namespace KWSE::Graphics;

void KWSE::Graphics::Skybox::Initialize(const std::filesystem::path & filePath)
{
	mSkyboxTexture.Initialize(filePath);
	mSkyboxMeshBuffer.Initialize(MeshBuilder::CreateSkyboxPX());
	mSkyboxPixelShader.Initialize(L"../../Assets/Shaders/Skybox.fx");
	mSkyboxVertexShader.Initialize(L"../../Assets/Shaders/Skybox.fx", VertexPX::Format);
	mSkyboxDepthStencilState.Initialize(false,true);
	mSkyboxRasterizerState.Initialize(RasterizerState::CullMode::Front, RasterizerState::FillMode::Solid);
	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Clamp);
	mTransformBuffer.Initialize();

}

void KWSE::Graphics::Skybox::Terminate()
{
	mTransformBuffer.Terminate();
	mSampler.Terminate();
	mSkyboxRasterizerState.Terminate();
	mSkyboxDepthStencilState.Terminate();
	mSkyboxVertexShader.Terminate();
	mSkyboxPixelShader.Terminate();
	mSkyboxMeshBuffer.Terminate();
	mSkyboxTexture.Terminate();
}

void KWSE::Graphics::Skybox::Render(Camera camera)
{
	auto matView = camera.GetViewMatrix();
	auto matProj = camera.GetProjectionMatrix();

	matView._41 = 0.0f;
	matView._42 = 0.0f;
	matView._43 = 0.0f;


	mSampler.BindPS(0);
	mSkyboxTexture.BindPS(0);
	mSkyboxDepthStencilState.Set();
	mSkyboxRasterizerState.Set();
	mSkyboxVertexShader.Bind();
	mSkyboxPixelShader.Bind();
	TransformData transformData{ Math::Transpose(matView*matProj)  };
	
	mTransformBuffer.Update(transformData);
	mTransformBuffer.BindVS(0);
	mSkyboxMeshBuffer.Render();


	mSkyboxDepthStencilState.Clear();
	mSkyboxRasterizerState.Clear();

}


