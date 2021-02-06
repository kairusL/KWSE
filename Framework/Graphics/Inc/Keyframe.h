#pragma once
#include "Common.h"
namespace KWSE::Graphics
{
	template <class T>
	struct Keyframe
	{
		T key;
		float time = 0.0f;
	};
	template <class T>
	using Keyframes = std::vector<Keyframe<T>>;

	using PositionKeys = Keyframes<Math::Vector3>;
	using RotationKeys = Keyframes<Math::Quaternion>;
	using ScaleKeys = Keyframes<Math::Vector3>;
}