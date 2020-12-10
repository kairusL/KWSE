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

private:
	struct  Unit
	{
		ImVec2 position;
		ImVec2 velocity;
		int cluster=0;
	};

	AppLog mAppLog;

	KWSE::Graphics::Texture mUnitTexture;
	std::vector<Unit> mUnits;

};