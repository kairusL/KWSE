#include"GameState.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;

namespace
{
	int animF = 0;
}

void GameState::Initialize()
{
	// 1. Add RenderService to the world before initialize the world.
	mGameWorld.AddService<RenderService>();
	mGameWorld.Initialize(1000);
	// 2. Create a game object
	mGameObjectHandle = mGameWorld.CreateGameObject("../../Assets/Templates/test.json", "Kairus")->GetHandle();
	//GameObjectIO::Read(nullptr, mGameObject);
	//mGameObject.Initialize();


	GameObject* gameObject = mGameWorld.GetGameObject(mGameObjectHandle);
	if (gameObject)
	{
		gameObject->DebugUI();
		auto animatorComponent = gameObject->GetComponent<AnimatorComponent>();
		if (animatorComponent)
		{
			animatorComponent->GetAnimator().Play();
		}
	}
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
	{
		auto newObject = mGameWorld.CreateGameObject("../../Assets/Templates/test.json", std::to_string(mNextId++));
		newObject->GetComponent<TransformComponent>()->SetPosition({ mNextPositionX,0.0f,0.0f });
		newObject->GetComponent<AnimatorComponent>()->GetAnimator().Play();
		newObject->GetComponent<AnimatorComponent>()->GetAnimator().SetLooping(true);
		mNextPositionX += 1.0f;

		if (mNextId >=5)
		{
			auto kill = mGameWorld.FindGameObject(std::to_string(mNextId - 5));
			mGameWorld.Destory(kill->GetHandle());
		}
	}




	//if (inputSystem->IsKeyDown(KeyCode::LEFT))
	//	mRotation.y += deltaTime;
	//if (inputSystem->IsKeyDown(KeyCode::RIGHT))
	//	mRotation.y -= deltaTime;
	//if (inputSystem->IsKeyDown(KeyCode::UP))
	//	mRotation.x += deltaTime;
	//if (inputSystem->IsKeyDown(KeyCode::DOWN))
	//	mRotation.x -= deltaTime;
	//mRotation += deltaTime;



	mFPS = 1.0f / deltaTime;
	mAnimationTimer += deltaTime;

	GameObject* gameObject = mGameWorld.GetGameObject(mGameObjectHandle);
	auto animatorComponent = gameObject->GetComponent<AnimatorComponent>();
	auto& animator = animatorComponent->GetAnimator();
	if (gameObject)
	{
		auto animatorComponent = gameObject->GetComponent<AnimatorComponent>();
		//if (animatorComponent)
		//{
		//
		//	animatorComponent->GetAnimator().PlayAnimation(animF);
		//}
	}


	mGameWorld.Update(deltaTime);

}
void GameState::Render()
{


	mGameWorld.Render();
	//mGameObject.Render();
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

	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);
	}

	if (ImGui::CollapsingHeader("Animation"))
	{
		//if (ImGui::Checkbox("Loop", &mAnimationLoop))
		//{
		//	//mAnimationLoop= (mAnimation = AnimationBuilder().SetLooping(true)) ? 1.0f : 0.0f;
		//}
	}
	//if (ImGui::CollapsingHeader("ChangeAnimation"))
	//{
	//	ImGui::DragInt("Anim", &animF);
	//}

	ImGui::End();


	mGameWorld.DebugUI();

	//ImGui::ShowDemoWindow();
	GameObject* gameObject = mGameWorld.GetGameObject(mGameObjectHandle);
	if (gameObject)
	{
		gameObject->DebugUI();
		auto animatorComponent = gameObject->GetComponent<AnimatorComponent>();
		if (animatorComponent)
		{
			auto& animator = animatorComponent->GetAnimator();
			//animator.SetLooping(mAnimationLoop);
		}
	}
}
