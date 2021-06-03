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
	void RenderBrightness();
	void ApplyBlur();
	void PostProcess();
	struct TransformData
	{
		KWSE::Math::Matrix4 world;
		KWSE::Math::Matrix4 wvp;
		KWSE::Math::Vector3 viewPosition;
		float padding;
	};
	struct TransformDataTextureWithLight
	{
		KWSE::Math::Matrix4 world;
		KWSE::Math::Matrix4 wvp;
		KWSE::Math::Vector3 viewPosition;
		float padding;
	};
	struct TransformDataTexture
	{
		KWSE::Math::Matrix4 wvp;
	};
	struct Setting
	{
		float displacementWeight = 0.001f;
		float normalWeight = 1.0f;
		float specularWeight = 1.0f;
		float padding;
	};
	//ID3D11Buffer* mConstantBuffer = nullptr;

	using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;
	using TransformCloudBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTextureWithLight>;
	using TransformTexture = KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Matrix4>;
	using LightBuffer = KWSE::Graphics::TypedConstantBuffer< KWSE::Graphics::DirectionalLight>;
	using MaterialBuffer = KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::Material>;
	using SettingBuffer = KWSE::Graphics::TypedConstantBuffer<Setting>;


	KWSE::Graphics::DirectionalLight mDirectionLight;
	KWSE::Graphics::Material mMaterial;
	Setting mSetting;


	KWSE::Graphics::Camera mCamera;

	KWSE::Graphics::RenderTarget mRenderTarger;




	KWSE::Graphics::Mesh mMesh;
	KWSE::Graphics::MeshBuffer mMeshBuffer;

	KWSE::Graphics::MeshPX mSunMesh;
	KWSE::Graphics::MeshBuffer mSunMeshBuffer;

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

	KWSE::Graphics::VertexShader mTextureVertexShader;
	KWSE::Graphics::PixelShader  mTexturePixelShader;

	KWSE::Graphics::VertexShader mGaussianBlurVertexShader;
	KWSE::Graphics::PixelShader  mGaussianBlurPixelShaderX;
	KWSE::Graphics::PixelShader  mGaussianBlurPixelShaderY;

	KWSE::Graphics::VertexShader mBloomVertexShader;
	KWSE::Graphics::PixelShader mBloomPixelShader;

	KWSE::Graphics::VertexShader mPostProcessVertexShader;
	KWSE::Graphics::PixelShader  mPostProcessPixelShader;

	KWSE::Math::Vector3 mRotation;
	float mRotaSunSpeed;
	float mCloudRotation = 0.0f;
	//float mRotationY= 0.f;
	//float mRotationX= 0.f;
	//float mRotation = 0.f;

	KWSE::Graphics::RenderTarget mBaseRenderTarget;
	KWSE::Graphics::RenderTarget mBloomRenderTarget;
	KWSE::Graphics::RenderTarget mBlurRenderTarget;

	TransformBuffer mTransformBuffer;
	TransformCloudBuffer mTransformCloudBuffer;
	TransformTexture mSunTransformBuffer;
	KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Vector4> mBlurSettingsBuffer;

	LightBuffer  mLightBuffer;
	MaterialBuffer mMaterialBuffer;
	SettingBuffer mSettingBuffer;

	KWSE::Graphics::Skybox mSkybox;
	KWSE::Graphics::Texture mTexture[5];
	KWSE::Graphics::Texture mCloudTexture;
	KWSE::Graphics::Texture mSunTexture;
	KWSE::Graphics::Texture mBlankTexture;
	KWSE::Graphics::Sampler mSampler;
	KWSE::Graphics::BlendState mBlendState;


	bool mNormal = true;
	bool mSpecular = true;

	float mFPS = 0.0f;
	bool mPause = false;

	int mBlurIterations = 10;
	float mBlurSaturation = 0.28f;

	KWSE::Graphics::MeshPX mScreenMesh;
	KWSE::Graphics::MeshBuffer mScreenMeshBuffer;

	bool ApplySun=false;
	bool ApplyCloud=false;
	bool NightMode = false;
};


//#pragma once
//
//#include <KWSE/Inc/KWSE.h>
//
//class GameState : public KWSE::AppState
//{
//public:
//	void Initialize() override;
//	void Terminate() override;
//
//	void Update(float deltaTime) override;
//	void Render() override;
//	void DebugUI() override;
//
//private:
//	void RenderScene();
//	void RenderBrightness();
//	void ApplyBlur();
//	void PostProcess();
//
//	struct EarthTransformData
//	{
//		KWSE::Math::Matrix4 world;
//		KWSE::Math::Matrix4 wvp;
//		KWSE::Math::Vector3 viewPosition;
//		float padding;
//	};
//	struct TransformDataTextureWithLight
//	{
//		KWSE::Math::Matrix4 world;
//		KWSE::Math::Matrix4 wvp;
//		KWSE::Math::Vector3 viewPosition;
//		float padding;
//	};
//	struct Setting
//	{
//		float displacementWeight = 0.001f;
//		float normalWeight = 1.0f;
//		float specularWeight = 1.0f;
//		float padding;
//	};
//	KWSE::Graphics::Camera mCamera;
//
//	KWSE::Graphics::RenderTarget mBaseRenderTarget;
//	KWSE::Graphics::RenderTarget mBloomRenderTarget;
//	KWSE::Graphics::RenderTarget mBlurRenderTarget;
//
//	using SettingBuffer = KWSE::Graphics::TypedConstantBuffer<Setting>;
//	using TransformCloudBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTextureWithLight>;
//	KWSE::Graphics::TypedConstantBuffer<EarthTransformData> mEarthTransformBuffer;
//	KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Matrix4> mTexturingTransformBuffer;
//	KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Vector4> mBlurSettingsBuffer;
//	KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::DirectionalLight> mLightBuffer;
//	KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::Material> mMaterialBuffer;
//
//	Setting mSetting;
//	SettingBuffer mSettingBuffer;
//
//	KWSE::Graphics::DirectionalLight mDirectionalLight;
//	KWSE::Graphics::Material mMaterial;
//
//	KWSE::Graphics::Mesh mEarthMesh;
//	KWSE::Graphics::MeshBuffer mEarthMeshBuffer;
//	KWSE::Graphics::MeshPX mSunMesh;
//	KWSE::Graphics::MeshBuffer mSunMeshBuffer;
//
//	KWSE::Graphics::MeshPNX mCloudMesh;
//	KWSE::Graphics::MeshBuffer mCloudMeshBuffer;
//
//	TransformCloudBuffer mTransformCloudBuffer;
//
//	KWSE::Graphics::VertexShader mTexturingVertexShader;
//	KWSE::Graphics::PixelShader mTexturingPixelShader;
//
//	KWSE::Graphics::VertexShader mEarthVertexShader;
//	KWSE::Graphics::PixelShader mEarthPixelShader;
//
//	KWSE::Graphics::VertexShader mCloudVertexShader;
//	KWSE::Graphics::PixelShader  mCloudPixelShader;
//
//	KWSE::Graphics::VertexShader mGaussianBlurVertexShader;
//	KWSE::Graphics::PixelShader mGaussianBlurXPixelShader;
//	KWSE::Graphics::PixelShader mGaussianBlurYPixelShader;
//
//	KWSE::Graphics::VertexShader mBloomVertexShader;
//	KWSE::Graphics::PixelShader mBloomPixelShader;
//
//	KWSE::Graphics::Sampler mSampler;
//	KWSE::Graphics::Texture mEarthDiffuseTexture;
//	KWSE::Graphics::Texture mEarthSpecularTexture;
//	KWSE::Graphics::Texture mEarthDisplacmentTexture;
//	KWSE::Graphics::Texture mEarthNormalTexture;
//	KWSE::Graphics::Texture mCloudTexture;
//	KWSE::Graphics::Texture mSunDiffuseTexture;
//	KWSE::Graphics::Texture mBlankTexture;
//
//
//
//	KWSE::Math::Vector3 mRotation;
//	float mFPS = 0.0f;
//
//	KWSE::Graphics::MeshPX mScreenMesh;
//	KWSE::Graphics::MeshBuffer mScreenMeshBuffer;
//
//	int mBlurIterations = 10;
//	float mBlurSaturation = 0.28f;
//	bool mNormal = true;
//	bool mSpecular = true;
//	KWSE::Graphics::BlendState mBlendState;
//};