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
	mDataset_b2 = 1.0f;
	mDataset_minX = 0.0f;
	mDataset_maxX = 100.0f;
	mDataset_noise = 10.0f;
	epoch = 10000;

	mDataset = Datasets::MakeLogistic(mDataset_samples, mDataset_b0, mDataset_b1, mDataset_b2, mDataset_minX, mDataset_maxX, mDataset_noise);
	mLogisticRegression.learningRate = 0.00001f;


	for (int e = 0; e < epoch; ++e)
	{
		float error = mLogisticRegression.Fit(mDataset);
		//float error = 0.0f;
		mAppLog.AddLog("b0 =%f, b1 = %f,b2=%f , error = %f \n", mLogisticRegression.b0, mLogisticRegression.b1,mLogisticRegression.b2, error);
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
	if (ImPlot::BeginPlot("Logistic Regression", "x0", "x1"))
	{
		std::vector<ImVec2> modelLine;

		float startX = mDataset_minX;
		float endX = mDataset_maxX;

		int count = mDataset.x0.size();
		int x0Back = mDataset.x0.back();
		float m = mLogisticRegression.b1 / -mLogisticRegression.b2;
		float b = mLogisticRegression.b0 / -mLogisticRegression.b2;//slope
		modelLine.push_back({ startX, startX * m + b});
		modelLine.push_back({ endX,  endX * m + b });
		ImPlot::PlotLine("Model", modelLine.data(), (int)modelLine.size());

		std::vector<float> ax, ay, bx, by;
		for (int i = 0; i < count; ++i)
		{
			float prediction = mLogisticRegression.b0 + mLogisticRegression.b1 * mDataset.x0[i] + mLogisticRegression.b2 * mDataset.x1[i];
			if (prediction >= 0)
			{
				ax.push_back(mDataset.x0[i]);
				ay.push_back(mDataset.x1[i]);
			}
			else
			{
				bx.push_back(mDataset.x0[i]);
				by.push_back(mDataset.x1[i]);
			}
		}
		if (!bx.empty())
		{
			ImPlot::PlotScatter("Zeros", bx.data(), by.data(), (int)bx.size());
		}
		if (!ax.empty())
		{
			ImPlot::PlotScatter("Ones", ax.data(), ay.data(), (int)ax.size());
		}

		ImPlot::EndPlot();
	}

		mAppLog.Draw("Console");

		ImGui::Begin("Debug Setting", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::DragInt("Dataset samples", &mDataset_samples, 1, 0, 100);
		ImGui::DragFloat("Dataset b0", &mDataset_b0, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Dataset b1", &mDataset_b1, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Dataset b2", &mDataset_b2, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Dataset minX", &mDataset_minX, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Dataset maxX", &mDataset_maxX, 0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Dataset noise", &mDataset_noise, 0.1f, 0.0f, 100.0f);

		if (ImGui::Button("Reset"))
		{
			mDataset = Datasets::MakeLogistic(mDataset_samples, mDataset_b0, mDataset_b1,mDataset_b2,mDataset_minX, mDataset_maxX, mDataset_noise);

		}
		if (ImGui::Button("ResetLine"))
		{
			mLogisticRegression.Reset();
		}

		ImGui::DragFloat("LearningRate", &mLogisticRegression.learningRate, 0.00001f, 0.0000001f, 1.f, "%.6f");
		ImGui::DragInt("Epoch", &epoch, 1.f, 0.f, 100000.f);
		if (ImGui::Button("Learning"))
		{
			mAppLog.Clear();
			float inf = std::numeric_limits<float>::infinity();

			float error=0.0f;
			for (int e = 0; e < epoch; ++e)
			{
				error = mLogisticRegression.Fit(mDataset);
				mAppLog.AddLog("b0 = %f , b1 = %f , b2 = %f , error = %f  \n", mLogisticRegression.b0, mLogisticRegression.b1, mLogisticRegression.b2, error);
			}
			if ((mLogisticRegression.b0 != mLogisticRegression.b0) || (mLogisticRegression.b1 != mLogisticRegression.b1))
			{
				mLogisticRegression.Reset();
				mAppLog.AddLog("Not a number anymore! Check your learning rate again!");
			}
		}
		ImGui::End();
}


