#pragma once
#include "Service.h"

namespace KWSE
{
	class AnimatorComponent;
	class ModelComponent;
	class TransformComponent;

	class RenderService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceId::Render);



		void Initialize() override;
		void Terminate() override;

		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void Register(const ModelComponent* modelComponent);
		void Unregister(const ModelComponent* modelComponent);

	private:
		void RenderDepthMap();
		void RenderScene();
		void RenderBrightness();
		void ApplyBlur();
		void PostProcess();

		// -------------------------------------------------------------------------
		// Wireframe
		bool mUseWireframe = false;
		/// Wireframe

		// -------------------------------------------------------------------------
		// setting
		struct Entry
		{
			const AnimatorComponent* animatorComponent=nullptr;
			const ModelComponent* modelComponent =nullptr;
			const TransformComponent* transformComponent = nullptr;
		};
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
			float depthBias = 0.000029f;
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
			float screenSizeScale = 0.0f;
			float paintRadius = 3.0f;
			float minSigma = 1.0f;
			float sizeWeight = 0.0f;
		};
		/// setting

		// -------------------------------------------------------------------------
		// Array of Entry
		std::vector< Entry> mRenderEntries;
		/// Array of Entry

		// -------------------------------------------------------------------------
		// Camera
		KWSE::Graphics::Camera mDefaultCamera;
		KWSE::Graphics::Camera mLightCamera;
		KWSE::Graphics::Camera* mActiveCamera = nullptr;

		float mLightCameraDistance = 100.0f;
		/// Camera

		// -------------------------------------------------------------------------
		// Graphics
		using TransBoneBuffer = KWSE::Graphics::TypedConstantBuffer<BoneTransformData>;
		using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;
		using TransformCloudBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTextureWithLight>;
		using TransformTextureBuffer = KWSE::Graphics::TypedConstantBuffer<TransformDataTexture>;
		using TransformTexture = KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Matrix4>;
		using LightBuffer = KWSE::Graphics::TypedConstantBuffer< KWSE::Graphics::DirectionalLight>;
		using MaterialBuffer = KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::Material>;
		using SettingBuffer = KWSE::Graphics::TypedConstantBuffer<Setting>;
		using OilSettingBuffer = KWSE::Graphics::TypedConstantBuffer<OilSetting>;

		// -------------------------------------------------------------------------
		//Setting
		Setting mSetting;
		TransformBuffer mTransformBuffer;
		TransformCloudBuffer mTransformCloudBuffer;
		TransBoneBuffer mTransBoneBuffer;
		OilSettingBuffer mOilSettingBuffer;
		OilSetting mOilSetting;
		LightBuffer  mLightBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingBuffer mSettingBuffer;
		///Setting

		// -------------------------------------------------------------------------
		KWSE::Graphics::DirectionalLight mDirectionLight;

		KWSE::Graphics::Material mMaterial;

		KWSE::Graphics::RenderTarget mRenderTarger;
		KWSE::Graphics::RenderTarget mDepthRebderTarget;   // <- record depth from light source
		KWSE::Graphics::RenderTarget mBaseRenderTarget;     // < - original scene, think "screenshot"
		KWSE::Graphics::RenderTarget mBloomRenderTarget;  // <- only the "bright" pixels
		KWSE::Graphics::RenderTarget mBlurRenderTarget;     // <- amplify the brightness


		KWSE::Graphics::RasterizerState mRasterizerStateSolid;
		KWSE::Graphics::RasterizerState mRasterizerStateWireframe;

		//Model
		KWSE::Graphics::Model model;
		KWSE::Graphics::Animation anima;
		KWSE::Graphics::Texture modelTexrure[2];

		bool showSkeleton = false;
		int animF = 0;

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


		KWSE::Graphics::TypedConstantBuffer<KWSE::Math::Vector4> mBlurSettingsBuffer;

		KWSE::Graphics::Skybox mSkybox;
		KWSE::Graphics::Texture mBlankTexture;
		KWSE::Graphics::Sampler mSampler;
		KWSE::Graphics::BlendState mBlendState;

		KWSE::Graphics::Animator mAnimator;
		KWSE::Graphics::Animation mAnimation;

		KWSE::Graphics::MeshPX mScreenMesh;
		KWSE::Graphics::MeshBuffer mScreenMeshBuffer;
		/// Graphics 

		// -------------------------------------------------------------------------
		// GaussianBlur
		int mBlurIterations = 10;
		float mBlurSaturation = 0.0f;
		/// GaussianBlur
	};
}