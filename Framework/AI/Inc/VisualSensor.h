#pragma once
#include "Sensor.h"

namespace KWSE::AI
{
class VisualSensor : public Sensor
{
public:
	float viewRange;
	float viewAngle;

	uint64_t neighborTypeId;

	void Update(Agent& agent, MemoryRecords& memory, float deltaTime)  override;



};
}
