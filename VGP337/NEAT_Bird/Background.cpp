#include "Background.h"

void Background::Load()
{

	mTextureId = KWSE::LoadTexture("Bird/background.png");
	mOffset.x = (float)KWSE::GetSpriteWidth(mTextureId);
}

void Background::Update(float deltaTime)
{
	auto velocity = KWSE::Math::Vector2{ -100.0f, 0.0f };
	mPosition += velocity * deltaTime;
	if (mPosition.x <= -mOffset.x)
		mPosition.x += mOffset.x;
}

void Background::Render()
{
	KWSE::DrawSprite(mTextureId, mPosition, 0.0f,KWSE::Graphics::Pivot::TopLeft);
	KWSE::DrawSprite(mTextureId, mPosition + mOffset, 0.0f, KWSE::Graphics::Pivot::TopLeft);
}