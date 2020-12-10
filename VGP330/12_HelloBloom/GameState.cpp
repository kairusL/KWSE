#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);


	mCamera.SetPosition({ 0.0f,0.0f,-15.0f });
	mCamera.SetDirection({ 0.0f,0.0f,1.0f });
	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(100.0f);

	mBaseRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight()
	);
	mBloomRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight()
	);
	mBlurRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight()
	);

	mRenderTarger.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight());


	mMesh = MeshBuilder::CreateSphere(1.5f, 256, 256);
	mMeshBuffer.Initialize(mMesh);


	mCloudMesh = MeshBuilder::CreateSpherePNX(1.52f, 256, 256);
	mCloudMeshBuffer.Initialize(mCloudMesh);

	mSunMesh = MeshBuilder::CreateSpherePX(5.0f, 256, 256);
	mSunMeshBuffer.Initialize(mSunMesh);

	mBlurSettingsBuffer.Initialize();


	const wchar_t* shaderFileNames = L"../../Assets/Shaders/DarkStandard.fx";
	const wchar_t* shaderFileNames1 = L"../../Assets/Shaders/GaussianBlur.fx";
	const wchar_t* shaderFileNames2 = L"../../Assets/Shaders/DoLightTexturing.fx";
	const wchar_t* shaderFileNames3 = L"../../Assets/Shaders/DoTexturing.fx";

	mGaussianBlurVertexShader.Initialize(shaderFileNames1, VertexPX::Format);
	mGaussianBlurPixelShaderX.Initialize(shaderFileNames1,"BlurXPS");
	mGaussianBlurPixelShaderY.Initialize(shaderFileNames1,"BlurYPS");


	mPixelShader.Initialize(shaderFileNames);
	mVertexShader.Initialize(shaderFileNames, Vertex::Format);

	mCloudPixelShader.Initialize(shaderFileNames2);
	mCloudVertexShader.Initialize(shaderFileNames2, VertexPNX::Format);

	mTexturePixelShader.Initialize(shaderFileNames3);
	mTextureVertexShader.Initialize(shaderFileNames3, VertexPX::Format);

	mBloomVertexShader.Initialize(L"../../Assets/Shaders/Bloom.fx", VertexPX::Format);
	mBloomPixelShader.Initialize(L"../../Assets/Shaders/Bloom.fx");
	
	mTransformBuffer.Initialize();
	mTransformCloudBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();
	mSunTransformBuffer.Initialize();


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
	mSunTexture.Initialize("../../Assets/Images/8k_sun.jpg");  // sun

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

	mSunTexture.Terminate();
	for (auto& texture : mTexture)
	{
		texture.Terminate();
	}
	mCloudTexture.Terminate();
	mSkybox.Terminate();
	mBloomPixelShader. Terminate();
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
	mSunTransformBuffer.Terminate();
	mSettingBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();

	mTransformCloudBuffer.Terminate();
	mTransformBuffer.Terminate();
	mSunMeshBuffer.Terminate();
	mCloudMeshBuffer.Terminate();
	mMeshBuffer.Terminate();
	mRenderTarger.Terminate();

	mBlurRenderTarget.Terminate();
	mBloomRenderTarget.Terminate();
	mBaseRenderTarget.Terminate();

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
	mCloudRotation += deltaTime * 0.1;
}
void GameState::Render()
{
	// Capture a Screen shot
	RenderScene();

	// Capture just the bright pixels for bloom - 2nd Pass
	RenderBrightness();

	// Apply Gaussian blur to the bloom pixels
	ApplyBlur();


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
 		ImGui::DragInt("Blur Iterations", &mBlurIterations, 1, 0, 100);
		ImGui::DragFloat("Blur Saturation", &mBlurSaturation, 0.001f, 0.0f, 1.0f);
 
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
	TransformDataTextureWithLight textureData;

	data.viewPosition = mCamera.GetPosition();
	textureData.viewPosition = mCamera.GetPosition();

	mSkybox.Render(mCamera);

	mSunTransformBuffer.Update(Matrix4::Identity);
	mSunTransformBuffer.BindVS(0);
	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	mSunTexture.BindPS(0);
	mSunMeshBuffer.Render();

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

	auto matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) *Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x*mCloudRotation*5.0f) * Matrix4::RotationY(mRotation.y*mCloudRotation) *Matrix4::RotationZ(mRotation.z*mCloudRotation));//* Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);

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
	//matWorld = Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x*mCloudRotation) * Matrix4::RotationY(mRotation.y*mCloudRotation) * Matrix4::RotationZ(mRotation.z*mCloudRotation));
	//Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) *Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x*mCloudRotation) * Matrix4::RotationY(mRotation.y*mCloudRotation) * Matrix4::RotationZ(mRotation.z*mCloudRotation));
	
	textureData.world = Transpose(matWorld);
	textureData.wvp = KWSE::Math::Transpose(matWorld*matView*matProj);
	mTransformCloudBuffer.Update(textureData);

	mTransformCloudBuffer.BindVS(0);
	mCloudTexture.BindPS(0);
	mBlendState.Set();

	mCloudMeshBuffer.Render();

	BlendState::ClearState();



	//SimpleDraw::AddLine(Vector3::Zero, Vector3::XAxis, Colors::Red);
	//SimpleDraw::AddLine(Vector3::Zero, Vector3::YAxis, Colors::Green);
	//SimpleDraw::AddLine(Vector3::Zero, Vector3::ZAxis, Colors::Blue);
	//

	//SimpleDraw::AddTransform(Matrix4::Identity);





	SimpleDraw::Render(mCamera);
	mRenderTarger.EndRender();

}

void GameState::RenderBrightness()
{
	mBloomRenderTarget.BeginRender();

	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();

	Matrix4 matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) * Matrix4::RotationX(mRotation.x*mCloudRotation*5.0f) * Matrix4::RotationY(mRotation.y*mCloudRotation)*Matrix4::RotationZ(mRotation.z*mCloudRotation);
	mSunTransformBuffer.Update(Transpose(matWorld * matView * matProj));
	mSunTransformBuffer.BindVS(0);

	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	mSampler.BindPS(0);

	mBlankTexture.BindPS(0);
	mMeshBuffer.Render();

	mSunTransformBuffer.Update(Transpose(matView * matProj));

	mSunTexture.BindPS(0);
	mSunMeshBuffer.Render();

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


//#include "GameState.h"
//
//using namespace KWSE::Graphics;
//using namespace KWSE::Input;
//using namespace KWSE::Math;
//
//void GameState::Initialize()
//{
//	GraphicsSystem::Get()->SetClearColor(Colors::Black);
//
//	mCamera.SetPosition({ 0.0f, 0.0f, -12.0f });
//
//	mBaseRenderTarget.Initialize(
//		GraphicsSystem::Get()->GetBackBufferWidth(),
//		GraphicsSystem::Get()->GetBackBufferHeight()
//	);
//	mBloomRenderTarget.Initialize(
//		GraphicsSystem::Get()->GetBackBufferWidth(),
//		GraphicsSystem::Get()->GetBackBufferHeight()
//	);
//	mBlurRenderTarget.Initialize(
//		GraphicsSystem::Get()->GetBackBufferWidth(),
//		GraphicsSystem::Get()->GetBackBufferHeight()
//	);
//
//	mEarthMesh = MeshBuilder::CreateSphere(1.0f,256, 256);
//	mEarthMeshBuffer.Initialize(mEarthMesh);
//
//	mCloudMesh = MeshBuilder::CreateSpherePNX(1.01f, 256, 256);
//	mCloudMeshBuffer.Initialize(mCloudMesh);
//
//	mSunMesh = MeshBuilder::CreateSpherePX(5.0f,256, 256);
//	mSunMeshBuffer.Initialize(mSunMesh);
//
//	mTexturingVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VertexPX::Format);
//	mTexturingPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");
//
//	mEarthVertexShader.Initialize(L"../../Assets/Shaders/Standard.fx", Vertex::Format);
//	mEarthPixelShader.Initialize(L"../../Assets/Shaders/Standard.fx");
//
//	mCloudPixelShader.Initialize(L"../../Assets/Shaders/DoLightTexturing.fx");
//	mCloudVertexShader.Initialize(L"../../Assets/Shaders/DoLightTexturing.fx", VertexPNX::Format);
//
//	mGaussianBlurVertexShader.Initialize(L"../../Assets/Shaders/GaussianBlur.fx", VertexPX::Format);
//	mGaussianBlurXPixelShader.Initialize(L"../../Assets/Shaders/GaussianBlur.fx", "BlurXPS");
//	mGaussianBlurYPixelShader.Initialize(L"../../Assets/Shaders/GaussianBlur.fx", "BlurYPS");
//
//	mBloomVertexShader.Initialize(L"../../Assets/Shaders/Bloom.fx", VertexPX::Format);
//	mBloomPixelShader.Initialize(L"../../Assets/Shaders/Bloom.fx");
//
//	mBlendState.Initialize(KWSE::Graphics::BlendState::Mode::Additive);
//
//
//	mTransformCloudBuffer.Initialize();
//	mEarthTransformBuffer.Initialize();
//	mTexturingTransformBuffer.Initialize();
//	mBlurSettingsBuffer.Initialize();
//	mLightBuffer.Initialize();
//	mMaterialBuffer.Initialize();
//	mSettingBuffer.Initialize();
//
//	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
//	mDirectionalLight.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
//	mDirectionalLight.diffuse = { 0.9f, 0.9f, 0.9f, 1.0f };
//	mDirectionalLight.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
//
//	mMaterial.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
//	mMaterial.diffuse = { 0.85f, 0.85f, 0.85f, 1.0f };
//	mMaterial.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
//	mMaterial.power = 10.0f;
//
//	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
//	mEarthDiffuseTexture.Initialize(L"../../Assets/Images/earth.jpg");
//	mEarthSpecularTexture.Initialize(L"../../Assets/Images/earth_spec.jpg");
//	mEarthDisplacmentTexture.Initialize(L"../../Assets/Images/earth_bump.jpg");
//	mEarthNormalTexture.Initialize(L"../../Assets/Images/earth_normal.jpg");
//	mSunDiffuseTexture.Initialize(L"../../Assets/Images/8k_sun.jpg");
//
//	//
//	// (-1,+1)---------------(+1,+1)
//	//    |          ^          |
//	//    |          +->        |
//	//    |                     |
//	// (-1,-1)---------------(+1,-1)
//	//
//	mScreenMesh.vertices.push_back({ {-1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
//	mScreenMesh.vertices.push_back({ {-1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f } });
//	mScreenMesh.vertices.push_back({ {+1.0f, +1.0f, 0.0f }, { 1.0f, 0.0f } });
//	mScreenMesh.vertices.push_back({ {+1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });
//
//	mScreenMesh.indices.push_back(0);
//	mScreenMesh.indices.push_back(1);
//	mScreenMesh.indices.push_back(2);
//
//	mScreenMesh.indices.push_back(0);
//	mScreenMesh.indices.push_back(2);
//	mScreenMesh.indices.push_back(3);
//
//	mScreenMeshBuffer.Initialize(mScreenMesh);
//}
//
//void GameState::Terminate()
//{
//	mScreenMeshBuffer.Terminate();
//	mSunDiffuseTexture.Terminate();
//	mEarthNormalTexture.Terminate();
//	mEarthDisplacmentTexture.Terminate();
//	mEarthSpecularTexture.Terminate();
//	mEarthDiffuseTexture.Terminate();
//	mSampler.Terminate();
//	mSettingBuffer.Terminate();
//	mMaterialBuffer.Terminate();
//	mLightBuffer.Terminate();
//	mBlurSettingsBuffer.Terminate();
//	mBlendState.Terminate();
//	mTexturingTransformBuffer.Terminate();
//	mTransformCloudBuffer.Terminate();
//	mEarthTransformBuffer.Terminate();
//	mBloomPixelShader.Terminate();
//	mBloomVertexShader.Terminate();
//	mGaussianBlurYPixelShader.Terminate();
//	mGaussianBlurXPixelShader.Terminate();
//	mGaussianBlurVertexShader.Terminate();
//	mCloudVertexShader.Terminate();
//	mCloudPixelShader.Terminate();
//	mEarthPixelShader.Terminate();
//	mEarthVertexShader.Terminate();
//	mTexturingPixelShader.Terminate();
//	mTexturingVertexShader.Terminate();
//	mCloudMeshBuffer.Terminate();
//	mSunMeshBuffer.Terminate();
//	mEarthMeshBuffer.Terminate();
//	mBlurRenderTarget.Terminate();
//	mBloomRenderTarget.Terminate();
//	mBaseRenderTarget.Terminate();
//}
//
//void GameState::Update(float deltaTime)
//{
//	mFPS = 1.0f / deltaTime;
//
//	auto inputSystem = InputSystem::Get();
//
//	if (inputSystem->IsKeyDown(KeyCode::LEFT))
//		mRotation.y += deltaTime;
//	if (inputSystem->IsKeyDown(KeyCode::RIGHT))
//		mRotation.y -= deltaTime;
//
//	if (inputSystem->IsKeyDown(KeyCode::UP))
//		mRotation.x += deltaTime;
//	if (inputSystem->IsKeyDown(KeyCode::DOWN))
//		mRotation.x -= deltaTime;
//
//	const float moveSpeed = 10.0f;
//	const float turnSpeed = 10.0f * Constants::DegToRad;
//	if (inputSystem->IsKeyDown(KeyCode::W))
//		mCamera.Walk(moveSpeed * deltaTime);
//	if (inputSystem->IsKeyDown(KeyCode::S))
//		mCamera.Walk(-moveSpeed * deltaTime);
//	if (inputSystem->IsKeyDown(KeyCode::D))
//		mCamera.Strafe(moveSpeed * deltaTime);
//	if (inputSystem->IsKeyDown(KeyCode::A))
//		mCamera.Strafe(-moveSpeed * deltaTime);
//	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
//	{
//		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
//		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
//	}
//}
//
//void GameState::Render()
//{
//	// Capture a screen shot - 1st Pass
//	RenderScene();
//
//	// Capture just the bright pixels for bloom - 2nd Pass
//	RenderBrightness();
//	
//	// Apply Gaussian blur to the bloom pixels
//	ApplyBlur();
//	
//	// Composite both textures - 3rd Pass
//	PostProcess();
//}
//
//void GameState::DebugUI()
//{
//	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
//	ImGui::Text("fps: %f", mFPS);
//	if (ImGui::DragFloat3("Light Direction", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
//		mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
//	ImGui::ColorEdit3("Light Ambient", &mDirectionalLight.ambient.x);
//	ImGui::ColorEdit3("Light Diffuse", &mDirectionalLight.diffuse.x);
//	ImGui::ColorEdit3("Light Specular", &mDirectionalLight.specular.x);
//	ImGui::ColorEdit3("Material Ambient", &mMaterial.ambient.x);
//	ImGui::ColorEdit3("Material Diffuse", &mMaterial.diffuse.x);
//	ImGui::ColorEdit3("Material Specular", &mMaterial.specular.x);
//	ImGui::DragFloat("Material Power", &mMaterial.power, 0.1f, 1.0f, 100.0f);
//	ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);
//
//	if (ImGui::CollapsingHeader("Setting"))
//	{
//		ImGui::DragFloat("Displacement Weight", &mSetting.displacementWeight, 0.1f, 0.0f, 100.0f);
//
//		if (ImGui::Checkbox("Normal", &mNormal))
//		{
//			mSetting.normalWeight = mNormal ? 1.0f : 0.0f;
//		}
//		if (ImGui::Checkbox("Specular", &mSpecular))
//		{
//			mSetting.specularWeight = mSpecular ? 1.0f : 0.0f;
//		}
//	}
//
//
//	ImGui::DragInt("Blur Iterations", &mBlurIterations, 1, 0, 100);
//	ImGui::DragFloat("Blur Saturation", &mBlurSaturation, 0.001f, 0.0f, 1.0f);
//	ImGui::End();
//}
//
//void GameState::RenderScene()
//{
//	mBaseRenderTarget.BeginRender();
//
//	Matrix4 matView = mCamera.GetViewMatrix();
//	Matrix4 matProj = mCamera.GetProjectionMatrix();
//
//	EarthTransformData earthTransformData;
//	earthTransformData.viewPosition = mCamera.GetPosition();
//	mEarthTransformBuffer.BindVS(0);
//	mEarthTransformBuffer.BindPS(0);
//
//	mLightBuffer.Update(mDirectionalLight);
//	mLightBuffer.BindVS(1);
//	mLightBuffer.BindPS(1);
//
//	mMaterialBuffer.Update(mMaterial);
//	mMaterialBuffer.BindVS(2);
//	mMaterialBuffer.BindPS(2);
//
//	Matrix4 matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) * Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
//	earthTransformData.world = Transpose(matWorld);
//	earthTransformData.wvp = Transpose(matWorld * matView * matProj);
//	mEarthTransformBuffer.Update(earthTransformData);
//
//	mEarthVertexShader.Bind();
//	mEarthPixelShader.Bind();
//
//	mSampler.BindVS(0);
//	mSampler.BindPS(0);
//
//	mEarthDiffuseTexture.BindPS(0);
//	mEarthSpecularTexture.BindPS(1);
//	mEarthDisplacmentTexture.BindVS(2);
//	mEarthNormalTexture.BindPS(3);
//
//	mEarthMeshBuffer.Render();
//
//	mTexturingTransformBuffer.Update(Transpose(matView * matProj));
//	mTexturingTransformBuffer.BindVS(0);
//
//	mTexturingVertexShader.Bind();
//	mTexturingPixelShader.Bind();
//
//	TransformDataTextureWithLight textureData;
//
//	mCloudPixelShader.Bind();
//	mCloudVertexShader.Bind();
//	textureData.world = Transpose(matWorld);
//	textureData.wvp = KWSE::Math::Transpose(matWorld*matView*matProj);
//	mTransformCloudBuffer.Update(textureData);
//
//	mTransformCloudBuffer.BindVS(0);
//	mCloudTexture.BindPS(0);
//	mBlendState.Set();
//
//	mCloudMeshBuffer.Render();
//
//	BlendState::ClearState();
//
//	mSunDiffuseTexture.BindPS(0);
//	mSunMeshBuffer.Render();
//
//	mSettingBuffer.Update(mSetting);
//	mSettingBuffer.BindVS(3);
//	mSettingBuffer.BindPS(3);
//
//	mBaseRenderTarget.EndRender();
//}
//
//void GameState::RenderBrightness()
//{
//	mBloomRenderTarget.BeginRender();
//
//	Matrix4 matView = mCamera.GetViewMatrix();
//	Matrix4 matProj = mCamera.GetProjectionMatrix();
//
//	Matrix4 matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) * Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);
//	mTexturingTransformBuffer.Update(Transpose(matWorld * matView * matProj));
//	mTexturingTransformBuffer.BindVS(0);
//
//	mTexturingVertexShader.Bind();
//	mTexturingPixelShader.Bind();
//
//	mSampler.BindPS(0);
//
//	mBlankTexture.BindPS(0);
//	mEarthMeshBuffer.Render();
//
//	mTexturingTransformBuffer.Update(Transpose(matView * matProj));
//
//	mSunDiffuseTexture.BindPS(0);
//	mSunMeshBuffer.Render();
//
//	mBloomRenderTarget.EndRender();
//}
//
//void GameState::ApplyBlur()
//{
//	auto graphicsSystem = GraphicsSystem::Get();
//	Vector4 settings;
//	settings.x = static_cast<float>(graphicsSystem->GetBackBufferWidth());
//	settings.y = static_cast<float>(graphicsSystem->GetBackBufferHeight());
//	settings.z = mBlurSaturation;
//	mBlurSettingsBuffer.Update(settings);
//	mBlurSettingsBuffer.BindPS(0);
//
//	mGaussianBlurVertexShader.Bind();
//	mSampler.BindPS(0);
//
//	for (int i = 0; i < mBlurIterations; ++i)
//	{
//		// Horizontal blur
//		mBlurRenderTarget.BeginRender();
//		mBloomRenderTarget.BindPS(0);
//		mGaussianBlurXPixelShader.Bind();
//		mScreenMeshBuffer.Render();
//		Texture::UnbindPS(0);
//		mBlurRenderTarget.EndRender();
//
//		// Vertical blur
//		mBloomRenderTarget.BeginRender();
//		mBlurRenderTarget.BindPS(0);
//		mGaussianBlurYPixelShader.Bind();
//		mScreenMeshBuffer.Render();
//		Texture::UnbindPS(0);
//		mBloomRenderTarget.EndRender();
//	}
//}
//
//void GameState::PostProcess()
//{
//	mBloomVertexShader.Bind();
//	mBloomPixelShader.Bind();
//
//	mSampler.BindPS(0);
//
//	mBaseRenderTarget.BindPS(0);
//	mBloomRenderTarget.BindPS(1);
//
//	mScreenMeshBuffer.Render();
//
//	Texture::UnbindPS(0);
//	Texture::UnbindPS(1);
//}