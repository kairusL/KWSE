#pragma once
#include"Common.h"
namespace KWSE
{

	class GameObjectHandle
	{
		public:
			GameObjectHandle() = default;

			//bool IsValid() const { return mIndex != -1 && mGeneration != -1; }
	private:
		friend class GameWorld;
		int mIndex = -1;
		int mGeneration = -1;

	};
}