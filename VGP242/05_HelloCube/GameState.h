#pragma once
#include<KWSE/Inc/KWSE.h>


class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;


	void Update(float deltaTime) override;
	void Render() override;
private:
	struct TransformData
	{
		KWSE::Math::Matrix4 wvp;
	};
	//ID3D11Buffer* mConstantBuffer = nullptr;

	KWSE::Graphics::Camera mCamera;
	KWSE::Graphics::MeshPC mMesh;
	KWSE::Graphics::MeshBuffer mMeshBuffer;
	KWSE::Graphics::ConstantBuffer mConstantBuffer;

	KWSE::Graphics::VertexShader mVertexShader;
	KWSE::Graphics::PixelShader mPixelShader;
	float mRotationY= 0.f;
	float mRotationX= 0.f;
	float mRotation = 0.f;


};