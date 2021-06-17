#include"Precompiled.h"
#include"RenderService.h"

#include "AnimatorComponent.h"
#include "GameObject.h"
#include "ModelComponent.h"
#include "TransformComponent.h"
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;

void RenderService::Initialize()
{
	// BackGround
	Graphics::GraphicsSystem::Get()->SetClearColor(Colors::Black);
	/// BackGround

	// Camera
	mDefaultCamera.SetPosition({ 0.0433705039f,2.54280877f,-8.64591217f });
	mDefaultCamera.SetDirection({ 0.036f,-0.17f, 0.983f });
	mDefaultCamera.SetNearPlane(0.001f);
	//activeCamDir = mDefaultCamera.GetDirection();
	mLightCamera.SetNearPlane(0.1f);
	mLightCamera.SetFarPlane(500.0f);
	mLightCamera.SetAspectRation(1.0f);

	mActiveCamera = &mDefaultCamera;
	/// Camera


	mTransBoneBuffer.Initialize();


	mTransformBuffer.Initialize();


	mBaseRenderTarget.Initialize(
		GraphicsSystem::Get()->GetBackBufferWidth(),
		GraphicsSystem::Get()->GetBackBufferHeight(), Texture::Format::RGBA_F32
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
	const wchar_t* shaderFileNames = L"../../Assets/Shaders/Skinning.fx";
	const wchar_t* shaderFileNames1 = L"../../Assets/Shaders/GaussianBlur.fx";
	const wchar_t* shaderFileNames2 = L"../../Assets/Shaders/DoLightTexturing.fx";
	const wchar_t* shaderFileNames3 = L"../../Assets/Shaders/DoTexturing.fx";

	mGaussianBlurVertexShader.Initialize(shaderFileNames1, VertexPX::Format);
	mGaussianBlurPixelShaderX.Initialize(shaderFileNames1, "BlurXPS");
	mGaussianBlurPixelShaderY.Initialize(shaderFileNames1, "BlurYPS");


	mPixelShader.Initialize(shaderFileNames);
	mVertexShader.Initialize(shaderFileNames, BoneVertex::Format);

	mCloudPixelShader.Initialize(shaderFileNames2);
	mCloudVertexShader.Initialize(shaderFileNames2, VertexPNX::Format);

	mTexturePixelShader.Initialize(shaderFileNames3);
	mTextureVertexShader.Initialize(shaderFileNames3, VertexPX::Format);

	mOilPaintingVertexShader.Initialize(L"../../Assets/Shaders/PostProcessOilPainting_S.fx", VertexPX::Format);
	mOilPaintingPixelShader.Initialize(L"../../Assets/Shaders/PostProcessOilPainting_S.fx");
	mOilSettingBuffer.Initialize();

	constexpr uint32_t depthMapSize = 4096;
	mDepthRebderTarget.Initialize(depthMapSize, depthMapSize, Texture::Format::RGBA_F32);

	mDepthMapVertexShader.Initialize(L"../../Assets/Shaders/DepthMap.fx", Vertex::Format);
	mDepthMapPixelShader.Initialize(L"../../Assets/Shaders/DepthMap.fx");
	mDepthMapBuffer.Initialize();

	mTransformBuffer.Initialize();
	mTransformCloudBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();


	mDirectionLight.direction = Math::Normalize({ 0.379f, -0.920f, 0.102f });
	mDirectionLight.ambient = { 0.5f };
	mDirectionLight.diffuse = { 0.784f };
	mDirectionLight.specular = { 0.858f };
	mMaterial.ambient = { 0.5f };
	mMaterial.diffuse = { 0.784f };
	mMaterial.specular = { 0.39f };
	mMaterial.power = 1.999f;



	mSkybox.Initialize("../../Assets/Images/Space_Skybox.jpg");

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
void RenderService::Terminate()
{
	mScreenMeshBuffer.Terminate();
	mBlendState.Terminate();
	mRasterizerStateWireframe.Terminate();
	mRasterizerStateSolid.Terminate();
	mSampler.Terminate();

	mSkybox.Terminate();
	mOilSettingBuffer.Terminate();
	mOilPaintingPixelShader.Terminate();
	mOilPaintingVertexShader.Terminate();
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


	modelTexrure[1].Terminate();
	modelTexrure[0].Terminate();
	mTransBoneBuffer.Terminate();
}
void RenderService::Update(float deltaTime)
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
	if (inputSystem->IsKeyDown(KeyCode::Q))
		mActiveCamera->Rise(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::E))
		mActiveCamera->Rise(-moveSpeed * deltaTime);

	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mActiveCamera->Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mActiveCamera->Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	//Synchronize the light camera to the directional light (cannot look straight up or down)
	mLightCamera.SetDirection(mDirectionLight.direction);
	KWSE::Math::Vector3 newCamaraPosition = -mLightCamera.GetDirection()*mLightCameraDistance;
	mLightCamera.SetPosition(newCamaraPosition);
	/// Camera

	// -------------------------------------------------------------------------

}
void RenderService::Render()
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
void RenderService::DebugUI()
{
	ImGui::Begin("Render Service", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	bool useLightCamera = (mActiveCamera == &mLightCamera);
	if (ImGui::CollapsingHeader("Camera"))//,ImGuiTreeNodeFlags_DefaultOpen)
	{
		if (ImGui::Checkbox("Use Light Camera", &useLightCamera))
		{
			mActiveCamera = useLightCamera ? &mLightCamera : &mDefaultCamera;
		}
		ImGui::DragFloat("Light Distance", &mLightCameraDistance, 0.01f, 1.0f, 200.0f);
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
			ImGui::DragFloat("Depth Bias", &mSetting.depthBias, 0.000001f, 0.0f, 1.0f, "%.7f");
		}
		if (ImGui::CollapsingHeader("OilSetting"))
		{
			ImGui::DragFloat("Screen Size Scale", &mOilSetting.screenSizeScale, 0.1f, 0.0f, 1000.0f);
			ImGui::DragFloat("Brush Radius", &mOilSetting.paintRadius, 1.0f, 3.0f, 9.0f);
			ImGui::DragFloat("Intensity", &mOilSetting.minSigma, 0.0f, 0.0f, 1.0f);
			bool _sizeWeight = mOilSetting.sizeWeight == 1.0f;
			if (ImGui::Checkbox("Oil Stretch Width", &_sizeWeight))
			{
				mOilSetting.sizeWeight = _sizeWeight ? 1.0f : 0.0f;
			}
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


	}
	ImGui::Checkbox("Skeleton", &showSkeleton);

	ImGui::End();
}

void KWSE::RenderService::Register(const ModelComponent * modelComponent)
{
	auto& gameObject = modelComponent->GetOwner();
	Entry& entry = mRenderEntries.emplace_back();
	entry.animatorComponent = gameObject.GetComponent<AnimatorComponent>();
	entry.modelComponent = modelComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();

}

void KWSE::RenderService::Unregister(const ModelComponent * modelComponent)
{
	auto iter = std::find_if(
		mRenderEntries.begin(), mRenderEntries.end(), [&](const auto& entry)
	{
		return(entry.modelComponent == modelComponent);
	});
	if (iter != mRenderEntries.end())
	{
		mRenderEntries.erase(iter);
	}
}




void RenderService::RenderDepthMap()
{
	mDepthRebderTarget.BeginRender(Colors::Black);
	//Draw all the shadow casters using light camera.
	auto matView = mLightCamera.GetViewMatrix();
	auto matProj = mLightCamera.GetProjectionMatrix();

	mDepthMapBuffer.BindVS(0);


	auto matWorld = Matrix4::Identity;
	auto wvp = Transpose(matWorld*matView*matProj);
	mDepthMapBuffer.Update(wvp);
	mDepthMapVertexShader.Bind();
	mDepthMapPixelShader.Bind();

	mSampler.BindVS(0);

	mDepthRebderTarget.EndRender();

}

void RenderService::RenderScene()
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

	//auto matWorld = Matrix4::Translation({ 0.0f, 0.0f, -8.0f }) *Matrix4::Scaling(1.0f)*(KWSE::Math::Matrix4::RotationX(mRotation.x*5.0f) * Matrix4::RotationY(mRotation.y) *Matrix4::RotationZ(mRotation.z));//* Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y);

	for (auto& entry : mRenderEntries)
	{
		Vector3 position = entry.transformComponent->GetPosition();
		auto rotation = entry.transformComponent->GetRotation();
		auto matWorld =
			//Matrix4::Scaling(10.0f)*		// HACK
			//Matrix4::RotationX(rotation.x)*
			//Matrix4::RotationY(rotation.y)*
			//Matrix4::RotationZ(rotation.z)*
			Matrix4::RotationQuaternion(rotation)*
			Matrix4::Translation(position);
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

		mDepthRebderTarget.BindPS(4);

		auto& game_model = entry.modelComponent->GetModel();
		if (entry.animatorComponent)
		{
			auto& animator = entry.animatorComponent->GetAnimator();



			//std::vector<Matrix4> boneMatrices(game_model.skeleton->bones.size());
			if (showSkeleton)
			{
				auto transforms = animator.GetSkeletonTransform();
				for (auto& transform : transforms)
					transform = transform * matWorld;

				auto& animationClip = game_model.animSet[0];
				KWSE::Graphics::DrawSkeleton(
					*game_model.skeleton,
					transforms,
					Skeleton::DrawType::cone);
				mSetting.Skinning = 0;
			}
			else
			{
				BoneTransformData boneData;
				// Apply offset transform to align the model to bone space
				auto& bones = game_model.skeleton.get()->bones;
				for (auto& bone : bones)
					boneData.boneTransforms[bone->index] =
					KWSE::Math::Transpose(animator.GetToLocalTransform()[bone->index]);
				mTransBoneBuffer.Update(boneData);
				mTransBoneBuffer.BindVS(4);
				mSetting.Skinning = 1;

				for (const auto& mesh : game_model.meshData)
				{
					auto& material = game_model.materialData[mesh->materialIndex];
					if (material.diffuseMap)
					{
						material.diffuseMap->BindPS(0);
					}
					if (material.specularMap)
					{
						material.specularMap->BindPS(1);
					}
					if (material.normalMap)
					{
						material.normalMap->BindPS(3);
					}
					mesh->meshBuffer.Render();
				}
			}
		}

		mSettingBuffer.Update(mSetting);
	}
	Texture::UnbindPS(4);

	//SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::AddGroundPlane(10.0f, Colors::DarkGoldenrod);
	SimpleDraw::Render(*mActiveCamera);

	mRenderTarger.EndRender();
}

void RenderService::RenderBrightness()
{
	mBloomRenderTarget.BeginRender();

	Matrix4 matView = mActiveCamera->GetViewMatrix();
	Matrix4 matProj = mActiveCamera->GetProjectionMatrix();

	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	mSampler.BindPS(0);

	mBlankTexture.BindPS(0);

	mBloomRenderTarget.EndRender();
}

void RenderService::ApplyBlur()
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

void RenderService::PostProcess()
{
	mOilPaintingVertexShader.Bind();
	mOilPaintingPixelShader.Bind();


	mOilSettingBuffer.Update(mOilSetting);
	mOilSettingBuffer.BindPS(0);


	mSampler.BindVS(0);

	mBaseRenderTarget.BindPS(0);
	mBloomRenderTarget.BindPS(1);

	mRenderTarger.BindPS(0);
	mScreenMeshBuffer.Render();
	mRenderTarger.UnbindPS(0);
}


