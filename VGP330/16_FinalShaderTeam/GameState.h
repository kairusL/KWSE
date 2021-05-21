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

	void SetAnimation();
private:
	void RenderDepthMap();
	void RenderScene();
	void RenderBrightness();
	void ApplyBlur();
	void PostProcess();

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
	};
	struct OilSetting
	{
		float screenSizeScale=2.0f;
		float paintRadius=3.0f;
		float minSigma =1.0f;
		float sizeWeight=0.0f;

	};
	struct ActiveSetting
	{
		float oilActive   =0.0f;
		float heatActive  =0.0f;
		float mosaicActive=0.0f;
		float padding;
	};
	//ID3D11Buffer* mConstantBuffer = nullptr;

	
	using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;
	using TransformCloudBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTextureWithLight>;
	using TransformTextureBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTexture>;
	using TransformTexture = KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Matrix4>;
	using LightBuffer = KWSE::Graphics::TypedConstantBuffer< KWSE::Graphics::DirectionalLight>;
	using MaterialBuffer = KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::Material>;
	using SettingBuffer = KWSE::Graphics::TypedConstantBuffer<Setting>;
	using OilSettingBuffer = KWSE::Graphics::TypedConstantBuffer<OilSetting>;
	using ActiveSettingBuffer = KWSE::Graphics::TypedConstantBuffer<ActiveSetting>;


	KWSE::Graphics::DirectionalLight mDirectionLight;
	KWSE::Graphics::Material mMaterial;
	Setting mSetting;


	KWSE::Graphics::Camera mDefaultCamera;
	KWSE::Graphics::Camera mLightCamera;
	KWSE::Graphics::Camera* mActiveCamera = nullptr;


	KWSE::Graphics::RenderTarget mRenderTarger;

	KWSE::Graphics::RenderTarget mDepthRenderTarget;   // <- record depth from light source
	KWSE::Graphics::RenderTarget mBaseRenderTarget;     // < - original scene, think "screenshot"
	KWSE::Graphics::RenderTarget mBloomRenderTarget;  // <- only the "bright" pixels
	KWSE::Graphics::RenderTarget mBlurRenderTarget;     // <- amplify the brightness

	//Terrain
	KWSE::Graphics::Mesh mTerrainMesh;
	KWSE::Graphics::Texture mTerrainTexrures;
	KWSE::Graphics::MeshBuffer mTerrainMeshBuffer;

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

	KWSE::Graphics::VertexShader mTextureVertexShader;
	KWSE::Graphics::PixelShader  mTexturePixelShader;


	KWSE::Graphics::VertexShader mOilPaintingVertexShader;
	KWSE::Graphics::PixelShader mOilPaintingPixelShader;

	OilSettingBuffer mOilSettingBuffer;
	OilSetting mOilSetting;
	ActiveSettingBuffer mActiveSettingBuffer;
	ActiveSetting mActiveSetting;

	KWSE::Math::Vector3 mTerrainPosition;


	TransformCloudBuffer mTransformCloudBuffer;
	
	LightBuffer  mLightBuffer;
	MaterialBuffer mMaterialBuffer;
	SettingBuffer mSettingBuffer;

	KWSE::Graphics::Skybox mSkybox;
	KWSE::Graphics::Texture mBlankTexture;
	KWSE::Graphics::Sampler mSampler;
	KWSE::Graphics::BlendState mBlendState;



	float mFPS = 0.0f;

	int mBlurIterations = 10;
	float mBlurSaturation = 0.0f;//0.28f;

	KWSE::Graphics::MeshPX mScreenMesh;
	KWSE::Graphics::MeshBuffer mScreenMeshBuffer;

	float mLightCameraDistance = 100.0f;

	//Air balloon0
	KWSE::Graphics::Mesh	mAirBalloonMesh0;
	KWSE::Graphics::Texture mAirBalloonTexrure0;
	KWSE::Graphics::MeshBuffer mAirBalloonMeshBuffer0;
	// Animator
	KWSE::Graphics::Animator mAnimator;
	KWSE::Graphics::Animation mAnimation;
	float mAnimationTimer = 0.0f;

	//Air balloon1
	KWSE::Graphics::Texture mAirBalloonTexrure1;
	KWSE::Graphics::MeshBuffer mAirBalloonMeshBuffer1;
	// Animator
	KWSE::Graphics::Animator mAnimator1;
	KWSE::Graphics::Animation mAnimation1;
	float mAnimationTimer1 = 0.0f;

	//Air balloon2
	KWSE::Graphics::Texture mAirBalloonTexrure2;
	KWSE::Graphics::MeshBuffer mAirBalloonMeshBuffer2;
	// Animator
	KWSE::Graphics::Animator mAnimator2;
	KWSE::Graphics::Animation mAnimation2;
	float mAnimationTimer2 = 0.0f;

	//Air balloon3
	KWSE::Graphics::Texture mAirBalloonTexrure3;
	KWSE::Graphics::MeshBuffer mAirBalloonMeshBuffer3;
	// Animator
	KWSE::Graphics::Animator mAnimator3;
	KWSE::Graphics::Animation mAnimation3;
	float mAnimationTimer3 = 0.0f;

	//Air balloon4
	KWSE::Graphics::Texture mAirBalloonTexrure4;
	KWSE::Graphics::MeshBuffer mAirBalloonMeshBuffer4;
	// Animator
	KWSE::Graphics::Animator mAnimator4;
	KWSE::Graphics::Animation mAnimation4;
	float mAnimationTimer4 = 0.0f;

	//Air balloon5
	KWSE::Graphics::Texture mAirBalloonTexrure5;
	KWSE::Graphics::MeshBuffer mAirBalloonMeshBuffer5;
	// Animator
	KWSE::Graphics::Animator mAnimator5;
	KWSE::Graphics::Animation mAnimation5;
	float mAnimationTimer5 = 0.0f;

	//Air balloon6
	KWSE::Graphics::Texture mAirBalloonTexrure6;
	KWSE::Graphics::MeshBuffer mAirBalloonMeshBuffer6;
	// Animator
	KWSE::Graphics::Animator mAnimator6;
	KWSE::Graphics::Animation mAnimation6;
	float mAnimationTimer6 = 0.0f;


};

