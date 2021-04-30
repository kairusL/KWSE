#include "Precompiled.h"
#include "Skeleton.h"

#include "SimpleDraw.h"

using namespace KWSE;
using namespace KWSE::Graphics;

namespace
{
	void DrawSkeletonConeShapes(const Skeleton & skeleton, const std::vector<Math::Matrix4>& boneMatrices)
	{
		auto treeDepth = [](const Bone* bone) -> float
		{
			auto treeDepthRecursive = [](auto func, const Bone* bone) -> float
			{
				float maxDepth = 0.0f;
				for (auto child : bone->children)
				{
					float childDepth = func(func, child);
					if (childDepth > maxDepth)
						maxDepth = childDepth;
				}
				return maxDepth + 1.0f;
			};
			return treeDepthRecursive(treeDepthRecursive, bone);
		};

		const float maxDepth = treeDepth(skeleton.root);
		auto drawBone = [&boneMatrices, maxDepth](const Bone* bone) -> void
		{
			auto drawBoneRecursive = [&boneMatrices](auto func, const Bone* bone, float depth, float maxDepth) -> void
			{
				if (bone->parent)
				{
					auto from = Math::GetTranslation(boneMatrices[bone->parentIndex]);
					auto to = Math::GetTranslation(boneMatrices[bone->index]);
					auto p = (depth / maxDepth);
					Color color{ 1.0f - p, 0.5f * p, p ,1.0f };
					SimpleDraw::AddCone(from, to - from, 0.15f, color);
				}

				for (auto child : bone->children)
					func(func, child, depth + 1.0f, maxDepth);
			};
			drawBoneRecursive(drawBoneRecursive, bone, 1.0f, maxDepth);
		};

		drawBone(skeleton.root);
	}

	void DrawBone(const Skeleton& skeleton, Bone* bone, const std::vector<Math::Matrix4>& boneMatrices)
	{
		if (bone->parent)
		{
			auto from = Math::GetTranslation(boneMatrices[bone->parentIndex]);
			auto to = Math::GetTranslation(boneMatrices[bone->index]);
			SimpleDraw::AddLine(from, to, Colors::Blue);
		}
		for (const auto& child : bone->children)
			DrawBone(skeleton, child, boneMatrices);
	}

	void ApplyBoneMatrices(Bone * bone, std::vector<Math::Matrix4>& boneMatrices)
	{
		boneMatrices[bone->index] = Math::Matrix4::Identity;
		if (bone->parent)
			boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parentIndex];

		for (const auto& child : bone->children)
			ApplyBoneMatrices(child, boneMatrices);
	}

	void ApplyBoneMatrices(Bone * bone, const AnimationClip& clip, std::vector<KWSE::Math::Matrix4>& boneMatrices, float animationTime)
	{
		boneMatrices[bone->index] = Math::Matrix4::Identity;
		if (bone->parent)
		{
			auto& boneAnim = clip.boneAnimations[bone->index];
			if (boneAnim)
			{
				Math::Vector3 scale = boneAnim->IsPositionKeyEmpty() ? Math::Vector3::One : boneAnim->GetScale(animationTime);
				Math::Quaternion rot = boneAnim->IsRotationKeyEmpty() ? Math::Quaternion::Identity : boneAnim->GetRotation(animationTime);
				Math::Vector3 pos = boneAnim->IsPositionKeyEmpty() ? Math::Vector3::Zero : boneAnim->GetPosition(animationTime);
				auto boneTransform = Math::Matrix4::Scaling(scale)*Math::Matrix4::RotationQuaternion(rot)*Math::Matrix4::Translation(pos);
				boneMatrices[bone->index] = boneTransform * boneMatrices[bone->parentIndex];
			}
			else
			{
				boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parentIndex];
			}
		}
		else
		{
			boneMatrices[bone->index] = bone->toParentTransform;
		}

		for (const auto& child : bone->children)
			ApplyBoneMatrices(child, clip, boneMatrices, animationTime);
	}
	//void ApplyBoneMatrices(Bone * bone, const AnimationClip& clip, std::vector<KWSE::Math::Matrix4>& boneMatrices, float animationTime)
	//{
	//	boneMatrices[bone->index] = Math::Matrix4::Identity;
	//	if (bone->parent)
	//	{
	//		auto& boneAnim = clip.boneAnimations[bone->index];
	//		if (boneAnim)
	//		{
	//			Math::Vector3 scale = boneAnim->IsPositionKeyEmpty() ? Math::Vector3::One : boneAnim->GetScale(animationTime);
	//			Math::Quaternion rot = boneAnim->IsRotationKeyEmpty() ? Math::Quaternion::Identity : boneAnim->GetRotation(animationTime);
	//			Math::Vector3 pos = boneAnim->IsPositionKeyEmpty() ? Math::Vector3::Zero : boneAnim->GetPosition(animationTime);
	//			auto boneTransform = Math::Matrix4::Scaling(scale)*Math::Matrix4::RotationQuaternion(rot)*Math::Matrix4::Translation(pos);
	//			boneMatrices[bone->index] = boneTransform * boneMatrices[bone->parentIndex];
	//		}
	//		//else
	//		//{
	//		//	boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parentIndex];
	//		//}
	//	}
	//	//else
	//	//{
	//	//	boneMatrices[bone->index] = bone->toParentTransform;
	//	//}
	//	for (const auto& child : bone->children)
	//		ApplyBoneMatrices(child, clip, boneMatrices, animationTime);
	//}
}

void KWSE::Graphics::DrawSkeleton(const Skeleton & skeleton, const std::vector<Math::Matrix4>& boneMatrices, Skeleton::DrawType drawType)
{
	if (drawType == Skeleton::DrawType::line)
		DrawBone(skeleton, skeleton.root, boneMatrices);
	else if (drawType == Skeleton::DrawType::cone)
		DrawSkeletonConeShapes(skeleton, boneMatrices);
}

std::vector<Math::Matrix4> KWSE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, Math::Matrix4 worldMatrix)
{
	std::vector<Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, boneMatrices);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform) * worldMatrix;

	return boneMatrices;
}

std::vector<Math::Matrix4> KWSE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, Math::Matrix4 worldMatrix, const AnimationClip & animationClip, float animationTime)
{
	std::vector<Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, animationClip, boneMatrices, animationTime);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform) * worldMatrix;

	return boneMatrices;
}

std::vector<KWSE::Math::Matrix4> KWSE::Graphics::CalculateSkinningMatrices(const Skeleton & skeleton)
{
	std::vector<KWSE::Math::Matrix4> skinningMatrices;
	skinningMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, skinningMatrices);

	return skinningMatrices;
}

std::vector<KWSE::Math::Matrix4> KWSE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton)
{
	std::vector<Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, boneMatrices);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform);

	return boneMatrices;
}

std::vector<KWSE::Math::Matrix4> KWSE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, const AnimationClip & animationClip, float animationTime)
{
	std::vector<Math::Matrix4> boneMatrices;
	boneMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, animationClip, boneMatrices, animationTime);

	for (auto& matrix : boneMatrices)
		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform);

	return boneMatrices;
}

std::vector<KWSE::Math::Matrix4> KWSE::Graphics::CalculateSkinningMatrices(const Skeleton & skeleton, const AnimationClip & animationClip, float animationTime)
{
	std::vector<KWSE::Math::Matrix4> skinningMatrices;
	skinningMatrices.resize(skeleton.bones.size());

	ApplyBoneMatrices(skeleton.root, animationClip, skinningMatrices, animationTime);

	return skinningMatrices;
}

//namespace
//{
//	int c = 1.0f;
//	float DepthCheck(Bone* bone)
//	{
//		float maxDepth = 0.0f;
//		for (auto child : bone->children)
//		{
//			return DepthCheck(child)+1.0f;
//		}
//
//	}
//	void DrawBone(const Skeleton& skeleton, Bone* bone, const std::vector<Math::Matrix4>& boneMatrices)
//	{
//		const float maxDepth =DepthCheck(skeleton.root);
//		if (bone->parent)
//		{
//			auto from = Math::GetTranslation(boneMatrices[bone->parentIndex]);
//			auto to = Math::GetTranslation(boneMatrices[bone->index]);
//			
//			auto p = ++c / maxDepth;
//			Color color{ 1.0f - p, 2.0f * p, p, 1.0f };
//			//SimpleDraw::AddLine(from, to, Colors::Black);
//			SimpleDraw::AddCone(from, to - from, 0.1f, color);
//		}
//		for (const auto& child : bone->children)
//			DrawBone(skeleton, child, boneMatrices);
//	}
//
//	void ApplyBoneMatrices(Bone * bone, std::vector<KWSE::Math::Matrix4>& boneMatrices)
//	{
//		boneMatrices[bone->index] = Math::Matrix4::Identity;
//		if (bone->parent)
//			boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parentIndex];
//
//		for (const auto& child : bone->children)
//			ApplyBoneMatrices(child, boneMatrices);
//	}
//
//	void ApplyBoneMatrices(Bone * bone, const AnimationClip& clip, std::vector<KWSE::Math::Matrix4>& boneMatrices, float animationTime)
//	{
//		boneMatrices[bone->index] = Math::Matrix4::Identity;
//		if (bone->parent)
//		{
//			Animation& boneAnim = *clip.boneAnimations[bone->index];
//			if (!boneAnim.IsScaleKeyEmpty())
//				boneMatrices[bone->index] = Math::Matrix4::Scaling(boneAnim.GetScale(animationTime));
//			if (!boneAnim.IsRotationKeyEmpty())
//				boneMatrices[bone->index] = boneMatrices[bone->index] * Math::Matrix4::RotationQuaternion(boneAnim.GetRotation(animationTime));
//			if (!boneAnim.IsPositionKeyEmpty())
//				boneMatrices[bone->index] = boneMatrices[bone->index] * Math::Matrix4::Translation(boneAnim.GetPosition(animationTime));
//			boneMatrices[bone->index] = boneMatrices[bone->index] * boneMatrices[bone->parentIndex];
//		}
//
//		for (const auto& child : bone->children)
//			ApplyBoneMatrices(child, clip, boneMatrices, animationTime);
//	}
//}
//
//void KWSE::Graphics::DrawSkeleton(const Skeleton & skeleton, const std::vector<Math::Matrix4>& boneMatrices)
//{
//	DrawBone(skeleton, skeleton.root, boneMatrices);
//}
//
//std::vector<KWSE::Math::Matrix4> KWSE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, KWSE::Math::Matrix4 worldMatrix, const AnimationClip & animationClip, float animationTime)
//{
//	std::vector<KWSE::Math::Matrix4> boneMatrices;
//	boneMatrices.resize(skeleton.bones.size());
//
//	ApplyBoneMatrices(skeleton.root, animationClip, boneMatrices, animationTime);
//
//	for (auto& matrix : boneMatrices)
//		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform) * worldMatrix;
//
//	return boneMatrices;
//}
//
//std::vector<KWSE::Math::Matrix4> KWSE::Graphics::CalculateBoneMatrices(const Skeleton & skeleton, Math::Matrix4 worldMatrix)
//{
//	std::vector<KWSE::Math::Matrix4> boneMatrices;
//	boneMatrices.resize(skeleton.bones.size());
//
//	ApplyBoneMatrices(skeleton.root, boneMatrices);
//
//	for (auto& matrix : boneMatrices)
//		matrix = matrix * Math::Inverse(skeleton.root->toParentTransform) * worldMatrix;
//
//	return boneMatrices;
//}