#pragma once
 
#include "Common.h"
namespace KWSE
{
	enum ComponentId
	{
		Animation,
		Animator,
		Collider,
		Transform,
		Model, 
		Movement,
		State,
		Spawner

	};
	//FourCC - Four Character Code
	//constexpr uint32_t TransformComponentId = 1;

	enum ServiceId
	{
		Render,
	};


}

#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId(){return id;}\
	uint32_t GetTypeId() const override { return id; }