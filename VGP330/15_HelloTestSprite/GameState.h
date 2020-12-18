#pragma once
#include<KWSE/Inc/KWSE.h>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::Math;

class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;


	void DebugUI() override;

	void Update(float deltaTime) override;
	void Render() override;
private:


	Vector2 mPosition;
	Texture mTexture;
	
};