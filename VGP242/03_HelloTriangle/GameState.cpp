#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::LightGray);

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
	mMesh.vertices.emplace_back(Vector3{  0.0f,  0.5f, 0.0f },Color{0.0f,0.0f,0.0f,0.0f });
	mMesh.vertices.emplace_back(Vector3{  0.5f, -0.5f, 0.0f },Color{0.0f,0.0f,0.0f,0.0f });
	mMesh.vertices.emplace_back(Vector3{ -0.5f, -0.5f, 0.0f },Color{0.0f,0.0f,0.0f,0.0f });
	mMesh.vertices.emplace_back(Vector3{ -0.8f, -0.8f, 0.0f },Color{0.0f,0.0f,0.0f,0.0f });

	//mMesh.indices.emplace_back(0);
	//mMesh.indices.emplace_back(1);
	//mMesh.indices.emplace_back(2);

	mMesh.indices.emplace_back(0);
	mMesh.indices.emplace_back(2);
	mMesh.indices.emplace_back(3);




	auto device = GraphicsSystem::Get()->GetDevice();

	// 
	mMeshBuffer.Initialize(mMesh);
	
	// Compile and create vertex shader
	




	mVertexShader.Initialize(L"../../Assets/Shaders/DoNothing.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoNothing.fx");


}
void GameState::Terminate()
{
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();

}
void GameState::Update(float deltaTime)
{

}
void GameState::Render()
{

	auto context = GraphicsSystem::Get()->GetContext();

	

	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}



// Add 04_HelloShapes project
// - Copy code from 03_HelloTriangle
// - Update to use DoSomething.fx shaders
// - Update Vertex to have Color as well
// - Make sure inputlayout is initialized with correct description
// - Create multiple meshes and vertex buffers
// - Draw a heart
// - Draw a triforce
// - Draw something with more than 5 triangles
// - Use input check so you can change between them


