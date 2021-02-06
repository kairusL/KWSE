#pragma once

#include<KWSE/Inc/KWSE.h>
using namespace KWSE::Math;
using namespace KWSE::Graphics;
class Background
{
public:
	void Load();

	void Update(float deltaTime);
	void Render();

private:
	TextureId mTextureId;
	Vector2 mPosition;
	Vector2 mOffset;
};