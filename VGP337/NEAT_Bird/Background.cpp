#include "Background.h"

void Background::Load()
{
	mTextureId.Initialize(L"../../Assets/Bird/background.png");
	mOffset.x = mTextureId.GetWidth();
}

void Background::Terminate()
{
	mTextureId.Terminate();
}

void Background::Update(float deltaTime)
{
	auto velocity = Math::Vector2{ -100.0f, 0.0f };
	mPosition += velocity * deltaTime;
	if (mPosition.x <= -mOffset.x)
		mPosition.x += mOffset.x;
}

void Background::Render()
{
	SpriteRenderer::Get()->Draw(mTextureId, mPosition, 0.0f,Pivot::TopLeft);
	SpriteRenderer::Get()->Draw(mTextureId, mPosition + mOffset, 0.0f, Pivot::TopLeft);
}