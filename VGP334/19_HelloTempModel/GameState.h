#pragma once
#include<KWSE/Inc/KWSE.h>


class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;


	void Render() override;
	void DebugUI() override;
private:
	void RenderDepthMap();
	void RenderScene();
	void RenderBrightness();
	void ApplyBlur();
	void PostProcess();
	void SetAnimation();

	struct TransformData
	{
		KWSE::Math::Matrix4 world;
		KWSE::Math::Matrix4 wvp[2];
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
		float normalWeight = 0.0f;
		float specularWeight = 0.0f;
		float depthBias= 0.000029f;
		int Skinning;
		KWSE::Math::Vector3 padding;
	};
	struct BoneTransformData
	{
		KWSE::Math::Matrix4 boneTransforms[256];
	};
	struct OilSetting
	{
		//float screenSizeScale=2.0f;
		float screenSizeScale=0.0f;
		float paintRadius=3.0f;
		float minSigma =1.0f;
		float sizeWeight=0.0f;
	};
	//ID3D11Buffer* mConstantBuffer = nullptr;

	using TransBoneBuffer = KWSE::Graphics::TypedConstantBuffer<BoneTransformData>;
	using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;
	using TransformCloudBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTextureWithLight>;
	using TransformTextureBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTexture>;
	using TransformTexture = KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Matrix4>;
	using LightBuffer = KWSE::Graphics::TypedConstantBuffer< KWSE::Graphics::DirectionalLight>;
	using MaterialBuffer = KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::Material>;
	using SettingBuffer = KWSE::Graphics::TypedConstantBuffer<Setting>;
	using OilSettingBuffer = KWSE::Graphics::TypedConstantBuffer<OilSetting>;


	KWSE::Graphics::DirectionalLight mDirectionLight;
	KWSE::Graphics::Material mMaterial;
	Setting mSetting;


	KWSE::Graphics::Camera mDefaultCamera;
	KWSE::Graphics::Camera mLightCamera;
	KWSE::Graphics::Camera* mActiveCamera = nullptr;


	KWSE::Graphics::RenderTarget mRenderTarger;

	KWSE::Graphics::RenderTarget mDepthRebderTarget;   // <- record depth from light source
	KWSE::Graphics::RenderTarget mBaseRenderTarget;     // < - original scene, think "screenshot"
	KWSE::Graphics::RenderTarget mBloomRenderTarget;  // <- only the "bright" pixels
	KWSE::Graphics::RenderTarget mBlurRenderTarget;     // <- amplify the brightness

	//Terrain
	KWSE::Graphics::Mesh mTerrainMesh;
	KWSE::Graphics::Texture mTerrainTexrures;
	KWSE::Graphics::MeshBuffer mTerrainMeshBuffer;

	//Model
	KWSE::Graphics::Model model;
	KWSE::Graphics::Animation anima;
	KWSE::Graphics::Texture modelTexrure[2];
	//SciFi
	KWSE::Graphics::Mesh mSciFiMesh;
	KWSE::Graphics::Texture mSci_fi_Texrures;
	KWSE::Graphics::MeshBuffer mSciFiMeshBuffer;
	KWSE::Math::Vector3 mShipPosition;
	KWSE::Math::Vector3 mShipDirection;
	float mShipRotation = 0.0f;
	float mShipElevation = 0.0f;
	float mShipTilt = 0.0f;

	//Plane
	KWSE::Graphics::Mesh mMesh;
	KWSE::Graphics::MeshBuffer mMeshPlaneBuffer;
	KWSE::Graphics::Texture mPlane_Texrures;

	//TransformData
	TransformBuffer mTransformBuffer;


	KWSE::Graphics::RasterizerState mRasterizerStateSolid;
	KWSE::Graphics::RasterizerState mRasterizerStateWireframe;

	bool mUseWireframe = false;
	//KWSE::Graphics::ConstantBuffer mConstantBuffer;  //<- it is danagurous.

	// DepthMap
	KWSE::Graphics::VertexShader mDepthMapVertexShader;
	KWSE::Graphics::PixelShader    mDepthMapPixelShader;
	KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Matrix4> mDepthMapBuffer;

	KWSE::Graphics::VertexShader mVertexShader;
	KWSE::Graphics::PixelShader mPixelShader;

	KWSE::Graphics::VertexShader mCloudVertexShader;
	KWSE::Graphics::PixelShader  mCloudPixelShader;

	KWSE::Graphics::VertexShader mTextureVertexShader;
	KWSE::Graphics::PixelShader  mTexturePixelShader;

	KWSE::Graphics::VertexShader mGaussianBlurVertexShader;
	KWSE::Graphics::PixelShader  mGaussianBlurPixelShaderX;
	KWSE::Graphics::PixelShader  mGaussianBlurPixelShaderY;

	KWSE::Graphics::VertexShader mOilPaintingVertexShader;
	KWSE::Graphics::PixelShader mOilPaintingPixelShader;

	OilSettingBuffer mOilSettingBuffer;
	OilSetting mOilSetting;

	KWSE::Math::Vector3 mRotation;
	KWSE::Math::Vector3 mSriFiPosition;
	KWSE::Math::Vector3 mTerrainPosition;
	//float mRotationY= 0.f;
	//float mRotationX= 0.f;
	//float mRotation = 0.f;

	TransBoneBuffer mTransBoneBuffer;

	TransformCloudBuffer mTransformCloudBuffer;
	KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Vector4> mBlurSettingsBuffer;


	LightBuffer  mLightBuffer;
	MaterialBuffer mMaterialBuffer;
	SettingBuffer mSettingBuffer;

	KWSE::Graphics::Skybox mSkybox;
	KWSE::Graphics::Texture mBlankTexture;
	KWSE::Graphics::Sampler mSampler;
	KWSE::Graphics::BlendState mBlendState;

	KWSE::Graphics::Animator mAnimator;
	KWSE::Graphics::Animation mAnimation;
	float mAnimationTimer = 0.0f;

	float mFPS = 0.0f;

	int mBlurIterations = 10;
	float mBlurSaturation = 0.0f;//0.28f;

	KWSE::Graphics::MeshPX mScreenMesh;
	KWSE::Graphics::MeshBuffer mScreenMeshBuffer;


	float mLightCameraDistance = 100.0f;
	bool mAnimationLoop = false;

	//Airballoon
	KWSE::Graphics::Mesh mAirballoonMesh;
	KWSE::Graphics::MeshBuffer mAirballoonMeshBuffer;
};

