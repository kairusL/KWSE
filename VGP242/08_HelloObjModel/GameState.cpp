#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);


	mCamera.SetPosition({ 0.0f,0.0f,0.0f });
	mCamera.SetDirection({ 0.0f,-1.0f,2.0f });
	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(100.0f);

	ModelLoader::LoadObj(L"../../Assets/Models/sci_fi_fighter/sci_fi_fighter.obj", 1.0f, mMesh);
	mMeshBuffer.Initialize(mMesh);

	mTransformBuffer.Initialize();

	//mMesh = MeshBuilder::CreatePlanePX(10,10,5.0f);
	//mMeshPlaneBuffer.Initialize(mMesh);

	mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx",VertexPX::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");
	mTexrure.Initialize("../../Assets/Models/sci_fi_fighter/sci_fi_fighter_diffuse.jpg");
	//mTexrure.Initialize("../../Assets/Images/nature.jpg");
	mSkybox.Initialize("../../Assets/Images/Skybox_04.jpg");

	mSampler.Initialize(Sampler::Filter::Anisotropic,Sampler::AddressMode::Clamp);
	

	mRasterizerStateSolid.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Solid);
	mRasterizerStateWireframe.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Wireframe);


	mShipPosition={0.0f,0.0f,0.0f};
	mShipDirection = { 1.0f,0.0f,0.0f };


}
void GameState::Terminate()
{
	mRasterizerStateSolid.Terminate();
	mRasterizerStateWireframe.Terminate();


	mSampler.Terminate();
	mSkybox.Terminate();
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

	//const float moveSpeed = 10.0f;
	//const float turnSpeed = 10.0f * Constants::DegToRad;
	//if (inputSystem->IsKeyDown(KeyCode::W))
	//	mCamera.Walk(moveSpeed * deltaTime);
	//if (inputSystem->IsKeyDown(KeyCode::S))
	//	mCamera.Walk(-moveSpeed * deltaTime);
	//if (inputSystem->IsKeyDown(KeyCode::D))
	//	mCamera.Strafe(moveSpeed * deltaTime);
	//if (inputSystem->IsKeyDown(KeyCode::A))
	//	mCamera.Strafe(-moveSpeed * deltaTime);
	//if (inputSystem->IsKeyDown(KeyCode::K))
	//	mRotationY += deltaTime;
	//if (inputSystem->IsKeyDown(KeyCode::J))
	//	mRotationX += deltaTime;
	//if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	//{
	//	mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
	//	mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	//}


	const float shipTurnSpeed = 0.1f;
	mShipRotation += inputSystem->GetMouseMoveX() * shipTurnSpeed * deltaTime;
	mShipElevation += inputSystem->GetMouseMoveY() * shipTurnSpeed * deltaTime;
	
	mShipDirection = Vector3::ZAxis;
	auto yawRotation = Math::Matrix4::RotationY(mShipRotation);
	mShipDirection = Math::TransformNormal(mShipDirection, yawRotation);
	
	const Math::Vector3 right = Math::Normalize(Cross(Math::Vector3::YAxis, mShipDirection));
	const Math::Matrix4 pitchRotation = Math::Matrix4::RotationAxis(right, mShipElevation);
	mShipDirection = Math::TransformNormal(mShipDirection, pitchRotation);
	
	const float shipMoveSpeed = 1.0f;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mShipPosition += mShipDirection * shipMoveSpeed;
	if (inputSystem->IsKeyDown(KeyCode::S))
		mShipPosition -= mShipDirection * shipMoveSpeed;
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		auto right = Cross(Vector3::YAxis, mShipDirection);
		mShipPosition += right * shipMoveSpeed;
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		auto right = Cross(Vector3::YAxis, mShipDirection);
		mShipPosition -= right * shipMoveSpeed;
	}
	
	auto cameraPosition = mShipPosition - (mShipDirection *5.0f) + (Vector3::YAxis * 2.0f);
	mCamera.SetPosition(cameraPosition);
	mCamera.SetDirection(mShipDirection);

	mRotation += deltaTime;
}
void GameState::Render()
{

	UINT slot = 0; // This needs to match the shader register index.

	auto matWorld = Matrix4::RotationY(mRotationY)*Matrix4::RotationX(mRotationX);

	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetProjectionMatrix();

	mSkybox.Render(mCamera);
	mUseWireframe ? mRasterizerStateWireframe.Set() : mRasterizerStateWireframe.Clear();


	static float angle = 0.0f;
	angle += 1.0f / 60.0f;

	const Math::Vector3 l = mShipDirection;
	const Math::Vector3 r = Math::Normalize(Math::Cross(Math::Vector3::YAxis, l));
	const Math::Vector3 u = Math::Normalize(Math::Cross(l, r));
	const Math::Vector3 p = mShipPosition;

	matWorld = Matrix4{
		r.x, r.y, r.z, 0.0f,
		u.x, u.y, u.z, 0.0f,
		l.x, l.y, l.z, 0.0f,
		p.x, p.y, p.z, 1.0f
	};
	auto context = GraphicsSystem::Get()->GetContext();




	// Pass transform data to the GPU.
	TransformData data;
	data.wvp = Transpose(matWorld*matView*matProj);
	
	

	mTransformBuffer.Update(data);
	mTransformBuffer.BindVS(slot);

	mVertexShader.Bind();
	mPixelShader.Bind();
	
	mSampler.BindPS(slot);
	mTexrure.BindPS(slot);
	
	mMeshBuffer.Render();

	mMeshPlaneBuffer.Render();

	//Matrix4 translation = Matrix4::Translation({0.0f,0.f,0.f});
	//data.wvp = Transpose(translation*matWorld*matView*matProj);
	//mTransformBuffer.Update(data);
	//mSampler1.BindPS(slot);
	//mMeshBuffer.Render();

	//translation = Matrix4::Translation({ 0.0f,0.f,0.f });
	//data.wvp = Transpose(translation*matWorld*matView*matProj);
	//mTransformBuffer.Update(data);
	////mSampler2.BindPS(slot);
	//mMeshBuffer.Render();


	SimpleDraw::AddLine(Vector3::Zero, Vector3::XAxis, Colors::Red);
	SimpleDraw::AddLine(Vector3::Zero, Vector3::YAxis, Colors::Green);
	SimpleDraw::AddLine(Vector3::Zero, Vector3::ZAxis, Colors::Blue);

	//SimpleDraw::AddCylinder(Vector3::Zero, Vector3::YAxis, 1.0f,Colors::DarkGoldenrod);

	//SimpleDraw::AddSphere(Vector3::Zero, 5.0f, Colors::DarkSlateBlue);
	//SimpleDraw::AddGroundPlane(10.0f,Colors::DarkGoldenrod);
	//SimpleDraw::AddCone(Vector3::Zero, Vector3::One*2.0f, 2.0f, Colors::Orange);

	SimpleDraw::AddAABB({ 2.0f,1.0f,0.0f }, Vector3::One, Colors::Orange);
	SimpleDraw::AddAABB({ -2.0f,1.0f,0.0f }, Vector3::One, Colors::Orange,true);

	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::Render(mCamera);
}



void  GameState::DebugUI()
{
	ImGui::Begin("Debug Setting",nullptr,ImGuiWindowFlags_AlwaysAutoResize);


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

	//Render mode
	const char* renderModeItems[] = { "Solid","Wireframe" };
	static int renderModeIndex = 0;
	if (ImGui::Combo("Render Mode",&renderModeIndex,renderModeItems,IM_ARRAYSIZE(renderModeItems)))
	{
		mUseWireframe = (renderModeIndex != 0);
	}
	//ImGui::Text("Hello");
	//ImGui::Button("Boom");
	ImGui::End();

	//ImGui::ShowDemoWindow();

}


// Homework
// - Add a skybox class to Graphics
// - Use DoTexturing.fx shader (you can make a copy of it and call it skybox.fx)
// - Create a textured cube mesh for drawing
//- Have a MeshBuilder::CreateSkybox function that generates a box that is textured mapped on the inside
// - For drawing, make sure the skybox is the same position as the camera (but leave rotation unchanged)
// - Make sure it is drawn first before anything else in your scene, disable Z when drawing the skybox
