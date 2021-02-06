#pragma once

#include<KWSE/Inc/KWSE.h>
using namespace KWSE;
using namespace KWSE::Graphics;
using namespace KWSE::Math;
class PipeManager;

class Bird
{
public:
	void Load();

	void Update(float deltaTime, const PipeManager& pm);
	void Render();

	void Flap();

	void Spawn(const Vector2& pos);
	void Kill();

	Circle GetBound() const { return { mPosition, mRadius }; }
	bool IsAlive() const { return mAlive; }

	std::unique_ptr<ML::NEAT::NeuralNet> brain;
	float fitness = 0.0f;

private:
	std::array<TextureId, 5> mTextureIds;
	Vector2 mPosition;
	Vector2 mVelocity;
	float mRadius = 30.0f;
	float mAnimationFrame = 0.0f;
	bool mAlive = false;
};