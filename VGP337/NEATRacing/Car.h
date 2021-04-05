#pragma once

#include <ML.h>
#include <XEngine.h>

class Track;

class Car
{
public:
	void Load();

	void Update(float deltaTime, const Track& track);
	void Render();

	void Accelerate();
	void Brake();
	void Turn(float radian);

	void Spawn(const X::Math::Vector2& pos, const X::Math::Vector2& heading);
	void Kill();

	bool IsActive() const { return mActive; }

	std::unique_ptr<ML::NEAT::NeuralNet> brain;
	size_t nextCheckPointIndex = 1;
	float fitness = 0.0f;

private:
	std::array<float, 5> mSensors;
	X::TextureId mTextureId;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mHeading;
	float mSpeed = 0.0f;
	bool mActive = false;
};