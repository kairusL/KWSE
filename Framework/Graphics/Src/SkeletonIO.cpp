#include"Precompiled.h"
#include "SkeletonIO.h"	

//void KWSE::Graphics::SkeletonIO::Write(FILE * file, const Skeleton & skeleton)
//{
//	fprintf(file, "BoneCount: %d\n", static_cast<uint32_t>(skeleton.bones.size()));
//	for (auto& bone : skeleton.bones)
//	{
//		fprintf(file, "Name: %s\n", bone->name.c_str());
//		fprintf(file, "Index: %d\n", bone->index);
//		fprintf(file, "ParentIndex: %d\n", bone->parent ? bone->parent->index : -1);
//		fprintf(file, "ChildCount: %d\n", static_cast<uint32_t>(bone->children.size()));
//		if (!bone->children.empty())
//		{
//			for (auto child : bone->children)
//				fprintf(file, "%d ", child->index);
//			fprintf(file, "\n");
//		}
//		const Math::Matrix4& _mP = bone->toParentTransform;
//		fprintf(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
//			_mP._11, _mP._12, _mP._13, _mP._14,
//			_mP._21, _mP._22, _mP._23, _mP._24,
//			_mP._31, _mP._32, _mP._33, _mP._34,
//			_mP._41, _mP._42, _mP._43, _mP._44);
//
//		const Math::Matrix4& _mC = bone->toParentTransform;
//		fprintf(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
//			_mC._11, _mC._12, _mC._13, _mC._14,
//			_mC._21, _mC._22, _mC._23, _mC._24,
//			_mC._31, _mC._32, _mC._33, _mC._34,
//			_mC._41, _mC._42, _mC._43, _mC._44);
//	}
//}
//
//void KWSE::Graphics::SkeletonIO::Read(FILE * file, Skeleton & skeleton)
//{
//	uint32_t boneCount = 0;
//	fscanf_s(file, "BoneCount: %d\n", &boneCount);
//	skeleton.bones.reserve(boneCount);
//
//	for (uint32_t i = 0; i < boneCount; ++i)
//	{
//		auto& bone = skeleton.bones.emplace_back(std::make_unique<Bone>());
//
//		char buffer[256];
//		fscanf_s(file, "Name: %s\n", buffer, (uint32_t)std::size(buffer));
//		bone->name = buffer;
//
//		fscanf_s(file, "Index: %d\n", &bone->index);
//		fscanf_s(file, "ParentIndex: %d\n", &bone->parentIndex);
//
//		uint32_t childCount = 0;
//		fscanf_s(file, "ChildCount: %d\n", &childCount);
//		bone->childrenIndices.reserve(childCount);
//	
//		if (childCount > 0)
//		{
//			bone->childrenIndices.resize(childCount);
//			for (uint32_t childIndex = 0; childIndex < childCount; ++childIndex)
//			{
//				fscanf_s(file, "%d ", &bone->childrenIndices[childIndex]);
//			}
//			fscanf_s(file, "\n");
//		}
//		const Math::Matrix4& _mP = bone->toParentTransform;
//		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
//			&_mP._11, &_mP._12, &_mP._13, &_mP._14,
//			&_mP._21, &_mP._22, &_mP._23, &_mP._24,
//			&_mP._31, &_mP._32, &_mP._33, &_mP._34,
//			&_mP._41, &_mP._42, &_mP._43, &_mP._44);
//		const Math::Matrix4& _mC = bone->toParentTransform;
//		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
//			&_mC._11, &_mC._12, &_mC._13, &_mC._14,
//			&_mC._21, &_mC._22, &_mC._23, &_mC._24,
//			&_mC._31, &_mC._32, &_mC._33, &_mC._34,
//			&_mC._41, &_mC._42, &_mC._43, &_mC._44);
//		if (bone->parentIndex == -1)
//		{
//			skeleton.root = bone.get();
//		}
//	}
//}


void KWSE::Graphics::SkeletonIO::Write(FILE * file, const Skeleton & skeleton)
{
	const auto& bones = skeleton.bones;
	const int boneCount = static_cast<int>(bones.size());
	fprintf_s(file, "%d\n", boneCount);

	const int rootIndex = skeleton.root->index;
	fprintf_s(file, "%d\n", rootIndex);

	for (size_t i = 0; i < bones.size(); ++i)
	{
		fprintf_s(file, "%s ", bones[i]->name.c_str());
		fprintf_s(file, "%d ", bones[i]->index);
		fprintf_s(file, "%d ", bones[i]->parentIndex);

		const auto& childIndices = bones[i]->childrenIndices;
		const int childIndicesCount = static_cast<int>(childIndices.size());
		fprintf_s(file, "%d ", childIndicesCount);
		for (const auto& index : childIndices)
			fprintf_s(file, "%d ", index);

		fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"
			, bones[i]->toParentTransform._11, bones[i]->toParentTransform._12, bones[i]->toParentTransform._13, bones[i]->toParentTransform._14
			, bones[i]->toParentTransform._21, bones[i]->toParentTransform._22, bones[i]->toParentTransform._23, bones[i]->toParentTransform._24
			, bones[i]->toParentTransform._31, bones[i]->toParentTransform._32, bones[i]->toParentTransform._33, bones[i]->toParentTransform._34
			, bones[i]->toParentTransform._41, bones[i]->toParentTransform._42, bones[i]->toParentTransform._43, bones[i]->toParentTransform._44);

		fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"
			, bones[i]->offsetTransform._11, bones[i]->offsetTransform._12, bones[i]->offsetTransform._13, bones[i]->offsetTransform._14
			, bones[i]->offsetTransform._21, bones[i]->offsetTransform._22, bones[i]->offsetTransform._23, bones[i]->offsetTransform._24
			, bones[i]->offsetTransform._31, bones[i]->offsetTransform._32, bones[i]->offsetTransform._33, bones[i]->offsetTransform._34
			, bones[i]->offsetTransform._41, bones[i]->offsetTransform._42, bones[i]->offsetTransform._43, bones[i]->offsetTransform._44);
	}
}

void KWSE::Graphics::SkeletonIO::Read(FILE * file, Skeleton & skeleton)
{
	int boneCount = 0;
	fscanf_s(file, "%d ", &boneCount);

	int rootIndex = 0;
	fscanf_s(file, "%d ", &rootIndex);

	char strBuff[255];
	skeleton.bones.reserve(boneCount);

	for (int i = 0; i < boneCount; ++i)
	{
		auto& bone = skeleton.bones.emplace_back(std::make_unique<Bone>());
		fscanf_s(file, "%s ", &strBuff, (int)std::size(strBuff));
		bone->name = strBuff;
		fscanf_s(file, "%d ", &bone->index);
		fscanf_s(file, "%d ", &bone->parentIndex);

		int childIndicesCount = 0;
		fscanf_s(file, "%d ", &childIndicesCount);
		auto& childIndices = bone->childrenIndices;
		childIndices.resize(childIndicesCount);

		for (size_t j = 0; j < childIndices.size(); ++j)
			fscanf_s(file, "%d ", &childIndices[j]);

		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"
			, &bone->toParentTransform._11, &bone->toParentTransform._12, &bone->toParentTransform._13, &bone->toParentTransform._14
			, &bone->toParentTransform._21, &bone->toParentTransform._22, &bone->toParentTransform._23, &bone->toParentTransform._24
			, &bone->toParentTransform._31, &bone->toParentTransform._32, &bone->toParentTransform._33, &bone->toParentTransform._34
			, &bone->toParentTransform._41, &bone->toParentTransform._42, &bone->toParentTransform._43, &bone->toParentTransform._44);

		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"
			, &bone->offsetTransform._11, &bone->offsetTransform._12, &bone->offsetTransform._13, &bone->offsetTransform._14
			, &bone->offsetTransform._21, &bone->offsetTransform._22, &bone->offsetTransform._23, &bone->offsetTransform._24
			, &bone->offsetTransform._31, &bone->offsetTransform._32, &bone->offsetTransform._33, &bone->offsetTransform._34
			, &bone->offsetTransform._41, &bone->offsetTransform._42, &bone->offsetTransform._43, &bone->offsetTransform._44);
	}

	skeleton.root = skeleton.bones[rootIndex].get();
}