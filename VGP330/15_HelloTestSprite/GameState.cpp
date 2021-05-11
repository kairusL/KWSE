#include"GameState.h"


//namespace KWSE::Graphics
//{
//	using _spriteRender = SpriteRenderer::Get();
//}

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	//mTextureId = TextureManager::Get()->Load("WaterTurtle.jpg");
	mTextureId = KWSE::Utilis::GUIUtili::LoadTexture("WaterTurtle.jpg");
	//mTexture.Initialize("../../Assets/Images/WaterTurtle.jpg");
	mPosition = Vector2(GraphicsSystem::Get()->GetBackBufferWidth() * 0.5f, GraphicsSystem::Get()->GetBackBufferHeight()* 0.5f);
	mFont.Initialize();
	
}
void GameState::Terminate()
{
	mFont.Terminate();
	//mTexture.Terminate();
}
void GameState::GUI(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float moveSpeed = 150.0f;
	const float turnSpeed = 150.0f * Constants::DegToRad;
	if (inputSystem->IsKeyDown(KeyCode::W))
		mPosition.y-=(moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::S))
		mPosition.y += (moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::D))
		mPosition.x += (moveSpeed * deltaTime);
	if (inputSystem->IsKeyDown(KeyCode::A))
		mPosition.x -= (moveSpeed * deltaTime);
	KWSE::Utilis::GUIUtili::DrawSprite(mTextureId, mPosition);
	KWSE::Utilis::GUIUtili::DrawScreenText("okay bye", 10.0f, 10.0f, 20.0f, Colors::DarkCyan);

	
}
//void GameState::Render()
//{
//	//SpriteRenderer::Get()->BeginRender();
//	//SpriteRenderer::Get()->Draw(*TextureManager::Get()->GetTexture(mTextureId),mPosition);
//	KWSE::DrawSprite(mTextureId,mPosition);
//	KWSE::DrawScreenText("okay bye", 10.0f, 10.0f, 20.0f, Colors::DarkCyan);
//	//mFont.Draw("okay bye", 10.0f, 10.0f, 20.0f, Colors::DarkCyan);
//	//SpriteRenderer::Get()->EndRender();
//}



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

	ImGui::DragFloat2("Position", (float*)&mPosition, 0.01f);
	ImGui::End();

	//ImGui::ShowDemoWindow();

}


