#pragma once
#include<KWSE/Inc/KWSE.h>

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;
class Background
{
public:
	void Load();
	void Terminate();
	void Update(float deltaTime);
	void Render();

private:
	Texture mTextureId;
	Math::Vector2 mPosition;
	Math::Vector2 mOffset;
};