#pragma once
#include<KWSE/Inc/KWSE.h>
#include "Pipe.h"

using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;

class Bird;

class PipeManager
{
public:
	void Update(float deltaTime);
	void Render();

	void Reset();

	bool Intersect(const Bird& bird) const;
	const Pipe& GetClosestPipe(const Bird& bird) const;

private:
	std::vector<Pipe> mPipes;
	float mSpawnDelay = 0.0f;
};