#include"GameState.h"
#include<ImGui/Inc/ImPlot.h>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <ImGui/Inc/ImPlot.h>
#include <ImGui/Src/imgui_internal.h>

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;

namespace
{
	struct ClusterResult
	{
		std::vector<Vector3> centroids;
		std::vector<int> assignment;
	};
	ClusterResult KMeansCluster(const std::vector<Vector3>& data, int k)
	{
		std::vector<Vector3> centroids;
		centroids.resize(k); 		//number of clusters to assign.
		for (auto& centroid : centroids)  // randomly initialize  k centroids.
		{
			centroid.x = RandomFloat(0, 800.0f);
			centroid.y = RandomFloat(0, 600.0f);
		}
		std::vector<int> assignment;
		assignment.resize(data.size());
		// Do assignment here, by finding the closest centroid the data point belongs to
		std::vector<Vector3> newCentroids;
		newCentroids.resize(k);

		bool centroidsChanged = true;

		while (centroidsChanged)
		{
			for (int i = 0; i < data.size(); ++i)
			{
				float clostestDistance = FLT_MAX;
				for (int j = 0; j < centroids.size(); ++j)
				{
					float distance = Distance(data[i], centroids[j]);
					if (clostestDistance > distance)
					{
						clostestDistance = distance;
						assignment[i] = j;
					}
				}
			}
			std::vector<int> assignmentCount; //Count how many group do we have 
			assignmentCount.resize(k);
			for (int i = 0; i < assignment.size(); ++i) // checking which centroid
			{
				//           group              pos
				newCentroids[assignment[i]] += data[i];
				assignmentCount[assignment[i]]++;
			}
			for (int i = 0; i < newCentroids.size(); ++i) // getting central of group
			{
				newCentroids[i] /= static_cast<float>(assignmentCount[i]);
			}
			for (int i = 0; i < newCentroids.size(); ++i)
			{
				// Compute new center position based on data assignment
				if (newCentroids[i].x != centroids[i].x && newCentroids[i].y != centroids[i].y)
				{
					centroidsChanged = true;
					break;
				}
				else
				{
					centroidsChanged = false;
				}
			}
			centroids = newCentroids;
		}

		ClusterResult result;
		result.centroids = std::move(centroids);

		result.assignment = std::move(assignment);
		return  result;
	}
	ClusterResult clusterResult;

}


void GameState::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(Colors::Black);

	mUnitTexture.Initialize(L"../../Assets/XImages/scv_01.png");

	for (size_t i = 0; i < 50; ++i)
	{
		float px = RandomFloat(0.0f, 800.0f);
		float py = RandomFloat(0.0f, 800.0f);
		float vX = RandomFloat(-100.0f, 100.0f);
		float vY = RandomFloat(-100.0f, 100.0f);

		mUnits.emplace_back(Unit{ {px,py}, {vX,vY} });
	}

}
void GameState::Terminate()
{

	mUnitTexture.Terminate();

}
void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
	{
		KWSE::MainApp().Quit();
		return;
	}

	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
	{
		std::vector<Vector3> data;
		int k = 3;
		for (size_t i = 0; i < mUnits.size(); ++i)
		{
			data.emplace_back( mUnits[i].position.x,mUnits[i].position.y,0.0f);
		}
		clusterResult = KMeansCluster(data, k);
		for (size_t i = 0; i < clusterResult.assignment.size(); ++i)
		{
			mUnits[i].cluster = clusterResult.assignment[i];
		}

	}

	for (auto& unit : mUnits)
	{
		unit.position += unit.velocity *deltaTime;
		if (unit.position.x < 0.0f)
		{
			unit.position.x += 800.0f;
		}
		if (unit.position.x > 800.0f)
		{
			unit.position.x -= 800.0f;
		}
		if (unit.position.y < 0.0f)
		{
			unit.position.y += 600.0f;
		}
		if (unit.position.y > 600.0f)
		{
			unit.position.y -= 600.0f;
		}
	}
}




void  GameState::DebugUI()
{
	ImGui::SetNextWindowSize({ 800.0f,600.0f });
	ImGui::Begin("game", nullptr, ImGuiWindowFlags_NoResize);
	ImVec2 winPos = ImGui::GetWindowPos();
	ImDrawList* drawList = ImGui::GetForegroundDrawList();

	ImVec2 unitSize = ImVec2{ 32.0f,32.0f };
	const ImU32 clusterColors[] = { 0xffff0000,0xff00ff00,0xff0000ff };
	for (auto& unit : mUnits)
	{
		ImGui::SetCursorPos(unit.position - (unitSize*0.5f));
		ImGui::Image(mUnitTexture.GetRawData(), unitSize);

		drawList->AddCircle(winPos + unit.position, 50.0f, clusterColors[unit.cluster]);
	}

	for (size_t i = 0; i < clusterResult.centroids.size(); ++i)
	{
		ImVec2 position;
		position.x = clusterResult.centroids[i].x;
		position.y = clusterResult.centroids[i].y;
		drawList->AddCircleFilled(winPos + position, 10.0f, clusterColors[i]);
	}





	ImGui::End();
}


