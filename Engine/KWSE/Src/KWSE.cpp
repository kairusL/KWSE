#include "Precompiled.h"

#include "KWSE.h"
using namespace KWSE::Graphics;
using namespace KWSE::Math;

KWSE::App& KWSE::MainApp()
{
	static App sApp;

	return sApp;
}

/*TextureId KWSE::LoadTexture(const char* filePath)
{
	return TextureManager::Get()->Load(filePath);
}

void KWSE::DrawSprite(TextureId textureId, const Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	SpriteRenderer::Get()->Draw(*TextureManager::Get()->GetTexture(textureId), position, rotation, pivot, flip);
}

void KWSE::DrawSprite(TextureId textureId, const Rect& sourceRect, const Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	SpriteRenderer::Get()->Draw(*TextureManager::Get()->GetTexture(textureId), sourceRect, position, rotation, pivot, flip);
}

void KWSE::DrawScreenText(const char* str, float x, float y, float size, const KWSE::Graphics::Color& color)
{
	FontManager::Get()->AddText(str, size, x, y, color);
}

uint32_t KWSE::GetSpriteWidth(TextureId textureId)
{
	Texture* texture = TextureManager::Get()->GetTexture(textureId);
	return texture ? texture->GetWidth() : 0u;
}

uint32_t KWSE::GetSpriteHeight(TextureId textureId)
{
	Texture* texture = TextureManager::Get()->GetTexture(textureId);
	return texture ? texture->GetHeight() : 0u;
}*/