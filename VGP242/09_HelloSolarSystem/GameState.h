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
	struct TransformData
	{
		KWSE::Math::Matrix4 wvp;
	};
	//ID3D11Buffer* mConstantBuffer = nullptr;

	using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;

	KWSE::Graphics::Camera mCamera;
	KWSE::Graphics::MeshPX mMesh;
	KWSE::Graphics::MeshBuffer mMeshBuffer;
	KWSE::Graphics::MeshBuffer mPlanetsMeshBuffer;
	KWSE::Graphics::MeshBuffer mShootingStarMeshBuffer;
	KWSE::Graphics::Texture mSci_fi_Texrures;
	KWSE::Graphics::Texture mShootingStarTexrures;
	std::vector<KWSE::Graphics::Texture> mTexrures;
	KWSE::Graphics::Sampler mSampler;


	KWSE::Graphics::RasterizerState mRasterizerStateSolid;
	KWSE::Graphics::RasterizerState mRasterizerStateWireframe;

	bool mUseWireframe = false;
	//KWSE::Graphics::ConstantBuffer mConstantBuffer;  //<- it is danagurous.

	KWSE::Graphics::VertexShader mVertexShader;
	KWSE::Graphics::PixelShader mPixelShader;
	float mRotationY= 0.f;
	float mRotationX= 0.f;
	float mRotation = 0.f;

	TransformBuffer mTransformBuffer;
	KWSE::Graphics::Skybox mSkybox;

	KWSE::Math::Vector3 mShipPosition;
	KWSE::Math::Vector3 mShipDirection;
	float mShipRotation = 0.0f;
	float mShipElevation = 0.0f;
	float mShipTilt = 0.0f;

	// Planets 
	std::vector<float> mRotationSpeed;
	std::vector<float> mSelfRotationSpeed;
	std::vector<float> mSize;

	KWSE::Math::Vector3 mCameraTargetPosition;
	float mCameraDistanceOffset =40.0f;
	float mCameraHeightOffset = 5.0f;


	// Shooting Star 
	float mShootingStarSpeed;
	float mShootingStarSpawnDelay;
	KWSE::Math::Vector3 mShootingStarPos;
	KWSE::Math::Vector3 mShootingStarDir;

	// ParticleEmitter
	KWSE::Graphics::ParticleEmitter mParticleEmitter;
};