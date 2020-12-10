#include"GameState.h"
#include<ImGui/Inc/ImPlot.h>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;


void GameState::Initialize()
{

	GraphicsSystem::Get()->SetClearColor(Colors::DarkGray);



	mDataset_samples = 100;
	mDataset_b0 = 0.0f;
	mDataset_b1 = 1.0f;
	mDataset_minX = 0.0f;
	mDataset_maxX = 100.0f;
	mDataset_noise = 10.0f;
	epoch = 10000;

	mDataset = Datasets::MakeLinear(mDataset_samples, mDataset_b0, mDataset_b1, mDataset_minX, mDataset_maxX, mDataset_noise);
	mLinearRegression.learningRate = 0.00001f;


	for (int e = 0; e < epoch; ++e)
	{
		float error = mLinearRegression.Fit(mDataset);
		//float error = 0.0f;
		mAppLog.AddLog("b0 =%f, b1 = %f , error = %f \n", mLinearRegression.b0, mLinearRegression.b1, error);
	}


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

	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
	{
		mAppLog.AddLog("Bam!\n");
	}
}




void  GameState::DebugUI()
{


	if (ImPlot::BeginPlot("Linear Regression", "x", "y"))
	{
		float startX = mDataset_minX;
		float endX = mDataset_maxX;
		float startY = mLinearRegression.Predict(startX);
		float endY = mLinearRegression.Predict(endX);
		std::vector<ImVec2> line;
		line.push_back({ startX,startY });
		line.push_back({ endX,endY });
		ImPlot::PlotScatter("Dataset", mDataset.x0.data(), mDataset.y.data(), mDataset.x0.size());
		ImPlot::PlotLine("Model", line.data(), line.size());
		ImPlot::EndPlot();
	}
	mAppLog.Draw("Console");
	ImGui::Begin("Debug Setting", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::DragInt("Dataset samples", &mDataset_samples, 1, 0, 100);
	ImGui::DragFloat("Dataset b0", &mDataset_b0, 0.1f, 0.0f, 100.0f);
	ImGui::DragFloat("Dataset b1", &mDataset_b1, 0.1f, 0.0f, 100.0f);
	ImGui::DragFloat("Dataset minX", &mDataset_minX, 0.1f, 0.0f, 100.0f);
	ImGui::DragFloat("Dataset maxX", &mDataset_maxX, 0.1f, 0.0f, 100.0f);
	ImGui::DragFloat("Dataset noise", &mDataset_noise, 0.1f, 0.0f, 100.0f);

	if (ImGui::Button("Reset"))
	{
		mDataset = Datasets::MakeLinear(mDataset_samples, mDataset_b0, mDataset_b1, mDataset_minX, mDataset_maxX, mDataset_noise);
		
	}

	ImGui::DragFloat("LearningRate", &mLinearRegression.learningRate, 0.00001f, 0.0000001f, 1.f, "%.6f");
	ImGui::DragInt("Epoch", &epoch, 1.f, 0.f, 100000.f);
	if (ImGui::Button("Learning"))
	{
		mAppLog.Clear();
		float inf = std::numeric_limits<float>::infinity();

		//mLinearRegression.b0 = mDataset_b0;
		//mLinearRegression.b1 = mDataset_b1;

		for (int e = 0; e < epoch; ++e)
		{
			float error = mLinearRegression.Fit(mDataset);

			//float error = 0.0f;
			mAppLog.AddLog("b0 =%f, b1 = %f , error = %f \n", mLinearRegression.b0, mLinearRegression.b1, error);
		}
		if ((mLinearRegression.b0 != mLinearRegression.b0)|| (mLinearRegression.b1 != mLinearRegression.b1))
		{
			mLinearRegression.Reset();
			mAppLog.AddLog("Not a number anymore! Check your learning rate again!");
		}
	}

	ImGui::End();
}


