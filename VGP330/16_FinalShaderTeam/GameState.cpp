#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);
	// Terrain
	ModelLoader::LoadObj(L"../../Assets/Models/Mountain/terrain.obj", 700.0f, mTerrainMesh);
	mTerrainMeshBuffer.Initialize(mTerrainMesh);
	mTerrainTexrures.Initialize("../../Assets/Models/Mountain/file_.jpg");


	// AirBalloon
	ModelLoader::LoadObj(L"../../Assets/Models/AirBallon/airBalloon.obj", 0.01f, mAirBalloonMesh0);
	mAirBalloonMeshBuffer0.Initialize(mAirBalloonMesh0);
	mAirBalloonTexrure0.Initialize("../../Assets/Models/AirBallon/top.png");

	mAirBalloonMeshBuffer1.Initialize(mAirBalloonMesh0);
	mAirBalloonTexrure1.Initialize("../../Assets/Models/AirBallon/top6.png");

	mAirBalloonMeshBuffer2.Initialize(mAirBalloonMesh0);
	mAirBalloonTexrure2.Initialize("../../Assets/Models/AirBallon/top2.png");

	mAirBalloonMeshBuffer3.Initialize(mAirBalloonMesh0);
	mAirBalloonTexrure3.Initialize("../../Assets/Models/AirBallon/top3.png");

	mAirBalloonMeshBuffer4.Initialize(mAirBalloonMesh0);
	mAirBalloonTexrure4.Initialize("../../Assets/Models/AirBallon/top4.png");

	mAirBalloonMeshBuffer5.Initialize(mAirBalloonMesh0);
	mAirBalloonTexrure5.Initialize("../../Assets/Models/AirBallon/top1.png");
	

	mAirBalloonMeshBuffer6.Initialize(mAirBalloonMesh0);
	mAirBalloonTexrure6.Initialize("../../Assets/Models/AirBallon/top5.png");

	//AirBalloon

	mTransformBuffer.Initialize();
	
	mTerrainPosition = {0.0f,-5.0f,0.0f};
	mDefaultCamera.SetPosition({ 32.1472855f,31.8910484f,122.345062f });
	mDefaultCamera.SetDirection({ -0.06837695f,-0.062366f,-0.99570f });
	mDefaultCamera.SetNearPlane(0.001f);

	

	SetAnimation();

	mLightCamera.SetNearPlane(0.01f);
	mLightCamera.SetFarPlane(1000.0f);
	mLightCamera.SetAspectRation(15.0f);

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






	const wchar_t* shaderFileNames = L"../../Assets/Shaders/Standard.fx";
	const wchar_t* shaderFileNames1 = L"../../Assets/Shaders/GaussianBlur.fx";
	const wchar_t* shaderFileNames2 = L"../../Assets/Shaders/DoLightTexturing.fx";
	const wchar_t* shaderFileNames3 = L"../../Assets/Shaders/DoTexturing.fx";


	mPixelShader.Initialize(shaderFileNames);
	mVertexShader.Initialize(shaderFileNames, Vertex::Format);


	mTexturePixelShader.Initialize(shaderFileNames3);
	mTextureVertexShader.Initialize(shaderFileNames3, VertexPX::Format);

	mOilPaintingVertexShader.Initialize(L"../../Assets/Shaders/PostProcessOilPainting_S.fx", VertexPX::Format);
	mOilPaintingPixelShader.Initialize(L"../../Assets/Shaders/PostProcessOilPainting_S.fx");
	mOilSettingBuffer.Initialize();
	mActiveSettingBuffer.Initialize();

	constexpr uint32_t depthMapSize = 4096;
	mDepthRenderTarget.Initialize(depthMapSize, depthMapSize,Texture::Format::RGBA_F32);

	mDepthMapVertexShader.Initialize(L"../../Assets/Shaders/DepthMap.fx", Vertex::Format);
	mDepthMapPixelShader.Initialize(L"../../Assets/Shaders/DepthMap.fx");
	mDepthMapBuffer.Initialize();

	mTransformBuffer.Initialize();
	mTransformCloudBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();


	mDirectionLight.direction = Math::Normalize({ -0.3450202351f,-0.662131011f,-0.665239573f });
	mDirectionLight.ambient = { 0.5f };
	mDirectionLight.diffuse = { 0.784f };
	mDirectionLight.specular = { 0.858f };
	mMaterial.ambient = { 0.5f };
	mMaterial.diffuse = { 0.784f };
	mMaterial.specular = { 0.39f };
	mMaterial.power = 1.999f;


	mSkybox.Initialize("../../Assets/Images/Skybox_04.jpg");

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Clamp);
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
	mActiveSettingBuffer.Terminate();
	mOilSettingBuffer.Terminate();
	mOilPaintingPixelShader.Terminate();
	mOilPaintingVertexShader.Terminate();
	mTextureVertexShader.Terminate();
	mTexturePixelShader.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();


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
	mDepthRenderTarget.Terminate();

	mBloomRenderTarget.Terminate();
	mBaseRenderTarget.Terminate();
	mDepthRenderTarget.Terminate();

	mTransformBuffer.Terminate();

	mAirBalloonTexrure6.Terminate();
	mAirBalloonMeshBuffer6.Terminate();

	mAirBalloonTexrure5.Terminate();
	mAirBalloonMeshBuffer5.Terminate();

	mAirBalloonTexrure4.Terminate();
	mAirBalloonMeshBuffer4.Terminate();

	mAirBalloonTexrure3.Terminate();
	mAirBalloonMeshBuffer3.Terminate();

	mAirBalloonTexrure2.Terminate();
	mAirBalloonMeshBuffer2.Terminate();


	mAirBalloonTexrure1.Terminate();
	mAirBalloonMeshBuffer1.Terminate();


	mAirBalloonTexrure0.Terminate();
	mAirBalloonMeshBuffer0.Terminate();

	mTerrainTexrures.Terminate();
	mTerrainMeshBuffer.Terminate();
}
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();



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

	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mActiveCamera->Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mActiveCamera->Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	//Synchronize the light camera to the directional light (cannot look straight up or down)
	mLightCamera.SetDirection(mDirectionLight.direction);
	KWSE::Math::Vector3 newCamaraPosition = -mLightCamera.GetDirection()*mLightCameraDistance;
	mLightCamera.SetPosition(newCamaraPosition);



	mFPS = 1.0f / deltaTime;

	// AirBalloon animation time
	mAnimationTimer += deltaTime;
	mAnimationTimer1 += deltaTime;
	mAnimationTimer2 += deltaTime;
	mAnimationTimer3 += deltaTime;
	mAnimationTimer4 += deltaTime;
	mAnimationTimer5 += deltaTime;
	mAnimationTimer6 += deltaTime;

	// AirBalloon animation time
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
	if (ImGui::CollapsingHeader("Post Processing Effects"))
	{
		bool mosaicactive = mActiveSetting.mosaicActive == 1.0f;
		if (ImGui::Checkbox("Mosaica Effect", &mosaicactive))
		{
			mActiveSetting.mosaicActive = mosaicactive ? 1.0f : 0.0f;
		}

		bool heatactive = mActiveSetting.heatActive == 1.0f;
		if (ImGui::Checkbox("HeatMap Effect", &heatactive))
		{
			mActiveSetting.heatActive = heatactive ? 1.0f : 0.0f;
		}

		bool oilactive = mActiveSetting.oilActive == 1.0f;
		if (ImGui::Checkbox("OilPainting Effect", &oilactive))
		{
			mActiveSetting.oilActive = oilactive ? 1.0f : 0.0f;
		}
	}
	if (ImGui::CollapsingHeader("OilSetting"))
	{
		ImGui::DragFloat("Screen Size Scale", &mOilSetting.screenSizeScale, 0.1f, 0.0f, 1000.0f);
		ImGui::DragFloat("Brush Radius", &mOilSetting.paintRadius, 1.0f, 3.0f, 9.0f );
		//ImGui::DragFloat("Intensity", &mOilSetting.minSigma, 0.0f, 0.0f, 1.0f );
		bool _sizeWeight = mOilSetting.sizeWeight == 1.0f;
		//if (ImGui::Checkbox("Oil Stretch Width", &_sizeWeight))
		//{
		//	mOilSetting.sizeWeight = _sizeWeight ? 1.0f : 0.0f;
		//}
	}
	if (ImGui::CollapsingHeader("Blur"))
	{
		ImGui::DragInt("Blur Iterations", &mBlurIterations, 1, 0, 100);
		ImGui::DragFloat("Blur Saturation", &mBlurSaturation, 0.001f, 0.0f, 1.0f);
	}
	if (ImGui::CollapsingHeader("DepthMap"))
	{
		ImGui::Image(mDepthRenderTarget.GetRawData(), { 200.0f,200.0f });
	}
	ImGui::End();

	//ImGui::ShowDemoWindow();

}


void GameState::RenderDepthMap()
{
	mDepthRenderTarget.BeginRender(Colors::Black);
	//Draw all the shadow casters using light camera.
	auto matView = mLightCamera.GetViewMatrix();
	auto matProj = mLightCamera.GetProjectionMatrix();

	mDepthMapBuffer.BindVS(0);

	KWSE::Math::Vector3     pos = mAnimation.GetPosition(mAnimationTimer);
	KWSE::Math::Quaternion  rot = mAnimation.GetRotation(mAnimationTimer);
	KWSE::Math::Vector3     pos1 = mAnimation1.GetPosition(mAnimationTimer1);
	KWSE::Math::Quaternion  rot1 = mAnimation1.GetRotation(mAnimationTimer1);
	KWSE::Math::Vector3     pos2 = mAnimation2.GetPosition(mAnimationTimer2);
	KWSE::Math::Quaternion  rot2 = mAnimation2.GetRotation(mAnimationTimer2);
	KWSE::Math::Vector3     pos3 = mAnimation3.GetPosition(mAnimationTimer3);
	KWSE::Math::Quaternion  rot3 = mAnimation3.GetRotation(mAnimationTimer3);
	KWSE::Math::Vector3     pos4 = mAnimation4.GetPosition(mAnimationTimer4);
	KWSE::Math::Quaternion  rot4 = mAnimation4.GetRotation(mAnimationTimer4);
	KWSE::Math::Vector3     pos5 = mAnimation5.GetPosition(mAnimationTimer5);
	KWSE::Math::Quaternion  rot5 = mAnimation5.GetRotation(mAnimationTimer5);
	KWSE::Math::Vector3     pos6 = mAnimation6.GetPosition(mAnimationTimer6);
	KWSE::Math::Quaternion  rot6 = mAnimation6.GetRotation(mAnimationTimer6);

	//airballoon 0
	auto matWorld = Matrix4::RotationQuaternion(rot)*Matrix4::Translation(pos)*Matrix4::Scaling(1.0f);
	auto wvp =Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();

	mAirBalloonTexrure0.BindPS(0);
	mSampler.BindVS(0);
	mAirBalloonMeshBuffer0.Render();
	//airballoon 1
	matWorld = Matrix4::RotationQuaternion(rot1)*Matrix4::Translation(pos1)*Matrix4::Scaling(1.0f);
	wvp = Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();
	mAirBalloonTexrure1.BindPS(0);
	mSampler.BindVS(0);
	mAirBalloonMeshBuffer1.Render();
	//airballoon 2
	matWorld =Matrix4::RotationQuaternion(rot2)*Matrix4::Translation(pos2)*Matrix4::Scaling(1.0f);
	wvp = Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();
	mAirBalloonTexrure2.BindPS(0);
	mSampler.BindVS(0);
	mAirBalloonMeshBuffer2.Render();
	//airballoon 3
	matWorld = Matrix4::RotationQuaternion(rot3)*Matrix4::Translation(pos3)*Matrix4::Scaling(1.0f);
	wvp = Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();
	mAirBalloonTexrure3.BindPS(0);
	mSampler.BindVS(0);
	mAirBalloonMeshBuffer3.Render();
	//airballoon 4
	matWorld = Matrix4::RotationQuaternion(rot4)*Matrix4::Translation(pos4)*Matrix4::Scaling(1.0f);
	wvp = Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();
	mAirBalloonTexrure4.BindPS(0);
	mSampler.BindVS(0);
	mAirBalloonMeshBuffer4.Render();
	//airballoon 5
	matWorld = Matrix4::RotationQuaternion(rot5)*Matrix4::Translation(pos5)*Matrix4::Scaling(1.0f);
	wvp = Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();
	mAirBalloonTexrure5.BindPS(0);
	mSampler.BindVS(0);
	mAirBalloonMeshBuffer5.Render();
	//airballoon 6
	matWorld = Matrix4::RotationQuaternion(rot6)*Matrix4::Translation(pos6)*Matrix4::Scaling(1.0f);
	wvp = Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();
	mAirBalloonTexrure6.BindPS(0);
	mSampler.BindVS(0);
	mAirBalloonMeshBuffer6.Render();

	mDepthRenderTarget.EndRender();

}

void GameState::RenderScene()
{
	mRenderTarger.BeginRender();
	mUseWireframe ? mRasterizerStateWireframe.Set() : mRasterizerStateWireframe.Clear();

	auto matView = mActiveCamera->GetViewMatrix();
	auto matProj = mActiveCamera->GetProjectionMatrix();

	auto matViewLight = mLightCamera.GetViewMatrix();
	auto matProjLight = mLightCamera.GetProjectionMatrix();

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

	auto matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) *Matrix4::Scaling(1.0f);//*(KWSE::Math::Matrix4::RotationX(mRotation.x*5.0f) * Matrix4::RotationY(mRotation.y) *Matrix4::RotationZ(mRotation.z));//* Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
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

	//const KWSE::Math::Vector3 pos = mAnimation.GetPosition(mAnimationTimer);
	//const auto rot = mAnimation.GetRotation(mAnimationTimer);
	//const auto pos1 = mAnimation1.GetPosition(mAnimationTimer1);
	//const auto rot1 = mAnimation1.GetRotation(mAnimationTimer1);
	//const auto pos2 = mAnimation2.GetPosition(mAnimationTimer2);
	//const auto rot2 = mAnimation2.GetRotation(mAnimationTimer2);
	//const auto pos3 = mAnimation3.GetPosition(mAnimationTimer3);
	//const auto rot3 = mAnimation3.GetRotation(mAnimationTimer3);
	//const auto pos4 = mAnimation4.GetPosition(mAnimationTimer4);
	//const auto rot4 = mAnimation4.GetRotation(mAnimationTimer4);
	//const auto pos5 = mAnimation5.GetPosition(mAnimationTimer5);
	//const auto rot5 = mAnimation5.GetRotation(mAnimationTimer5);
	//const auto pos6 = mAnimation6.GetPosition(mAnimationTimer6);
	//const auto rot6 = mAnimation6.GetRotation(mAnimationTimer6);

	KWSE::Math::Vector3    pos = mAnimation.GetPosition(mAnimationTimer);
	KWSE::Math::Quaternion rot = mAnimation.GetRotation(mAnimationTimer);
	KWSE::Math::Vector3    pos1 = mAnimation1.GetPosition(mAnimationTimer1);
	KWSE::Math::Quaternion rot1 = mAnimation1.GetRotation(mAnimationTimer1);
	KWSE::Math::Vector3    pos2 = mAnimation2.GetPosition(mAnimationTimer2);
	KWSE::Math::Quaternion rot2 = mAnimation2.GetRotation(mAnimationTimer2);
	KWSE::Math::Vector3    pos3 = mAnimation3.GetPosition(mAnimationTimer3);
	KWSE::Math::Quaternion rot3 = mAnimation3.GetRotation(mAnimationTimer3);
	KWSE::Math::Vector3    pos4 = mAnimation4.GetPosition(mAnimationTimer4);
	KWSE::Math::Quaternion rot4 = mAnimation4.GetRotation(mAnimationTimer4);
	KWSE::Math::Vector3    pos5 = mAnimation5.GetPosition(mAnimationTimer5);
	KWSE::Math::Quaternion rot5 = mAnimation5.GetRotation(mAnimationTimer5);
	KWSE::Math::Vector3    pos6 = mAnimation6.GetPosition(mAnimationTimer6);
	KWSE::Math::Quaternion rot6 = mAnimation6.GetRotation(mAnimationTimer6);

	// Air Balloon0
	matWorld = Matrix4::RotationQuaternion(rot)*Matrix4::Translation(pos)*Matrix4::Scaling(1.0f);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mAirBalloonTexrure0.BindPS(0);	
	mAirBalloonMeshBuffer0.Render();
	// Air Balloon1
	matWorld = Matrix4::RotationQuaternion(rot1)*Matrix4::Translation(pos1)*Matrix4::Scaling(1.0f);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mAirBalloonTexrure1.BindPS(0);
	mAirBalloonMeshBuffer1.Render();
	// Air Balloon2
	matWorld = Matrix4::RotationQuaternion(rot2)*Matrix4::Translation(pos2)*Matrix4::Scaling(1.0f);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mAirBalloonTexrure2.BindPS(0);
	mAirBalloonMeshBuffer2.Render();
	// Air Balloon3
	matWorld = Matrix4::RotationQuaternion(rot3)*Matrix4::Translation(pos3)*Matrix4::Scaling(1.0f);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mAirBalloonTexrure3.BindPS(0);
	mAirBalloonMeshBuffer3.Render();
	// Air Balloon4
	matWorld = Matrix4::RotationQuaternion(rot4)*Matrix4::Translation(pos4)*Matrix4::Scaling(1.0f);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mAirBalloonTexrure4.BindPS(0);
	mAirBalloonMeshBuffer4.Render();
	// Air Balloon5
	matWorld = Matrix4::RotationQuaternion(rot5)*Matrix4::Translation(pos5)*Matrix4::Scaling(1.0f);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mAirBalloonTexrure5.BindPS(0);
	mAirBalloonMeshBuffer5.Render();
	// Air Balloon6
	matWorld = Matrix4::RotationQuaternion(rot6)*Matrix4::Translation(pos6)*Matrix4::Scaling(1.0f);
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mAirBalloonTexrure6.BindPS(0);
	mAirBalloonMeshBuffer6.Render();

	mDepthRenderTarget.BindPS(4);
	// Terrain
	matWorld =Matrix4::Translation({ mTerrainPosition.x,mTerrainPosition.y,mTerrainPosition.z });
	data.world = Transpose(matWorld);
	data.wvp[0] = Transpose(matWorld*(matView)*matProj);
	data.wvp[1] = Transpose(matWorld*(matViewLight)*matProjLight);
	mTransformBuffer.Update(data);
	mTerrainTexrures.BindPS(0);
	mTerrainMeshBuffer.Render();



	Texture::UnbindPS(4);

	mRenderTarger.EndRender();

}

void GameState::RenderBrightness()
{
	mBloomRenderTarget.BeginRender();

	Matrix4 matView = mActiveCamera->GetViewMatrix();
	Matrix4 matProj = mActiveCamera->GetProjectionMatrix();

	Matrix4 matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f });// *Matrix4::RotationX(mRotation.x*5.0f) * Matrix4::RotationY(mRotation.y)*Matrix4::RotationZ(mRotation.z);

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

	mSampler.BindPS(0);

	for (int i = 0; i < mBlurIterations; ++i)
	{
		// Horizontal blur
		mBlurRenderTarget.BeginRender();
		mBloomRenderTarget.BindPS(0);
		mScreenMeshBuffer.Render();
		Texture::UnbindPS(0);
		mBlurRenderTarget.EndRender();

		// Vertical blur
		mBloomRenderTarget.BeginRender();
		mBlurRenderTarget.BindPS(0);
		mScreenMeshBuffer.Render();
		Texture::UnbindPS(0);
		mBloomRenderTarget.EndRender();
	}
}

void GameState::PostProcess()
{
	mOilPaintingVertexShader.Bind();
	mOilPaintingPixelShader.Bind();


	mOilSettingBuffer.Update(mOilSetting);
	mOilSettingBuffer.BindPS(0);
	mActiveSettingBuffer.Update(mActiveSetting);
	mActiveSettingBuffer.BindPS(1);

	mSampler.BindVS(0);

	mBaseRenderTarget.BindPS(0);
	mBloomRenderTarget.BindPS(1);

	mRenderTarger.BindPS(0);
	mScreenMeshBuffer.Render();
	mRenderTarger.UnbindPS(0);
}



void GameState::SetAnimation()
{
	mAnimation = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 15.0f,1.1f,1.0f })
		.AddRotationKey({ Math::Quaternion::RotationAxis(Vector3(0.0f,0.0f,0.0f),0.0f) })
		//.AddScaleKey({ 1.0f,1.0f,1.0f })
		.AdvanceTime(100.0f)
		.AddPositionKey({ 15.0f,100.0f,1.0f })
		.AddRotationKey({ Math::Quaternion::RotationLook(Vector3(0.0f,0.0f,-5.0f))})
		.AdvanceTime(100.0f)
		.AddPositionKey({ 15.0f,100.0f,0.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-100.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-200.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-300.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-400.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-500.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-600.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-700.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-800.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 15.0f,100.0f,-900.0f })
		.AdvanceTime(10000.00)
		.SetLooping(true)
		.Get();


	mAnimation1 = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 30.0f,1.1f,1.0f })
		.AddRotationKey({ Math::Quaternion::RotationAxis(Vector3(0.0f,0.0f,0.0f),0.0f) })
		//.AddScaleKey({ 1.0f,1.0f,1.0f })
		.AdvanceTime(100.0f)
		.AddPositionKey({ 30.0f,60.0f,1.0f })
		.AddRotationKey({ Math::Quaternion::RotationLook(Vector3(0.0f,0.0f,-5.0f)) })
		.AdvanceTime(100.0f)
		.AddPositionKey({ 30.0f,60.0f,0.0f })
		.AdvanceTime(100.0f)
		.AddPositionKey({ 30.0f,60.0f,-100.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-200.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-300.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-400.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-500.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-600.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-700.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-800.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 30.0f,60.0f,-900.0f })
		.AdvanceTime(10000.00)
		.SetLooping(true)
		.Get();

	mAnimation2 = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 50.0f,1.1f,-100.0f })
		.AddRotationKey({ Math::Quaternion::RotationAxis(Vector3(0.0f,0.0f,0.0f),0.0f) })
		//.AddScaleKey({ 1.0f,1.0f,1.0f })
		.AdvanceTime(150.0f)
		.AddPositionKey({ 50.0f,55.0f,-100.0f })
		.AddRotationKey({ Math::Quaternion::RotationLook(Vector3(0.0f,0.0f,-5.0f)) })
		.AdvanceTime(15000.0f)
		.AddPositionKey({ 50.0f,55.0f,-200.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 50.0f,55.0f,-300.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 50.0f,55.0f,-400.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 50.0f,55.0f,-500.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 50.0f,55.0f,-600.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 50.0f,55.0f,-700.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 50.0f,55.0f,-800.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 50.0f,55.0f,-900.0f })
		.AdvanceTime(10000.00)
		.SetLooping(true)
		.Get();
	mAnimation3 = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 40.0f,1.1f,40.0f })
		.AddRotationKey({ Math::Quaternion::RotationAxis(Vector3(0.0f,0.0f,0.0f),0.0f) })
		//.AddScaleKey({ 1.0f,1.0f,1.0f })
		.AdvanceTime(100.0f)
		.AddPositionKey({ 40.0f,60.0f,40.0f })
		.AddRotationKey({ Math::Quaternion::RotationLook(Vector3(0.0f,0.0f,-5.0f)) })
		.AdvanceTime(1000.0f)
		.AddPositionKey({ 40.0f,60.0f,0.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-100.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-200.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-300.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-400.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-500.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-600.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-700.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-800.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 40.0f,60.0f,-900.0f })
		.AdvanceTime(10000.00)
		.SetLooping(true)
		.Get();
	mAnimation4 = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 80.0f,1.1f,20.0f })
		.AddRotationKey({ Math::Quaternion::RotationAxis(Vector3(0.0f,0.0f,0.0f),0.0f) })
		//.AddScaleKey({ 1.0f,1.0f,1.0f })
		.AdvanceTime(50.0f)
		.AddPositionKey({ 80.0f,75.0f,20.0f })
		.AddRotationKey({ Math::Quaternion::RotationLook(Vector3(0.0f,0.0f,-1.0f)) })
		.AdvanceTime(50.0f)
		.AddPositionKey({ 80.0f,75.0f,0.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-100.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-200.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-300.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-400.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-500.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-600.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-700.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-800.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-900.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 80.0f,75.0f,-1000.0f })
		.AdvanceTime(10000.00)
		.SetLooping(true)
		.Get();
	mAnimation5 = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 10.0f,1.1f,55.0f })
		.AddRotationKey({ Math::Quaternion::RotationAxis(Vector3(0.0f,0.0f,0.0f),0.0f) })
		//.AddScaleKey({ 1.0f,1.0f,1.0f })
		.AdvanceTime(15.0f)
		.AddPositionKey({ 10.0f,60.0f,55.0f })
		.AddRotationKey({ Math::Quaternion::RotationLook(Vector3(0.0f,0.0f,-5.0f)) })
		.AdvanceTime(15.0f)
		.AddPositionKey({ 10.0f,60.0f,0.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-100.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-200.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-300.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-400.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-500.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-600.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-700.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-800.0f })
		.AdvanceTime(10000.00)
		.AddPositionKey({ 10.0f,60.0f,-900.0f })
		.AdvanceTime(10000.00)
		.SetLooping(true)
		.Get();
	mAnimation6 = AnimationBuilder()
		.SetTime(0.0f)
		.AddPositionKey({ 50.0f,1.1f,100.0f })
		.AddRotationKey({ Math::Quaternion::RotationAxis(Vector3(0.0f,0.0f,0.0f),0.0f) })
		//.AddScaleKey({ 1.0f,1.0f,1.0f })
		.AdvanceTime(10.0f)
		.AddPositionKey({ 50.0f,30.0f,100.0f })
		.AddRotationKey({ Math::Quaternion::RotationLook(Vector3(0.0f,0.0f,-5.0f)) })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,0.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-100.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-200.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-300.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-400.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-500.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-600.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-700.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-800.0f })
		.AdvanceTime(100.00)
		.AddPositionKey({ 50.0f,30.0f,-900.0f })
		.AdvanceTime(100.00)
		.SetLooping(true)
		.Get();
}