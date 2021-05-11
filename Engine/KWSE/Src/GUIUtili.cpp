#include"Precompiled.h"
#include"GUIUtili.h"

using namespace KWSE::Graphics;
using namespace KWSE::Math;
TextureId KWSE::Utilis::GUIUtili::LoadTexture(const char* filePath)
{
	return TextureManager::Get()->Load(filePath);
}

void KWSE::Utilis::GUIUtili::DrawSprite(TextureId textureId, const Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	SpriteRenderer::Get()->Draw(*TextureManager::Get()->GetTexture(textureId), position, rotation, pivot, flip);
}

void KWSE::Utilis::GUIUtili::DrawSprite(TextureId textureId, const Rect& sourceRect, const Vector2& position, float rotation, Pivot pivot, Flip flip)
{
	SpriteRenderer::Get()->Draw(*TextureManager::Get()->GetTexture(textureId), sourceRect, position, rotation, pivot, flip);
}

void KWSE::Utilis::GUIUtili::DrawScreenText(const char* str, float x, float y, float size, const KWSE::Graphics::Color& color)
{
	FontManager::Get()->AddText(str, size, x, y, color);
}

uint32_t KWSE::Utilis::GUIUtili::GetSpriteWidth(TextureId textureId)
{
	Texture* texture = TextureManager::Get()->GetTexture(textureId);
	return texture ? texture->GetWidth() : 0u;
}

uint32_t KWSE::Utilis::GUIUtili::GetSpriteHeight(TextureId textureId)
{
	Texture* texture = TextureManager::Get()->GetTexture(textureId);
	return texture ? texture->GetHeight() : 0u;
}