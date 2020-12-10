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
	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(100.0f);


	mMesh = MeshBuilder::CreateSpherePN(5.0f,10,10);

	mMeshBuffer.Initialize(mMesh);

	const wchar_t* shaderFileNames[] =
	{
		L"../../Assets/Shaders/DoGouraudShading.fx",
		L"../../Assets/Shaders/DoPhongShading.fx"
	};
	for (size_t i = 0; i < std::size(shaderFileNames); ++i)
	{
		mVertexShader[i].Initialize(shaderFileNames[i],VertexPN::Format);
		mPixelShader[i].Initialize(shaderFileNames[i]);
	}
	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	mDirectionLight.direction = { 0.577f, -0.577f, 0.577f };
	mDirectionLight.ambient = { 0.2f};
	mDirectionLight.diffuse = { 0.901f };
	mDirectionLight.specular = { 0.2f };
	mMaterial.ambient = { 0.2f };
	mMaterial.diffuse = { 0.949f,0.2f,0.2f,1.0f };
	mMaterial.specular = { 0.5019f };
	mMaterial.power = 10;


	mSkybox.Initialize("../../Assets/Images/Skybox_04.jpg");



	mRasterizerStateSolid.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Solid);
	mRasterizerStateWireframe.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Wireframe);


}
void GameState::Terminate()
{
	mRasterizerStateSolid.Terminate();
	mRasterizerStateWireframe.Terminate();

	mSkybox.Terminate();
	for(auto& ps:mPixelShader)
		ps.Terminate();
	for (auto& vs : mVertexShader)
		vs.Terminate();

	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
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
		mRotation.y += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::J))
		mRotation.x += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::Q))
		mCamera.Rise(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::E))
		mCamera.Rise(-moveSpeed * deltaTime);
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::LEFT))
		mRotation.y += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::RIGHT))
		mRotation.y -= deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::UP))
		mRotation.x += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::DOWN))
		mRotation.x -= deltaTime;
	//mRotation += deltaTime;
	mFPS = 1.0f / deltaTime;
}
void GameState::Render()
{
	mUseWireframe ? mRasterizerStateWireframe.Set() : mRasterizerStateWireframe.Clear();




	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetProjectionMatrix();

	
	auto matViewSkybox = Matrix4::Scaling(1)*matView;
	matViewSkybox._41 = 0.0f;
	matViewSkybox._42 = 0.0f;
	matViewSkybox._43 = 0.0f;
	//mSkybox.Render(Math::Transpose(matViewSkybox*matProj));
	mSkybox.Render(mCamera);

	// Pass transform data to the GPU.
	TransformData data;
	data.viewPosition = mCamera.GetPosition();

	UINT slot = 0; // This needs to match the shader register index.
	mTransformBuffer.BindVS(slot);
	mTransformBuffer.BindPS(slot);
	mLightBuffer.Update(mDirectionLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);
	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	const float xOffsets[] = { -7.0f,7.0f };
	for (size_t i = 0; i < std::size(xOffsets); ++i)
	{
		auto matWorld = Matrix4::RotationX(mRotation.x)*
						Matrix4::RotationY(mRotation.y)*
			Matrix4::Translation({xOffsets[i],0.0f,0.0f});
		data.world = Transpose(matWorld); 
		data.wvp = Transpose(matWorld*matView*matProj);
		mTransformBuffer.Update(data);
		mVertexShader[i].Bind();
		mPixelShader [i].Bind();
		mMeshBuffer.Render();
	}




	SimpleDraw::AddLine(Vector3::Zero, Vector3::XAxis, Colors::Red);
	SimpleDraw::AddLine(Vector3::Zero, Vector3::YAxis, Colors::Green);
	SimpleDraw::AddLine(Vector3::Zero, Vector3::ZAxis, Colors::Blue);

	//SimpleDraw::AddCylinder(Vector3::Zero, Vector3::YAxis, 1.0f,Colors::DarkGoldenrod);

	//SimpleDraw::AddSphere(Vector3::Zero, 5.0f, Colors::DarkSlateBlue);
	//SimpleDraw::AddGroundPlane(10.0f,Colors::DarkGoldenrod);
	//SimpleDraw::AddCone(Vector3::Zero, Vector3::One*2.0f, 2.0f, Colors::Orange);

	//SimpleDraw::AddAABB({ 2.0f,1.0f,0.0f }, Vector3::One, Colors::Orange);
	//SimpleDraw::AddAABB({ -2.0f,1.0f,0.0f }, Vector3::One, Colors::Orange,true);

	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::Render(mCamera);
}



void  GameState::DebugUI()
{
	ImGui::Begin("Debug Setting",nullptr,ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("FPS: %f", mFPS);

	ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);

	const char* themeItems[] = { "Classic", "Dark","Light" };
	static int themeItemIndex = 0;
	if (ImGui::Combo("UI Theme", &themeItemIndex,themeItems,IM_ARRAYSIZE(themeItems)))
	{
		if (themeItemIndex==0)
		{
			DebugUI::SetTheme(DebugUI::Theme::Classic);
		}
		else if (themeItemIndex==1)
		{
			DebugUI::SetTheme(DebugUI::Theme::Dark);
		}
		else
		{
			DebugUI::SetTheme(DebugUI::Theme::Light);

		}
	}
	ImGui::DragFloat3("Light Direction", &mDirectionLight.direction.x,0.01f,-1.0f,1.0f);
	ImGui::ColorEdit3("Light Ambient", &mDirectionLight.ambient.x);
	ImGui::ColorEdit3("Light Diffuse", &mDirectionLight.diffuse.x);
	ImGui::ColorEdit3("Light Specular", &mDirectionLight.specular.x);

	ImGui::ColorEdit3("Material Ambient", &mMaterial.ambient.x);
	ImGui::ColorEdit3("Material Diffuse", &mMaterial.diffuse.x);
	ImGui::ColorEdit3("Material Specular", &mMaterial.specular.x);
	ImGui::DragFloat("Material Power", &mMaterial.power,0.1f,0.0001f,100.0f);
	ImGui::End();

	//ImGui::ShowDemoWindow();

}


