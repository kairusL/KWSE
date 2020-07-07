#include"GameState.h"


using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);



	// Sci_fi_fighter
	ModelLoader::LoadObj(L"../../Assets/Models/sci_fi_fighter/sci_fi_fighter.obj", 10.0f, mMesh);

	mMeshBuffer.Initialize(mMesh);
	// Planets
	mPlanetsMeshBuffer.Initialize(MeshBuilder::CreateSpherePX(1.f,32,32));
	// ParticleEmitter
	mParticleEmitter.Initialize();
	mParticleEmitter.SetStartColor(Colors::LightCyan);
	mParticleEmitter.SetEndColor(Colors::DarkCyan);
	mParticleEmitter.SetStartSize(1.0f);
	mParticleEmitter.SetEndSize(0.0f);
	
	//shootingstar
	mShootingStarMeshBuffer.Initialize(MeshBuilder::CreateSpherePX(.35f, 32, 32));
	mShootingStarTexrures.Initialize("../../Assets/Images/8k_saturn.jpg");

	mTransformBuffer.Initialize();
	mShootingStarSpawnDelay = 2.0f;
	mShootingStarSpeed = 250.0f;




	mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx",VertexPX::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");


	// Planets
	mSci_fi_Texrures.Initialize("../../Assets/Models/sci_fi_fighter/sci_fi_fighter_diffuse.jpg");
	mTexrures.resize(10);
	mTexrures[0].Initialize("../../Assets/Images/8k_sun.jpg");
	mTexrures[1].Initialize("../../Assets/Images/8k_mercury.jpg");
	mTexrures[2].Initialize("../../Assets/Images/4k_venus.jpg");
	mTexrures[3].Initialize("../../Assets/Images/8k_earth_daymap.jpg");
	mTexrures[4].Initialize("../../Assets/Images/8k_mars.jpg");
	mTexrures[5].Initialize("../../Assets/Images/8k_jupiter.jpg");
	mTexrures[6].Initialize("../../Assets/Images/8k_saturn.jpg");
	mTexrures[7].Initialize("../../Assets/Images/2k_uranus.jpg");
	mTexrures[8].Initialize("../../Assets/Images/2k_neptune.jpg");
	mTexrures[9].Initialize("../../Assets/Images/8k_moon.jpg");

	mSkybox.Initialize("../../Assets/Images/Space_Skybox.jpg");

	// Rota the Sun
	mRotationSpeed.resize(10);
	mRotationSpeed[0] = 1.f;
	mRotationSpeed[1] = 0.1f;
	mRotationSpeed[2] = 0.2f;
	mRotationSpeed[3] = 0.3f;
	mRotationSpeed[4] = 0.1f;
	mRotationSpeed[5] = 0.2f;
	mRotationSpeed[6] = 0.3f;
	mRotationSpeed[7] = 0.4f;
	mRotationSpeed[8] = 0.5f;
	mRotationSpeed[9] = 0.6f;

	// SelfRotation
	mSelfRotationSpeed.resize(10);
	mSelfRotationSpeed[0] = 1.f;
	mSelfRotationSpeed[1] = 0.1f;
	mSelfRotationSpeed[2] = 0.2f;
	mSelfRotationSpeed[3] = 0.3f;
	mSelfRotationSpeed[4] = 0.1f;
	mSelfRotationSpeed[5] = 0.8f;
	mSelfRotationSpeed[6] = 0.6f;
	mSelfRotationSpeed[7] = 0.5f;
	mSelfRotationSpeed[8] = 0.4f;
	mSelfRotationSpeed[9] = 0.6f;
	
	// Planets size
	mSize.resize(10);
	mSize[0] = 5.f;
	mSize[1] = 1.1f;
	mSize[2] = 1.3f;
	mSize[3] = 1.3f;
	mSize[4] = 1.2f;
	mSize[5] = 1.8f;
	mSize[6] = 1.6f;
	mSize[7] = 1.5f;
	mSize[8] = 1.4f;
	mSize[9] = 0.6f;


	mSampler.Initialize(Sampler::Filter::Anisotropic,Sampler::AddressMode::Clamp);
	

	mRasterizerStateSolid.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Solid);
	mRasterizerStateWireframe.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Wireframe);


	mShipPosition={0.0f,0.0f,0.0f};
	mShipDirection = { 1.0f,0.0f,0.0f };

	//Snap camera to target position be defaule
	mCameraTargetPosition = mShipPosition - (mShipDirection *mCameraDistanceOffset) + (Vector3::YAxis * mCameraHeightOffset);
	mCamera.SetPosition(mCameraTargetPosition);
	mCamera.SetDirection(mShipDirection);
	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(500.0f);


}
void GameState::Terminate()
{
	mRasterizerStateSolid.Terminate();
	mRasterizerStateWireframe.Terminate();


	mSampler.Terminate();
	mSkybox.Terminate();
	for (int i = 0; i < mTexrures.size(); ++i)
	{
		mTexrures[i].Terminate();
	}
	mSci_fi_Texrures.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();

	mTransformBuffer.Terminate();
	mShootingStarTexrures.Terminate();
	mShootingStarMeshBuffer.Terminate();
	mParticleEmitter.Terminate();
	mPlanetsMeshBuffer.Terminate();
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

	mShipTilt *= 0.95f;

	const float shipTurnSpeed = .33f;
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
		//auto right = Cross(Vector3::YAxis, mShipDirection);
		mShipTilt = Clamp(mShipTilt - (1.0f*deltaTime), -0.5f, 0.5f);
		mShipPosition += right * shipMoveSpeed;
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		//auto right = Cross(Vector3::YAxis, mShipDirection);
		mShipTilt = Clamp(mShipTilt + (1.0f*deltaTime), -0.5f, 0.5f);

		mShipPosition -= right * shipMoveSpeed;
	}
	
	mCameraTargetPosition = mShipPosition - (mShipDirection *mCameraDistanceOffset) + (Vector3::YAxis * mCameraHeightOffset);
	auto cameraPosition = Lerp(mCamera.GetPosition(), mCameraTargetPosition, 0.25f);
	mCamera.SetPosition(cameraPosition);
	mCamera.SetDirection(mShipDirection);

	mRotation += deltaTime;


	// Shooting Star
	mShootingStarSpawnDelay += deltaTime;
	if (mShootingStarSpawnDelay>2.0f)
	{

		auto x = std::rand() % 60 - 50.0f;
		auto y = std::rand() % 30 +10.0f;
		mShootingStarSpawnDelay = 0.0f;
		mShootingStarPos = { x,y,1.0f };
		mShootingStarDir = { -x,-y,1.0f };
	}
	mShootingStarPos += Math::Normalize(mShootingStarDir)*deltaTime * mShootingStarSpeed;
	
	// ParticleEmitter
	mParticleEmitter.Start(10.0f);
	mParticleEmitter.Update(deltaTime);
	mParticleEmitter.SetPosition(mShipPosition - (mShipDirection*4.0f));

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
	
	auto matTile = Matrix4::RotationZ(mShipTilt);

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
	data.wvp = Transpose(matTile*matWorld*matView*matProj);
	
	

	mTransformBuffer.Update(data);
	mTransformBuffer.BindVS(slot);

	mVertexShader.Bind();
	mPixelShader.Bind();
	
	mSampler.BindPS(slot);
	mSci_fi_Texrures.BindPS(slot);

	mMeshBuffer.Render();


	// 
	data.wvp = Transpose(Math::Matrix4::Translation(mShootingStarPos)*matView*matProj);
	mTransformBuffer.Update(data);
	mTransformBuffer.BindVS(slot);
	mShootingStarTexrures.BindPS(slot);
	mShootingStarMeshBuffer.Render();


	for (int i = 0; i < mTexrures.size()-1; ++i)
	{
		auto scaling = Math::Matrix4::Scaling(mSize[i]);
		mTexrures[i].BindPS(slot);
		matWorld = Math::Matrix4::RotationY(mRotation*mRotationSpeed[i]);
		auto matSelfRotataion = Math::Matrix4::RotationY(mRotation*mSelfRotationSpeed[i]);
		auto matTranslation = Math::Matrix4::Translation({ 0.5f*i+i*15.f,0.0f,0.0f });
		//                   Scaling size of planet,  planet selfrotation ,  distance from the sun(in centre) , Rotate around the Sun from Y , move camera
		auto wvp = Math::Transpose(scaling*matSelfRotataion*matTranslation*matWorld*matView*matProj);
		data.wvp = wvp;
		mTransformBuffer.Update(data);
		mPlanetsMeshBuffer.Render();

		//Moon
		//if is the sun go back to for loop.
		if (i==0)
		{
			continue;
		}
		mTexrures[9].BindPS(slot);
		auto moonScaling = Math::Matrix4::Scaling(mSize[9]);
		auto matMoonWorld = Math::Matrix4::RotationY(mRotation*mRotationSpeed[9]);
		auto matMoonSelfRotataion = Math::Matrix4::RotationY(mRotation*mSelfRotationSpeed[9]);
		auto matMoonTranslation = Math::Matrix4::Translation({5.f,0.0f,0.0f });
		data.wvp = Math::Transpose(moonScaling*matMoonSelfRotataion*matMoonTranslation*matMoonWorld*matTranslation*matWorld*matView*matProj);
		mTransformBuffer.Update(data);
		mPlanetsMeshBuffer.Render();
	}

	mParticleEmitter.Render(mCamera);



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
