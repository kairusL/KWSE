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
		KWSE::Math::Matrix4 world;
		KWSE::Math::Matrix4 wvp;
		KWSE::Math::Vector3 viewPosition;
		float padding;
	};
	//ID3D11Buffer* mConstantBuffer = nullptr;

	using TransformBuffer = KWSE::Graphics::TypedConstantBuffer<TransformData>;
	using LightBuffer = KWSE::Graphics::TypedConstantBuffer< KWSE::Graphics::DirectionalLight>;
	using MaterialBuffer = KWSE::Graphics::TypedConstantBuffer<KWSE::Graphics::Material>;

	//TODO: Show these in ImGui so we can change them on the fly
	KWSE::Graphics::DirectionalLight mDirectionLight;
	KWSE::Graphics::Material mMaterial;


	KWSE::Graphics::Camera mCamera;

	//TODO:
	// - Add VertexPN and MeshPN to Graphics
	// - Add MeshBuilder:: CreateSpherePN

	KWSE::Graphics::MeshPN mMesh;

	KWSE::Graphics::MeshBuffer mMeshBuffer;


	KWSE::Graphics::RasterizerState mRasterizerStateSolid;
	KWSE::Graphics::RasterizerState mRasterizerStateWireframe;

	bool mUseWireframe = false;
	//KWSE::Graphics::ConstantBuffer mConstantBuffer;  //<- it is danagurous.

	KWSE::Graphics::VertexShader mVertexShader[2];
	KWSE::Graphics::PixelShader mPixelShader[2];
	
	KWSE::Math::Vector3 mRotation;
	//float mRotationY= 0.f;
	//float mRotationX= 0.f;
	//float mRotation = 0.f;


	TransformBuffer mTransformBuffer;
	LightBuffer  mLightBuffer;
	MaterialBuffer mMaterialBuffer;

	KWSE::Graphics::Skybox mSkybox;

	float mFPS = 0.0f;
};