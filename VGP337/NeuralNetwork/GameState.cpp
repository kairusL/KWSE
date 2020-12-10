#include"GameState.h"
#include<ImGui/Inc/ImPlot.h>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;

namespace
{

	std::vector<size_t> topology;

	std::vector<float> inputValue1,inputValue2 ,inputValue3,inputValue4;

	std::vector<float> targetValue1,targetValue2,targetValue3,targetValue4;

	int predicted[2];
}
void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(Colors::DarkGray);

	topology.push_back(2);
	topology.push_back(2);
	topology.push_back(1);

	mNeuralNetwork = new NeuralNetwork(topology);

	inputValue1.push_back(0);
	inputValue1.push_back(0);

	inputValue2.push_back(0);
	inputValue2.push_back(1);

	inputValue3.push_back(1);
	inputValue3.push_back(0);

	inputValue4.push_back(1);
	inputValue4.push_back(1);

	targetValue1.push_back(0);
	targetValue2.push_back(1);
	targetValue3.push_back(1);
	targetValue4.push_back(0);

}
void GameState::Terminate()
{



}
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();


	if (inputSystem->IsKeyDown(KeyCode::ESCAPE))
	{
		KWSE::MainApp().Quit();
		return;
	}

}




void  GameState::DebugUI()
{
	mAppLog.Draw("Console");

	ImGui::Begin("Data Setup", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Predict"))
	{
		//ImGui::DragInt2("Set Predicted", predicted, 0, 0, 10);
		ImGui::DragInt("X0", &predicted[0], 0, 0, 10);
		ImGui::DragInt("X1", &predicted[1], 0, 0, 10);
	}
	if (ImGui::CollapsingHeader("TrainData"))
	{
		ImGui::DragInt("Train Times", &trainingTime, 100, 0, 10000);
		if (ImGui::Button("Train"))
		{
			TrainData();
			mAppLog.AddLog("\nTraining %i :  times", trainingTime);
		}
	}

	if (ImGui::Button("ShowResult"))
	{
		std::vector<float> input;
		input.push_back(predicted[0]);
		input.push_back(predicted[1]);
		mNeuralNetwork->FeedFoward(input);
		const std::vector<float> result = mNeuralNetwork->GetResults();
		for (auto &output :result)
		{
			mAppLog.AddLog("\nResult :%f ", output);
		}
	}

	ImGui::End();
}

void GameState::TrainData()
{
	for (size_t i = 0; i < trainingTime; ++i)
	{
		mNeuralNetwork->FeedFoward(inputValue1);
		mNeuralNetwork->BackPropagate(targetValue1);
		mNeuralNetwork->FeedFoward(inputValue2);
		mNeuralNetwork->BackPropagate(targetValue2);
		mNeuralNetwork->FeedFoward(inputValue3);
		mNeuralNetwork->BackPropagate(targetValue3);
		mNeuralNetwork->FeedFoward(inputValue4);
		mNeuralNetwork->BackPropagate(targetValue4);
	}
}

