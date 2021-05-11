#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);


	mCamera.SetPosition({ 0.0f,0.0f,-5.0f });
	mCamera.SetDirection({ 0.0f,0.0f,1.0f });
	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(100.0f);

	mRenderTarger.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight());


	mMesh = MeshBuilder::CreateSphere(1.5f, 256, 256);
	mMeshBuffer.Initialize(mMesh);

	mCloudMesh = MeshBuilder::CreateSpherePNX(1.52f, 256, 256);
	mCloudMeshBuffer.Initialize(mCloudMesh);




	const wchar_t* shaderFileNames = L"../../Assets/Shaders/DarkStandard.fx";
	//const wchar_t* shaderFileNames1 = L"../../Assets/Shaders/PostProcessOilPainting.fx";
	const wchar_t* shaderFileNames1 = L"../../Assets/Shaders/PostProcess.fx";
	const wchar_t* shaderFileNames2 = L"../../Assets/Shaders/DoLightTexturing.fx";

	mPostProcessVertexShader.Initialize(shaderFileNames1,VertexPX::Format);
	mPostProcessPixelShader.Initialize(shaderFileNames1);


	mPixelShader.Initialize(shaderFileNames);
	mVertexShader.Initialize(shaderFileNames, Vertex::Format);

	mCloudPixelShader.Initialize(shaderFileNames2);
	mCloudVertexShader.Initialize(shaderFileNames2, VertexPNX::Format);

	mTransformBuffer.Initialize();
	mTransformCloudBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();


	mDirectionLight.direction = Math::Normalize({ 0.854f, -0.552f, 0.229f });
	mDirectionLight.ambient = { 0.145f };
	mDirectionLight.diffuse = { 0.784f };
	mDirectionLight.specular = { 0.858f };
	mMaterial.ambient = { 0.145f };
	mMaterial.diffuse = { 0.784f };
	mMaterial.specular = { 0.39 };
	mMaterial.power = 1.999f;



	mSkybox.Initialize("../../Assets/Images/Space_Skybox.jpg");
	//mSkybox.Initialize("../../Assets/Images/Skybox_04.jpg");
	mCloudTexture.Initialize("../../Assets/Images/earth_clouds.jpg");
	mTexture[0].Initialize("../../Assets/Images/earth.jpg");   // diffuse
	mTexture[1].Initialize("../../Assets/Images/earth_spec.jpg");  //specular
	mTexture[2].Initialize("../../Assets/Images/earth_bump.jpg");  // displacement
	mTexture[3].Initialize("../../Assets/Images/earth_normal.jpg");  // normal
	mTexture[4].Initialize("../../Assets/Images/earth_lights.jpg");  // normal

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mBlendState.Initialize(KWSE::Graphics::BlendState::Mode::Additive);
	mRasterizerStateSolid.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Solid);
	mRasterizerStateWireframe.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Wireframe);

	mOilSettingBuffer.Initialize();

	// NPC Space
	mScreenMesh.vertices.push_back({ {-1.0f,-1.0f,0.0f}, {0.0f,1.0f} });
	mScreenMesh.vertices.push_back({ {-1.0f,+1.0f,0.0f}, {0.0f,0.0f} });
	mScreenMesh.vertices.push_back({ {+1.0f,+1.0f,0.0f}, {1.0f,0.0f} });
	mScreenMesh.vertices.push_back({ {+1.0f,-1.0f,0.0f}, {1.0f,1.0f} });

	mScreenMesh.indices.push_back(0);
	mScreenMesh.indices.push_back(1);
	mScreenMesh.indices.push_back(2);

	mScreenMesh.indices.push_back(0);
	mScreenMesh.indices.push_back(2);
	mScreenMesh.indices.push_back(3);

	mScreenMeshBuffer.Initialize(mScreenMesh);
}
void GameState::Terminate()
{
	mScreenMeshBuffer.Terminate();
	mOilSettingBuffer.Terminate();
	mBlendState.Terminate();
	mRasterizerStateWireframe.Terminate();
	mRasterizerStateSolid.Terminate();
	mSampler.Terminate();

	for (auto& texture : mTexture)
	{
		texture.Terminate();
	}
	mCloudTexture.Terminate();
	mSkybox.Terminate();
	mCloudVertexShader.Terminate();
	mCloudPixelShader.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();

	mPostProcessPixelShader. Terminate();
	mPostProcessVertexShader.Terminate();

	mSettingBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();

	mTransformCloudBuffer.Terminate();
	mTransformBuffer.Terminate();
	mCloudMeshBuffer.Terminate();
	mMeshBuffer.Terminate();
	mRenderTarger.Terminate();


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
	mCloudRotation += deltaTime * 0.01;
}
void GameState::Render()
{
	// Capture a Screen shot
	RenderScene();
	// Process screen shot before presenting
	PostProcess();

}



void  GameState::DebugUI()
{
	ImGui::Begin("Debug Setting", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("FPS: %f", mFPS);
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);
	}
	const char* themeItems[] = { "Classic", "Dark","Light" };
	static int themeItemIndex = 0;
	if (ImGui::Combo("UI Theme", &themeItemIndex, themeItems, IM_ARRAYSIZE(themeItems)))
	{
		if (themeItemIndex == 0)
		{
			DebugUI::SetTheme(DebugUI::Theme::Classic);
		}
		else if (themeItemIndex == 1)
		{
			DebugUI::SetTheme(DebugUI::Theme::Dark);
		}
		else
		{
			DebugUI::SetTheme(DebugUI::Theme::Light);

		}
	}
	if (ImGui::CollapsingHeader("OilSetting"))
	{
		ImGui::DragFloat("Screen Size Scale", &mOilSetting.screenSizeScale, 0.1f, 0.0f, 1000.0f);
		ImGui::DragFloat("Brush Radius", &mOilSetting.paintRadius, 0.01f, 0.0f, 1000.0f);
	}
	if (ImGui::CollapsingHeader("Light"))
	{
		if (ImGui::DragFloat3("Light Direction", &mDirectionLight.direction.x, 0.01f, -1.0f, 1.0f))
		{
			mDirectionLight.direction = Math::Normalize(mDirectionLight.direction);
		}
		ImGui::ColorEdit3("Light Ambient", &mDirectionLight.ambient.x);
		ImGui::ColorEdit3("Light Diffuse", &mDirectionLight.diffuse.x);
		ImGui::ColorEdit3("Light Specular", &mDirectionLight.specular.x);
	}
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::ColorEdit3("Material Ambient", &mMaterial.ambient.x);
		ImGui::ColorEdit3("Material Diffuse", &mMaterial.diffuse.x);
		ImGui::ColorEdit3("Material Specular", &mMaterial.specular.x);
		ImGui::DragFloat("Material Power", &mMaterial.power, 0.1f, 0.0001f, 100.0f);
	}
	if (ImGui::CollapsingHeader("Setting"))
	{
		ImGui::DragFloat("Displacement Weight", &mSetting.displacementWeight, 0.1f, 0.0f, 100.0f);

		if (ImGui::Checkbox("Normal", &mNormal))
		{
			mSetting.normalWeight = mNormal ? 1.0f : 0.0f;
		}
		if (ImGui::Checkbox("Specular", &mSpecular))
		{
			mSetting.specularWeight = mSpecular ? 1.0f : 0.0f;
		}
	}

	ImGui::End();

	//ImGui::ShowDemoWindow();

}


void GameState::RenderScene()
{
	mRenderTarger.BeginRender();

	mUseWireframe ? mRasterizerStateWireframe.Set() : mRasterizerStateWireframe.Clear();




	auto matView = mCamera.GetViewMatrix();
	auto matProj = mCamera.GetProjectionMatrix();


	auto matViewSkybox = Matrix4::Scaling(1)*matView;
	matViewSkybox._41 = 0.0f;
	matViewSkybox._42 = 0.0f;
	matViewSkybox._43 = 0.0f;


	// Pass transform data to the GPU.
	TransformData data;
	TransformDataTexture textureData;

	data.viewPosition = mCamera.GetPosition();
	textureData.viewPosition = mCamera.GetPosition();

	mSkybox.Render(mCamera);

	UINT slot = 0; // This needs to match the shader register index.
	//mTransformCloudBuffer.BindPS(0);

	mTransformBuffer.BindVS(slot);
	mTransformBuffer.BindPS(slot);

	mLightBuffer.Update(mDirectionLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	auto matWorld = Matrix4::RotationX(mRotation.x)*
		Matrix4::RotationY(mRotation.y);
	data.world = Transpose(matWorld);
	data.wvp = Transpose(matWorld*matView*matProj);

	mTransformBuffer.Update(data);

	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindVS(slot);
	mSampler.BindPS(slot);


	mTexture[0].BindPS(0);
	mTexture[1].BindPS(1);
	mTexture[2].BindVS(2);
	mTexture[3].BindPS(3);
	mTexture[4].BindPS(4);

	mSettingBuffer.Update(mSetting);
	mSettingBuffer.BindVS(3);
	mSettingBuffer.BindPS(3);
	mMeshBuffer.Render(); //draw

	mCloudPixelShader.Bind();
	mCloudVertexShader.Bind();
	//mLightBuffer.BindVS(1);
	//mLightBuffer.BindPS(1);
	//mMaterialBuffer.BindVS(2);
	//mMaterialBuffer.BindPS(2);
	matWorld = Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x*mCloudRotation) * Matrix4::RotationY(mRotation.y*mCloudRotation) * Matrix4::RotationZ(mRotation.z*mCloudRotation));
	textureData.world = Transpose(matWorld);
	textureData.wvp = KWSE::Math::Transpose(matWorld*matView*matProj);
	mTransformCloudBuffer.Update(textureData);

	mTransformCloudBuffer.BindVS(0);
	mCloudTexture.BindPS(0);
	mBlendState.Set();

	mCloudMeshBuffer.Render();

	BlendState::ClearState();



	SimpleDraw::AddLine(Vector3::Zero, Vector3::XAxis, Colors::Red);
	SimpleDraw::AddLine(Vector3::Zero, Vector3::YAxis, Colors::Green);
	SimpleDraw::AddLine(Vector3::Zero, Vector3::ZAxis, Colors::Blue);


	SimpleDraw::AddTransform(Matrix4::Identity);

	SimpleDraw::Render(mCamera);

	mRenderTarger.EndRender();

}
void GameState::PostProcess()
{
	mPostProcessVertexShader.Bind();
	mPostProcessPixelShader.Bind();

	mOilSettingBuffer.Update(mOilSetting);
	mOilSettingBuffer.BindPS(0);

	mSampler.BindVS(0);

	mRenderTarger.BindPS(0);
	mScreenMeshBuffer.Render();
	mRenderTarger.UnbindPS(0);
}