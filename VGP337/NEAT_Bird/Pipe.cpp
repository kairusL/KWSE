#include "Pipe.h"

void Pipe::Load()
{
	mTextureId.Initialize("../../Assets/Bird/pipe.png");
}

void Pipe::Update(float deltaTime)
{
	mPosition += mVelocity * deltaTime;
}

void Pipe::Render()
{
	auto topRect = GetTopRect();
	auto bottomRect = GetBottomRect();

	SpriteRenderer::Get()->Draw(mTextureId, { topRect.left, topRect.bottom }, 0.0f,Pivot::BottomLeft, Flip::Vertical);
	SpriteRenderer::Get()->Draw(mTextureId, { bottomRect.left, bottomRect.top }, 0.0f,Pivot::TopLeft);
}

void Pipe::Spawn(float gapSize)
{
	mGapSize = gapSize;
	mVelocity = Math::Vector2{ -100.0f, 0.0f };
	mPosition.x = (float)GraphicsSystem::Get()->GetBackBufferWidth();
	mPosition.y = RandomFloat(gapSize,(float)GraphicsSystem::Get()->GetBackBufferHeight() - gapSize);
}

Math::Rect Pipe::GetTopRect() const
{
	return {
		mPosition.x,
		-FLT_MAX,
		mPosition.x + mGapSize,
		mPosition.y - mGapSize,
	};
}

Math::Rect Pipe::GetBottomRect() const
{
	return {
		mPosition.x,
		mPosition.y + mGapSize,
		mPosition.x + mGapSize,
		FLT_MAX,
	};
}