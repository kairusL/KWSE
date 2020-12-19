#pragma once

#include<KWSE/Inc/KWSE.h>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;

class Pipe
{
public:
	void Load();

	void Update(float deltaTime);
	void Render();

	void Spawn(float gapSize);

	Math::Rect GetTopRect() const;
	Math::Rect GetBottomRect() const;

private:
	Texture mTextureId;
	Math::Vector2 mPosition;
	Math::Vector2 mVelocity;
	float mGapSize;
};