#include"GameState.h"
#include<ImGui/Inc/ImPlot.h>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <ImGui//Src/imgui_internal.h>

namespace
{
	const std::string KTarget = "GA is Co000000000ol!";
	char nTarget[128] = "";
	std::string* newtarget;
	const int kValidGeneValue = 126 - 32; // from Character `~` to ` ` in ASCII table

	auto fitnessF = [](auto& genome)
	{
		float fitness = 0.0f;
		// One point per matching character
		for (size_t i = 0; i < nTarget.size(); ++i)
		{
			if (nTarget[i] == genome.chromosome[i] + 32)
			{
				fitness += 1.0f;
			}
		}
		return fitness;
	};
	auto crossOverF = [](auto& genome, auto& parent1, auto& parent2, float crossoverRate)
	{
		for (size_t i = 0; i < parent1.chromosome.size(); ++i)
		{
			if (RandomFloat() < crossoverRate)
			{
				genome.chromosome.push_back(parent1.chromosome[i]);
			}
			else
			{
				genome.chromosome.push_back(parent2.chromosome[i]);
			}
		}
	};
	auto mutateF = [](auto& genome, float mutationRate, float maxGeneValue)
	{
		if (RandomFloat() < mutationRate)
		{
			genome.chromosome[Random(0, genome.chromosome.size() - 1)] = (Random(0, (int)maxGeneValue));
		}
	};

	auto crossOverMutateF = [](auto& genome, auto& parent1, auto& parent2, float crossoverRate, float mutationRate, float maxGeneValue)
	{
		for (size_t i = 0; i < parent1.chromosome.size(); ++i)
		{
			if (RandomFloat() < mutationRate)
			{
				genome.chromosome.push_back(Random(0, (int)maxGeneValue));
			}
			else if (RandomFloat() < crossoverRate)
			{
				genome.chromosome.push_back(parent1.chromosome[i]);
			}
			else
			{
				genome.chromosome.push_back(parent2.chromosome[i]);
			}
		}

	};
}
void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(Colors::DarkGray);



}
void GameState::Terminate()
{



}
//3.07
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();


	if (inputSystem->IsKeyDown(KeyCode::ESCAPE))
	{
		KWSE::MainApp().Quit();
		return;
	}
	if (mInitialized)
	{
		auto& best = mGA.GetBestGenome();
		if (best.fitness < strlen(nTarget))
		{
			mGA.Advance();

			// Print the next best genome
			std::string bestStr;
			for (auto& gene : mGA.GetBestGenome().chromosome)
			{
				bestStr += (char)(gene + 32);
			}
			mAppLog.AddLog("Generation %d: %s\n", mGA.GetGeneration(), bestStr.c_str());
		}

	}

}





void  GameState::DebugUI()
{
	ImGui::ShowDemoWindow();


	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::InputText("input text", nTarget, IM_ARRAYSIZE(nTarget)))
	{
		mInitialized = false;
	}
	if (ImGui::Button("Run!"))
	{
		mAppLog.AddLog("Initializing new population...\n");
		InitGA();
		mInitialized = true;
	}
	ImGui::End();
	DrawMap();
	mAppLog.Draw("Console");


}

void GameState::InitGA()
{
	int size = strlen(nTarget);
	mGA.Initialize
	(
		100, size,
		kValidGeneValue, 0.45f, 0.1f,
		[](auto& genome)
	{
		float fitness = 0.0f;
		// One point per matching character
		for (size_t i = 0; i < strlen(nTarget); ++i)
		{
			if (nTarget[i] == genome.chromosome[i] + 32)
			{
				fitness += 1.0f;
			}
		}
		return fitness;
	}, crossOverMutateF//crossOverF, mutateF
	);
}

void GameState::DrawMap()
{

	ImVec2 circleSize{ 10.0f, 10.0f };
	ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoTitleBar);
	ImVec2 winPos = ImGui::GetWindowPos();
	ImVec2 winSize = ImGui::GetWindowSize();
	//ImGui::SetNextWindowSize(winPos +offset);
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	//for (int y = 0; y < winSize.y; ++y)
	//{
	//	for (int x = 0; x < winSize.x; ++x)
	//	{
	//		int i = x + (y * winSize.x);
	//		ImVec2 min{ x * winSize.x, y * winSize.y };
	//		ImVec2 max = min + winSize;
	//		//float intensity = mDataset.inputs[mCurrentEntry][i];
	//		//ImColor color{ intensity, intensity, intensity };
	//		ImColor color{ 1.0f, 1.0f, 1.0f };
	//		drawList->AddRectFilled(min+winSize, max+winSize, color);
	//	}
	//}

	ImColor color{ 1.0f, 1.0f, 1.0f };
	//drawList->AddRectFilled(winPos+ winSize, winPos+ winSize, color);
	ImVec2 startPos{ circleSize };
	ImVec2 endPos{ winSize - circleSize };

	drawList->AddCircle(winPos + startPos, 10.0f, color);
	drawList->AddCircle(winPos + endPos, 10.0f, color);


	ImGui::End();

}

