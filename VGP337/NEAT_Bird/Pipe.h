#pragma once

#include<KWSE/Inc/KWSE.h>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Math;

class Pipe
{
public:
	void Load();

	void Update(float deltaTime);
	void Render();

	void Spawn(float gapSize);

	Rect GetTopRect() const;
	Rect GetBottomRect() const;

private:
	TextureId mTextureId;
	Vector2 mPosition;
	Vector2 mVelocity;
	float mGapSize;
};