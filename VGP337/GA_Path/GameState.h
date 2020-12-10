#pragma once
#include<KWSE/Inc/KWSE.h>
#include<ImGui/Inc/AppLog.h>


class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void DebugUI() override;

	void InitGA();

	void DrawMap();

private:
	AppLog mAppLog;

	KWSE::ML::GeneticAlgorithm mGA;
	bool mInitialized = false;
};