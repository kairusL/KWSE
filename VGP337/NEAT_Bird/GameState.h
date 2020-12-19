#pragma once
#include<KWSE/Inc/KWSE.h>
#include<ImGui/Inc/AppLog.h>
#include "Background.h"
#include "Bird.h"
#include "PipeManager.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;

enum State
{
	Init,
	Title,
	Play,
	RunNEAT,
	RunXOR
};

class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Render() override;
	void Update(float deltaTime) override;
	void DebugUI() override;

	bool Init(float deltaTime);
	bool Title(float deltaTime);
	bool Play(float deltaTime);
	bool RunNEAT(float deltaTime);
	bool RunXOR(float deltaTime);


private:

	float mDeltaTime=0.0f;
	AppLog mAppLog;
	std::function<void(float)> Tick;
	State mCurrentyState = State::Init;

};