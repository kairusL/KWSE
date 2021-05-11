#pragma once
namespace KWSE
{

	class GameObject;
	namespace GameObjectIO
	{
		void Write(FILE* file, const GameObject& gameObject);
		void Read(FILE* file, GameObject& gameObject);
	}
}