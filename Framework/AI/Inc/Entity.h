#pragma once


namespace KWSE::AI
{
	class AIWorld;
	class Entity;
	using EntityList = std::vector<Entity*>;

	class Entity
	{
	public:


		//& *const address to the aiworld can not be change. but the world cant be change.
		Entity(AIWorld& world, uint32_t typeId);

		virtual ~Entity();

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator =(Entity&&) = delete;

		KWSE::Math::Matrix3 LocalToWorld() const;
		const uint32_t GetTypeId() const { return mUniqueId >> 32; }
		const uint64_t GetUniqurId() const { return mUniqueId; }

		AIWorld& world;
		KWSE::Math::Vector2 position = KWSE::Math::Vector2::Zero;
		KWSE::Math::Vector2 heading = KWSE::Math::Vector2::YAxis;
		float radius = 1.0f;

	private:
		const uint64_t mUniqueId = 0;


	};


}