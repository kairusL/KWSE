#pragma once
#include "KWSE/Inc/KWSE.h"
#include "PipeManager.h"
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Input;
using namespace KWSE::ML;
using namespace KWSE::Math;

class PipeManager;

class Bird
{
public:
	void Load();

	void Update(float deltaTime, const PipeManager& pm);
	void Render();

	void Flap();
	void Terminate();
	void Spawn(const Math::Vector2& pos);
	void Kill();

	Math::Circle GetBound() const { return { mPosition, mRadius }; }
	bool IsAlive() const { return mAlive; }

	std::unique_ptr<ML::NEAT::NeuralNet> brain;
	float fitness = 0.0f;

private:
	std::array<Texture, 5> mTextureIds;
	Math::Vector2 mPosition;
	Math::Vector2 mVelocity;
	float mRadius = 30.0f;
	float mAnimationFrame = 0.0f;
	bool mAlive = false;
	Font mfont;
};