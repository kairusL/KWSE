#include "Precompiled.h"
#include "GameObjectIO.h"

#include "GameObject.h"

#include "AnimatorComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"


#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

using namespace KWSE;
using namespace rapidjson;

void GameObjectIO::Write(FILE* file, const GameObject& gameObject)
{
	//Todo

}

void GameObjectIO::Read(FILE* file,GameObject& gameObject)
{
	char readBuffer[65536];
	FileReadStream readStream(file, readBuffer, sizeof(readBuffer));

	Document document;
	document.ParseStream(readStream);

	// get object from json file.
	// 1. grab the object by name.
	document.HasMember("Components");
	auto components = document["Components"].GetObj();
	// 2. iterate the stuff in it.
	for (auto& component : components)
	{
		// 3. check the which childs name under the components.  then we need to add that.
		const char* componentName = component.name.GetString();
		if (strcmp(componentName,"TransformComponent")==0)
		{
			auto transform =	gameObject.AddComponent<TransformComponent>();
			// sometimes have the component but you dont actually want to initialize it.
			// want to keep it empty for example.
			// if thats the case, cannot guarantee you have a component in there.
			// So need to check if there is something call position in there.
			if (component.value.HasMember("Position"))
			{
				const auto& position = component.value["Position"].GetArray();
				float x = position[0].GetFloat();
				float y = position[1].GetFloat();
				float z = position[2].GetFloat();
				transform->SetPosition({ x,y,z });
			}
		}		
		else if (strcmp(componentName,"ColliderComponent")==0)
		{
			auto collider = gameObject.AddComponent<ColliderComponent>();
			// load collider stuff here.
			if (component.value.HasMember("Center"))
			{
				const auto& center = component.value["Center"].GetArray();
				float x = center[0].GetFloat();
				float y = center[1].GetFloat();
				float z = center[2].GetFloat();
				collider->SetCenter({ x,y,z });
			}
			if (component.value.HasMember("Extend"))
			{
				const auto& extend = component.value["Extend"].GetArray();
				float x = extend[0].GetFloat();
				float y = extend[1].GetFloat();
				float z = extend[2].GetFloat();				
				collider->SetExtend({ x,y,z });
			}
		}
		else if (strcmp(componentName, "ModelComponent") == 0)
		{
			auto model = gameObject.AddComponent<ModelComponent>();
			if (component.value.HasMember("FileName"))
			{  
				const auto& FName = component.value["FileName"].GetString();
				model->SetFileName(FName);
			}
			if (component.value.HasMember("AnimationFileName"))
			{
				const auto& FName = component.value["AnimationFileName"].GetString();
				model->SetFileName(FName);
			}
		}
		else if (strcmp(componentName, "AnimatorComponent") == 0)
		{
			auto animator = gameObject.AddComponent<AnimatorComponent>();
		}
	}
}


