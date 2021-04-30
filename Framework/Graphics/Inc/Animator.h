#pragma once

#include "Model.h"

namespace KWSE::Graphics
{
	class Animator
	{
	public:
		Animator() = default;
		~Animator();

		Animator(const Animator&) = delete;
		Animator& operator=(const Animator&) = delete;

		void Initialize(KWSE::Graphics::Model* model) { mModel = model; }
		void Terminate();

		void AddClip(std::filesystem::path fileName);

		//void PlayAnimation(const char* clipName);
		void PlayAnimation(int clipIndex);
		void Play() { mAnimate = true; }
		void Stop() { mAnimate = false; }

		void Update(float deltaTime);

		const std::vector<KWSE::Math::Matrix4> GetSkeletonTransform(const KWSE::Math::Matrix4 matWorld = KWSE::Math::Matrix4::Identity);;
		const std::vector<KWSE::Math::Matrix4> GetToLocalTransform() const { return mToLocalTransform; };

		void SetAnimationSpeed(float speed) { mAnimationSpeed = speed; }
		void SetLooping(bool loop) { mLooping = loop; }

	private:
		KWSE::Graphics::Model* mModel = nullptr;
		std::vector<KWSE::Math::Matrix4> mSkeletonTransform;
		std::vector<KWSE::Math::Matrix4> mToLocalTransform;
		float mAnimationTimer = 0.0f;
		float mAnimationSpeed = 1.0f;
		int mAnimClipIndex = 0;
		bool mAnimate = false;
		bool mLooping = false;
	};
}