#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);


	mCamera.SetPosition({0.0f,0.0f,-5.0f});
	mCamera.SetDirection({ 0.0f,0.0f,1.0f });

	mMesh = MeshBuilder::CreateCubePX();


	mMeshBuffer.Initialize(mMesh);
	mTransformBuffer.Initialize();

	mMesh = MeshBuilder::CreatePlanePX(10,10,5.0f);
	mMeshPlaneBuffer.Initialize(mMesh);

	mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx",VertexPX::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");
	mTexrure.Initialize("../../Assets/Images/nature.jpg");
	mSampler.Initialize(Sampler::Filter::Anisotropic,Sampler::AddressMode::Border);
	mSampler1.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Clamp);
	mSampler2.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Mirror);

}
void GameState::Terminate()
{
	mSampler2.Terminate();
	mSampler1.Terminate();
	mSampler.Terminate();
	mTexrure.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshPlaneBuffer.Terminate();
	mTransformBuffer.Terminate();
	mMeshBuffer.Terminate();
	
}
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::K))
		mRotationY += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::J))
		mRotationX += deltaTime;
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
	mRotation += deltaTime;
}
void GameState::Render()
{

	auto matWorld = Matrix4::RotationY(mRotationY)*Matrix4::RotationX(mRotationX);

	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetProjectionMatrix();





	// Pass transform data to the GPU.
	TransformData data;
	data.wvp = Transpose(matWorld*matView*matProj);

	UINT slot = 0; // This needs to match the shader register index.
	mTransformBuffer.BindVS(slot);
	mVertexShader.Bind();
	mPixelShader.Bind();

	mSampler.BindPS(slot);
	mTexrure.BindPS(slot);

	mTransformBuffer.Update(data);
	mMeshBuffer.Render();

	mMeshPlaneBuffer.Render();

	Matrix4 translation = Matrix4::Translation({5.0f,0.f,0.f});
	data.wvp = Transpose(translation*matWorld*matView*matProj);
	mTransformBuffer.Update(data);
	mSampler1.BindPS(slot);
	mMeshBuffer.Render();

	translation = Matrix4::Translation({ -5.0f,0.f,0.f });
	data.wvp = Transpose(translation*matWorld*matView*matProj);
	mTransformBuffer.Update(data);
	mSampler2.BindPS(slot);
	mMeshBuffer.Render();
}



