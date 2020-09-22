#include "Precompiled.h"
#include "AIWorld.h"

using namespace KWSE::AI;
using namespace KWSE::Graphics;
namespace// internal linkage
{
	template <class Element >
	std::vector<Element*>GetElements
	(const PartitionGrid<Entity>& grid,
		const KWSE::Math::Circle& range,
		float cellSize,
		uint32_t typeId)

	{
		std::vector<Element*>elements;

		int minX = static_cast<int>((range.center.x - range.radius) / cellSize);
		int maxX = static_cast<int>((range.center.x + range.radius) / cellSize);
		int minY = static_cast<int>((range.center.y - range.radius) / cellSize);
		int maxY = static_cast<int>((range.center.y + range.radius) / cellSize);

		minX = KWSE::Math::Max(minX, 0);
		maxX = KWSE::Math::Min(maxX, grid.GetColumns() - 1);
		minY = KWSE::Math::Max(minY, 0);
		maxY = KWSE::Math::Min(maxY, grid.GetRows() - 1);

		for (int y = 0; y < maxY; ++y)
		{

			for (int x = minX; x < maxX; ++x)
			{
				auto& cell = grid.GetCell(x, y);
				for (auto& element : cell)
				{
					if (element->GetTypeId() == typeId)
					{
						elements.push_back(static_cast<Element*>(element));
					}
				}
			}
		}
		return elements;

	}

}

void KWSE::AI::AIWorld::Initialize(const Settings& settings)
{
	mSettings = settings;
	ASSERT(settings.partitionGridSize > 0.0f, "[AIWorld] Partition grid size must be greater than 0 ");
	const int columns = static_cast<int> (std::ceilf(settings.worldSize.x / settings.partitionGridSize));
	const int rows = static_cast<int> (std::ceilf(settings.worldSize.y / settings.partitionGridSize));
	mPartitionGrid.Resize(columns, rows);

}

void KWSE::AI::AIWorld::Update()
{
	mPartitionGrid.ClearCells();
	for (auto entity : mEntities)
	{
		const int columns = static_cast<int> (entity->position.x / mSettings.partitionGridSize);
		const int rows = static_cast<int> (entity->position.y / mSettings.partitionGridSize);
		mPartitionGrid.GetCell(columns, rows).push_back(entity);
	}

}

void KWSE::AI::AIWorld::RegisterEntity(Entity * entity)
{
	mEntities.push_back(entity);
}

void KWSE::AI::AIWorld::UnregisterEntity(Entity * entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	}
}

void KWSE::AI::AIWorld::AddObstacles(const KWSE::Math::Circle & obstacles)
{
	mObstacles.push_back(obstacles);
}

void KWSE::AI::AIWorld::AddWalls(const KWSE::Math::LineSegment & wall)
{
	mWalls.push_back(wall);
}


EntityList KWSE::AI::AIWorld::GetEntities(const KWSE::Math::Circle & range, uint32_t typeId)
{
	return GetElements<Entity>(mPartitionGrid, range, mSettings.partitionGridSize, typeId);
}

AgentList KWSE::AI::AIWorld::GetNeighborhood(const KWSE::Math::Circle & range, uint32_t typeId)
{
	return GetElements<Agent>(mPartitionGrid, range, mSettings.partitionGridSize, typeId);
}

Entity* KWSE::AI::AIWorld::GetEntity(uint64_t entityId)
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->GetUniqurId() == entityId)
		{
			return mEntities[i];
		}
	}
	return nullptr;
}



void AIWorld::DebugDraw()
{
	for (auto& obstacles : mObstacles)
		KWSE::Graphics::SimpleDraw::AddScreenCircle(obstacles.center, obstacles.radius, KWSE::Graphics::Colors::Cyan);
	for (auto& wall : mWalls)
		KWSE::Graphics::SimpleDraw::AddScreenLine(wall.from, wall.to, KWSE::Graphics::Colors::Cyan);
	for (int x = 0; x < mPartitionGrid.GetColumns(); ++x)
	{
		KWSE::Math::Vector2 to = { x*   mSettings.partitionGridSize ,0 };
		KWSE::Math::Vector2 from = { x* mSettings.partitionGridSize ,static_cast<float>(KWSE::Graphics::GraphicsSystem::Get()->GetBackBufferHeight()) };
		KWSE::Graphics::SimpleDraw::AddScreenLine(to, from, KWSE::Graphics::Colors::LightBlue);
	}
	for (int y = 0; y < mPartitionGrid.GetRows(); ++y)
	{
		KWSE::Math::Vector2 to = { 0, y*   mSettings.partitionGridSize };
		KWSE::Math::Vector2 from = { static_cast<float>(KWSE::Graphics::GraphicsSystem::Get()->GetBackBufferWidth()), y* mSettings.partitionGridSize };
		KWSE::Graphics::SimpleDraw::AddScreenLine(to, from, KWSE::Graphics::Colors::LightBlue);
	}
}

// checking if there is wall or obstacle. 
bool AIWorld::HasLineOfSight(const KWSE::Math::Vector2 & start, const KWSE::Math::Vector2 & end) const
{
	KWSE::Math::LineSegment line{ start,end };
	for (auto& wall : mWalls)
	{
		if (KWSE::Math::Intersect(line, wall))
		{
			return false;
		}
	}
	for (auto& obstacle : mObstacles)
	{
		if (KWSE::Math::Intersect(line, obstacle))
		{
			return false;
		}
	}
	return true;

}

uint32_t AIWorld::GetNextId()
{

	ASSERT(mNextId < UINT32_MAX, "Run out of Ids");
	return mNextId++;

}
