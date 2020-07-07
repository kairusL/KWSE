#pragma once
#include "Camera.h"
#include "Colors.h"
#include"ConstantBuffer.h"
#include "DepthStencilState.h"
#include "BlendState.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "Texture.h"
#include "VertexShader.h"
namespace KWSE::Graphics
{
	struct Particle
	{
		Math::Vector3 position;
		Math::Vector3 velocity;
		Math::Vector3 acceleration;
		Color startColor,endColor;
		float startSize, endSize;
		float lifetime,maxLifetime;
		int textureIndex = 0;
	};
	class ParticleEmitter
	{
	public:
		void Initialize();
		void Terminate();

		void Start(float emitRate);
		void Stop();

		void Render(const Camera& camera);
		void Update(float deltaTime);


		void SetPosition(const Math::Vector3 pos);
		void SetDirection(const Math::Vector3& dir, float span);

		void SetStartColor(const Color& color) { mStartColor = color; }
		void SetEndColor(const Color& color) { mEndColor = color; }

		void SetStartSize( float size) { mStartSize = size; }
		void SetEndSize( float size) { mEndSize = size; }

		void SetMaxLifeTime(float maxLifeTime) { mMaxLifetime = maxLifeTime; }
	private:
		KWSE::Graphics::ConstantBuffer mConstantBuffer;
		KWSE::Graphics::MeshBuffer mMeshBuffer;
		KWSE::Graphics::VertexShader mVertexShader;
		KWSE::Graphics::PixelShader mPixelShader;
		KWSE::Graphics::Sampler mSampler;
		KWSE::Graphics::Texture mTexture;
		KWSE::Graphics::BlendState mBlendState;
		KWSE::Graphics::DepthStencilState mDepthStencilState;

		Math::Vector3 mPosition;
		Math::Vector3 mDirection;
		float mDirectionSpan = 0.0f;
		float mEmitRate = 0.0f;
		float mEmitCount = 0.0f;
		Color mStartColor=Colors::White, mEndColor=Colors::White;
		float mStartSize=1.0f, mEndSize=1.0f;
		float mMaxLifetime = 1.0f;

		std::vector<Particle> mParticles;
	};
}