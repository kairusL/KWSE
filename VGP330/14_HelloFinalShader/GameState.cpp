#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);

	// Sci_fi_fighter
	ModelLoader::LoadObj(L"../../Assets/Models/sci_fi_fighter/sci_fi_fighter.obj", 10.0f, mSciFiMesh);
	mSciFiMeshBuffer.Initialize(mSciFiMesh);
	mSci_fi_Texrures.Initialize("../../Assets/Models/sci_fi_fighter/sci_fi_fighter_diffuse.jpg");
	//2.15

	//Plane
	mMesh = MeshBuilder::CreatePlane(10, 10, 5.0f);
	mMeshPlaneBuffer.Initialize(mMesh);
	mPlane_Texrures.Initialize("../../Assets/Images/4k_venus.jpg");

	mTransformBuffer.Initialize();

	mSriFiPosition = { 1.0f,1.1f,1.0f };
	mDefaultCamera.SetPosition({ 0.0f,5.0f,15.0f });
	mDefaultCamera.SetDirection({ 0.0f,0.0f,-1.0f });
	mDefaultCamera.SetNearPlane(0.001f);
	//mDefaultCamera.SetFarPlane(100.0f);

	mLightCamera.SetNearPlane(0.1f);
	mLightCamera.SetFarPlane(200.0f);
	mLightCamera.SetAspectRation(1.0f);

	mActiveCamera = &mDefaultCamera;

	mBaseRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight(),Texture::Format::RGBA_F32
	);
	mBloomRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight(), Texture::Format::RGBA_F32
	);
	mBlurRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight(), Texture::Format::RGBA_F32
	);

	mRenderTarger.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight(), Texture::Format::RGBA_F32);





	mBlurSettingsBuffer.Initialize();


	const wchar_t* shaderFileNames = L"../../Assets/Shaders/Standard.fx";
	const wchar_t* shaderFileNames1 = L"../../Assets/Shaders/GaussianBlur.fx";
	const wchar_t* shaderFileNames2 = L"../../Assets/Shaders/DoLightTexturing.fx";
	const wchar_t* shaderFileNames3 = L"../../Assets/Shaders/DoTexturing.fx";

	mGaussianBlurVertexShader.Initialize(shaderFileNames1, VertexPX::Format);
	mGaussianBlurPixelShaderX.Initialize(shaderFileNames1, "BlurXPS");
	mGaussianBlurPixelShaderY.Initialize(shaderFileNames1, "BlurYPS");


	mPixelShader.Initialize(shaderFileNames);
	mVertexShader.Initialize(shaderFileNames, Vertex::Format);

	mCloudPixelShader.Initialize(shaderFileNames2);
	mCloudVertexShader.Initialize(shaderFileNames2, VertexPNX::Format);

	mTexturePixelShader.Initialize(shaderFileNames3);
	mTextureVertexShader.Initialize(shaderFileNames3, VertexPX::Format);

	mBloomVertexShader.Initialize(L"../../Assets/Shaders/PostProcessOilPainting.fx", VertexPX::Format);
	mBloomPixelShader.Initialize(L"../../Assets/Shaders/PostProcessOilPainting.fx");

	constexpr uint32_t depthMapSize = 4096;
	mDepthRebderTarget.Initialize(depthMapSize, depthMapSize,Texture::Format::RGBA_F32);

	mDepthMapVertexShader.Initialize(L"../../Assets/Shaders/DepthMap.fx", Vertex::Format);
	mDepthMapPixelShader.Initialize(L"../../Assets/Shaders/DepthMap.fx");
	mDepthMapBuffer.Initialize();

	mTransformBuffer.Initialize();
	mTransformCloudBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();


	mDirectionLight.direction = Math::Normalize({ 0.854f, -0.552f, 0.229f });
	mDirectionLight.ambient = { 0.5f };
	mDirectionLight.diffuse = { 0.784f };
	mDirectionLight.specular = { 0.858f };
	mMaterial.ambient = { 0.5f };
	mMaterial.diffuse = { 0.784f };
	mMaterial.specular = { 0.39f };
	mMaterial.power = 1.999f;



	//mSkybox.Initialize("../../Assets/Images/Space_Skybox.jpg");
	mSkybox.Initialize("../../Assets/Images/Skybox_04.jpg");

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mBlendState.Initialize(KWSE::Graphics::BlendState::Mode::Additive);
	mRasterizerStateSolid.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Solid);
	mRasterizerStateWireframe.Initialize(RasterizerState::CullMode::Back, RasterizerState::FillMode::Wireframe);


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
	mBlendState.Terminate();
	mRasterizerStateWireframe.Terminate();
	mRasterizerStateSolid.Terminate();
	mSampler.Terminate();

	mSkybox.Terminate();
	mBloomPixelShader.Terminate();
	mBloomVertexShader.Terminate();
	mTextureVertexShader.Terminate();
	mTexturePixelShader.Terminate();
	mCloudVertexShader.Terminate();
	mCloudPixelShader.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();

	mGaussianBlurPixelShaderY.Terminate();
	mGaussianBlurPixelShaderX.Terminate();
	mGaussianBlurVertexShader.Terminate();

	mBlurSettingsBuffer.Terminate();
	mSettingBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();

	mTransformCloudBuffer.Terminate();
	mTransformBuffer.Terminate();
	mRenderTarger.Terminate();

	mBlurRenderTarget.Terminate();

	mDepthMapBuffer.Terminate();
	mDepthMapPixelShader.Terminate();
	mDepthMapVertexShader.Terminate();
	mDepthRebderTarget.Terminate();

	mBloomRenderTarget.Terminate();
	mBaseRenderTarget.Terminate();
	mDepthRebderTarget.Terminate();

	mTransformBuffer.Terminate();

	mPlane_Texrures.Terminate();
	mMeshPlaneBuffer.Terminate();

	mSci_fi_Texrures.Terminate();
	mSciFiMeshBuffer.Terminate();
}
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	//SciFi
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

	// Camera
	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mActiveCamera->Walk(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mActiveCamera->Walk(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mActiveCamera->Strafe(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mActiveCamera->Strafe(-moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::K))
		mRotation.y += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::J))
		mRotation.x += deltaTime;
	if (inputSystem->IsKeyDown(KeyCode::Q))
		mActiveCamera->Rise(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::E))
		mActiveCamera->Rise(-moveSpeed * deltaTime);

	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mActiveCamera->Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mActiveCamera->Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
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

	//Synchronize the light camera to the directional light (cannot look straight up or down)
	mLightCamera.SetDirection(mDirectionLight.direction);
	KWSE::Math::Vector3 newCamaraPosition = -mLightCamera.GetDirection()*mLightCameraDistance;
	mLightCamera.SetPosition(newCamaraPosition);

	mFPS = 1.0f / deltaTime;
}
void GameState::Render()
{
	// Record scene depths from light source
	RenderDepthMap();

	// Capture a Screen shot
	RenderScene();

	//// Capture just the bright pixels for bloom - 2nd Pass
	RenderBrightness();
	//
	//// Apply Gaussian blur to the bloom pixels
	ApplyBlur();
	
	
	// Process screen shot before presenting
	PostProcess();



}



void  GameState::DebugUI()
{
	ImGui::Begin("Debug Setting", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("FPS: %f", mFPS);

	if (ImGui::CollapsingHeader("Theme"))
	{
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
	}

	bool useLightCamera = (mActiveCamera == &mLightCamera);
	if (ImGui::CollapsingHeader("Camera"))//,ImGuiTreeNodeFlags_DefaultOpen)
	{
		if (ImGui::Checkbox("Use Light Camera", &useLightCamera))
		{
			mActiveCamera = useLightCamera ? &mLightCamera : &mDefaultCamera;
		}
		ImGui::DragFloat("Light Distance", &mLightCameraDistance, 0.01f, 1.0f, 200.0f);
	}

	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);
	}
	if (ImGui::CollapsingHeader("Sci_Fi_Transform"))
	{
		ImGui::DragFloat3("Position", (float*)&mSriFiPosition, 0.01f);
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

		bool normal = mSetting.normalWeight == 1.0f;
		if (ImGui::Checkbox("Normal", &normal))
		{
			mSetting.normalWeight = normal ? 1.0f : 0.0f;
		}
		bool specular = mSetting.specularWeight == 1.0f;
		if (ImGui::Checkbox("Specular", &specular))
		{
			mSetting.specularWeight = specular ? 1.0f : 0.0f;
		}
		ImGui::DragFloat("Depth Bias", &mSetting.depthBias, 0.000001f,0.0f,1.0f,"%.7f");
	}
	if (ImGui::CollapsingHeader("Blur"))
	{
		ImGui::DragInt("Blur Iterations", &mBlurIterations, 1, 0, 100);
		ImGui::DragFloat("Blur Saturation", &mBlurSaturation, 0.001f, 0.0f, 1.0f);
	}
	if (ImGui::CollapsingHeader("DepthMap"))
	{
		ImGui::Image(mDepthRebderTarget.GetRawData(), { 200.0f,200.0f });
	}
	ImGui::End();

	//ImGui::ShowDemoWindow();

}


void GameState::RenderDepthMap()
{
	mDepthRebderTarget.BeginRender(Colors::Black);
	//Draw all the shadow casters using light camera.
	auto matView = mLightCamera.GetViewMatrix();
	auto matProj = mLightCamera.GetProjectionMatrix();

	mDepthMapBuffer.BindVS(0);

	auto matWorld =KWSE::Math::Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y) *Matrix4::RotationZ(mRotation.z)*Matrix4::Translation({ mSriFiPosition.x,mSriFiPosition.y,mSriFiPosition.z }); 
	auto wvp =Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();

	mSci_fi_Texrures.BindPS(0);
	mSampler.BindVS(0);
	mSciFiMeshBuffer.Render();

	mDepthRebderTarget.EndRender();

}

void GameState::RenderScene()
{
	mRenderTarger.BeginRender();
	mUseWireframe ? mRasterizerStateWireframe.Set() : mRasterizerStateWireframe.Clear();




	auto matView = mActiveCamera->GetViewMatrix();
	auto matProj = mActiveCamera->GetProjectionMatrix();

	auto matViewLight = mLightCamera.GetViewMatrix();
	auto matProjLight = mLightCamera.GetProjectionMatrix();

	//auto matViewSkybox = Matrix4::Scaling(1)*matView;
	//matViewSkybox._41 = 0.0f;
	//matViewSkybox._42 = 0.0f;
	//matViewSkybox._43 = 0.0f;


	// Pass transform data to the GPU.
	TransformData data;

	data.viewPosition = mActiveCamera->GetPosition();

	mSkybox.Render(*mActiveCamera);

	mSettingBuffer.Update(mSetting);
	mSettingBuffer.BindVS(3);
	mSettingBuffer.BindPS(3);

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

	auto matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) *Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x*5.0f) * Matrix4::RotationY(mRotation.y) *Matrix4::RotationZ(mRotation.z));//* Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*matView*matProj);
	data.wvp[1] = Transpose(matWorld*matViewLight*matProjLight);
	data.viewPosition = mActiveCamera->GetPosition();
	mTransformBuffer.Update(data);
	mTransformBuffer.BindVS(slot);
	mTransformBuffer.BindPS(slot);

	mVertexShader.Bind();
	mPixelShader.Bind();

	mSampler.BindVS(slot);
	mSampler.BindPS(slot);

	// SciFi
	matWorld = KWSE::Math::Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y) *Matrix4::RotationZ(mRotation.z)*Matrix4::Translation({ mSriFiPosition.x,mSriFiPosition.y,mSriFiPosition.z });
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mSci_fi_Texrures.BindPS(0);	
	mDepthRebderTarget.BindPS(4);
	mSciFiMeshBuffer.Render();
	//Texture::UnbindPS(0);
	//Texture::UnbindPS(4);


	//Plane
	matWorld = Transpose(Matrix4::Identity);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose((matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mPlane_Texrures.BindPS(0);

	mMeshPlaneBuffer.Render();

	Texture::UnbindPS(4);











	//mCloudPixelShader.Bind();
	//mCloudVertexShader.Bind();
	//mLightBuffer.BindVS(1);
	//mLightBuffer.BindPS(1);
	//mMaterialBuffer.BindVS(2);
	//mMaterialBuffer.BindPS(2);
	//matWorld = Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y) * Matrix4::RotationZ(mRotation.z));
	//Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) *Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y) * Matrix4::RotationZ(mRotation.z));


	
	//mBlendState.Set();
	//BlendState::ClearState();





	//SimpleDraw::AddLine(Vector3::Zero, Vector3::XAxis, Colors::Red);
	//SimpleDraw::AddLine(Vector3::Zero, Vector3::YAxis, Colors::Green);
	//SimpleDraw::AddLine(Vector3::Zero, Vector3::ZAxis, Colors::Blue);
	//
	//SimpleDraw::Render(*mActiveCamera);

	mRenderTarger.EndRender();

}

void GameState::RenderBrightness()
{
	mBloomRenderTarget.BeginRender();

	Matrix4 matView = mActiveCamera->GetViewMatrix();
	Matrix4 matProj = mActiveCamera->GetProjectionMatrix();

	Matrix4 matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) * Matrix4::RotationX(mRotation.x*5.0f) * Matrix4::RotationY(mRotation.y)*Matrix4::RotationZ(mRotation.z);

	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	mSampler.BindPS(0);

	mBlankTexture.BindPS(0);

	mBloomRenderTarget.EndRender();
}

void GameState::ApplyBlur()
{
	auto graphicsSystem = GraphicsSystem::Get();
	Vector4 settings;
	settings.x = static_cast<float>(graphicsSystem->GetBackBufferWidth());
	settings.y = static_cast<float>(graphicsSystem->GetBackBufferHeight());
	settings.z = mBlurSaturation;
	mBlurSettingsBuffer.Update(settings);
	mBlurSettingsBuffer.BindPS(0);

	mGaussianBlurVertexShader.Bind();
	mSampler.BindPS(0);

	for (int i = 0; i < mBlurIterations; ++i)
	{
		// Horizontal blur
		mBlurRenderTarget.BeginRender();
		mBloomRenderTarget.BindPS(0);
		mGaussianBlurPixelShaderX.Bind();
		mScreenMeshBuffer.Render();
		Texture::UnbindPS(0);
		mBlurRenderTarget.EndRender();

		// Vertical blur
		mBloomRenderTarget.BeginRender();
		mBlurRenderTarget.BindPS(0);
		mGaussianBlurPixelShaderY.Bind();
		mScreenMeshBuffer.Render();
		Texture::UnbindPS(0);
		mBloomRenderTarget.EndRender();
	}
}

void GameState::PostProcess()
{
	mBloomVertexShader.Bind();
	mBloomPixelShader.Bind();

	mSampler.BindVS(0);

	mBaseRenderTarget.BindPS(0);
	mBloomRenderTarget.BindPS(1);

	mRenderTarger.BindPS(0);
	mScreenMeshBuffer.Render();
	mRenderTarger.UnbindPS(0);
}