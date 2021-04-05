#include "Car.h"

#include "Track.h"

void Car::Load()
{
	mTextureId = X::LoadTexture("red_car_small.png");
}

void Car::Update(float deltaTime, const Track& track)
{
	if (IsActive())
	{
		if (brain)
		{
			std::vector<double> weights;
			for (auto sensor : mSensors)
				weights.push_back(sensor);
			auto result = brain->Evaluate(weights);
			
			if (result[0] > 0.5f && result[0] > result[1] && result[0] > result[2] && result[0] > result[3])
				Accelerate();
			else if (result[1] > 0.5f && result[1] > result[0] && result[1] > result[2] && result[1] > result[3])
				Brake();
			else if (result[2] > 0.5f && result[2] > result[0] && result[2] > result[1] && result[2] > result[3])
				Turn(0.05f);
			else if (result[3] > 0.5f && result[3] > result[0] && result[3] > result[1] && result[3] > result[2])
				Turn(-0.05f);
		}

		X::Math::Vector2 lastPosition = mPosition;
		mPosition += mHeading * mSpeed * deltaTime;

		fitness += mSpeed * deltaTime;
		if (track.ReachedCheckPoint({ lastPosition, mPosition }, nextCheckPointIndex))
			fitness += 100.0f;

		std::array<X::Math::Vector2, 5> directions;
		directions[0] = mHeading;
		directions[1] = X::Math::PerpendicularLH(mHeading);
		directions[2] = X::Math::PerpendicularRH(mHeading);
		directions[3] = X::Math::Normalize(directions[0] + directions[1]);
		directions[4] = X::Math::Normalize(directions[0] + directions[2]);

		X::Math::Vector2 point;
		for (size_t i = 0; i < std::size(directions); ++i)
		{
			X::Math::LineSegment ray = { mPosition, mPosition + directions[i] * 1000.0f };
			if (track.IntersectWalls(ray, point))
				ray.to = point;
			mSensors[i] = X::Math::Distance(ray.from, ray.to);

			if (brain == nullptr)
				X::DrawScreenLine(ray.from, ray.to, X::Colors::Pink);
		}

		if (mSensors[0] < 10.0f)
			Kill();
	}
}

void Car::Render()
{
	const float angle = atan2(-mHeading.x, mHeading.y) + X::Math::kPiByTwo;
	X::DrawSprite(mTextureId, mPosition, angle);
	if (brain)
	{
		std::string txt;
		txt += "fitness: " + std::to_string(fitness);
		X::DrawScreenText(txt.c_str(), mPosition.x + 40.0f, mPosition.y - 30.0f, 12.0f, X::Colors::White);
	}
}

void Car::Accelerate()
{
	if (mSpeed < 500.0f)
		mSpeed += 1.0f;
}

void Car::Brake()
{
	if (mSpeed > 0.0f)
		mSpeed -= 1.0f;
}

void Car::Turn(float radian)
{
	mHeading = X::Math::Rotate(mHeading, radian);
}

void Car::Spawn(const X::Math::Vector2& pos, const X::Math::Vector2& heading)
{
	mPosition = pos;
	mHeading = heading;
	mSpeed = 200.0f;
	mActive = true;
}

void Car::Kill()
{
	mActive = false;
}
