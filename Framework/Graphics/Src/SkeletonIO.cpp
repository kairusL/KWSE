#include"Precompiled.h"
#include "SkeletonIO.h"	

void KWSE::Graphics::SkeletonIO::Write(FILE * file, const Skeleton & skeleton)
{
	fprintf(file, "BoneCount: %d\n", static_cast<uint32_t>(skeleton.bones.size()));
	for (auto& bone : skeleton.bones)
	{
		fprintf(file, "Name: %s\n", bone->name.c_str());
		fprintf(file, "Index: %d\n", bone->index);
		fprintf(file, "ParentIndex: %d\n", bone->parent ? bone->parent->index : -1);
		fprintf(file, "ChildCount: %d\n", static_cast<uint32_t>(bone->children.size()));
		if (!bone->children.empty())
		{
			for (auto child : bone->children)
				fprintf(file, "%d ", child->index);
			fprintf(file, "\n");
		}
		const Math::Matrix4& _mP = bone->toParentTransform;
		fprintf(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			_mP._11, _mP._12, _mP._13, _mP._14,
			_mP._21, _mP._22, _mP._23, _mP._24,
			_mP._31, _mP._32, _mP._33, _mP._34,
			_mP._41, _mP._42, _mP._43, _mP._44);

		const Math::Matrix4& _mC = bone->toParentTransform;
		fprintf(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			_mC._11, _mC._12, _mC._13, _mC._14,
			_mC._21, _mC._22, _mC._23, _mC._24,
			_mC._31, _mC._32, _mC._33, _mC._34,
			_mC._41, _mC._42, _mC._43, _mC._44);
	}
}

void KWSE::Graphics::SkeletonIO::Read(FILE * file, Skeleton & skeleton)
{
	uint32_t boneCount = 0;
	fscanf_s(file, "BoneCount: %d\n", &boneCount);
	skeleton.bones.reserve(boneCount);

	for (uint32_t i = 0; i < boneCount; ++i)
	{
		auto& bone = skeleton.bones.emplace_back(std::make_unique<Bone>());

		char buffer[256];
		fscanf_s(file, "Name: %s\n", buffer, (uint32_t)std::size(buffer));
		bone->name = buffer;

		fscanf_s(file, "Index: %d\n", &bone->index);
		fscanf_s(file, "ParentIndex: %d\n", &bone->parentIndex);

		uint32_t childCount = 0;
		fscanf_s(file, "ChildCount: %d\n", &childCount);
		bone->childrenIndices.reserve(childCount);
	
		if (childCount > 0)
		{
			bone->childrenIndices.resize(childCount);
			for (uint32_t childIndex = 0; childIndex < childCount; ++childIndex)
			{
				fscanf_s(file, "%d ", &bone->childrenIndices[childIndex]);
			}
			fscanf_s(file, "\n");
		}
		const Math::Matrix4& _mP = bone->toParentTransform;
		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			&_mP._11, &_mP._12, &_mP._13, &_mP._14,
			&_mP._21, &_mP._22, &_mP._23, &_mP._24,
			&_mP._31, &_mP._32, &_mP._33, &_mP._34,
			&_mP._41, &_mP._42, &_mP._43, &_mP._44);
		const Math::Matrix4& _mC = bone->toParentTransform;
		fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			&_mC._11, &_mC._12, &_mC._13, &_mC._14,
			&_mC._21, &_mC._22, &_mC._23, &_mC._24,
			&_mC._31, &_mC._32, &_mC._33, &_mC._34,
			&_mC._41, &_mC._42, &_mC._43, &_mC._44);
		if (bone->parentIndex == -1)
		{
			skeleton.root = bone.get();
		}
	}
}
