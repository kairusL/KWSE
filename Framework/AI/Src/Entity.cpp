#include "Precompiled.h"
#include "Entity.h"
#include "AIWorld.h"

using namespace KWSE::AI;

Entity::Entity(AIWorld& world, uint32_t typeId)
	:world(world)
	, mUniqueId((static_cast<uint64_t>(typeId) << 32) | world.GetNextId())
{
	world.RegisterEntity(this);
}

Entity::~Entity()
{
	world.UnregisterEntity(this);
}

KWSE::Math::Matrix3 Entity::LocalToWorld() const
{
	auto f = KWSE::Math::Normalize(heading);
	auto s = KWSE::Math::PerpendicularRH(f);
	auto p = position;

	return
	{
		 s.x,s.y,0.0f,
		 f.x,f.y,0.0f,
		 p.x,p.y,1.0f
	};
}