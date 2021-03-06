#pragma once
#include"Common.h"
namespace KWSE::Graphics
{
	struct Bone
	{
		// all indices use for save load purpose.
		std::string name;
		int index = -1; // nodees index

		// use pointer only when game is running, but dont save it to file. because is an address, everytime run the program will be different.
		// so save the index, no matter where the memory is , the children index wont change.
		
		// hierarchy => tree	
		Bone* parent = nullptr; //runtime
		int parentIndex = -1;
		
		//Bunch of weak pointer -> raw pointer	
		std::vector<Bone*> children;
		std::vector<int> childrenIndices;//runtime

		Math::Matrix4 toParentTransform;
		Math::Matrix4  offsetTransform;
	};


}