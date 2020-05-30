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

	// NDC - Normalized Device Coordinate
	//
	//          +-----------------+
	//         /                 /|
	//   1.0  +-----------------+ |
	//	      |        ^        | |
	//	      |        |        | |
	//	      | <------|------> | |
	//	      |        |        | | 1.0
	//	      |        v        |/
	//	-1.0  +-----------------+ 0.0
	//      -1.0               1.0
	//

	/// Cube 1
	mMesh.vertices.emplace_back(Vector3{ -0.5f, -0.5f, 0.0f }, Colors::AliceBlue);// bottom left  0
	mMesh.vertices.emplace_back(Vector3{ -0.5f,  0.5f, 0.0f }, Colors::LightGoldenrodYellow);// top left     1
	mMesh.vertices.emplace_back(Vector3{ 0.5f, 0.5f, 0.0f }, Colors::DarkBlue); // top right     2
	mMesh.vertices.emplace_back(Vector3{ 0.5f, -0.5f, 0.0f},Colors::Orange);     //bottom right   3

	mMesh.vertices.emplace_back(Vector3{ -0.5f, -0.5f, 1.0f }, Colors::LightCyan);// bottom left  4
	mMesh.vertices.emplace_back(Vector3{ -0.5f,  0.5f, 1.0f }, Colors::LightGray);// top left     5
	mMesh.vertices.emplace_back(Vector3{ 0.5f, 0.5f,   1.0f }, Colors::DarkOrange); // top right   6
	mMesh.vertices.emplace_back(Vector3{ 0.5f, -0.5f,  1.0f }, Colors::DarkGoldenrod);    //bottom right 7


	// Front
	mMesh.indices.emplace_back(0);
	mMesh.indices.emplace_back(1);
	mMesh.indices.emplace_back(2);

	mMesh.indices.emplace_back(2);
	mMesh.indices.emplace_back(3);
	mMesh.indices.emplace_back(0);

	// Back
	mMesh.indices.emplace_back(6);
	mMesh.indices.emplace_back(5);
	mMesh.indices.emplace_back(4);

	mMesh.indices.emplace_back(6);
	mMesh.indices.emplace_back(4);
	mMesh.indices.emplace_back(7);

	// Right
	mMesh.indices.emplace_back(2);
	mMesh.indices.emplace_back(6);
	mMesh.indices.emplace_back(3);

	mMesh.indices.emplace_back(6);
	mMesh.indices.emplace_back(7);
	mMesh.indices.emplace_back(3);

	// Left
	mMesh.indices.emplace_back(1);
	mMesh.indices.emplace_back(0);
	mMesh.indices.emplace_back(5);

	mMesh.indices.emplace_back(5);
	mMesh.indices.emplace_back(0);
	mMesh.indices.emplace_back(4);

	// Top
	mMesh.indices.emplace_back(6);
	mMesh.indices.emplace_back(2);
	mMesh.indices.emplace_back(1);

	mMesh.indices.emplace_back(6);
	mMesh.indices.emplace_back(1);
	mMesh.indices.emplace_back(5);
	
	// Bottom
	mMesh.indices.emplace_back(0);
	mMesh.indices.emplace_back(3);
	mMesh.indices.emplace_back(4);

	mMesh.indices.emplace_back(4);
	mMesh.indices.emplace_back(3);
	mMesh.indices.emplace_back(7);
	




	mMeshBuffer.Initialize(mMesh);
	mTransformBuffer.Initialize();

	mVertexShader.Initialize(L"../../Assets/Shaders/DoTransform.fx",VertexPC::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");


}
void GameState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	mTransformBuffer.Terminate();
	
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

	mTransformBuffer.Update(data);
	mMeshBuffer.Render();

	Matrix4 translation = Matrix4::Translation({2.0f,0.f,0.f});
	Matrix4 rotation = Matrix4::RotationY(mRotation)* 
						Matrix4::RotationZ(-mRotation)*
						Matrix4::RotationX(-mRotation);
	data.wvp = Transpose(translation*rotation*matWorld*matView*matProj);
	mTransformBuffer.Update(data);
	mMeshBuffer.Render();
}





