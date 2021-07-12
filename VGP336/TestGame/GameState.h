#pragma once
#include<KWSE/Inc/KWSE.h>


class GameState : public KWSE::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;


	void Render() override;
	void DebugUI() override;
private:


	KWSE::Math::Vector3 mRotation;
	float mAnimationTimer = 0.0f;

	float mFPS = 0.0f;




	bool mAnimationLoop = false;

	KWSE::GameWorld mGameWorld;
	KWSE::GameObjectHandle mGameObjectHandle;
	KWSE::GameObjectHandle mGameObjectHandle2;
	KWSE::GameObjectHandle mGameObjectHandle3;

	int mNextId = 0;
	float mNextPositionX = 10.0f;

};
