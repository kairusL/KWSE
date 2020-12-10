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
	AppLog mAppLog;

	KWSE::ML::Dataset mDataset;
	KWSE::ML::LinearRegression mLinearRegression;

	// Or you can loop until error is smaller than some threshold..
	int epoch = 0;
	int mDataset_samples =0;
	float  mDataset_b0=0.0f;
	float  mDataset_b1=0.0f;
	float  mDataset_minX=0.0f;
	float  mDataset_maxX=0.0f;
	float  mDataset_noise=0.0f;
	float mLinearRegLearningRate= 0.00001f;
};