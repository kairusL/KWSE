#pragma once

#include "AnimationClip.h"
#include "Animation.h"

namespace KWSE::Graphics
{
	class AnimationIO
	{
	public:
		static void Write(FILE* file, const KWSE::Graphics::AnimationClip& clip);
		static void Read(FILE* file, KWSE::Graphics::AnimationClip& clip);
		static void WriteBinary(FILE* file, const KWSE::Graphics::AnimationClip& clip);
		static void ReadBinary(FILE* file, KWSE::Graphics::AnimationClip& clip);
	};
}
