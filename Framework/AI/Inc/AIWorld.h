#pragma once
#include "Agent.h"
#include "PartitionGrid.h"
namespace KWSE::AI
{
	class AIWorld
	{

	public:

		struct Settings
		{
			KWSE::Math::Vector2 worldSize;
			float partitionGridSize=0.0f;
		};


		using	Obstacles = std::vector < KWSE::Math::Circle>;
		using	Walls = std::vector<KWSE::Math::LineSegment>;

		void Initialize(const Settings& settings);
		void Update();

		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		void AddObstacles(const KWSE::Math::Circle& obstacles);
		void AddWalls(const KWSE::Math::LineSegment& wall);

		EntityList GetEntities(const KWSE::Math::Circle& range, uint32_t typeId);
		AgentList GetNeighborhood(const KWSE::Math::Circle&range, uint32_t typeId);


		Entity* GetEntity(uint64_t entityId);
		const Obstacles& GetObstacles() { return mObstacles; }
		const Walls& GetWalls() { return mWalls; }

		bool HasLineOfSight(const KWSE::Math::Vector2& start, const KWSE::Math::Vector2& end) const;

		uint32_t GetNextId();


		void DebugDraw();

	private:
		Settings mSettings;
		EntityList mEntities;
		Obstacles mObstacles;
		Walls mWalls;
		PartitionGrid<Entity> mPartitionGrid;

		uint32_t mNextId = 0;



	};






}