#pragma once
#include "Common.h"

// App
#include"App.h"
#include "AppState.h"
// Component 
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "AnimatorComponent.h"
// Service header
#include"RenderService.h"
// World
#include "Component.h"
#include "GameObject.h"
#include "GameObjectIO.h"
#include "GameObjectHandle.h"
#include "GameWorld.h"
#include "Service.h"
// Utilis
#include "GUIUtili.h"

namespace KWSE
{
	App& MainApp();

	/*KWSE::Graphics::TextureId LoadTexture(const char* filePath);
	void DrawSprite(KWSE::Graphics::TextureId textureId, const KWSE::Math::Vector2& position, float rotation = 0.0f, KWSE::Graphics::Pivot pivot = KWSE::Graphics::Pivot::Center, KWSE::Graphics::Flip flip = KWSE::Graphics::Flip::None);
	void DrawSprite(KWSE::Graphics::TextureId textureId, const KWSE::Math::Rect& sourceRect, const KWSE::Math::Vector2& position, float rotation = 0.0f, KWSE::Graphics::Pivot pivot = KWSE::Graphics::Pivot::Center, KWSE::Graphics::Flip flip = KWSE::Graphics::Flip::None);
	uint32_t GetSpriteWidth(KWSE::Graphics::TextureId textureId);
	uint32_t GetSpriteHeight(KWSE::Graphics::TextureId textureId);
	void DrawScreenText(const char* str, float x, float y, float size, const KWSE::Graphics::Color& color);*/
}