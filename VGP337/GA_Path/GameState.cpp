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
	enum NextMove
	{
		Top,     //0
		Right,	 //1
		Bottom,	 //2
		Left	 //3
	};

	int target = 100;

	auto pathfitnessF = [](auto& genome)
	{
		float fitness = 0.0f;
		// One point per matching character
		for (size_t i = 0; i < target; ++i)
		{

			if (curPos == endPos)
			{
				break;
			}
			else
			{
				if (KTarget[i] == genome.chromosome[i] + 32)
				{
					fitness += Math::Distance(corpos);
				}
			}
		}
		return fitness;
	};

}
namespace
{

	const std::string KTarget = "GA is Co000000000ol!";
	std::string* newtarget;
	const int kValidGeneValue = 126 - 32; // from Character `~` to ` ` in ASCII table

	auto fitnessF = [](auto& genome)
	{
		float fitness = 0.0f;
		// One point per matching character
		for (size_t i = 0; i < KTarget.size(); ++i)
		{
			if (KTarget[i] == genome.chromosome[i] + 32)
			{
				fitness += 1.0f;
			}
		}
		return fitness;
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

	mCircleSize = { 10.0f, 10.0f };
	mStartPos = mCircleSize;
	mEndPos = { Vector2{371,242} -mCircleSize };



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


}





void  GameState::DebugUI()
{
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
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
	mGA.Initialize
	(
		100, (int)KTarget.size(), 
		kValidGeneValue, 0.45f, 0.1f, 
		[](auto& genome)
	{
		float fitness = 0.0f;
		// One point per matching character
		for (size_t i = 0; i < KTarget.size(); ++i)
		{
			if (KTarget[i] == genome.chromosome[i] + 32)
			{
				fitness += 1.0f;
			}
		}
		return fitness;
	}, crossOverMutateF
	);
}

void GameState::DrawMap()
{

	ImGui::Begin(" ",nullptr,ImGuiWindowFlags_NoTitleBar);
	ImVec2 winPos = ImGui::GetWindowPos();
	ImVec2 winSize = ImGui::GetWindowSize();
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	
	ImColor color{ 1.0f, 1.0f, 1.0f };


	drawList->AddCircle(winPos + ImVec2{mStartPos.x,mStartPos.y}, 10.0f, color);
	drawList->AddCircle(winPos+ ImVec2{ mEndPos.x,mEndPos.y }, 10.0f, color);

	if (mInitialized)
	{
		auto& best = mGA.GetBestGenome();
		if (best.fitness < (int)KTarget.size())
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
	
	ImGui::End();

}

