#include "Precompiled.h"
#include "Skeleton.h"

#include "SimpleDraw.h"

using namespace KWSE;
using namespace KWSE::Graphics;
namespace
{
	void DrawBone(const Skeleton& skeleton, Bone* bone, const std::vector<Math::Matrix4>& boneMatrices)
	{
		if (bone->parent)
		{
			auto from = Math::GetTranslation(boneMatrices[bone->parentIndex]);
			auto to = Math::GetTranslation(boneMatrices[bone->index]);
			SimpleDraw::AddLine(from, to, Colors::Black);
		}
		for (const auto& child : bone->children)
			DrawBone(skeleton, child, boneMatrices);
	}

	void ApplyBoneMatrices(Bone * bone, std::vector<KWSE::Math::Matrix4>& boneMatrices)
	{
		boneMatrices[bone->index] = Math::Matrix4::Identity;
		if (bone->parent)
			boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parentIndex];

		for (const auto& child : bone->children)
			ApplyBoneMatrices(child, boneMatrices);
	}
}

void KWSE::Graphics::DrawSkeleton(const Skeleton & skeleton, const std::vector<Math::Matrix4>& boneMatrices)
{
	DrawBone(skeleton, skeleton.root, boneMatrices);
}

std::vector<KWSE::Math::Matrix4> KWSE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, Math::Matrix4 worldMatrix)
{
	std::vector<KWSE::Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, boneMatrices);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform) * worldMatrix;

	return boneMatrices;
}