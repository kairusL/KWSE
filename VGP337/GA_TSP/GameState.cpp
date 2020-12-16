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

	float mBestFitness;
	int mNumCity = 15;
	std::vector<KWSE::Math::Vector2> mCitys;
	const float mCirSize = 5.0f;
	bool isFound = false;
	bool drawLine = false;
	std::vector<int> KTarget;
	std::vector<int> KBestTarget;
	std::string* newtarget;
	float mutationRate = 0.25;
	float crossoverRate = 0.15;
	const int kValidGeneValue = mNumCity -1;
	Vector2 offest;


	auto generateF = [](auto& population)
	{
		population.resize(100);
		for (auto& genome: population)
		{
			genome.chromosome.reserve(KTarget.size());
			std::vector<int> cities = KTarget;
			for (int i = 0; i < KTarget.size(); ++i)
			{
				const int size = cities.size();
				int randomInt = Random(0, size - 1);
				genome.chromosome.push_back(cities[randomInt]);
				cities.erase(cities.begin() + randomInt);
			}
		}
	};
	/// fun[]
	
	auto fitnessF = [](auto& genome)
	{
		float fitness = 0.0f;
		for (size_t i = 0; i < genome.chromosome.size()-1; ++i)
		{
			fitness += Distance(mCitys[genome.chromosome[i]], mCitys[genome.chromosome[i + 1]]);
		}
		return mBestFitness-fitness;
	};
	auto crossOverMutateF = [](auto& genome, auto& parent1, auto& parent2, float crossoverRate, float mutationRate, float maxGeneValue)
	{
		for (size_t i = 0; i < parent1.chromosome.size(); ++i)
		{
			genome.chromosome.push_back(parent1.chromosome[i]);
		}
		for (size_t i = 0; i < parent1.chromosome.size(); ++i)
		{
			 if (RandomFloat() < mutationRate)
			{
				int gene1 = Random(1, (int)kValidGeneValue);
				//int gene2 = Random(0, (int)kValidGeneValue);
				int tempValue = genome.chromosome[gene1];
				genome.chromosome.erase(genome.chromosome.begin() + gene1);
				genome.chromosome.push_back(tempValue);

				//tempValue = genome.chromosome[gene2];
				//genome.chromosome.erase(genome.chromosome.begin() + gene2);
				//genome.chromosome.push_back(tempValue);
				//std::swap(genome.chromosome[gene1], genome.chromosome[gene2]);
				//int gene1 = Random(0, (int)maxGeneValue);
				//int gene2 = Random(0, (int)maxGeneValue);
				//std::swap(genome.chromosome[parent1.chromosome.size()-1], genome.chromosome[gene2]);
			}
			 else if (RandomFloat() < crossoverRate)
			{
				int newTarget = Random(1, (int)kValidGeneValue);
				std::swap(genome.chromosome[i], genome.chromosome[newTarget]);
			
			}
			 //else
			 //{
			//	 genome.chromosome.push_back(parent2.chromosome[i]);
			 //}
		}

	};
	/// 
}

void GameState::InitGA()
{

	mGA.Initialize
	(
		100, mNumCity,
		kValidGeneValue, 
		crossoverRate, 
		mutationRate,
		generateF,
		fitnessF
		, crossOverMutateF
	);
}
void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(Colors::DarkGray);
	//for (size_t i = 0; i < mNumCity; i++)
	//{
	//	mCitys.push_back(KWSE::Math::Vector2{ RandomFloat(0.0f,10.0f) });
	//}
	float constant = 2 * Constants::Pi / mNumCity;
	float angle = 0;
	for (int i = 0; i < mNumCity; ++i)
	{
		angle += constant;
		mCitys.push_back(Vector2(sin(angle)*100.0f, cos(angle)*100.0f));
	}
	for (int i = 0; i < mNumCity; i++)
	{
		KTarget.push_back(i);
	}
	for (int i = 0; i < KTarget.size()-1; ++i)
	{
		mBestFitness += Distance(mCitys[KTarget[i]], mCitys[KTarget[i + 1]]);
	}
	for (size_t i = KTarget.size(); i > 0; --i)
	{
		KBestTarget.push_back(i-1);
	}
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
		if (!isFound)
		{
			mGA.Advance();

			// Print the next best genome
			mAppLog.AddLog("Generation: %d: ", mGA.GetGeneration());
			auto& newBest = mGA.GetBestGenome();
			for (auto& gene : newBest.chromosome)
				mAppLog.AddLog("%s ", std::to_string(gene).c_str());
				
			mAppLog.AddLog(" - %f", newBest.fitness);
			mAppLog.AddLog("\n");

		}
		if (mGA.GetBestGenome().chromosome ==KBestTarget|| mGA.GetBestGenome().chromosome==KTarget)
		{
			isFound = true;
		}
	}


}





void  GameState::DebugUI()
{
	//if (ImGui::Button("Init!"))
	//{
	//	mAppLog.AddLog("Initializing new population...\n");
	//	Initialize();
	//	for (size_t i = 0; i < mCitys.size(); i++)
	//	{
	//		mAppLog.AddLog("Ciry=%d, Pos ={ %f , %f} \n", i, mCitys[i].x, mCitys[i].y);
	//	}
	//}
	ImGui::ShowDemoWindow();


	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);


	if (ImGui::Button("Run!"))
	{
		mAppLog.AddLog("Initializing new population...\n");
		InitGA();
		mInitialized = true;
		drawLine = true;
	}
	DrawMap();
	ImGui::End();
	mAppLog.Draw("Console");


}



void GameState::DrawMap()
{

	ImVec2 circleSize{ 10.0f, 10.0f };
	ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoTitleBar);
	ImVec2 winPos = ImGui::GetWindowPos();
	ImVec2 winSize = ImGui::GetWindowSize();
	ImVec2 centre = winSize/2;
	//ImGui::SetNextWindowSize(winPos +offset);
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	ImColor color{ 1.0f, 1.0f, 1.0f };
	//drawList->AddRectFilled(winPos+ winSize, winPos+ winSize, color);
	ImVec2 startPos{ circleSize };
	ImVec2 endPos{ winSize - circleSize };
	offest += Vector2{ (centre + winPos).x,(centre + winPos).y };
	for (int i = 0; i < mNumCity; ++i)
	{

		drawList->AddCircle(ImVec2{mCitys[i].x,mCitys[i].y}+centre + winPos,25.0f,color);
		drawList->AddText(ImVec2{ mCitys[i].x,mCitys[i].y }+centre+ winPos,color,std::to_string(i).c_str());
		if (i!=mNumCity-1&& drawLine)
		{
			drawList->AddLine(ImVec2{ mCitys[i].x,mCitys[i].y }+centre + winPos, ImVec2{ mCitys[i + 1].x,mCitys[i + 1].y }+centre + winPos, color,0.5f);
		}
	}





	ImGui::End();

}

