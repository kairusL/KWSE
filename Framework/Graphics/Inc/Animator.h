#pragma once

#include "Model.h"

namespace KWSE::Graphics
{
	class Animator
	{
	public:
		Animator() = default;

		Animator(const Animator&) = delete;
		Animator& operator=(const Animator&) = delete;

		void Initialize(const KWSE::Graphics::Model* model) { mModel = model; }

		//void PlayAnimation(const char* clipName);
		void PlayAnimation(int clipIndex);
		void PlayAnimation(std::string name);
		void Play() { mAnimate = true; }
		void Stop() { mAnimate = false; }

		void Update(float deltaTime);

		const std::vector<KWSE::Math::Matrix4>& GetSkeletonTransform() const { return mSkeletonTransform; }
		const std::vector<KWSE::Math::Matrix4>& GetToLocalTransform() const { return mToLocalTransform; };

		void SetAnimationSpeed(float speed) { mAnimationSpeed = speed; }
		float GetAnimationSpeed() { return mAnimationSpeed; }
		void SetLooping(bool loop) { mLooping = loop; }



	private:
		const KWSE::Graphics::Model* mModel = nullptr;
		std::vector<KWSE::Math::Matrix4> mSkeletonTransform;
		std::vector<KWSE::Math::Matrix4> mToLocalTransform;
		float mAnimationTimer = 0.0f;
		float mAnimationSpeed = 1.0f;
		int mAnimClipIndex = 0;
		bool mAnimate = false;
		bool mLooping = false;
		bool mNameFinded = false;
		int clip=0;
	};
}