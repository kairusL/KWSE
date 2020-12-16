#pragma once
#include<KWSE/Inc/KWSE.h>


class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;


	void DebugUI() override;

	void Update(float deltaTime) override;
	void Render() override;
private:
	void RenderScene();
	void PostProcess();
	struct TransformData
	{
		KWSE::Math::Matrix4 world;
		KWSE::Math::Matrix4 wvp;
		KWSE::Math::Vector3 viewPosition;
		float padding;
	};
	struct TransformDataTexture
	{
		KWSE::Math::Matrix4 world;
		KWSE::Math::Matrix4 wvp;
		KWSE::Math::Vector3 viewPosition;
		float padding;
	};
	struct Setting
	{
		float displacementWeight = 0.001f;
		float normalWeight = 1.0f;
		float specularWeight = 1.0f;
		float padding;
	};
	struct OilSetting
	{
		float screenSizeScale = 2.0f;
		float paintRadius = 3.0f;
		float padding[2];
	};
	//ID3D11Buffer* mConstantBuffer = nullptr;

	using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;
	using TransformCloudBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTexture>;
	using LightBuffer = KWSE::Graphics::TypedConstantBuffer< KWSE::Graphics::DirectionalLight>;
	using MaterialBuffer = KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::Material>;
	using SettingBuffer = KWSE::Graphics::TypedConstantBuffer<Setting>;
	using OilSettingBuffer = KWSE::Graphics::TypedConstantBuffer<OilSetting>;


	KWSE::Graphics::DirectionalLight mDirectionLight;
	KWSE::Graphics::Material mMaterial;
	Setting mSetting;


	KWSE::Graphics::Camera mCamera;

	KWSE::Graphics::RenderTarget mRenderTarger;

	OilSettingBuffer mOilSettingBuffer;
	OilSetting mOilSetting;


	KWSE::Graphics::Mesh mMesh;
	KWSE::Graphics::MeshBuffer mMeshBuffer;

	KWSE::Graphics::MeshPNX mCloudMesh;
	KWSE::Graphics::MeshBuffer mCloudMeshBuffer;


	KWSE::Graphics::RasterizerState mRasterizerStateSolid;
	KWSE::Graphics::RasterizerState mRasterizerStateWireframe;

	bool mUseWireframe = false;
	//KWSE::Graphics::ConstantBuffer mConstantBuffer;  //<- it is danagurous.

	KWSE::Graphics::VertexShader mVertexShader;
	KWSE::Graphics::PixelShader mPixelShader;

	KWSE::Graphics::VertexShader mCloudVertexShader;
	KWSE::Graphics::PixelShader  mCloudPixelShader;

	KWSE::Graphics::VertexShader mPostProcessVertexShader;
	KWSE::Graphics::PixelShader  mPostProcessPixelShader;

	KWSE::Math::Vector3 mRotation;
	float mCloudRotation = 0.0f;
	//float mRotationY= 0.f;
	//float mRotationX= 0.f;
	//float mRotation = 0.f;

	TransformBuffer mTransformBuffer;
	TransformCloudBuffer mTransformCloudBuffer;

	LightBuffer  mLightBuffer;
	MaterialBuffer mMaterialBuffer;
	SettingBuffer mSettingBuffer;

	KWSE::Graphics::Skybox mSkybox;
	KWSE::Graphics::Texture mTexture[5];
	KWSE::Graphics::Texture mCloudTexture;
	KWSE::Graphics::Sampler mSampler;
	KWSE::Graphics::BlendState mBlendState;


	bool mNormal = true;
	bool mSpecular = true;

	float mFPS = 0.0f;

	KWSE::Graphics::MeshPX mScreenMesh;
	KWSE::Graphics::MeshBuffer mScreenMeshBuffer;
};