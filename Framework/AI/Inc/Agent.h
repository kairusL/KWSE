#pragma once
#include"Entity.h"

// Never use using namespace in the header 
namespace KWSE::AI
{
	class Agent;
	using AgentList = std::vector < Agent*>;


	class Agent : public Entity
	{
	public:
		Agent(AIWorld& world, uint32_t typeId);
		~Agent() override = default;

		Agent* threat = nullptr;


		AgentList neighbors;
		KWSE::Math::Vector2 velocity = KWSE::Math::Vector2();
		KWSE::Math::Vector2 destination = KWSE::Math::Vector2();
		float maxSpeed = 1.0f;
		float mass = 1.0f;
	};

}