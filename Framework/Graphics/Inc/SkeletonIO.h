#pragma once
#include "Skeleton.h"

namespace KWSE::Graphics::SkeletonIO
{
	void Write(FILE* file, const Skeleton& skeleton);
	void Read(FILE* file, Skeleton& skeleton);
}