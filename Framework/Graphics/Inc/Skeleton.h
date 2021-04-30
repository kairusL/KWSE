#pragma once
#include"Bone.h"
#include "AnimationClip.h"
namespace KWSE::Graphics
{

	//saving a tree to file is harder
	//saving an array to file is easy
	
	//cont
	//entry[ 0]
	struct Skeleton 
	{
		enum  DrawType
		{
			line,
			cone
		};
		Bone* root = nullptr;

		// All the bones in here , so "Bone* root = nullptr;" is weak pointer
		std::vector<std::unique_ptr<Bone>> bones;
	};
	
	void DrawSkeleton(const Skeleton& skeleton, const std::vector<Math::Matrix4>& boneMatrices,Skeleton::DrawType drawType);
	std::vector<KWSE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton, Math::Matrix4 worldMatrix);
	std::vector<KWSE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton, KWSE::Math::Matrix4 worldMatrix, const AnimationClip & animationClip, float animationTime);
	std::vector<KWSE::Math::Matrix4> CalculateSkinningMatrices(const Skeleton & skeleton);
	std::vector<KWSE::Math::Matrix4> CalculateSkinningMatrices(const Skeleton & skeleton, const AnimationClip & animationClip, float animationTime);
	

	std::vector<KWSE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton);
	std::vector<KWSE::Math::Matrix4> CalculateBoneMatrices(const Skeleton & skeleton, const AnimationClip& animationClip, float animationTime);

	//skeleton -> relationship between each bone.
	//boneMatrices -> array of matrix
	//[a b c 0]  (a b c) = right vector (X axis)
	//[d e f 0]  (d e f) = up vector (Y axis)
	//[g h i 0]  (g h i) = look vector (Z axis)
	//[x y z 1]  (x y z) = position
}