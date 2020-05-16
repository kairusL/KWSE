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
	//	      | <------0------> | |
	//	      |        |        | | 1.0
	//	      |        v        |/
	//	-1.0  +-----------------+ 0.0
	//      -1.0               1.0
	//
	mVertices.emplace_back(Vertex{ Vector3{  0.0f,  0.5f, 0.0f },Colors::DarkSlateGray });
	mVertices.emplace_back(Vertex{ Vector3{  0.5f, -0.5f, 0.0f },Colors::DarkRed });
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.5f, 0.0f },Colors::DarkBlue }); 
	mShape[Triangle] = std::move(mVertices); // std::move will move the all the data to new position without any copy.
	//mShape[Triangle] = mVertices;   // Making a copy from a data and put into shape.
	//mVertices.clear();  // remove reference 

	mVertices.emplace_back(Vertex{ Vector3{ -0.025f, 0.065f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.00f,  0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{ -0.05f,  0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.025f, 0.065f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.05f,  0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.00f,  0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{ -0.05f,  0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.05f,  0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{ -0.04f, -0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.05f,  0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.04f, -0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{ -0.04f, -0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{ -0.04f, -0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.04f, -0.025f, 0.0f} ,Colors::DarkRed});
	mVertices.emplace_back(Vertex{ Vector3{  0.00f, -0.075f, 0.0f} ,Colors::DarkRed});
	mShape[Heart] = std::move(mVertices);



	mVertices.emplace_back(Vertex{ Vector3{  0.0f,  0.5f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{  0.25f, 0.0f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{ -0.25f, 0.0f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{ -0.25f, 0.0f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{  0.0f, -0.5f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{ -0.5f, -0.5f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{  0.25f, 0.0f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{  0.5f, -0.5f, 0.0f} ,Colors::Yellow});
	mVertices.emplace_back(Vertex{ Vector3{  0.0f, -0.5f, 0.0f} ,Colors::Yellow});
	mShape[Triforce] = std::move(mVertices);




	//mVertices.emplace_back(Vertex{ Vector3{  0.0f,  0.0f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{  0.45f, -0.5f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.45f, -0.5f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{  0.0f,  0.5f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{  0.35f, 0.0f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.35f, 0.0f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{  0.0f,  1.0f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{  0.25f, 0.5f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.25f, 0.5f, 0.0f} , Colors::Orange });
	//mVertices.emplace_back(Vertex{ Vector3{  0.20f,  -0.55f, 0.0f} , Colors::Brown });
	//mVertices.emplace_back(Vertex{ Vector3{ -0.20f,  -0.55f, 0.0f} , Colors::Brown });
	//mVertices.emplace_back(Vertex{ Vector3{  0.0f, -0.75f, 0.0f} ,  Colors::Brown });
	//mShape[Tree] = std::move(mVertices);


	auto device = GraphicsSystem::Get()->GetDevice();
	HRESULT hr;

	for (auto iter = mShape.begin(); iter!=mShape.end(); iter++)
	{
		// Create vertex buffer
		D3D11_BUFFER_DESC bufferDesc{};
		bufferDesc.ByteWidth = iter->second.size() * sizeof(Vertex);
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = iter->second.data();
		mShapeBuffer[iter->first] = nullptr;

		hr = device->CreateBuffer(&bufferDesc, &initData, &mShapeBuffer[iter->first]);
		ASSERT(SUCCEEDED(hr), "Failed to create vertex buffer.");
	}
	

	// Compile and create vertex shader
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
		L"../../Assets/Shaders/DoSomething.fx",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlags, 0, &shaderBlob, &errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	ASSERT(SUCCEEDED(hr), "Failed to compile vertex shader");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mVertexShader);
	ASSERT(SUCCEEDED(hr), "Failed to create vertex shader.");

	// Define vertex element descriptions
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

	// Create the input layout
	hr = device->CreateInputLayout(
		vertexLayout.data(),
		(UINT)vertexLayout.size(),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&mInputLayout);
	ASSERT(SUCCEEDED(hr), "Failed to create input layout.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

	hr = D3DCompileFromFile(
		L"../../Assets/Shaders/DoSomething.fx",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0, &shaderBlob, &errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	ASSERT(SUCCEEDED(hr), "Failed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	ASSERT(SUCCEEDED(hr), "Failed to create pixel shader.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);



}
void GameState::Terminate()
{

	SafeRelease(mVertexBuffer);
	SafeRelease(mVertexShader);
	SafeRelease(mInputLayout);
	SafeRelease(mPixelShader);

}
void GameState::Update(float deltaTime)
{

	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		++mShapeCount;
		mCurrentShape = static_cast<Shape> (mShapeCount % mShape.size());
	}
	
}
void GameState::Render()
{

	auto context = GraphicsSystem::Get()->GetContext();

	context->IASetInputLayout(mInputLayout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mShapeBuffer[mCurrentShape], &stride, &offset);

	context->VSSetShader(mVertexShader, nullptr, 0);
	context->PSSetShader(mPixelShader, nullptr, 0);

	context->Draw((UINT)mShape[mCurrentShape].size(), 0);



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


