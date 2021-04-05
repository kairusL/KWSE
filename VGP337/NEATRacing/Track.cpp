#include "Track.h"

void Track::Load()
{
	FILE* file = nullptr;
	fopen_s(&file, "track.txt", "r");

	mWalls.clear();
	mWayPoints.clear();

	uint32_t count = 0;
	fscanf_s(file, "Waypoints: %u\n", &count);
	mWayPoints.reserve(count);

	for (uint32_t i = 0; i < count; ++i)
	{
		float x, y;
		fscanf_s(file, "%f %f\n", &x, &y);
		mWayPoints.push_back({ x, y });
	}

	fscanf_s(file, "Walls: %u\n", &count);
	mWalls.reserve(count);

	for (uint32_t i = 0; i < count; ++i)
	{
		float x0, y0, x1, y1;
		fscanf_s(file, "%f %f %f %f\n", &x0, &y0, &x1, &y1);
		mWalls.push_back({ x0, y0, x1, y1 });
	}

	// Generate checkpoints
	for (size_t i = 0; i < mWalls.size(); i += 2)
	{
		auto& outer = mWalls[i];
		auto& inner = mWalls[i + 1];
		mCheckPoints.push_back({ outer.from, inner.from });
	}

	fclose(file);
}

void Track::Save()
{
	FILE* file = nullptr;
	fopen_s(&file, "track.txt", "w");

	const uint32_t wpCount = static_cast<uint32_t>(mWayPoints.size());
	fprintf_s(file, "Waypoints: %u\n", wpCount);
	for (auto& pt : mWayPoints)
		fprintf_s(file, "%f %f\n", pt.x, pt.y);

	const uint32_t wallCount = static_cast<uint32_t>(mWalls.size());
	fprintf_s(file, "Walls: %u\n", wallCount);
	for (auto& wall : mWalls)
		fprintf_s(file, "%f %f %f %f\n", wall.from.x, wall.from.y, wall.to.x, wall.to.y);

	fclose(file);
}

void Track::RunEditor()
{
	X::DrawScreenText(
		"Left Click to place waypoints\n"
		"Hit [C] to clear\n"
		"Hit [S] to save\n"
		"Hit [ESC] to exit",
		10.0f, 10.0f, 20.0f, X::Colors::White);

	if (!mPlaceWayPoint)
	{
		if (!mFinished && X::IsMousePressed(X::Mouse::LBUTTON))
			mPlaceWayPoint = true;
	}
	else
	{
		const float x = static_cast<float>(X::GetMouseScreenX());
		const float y = static_cast<float>(X::GetMouseScreenY());
		mNextWayPoints = { x, y };

		if (!mWayPoints.empty())
		{
			X::Math::Vector2 from = mWayPoints.back();
			X::Math::Vector2 to = mNextWayPoints;
			X::Math::Vector2 direction = X::Math::Normalize(to - from);
			X::Math::Vector2 leftSide = X::Math::PerpendicularLH(direction);
			X::Math::LineSegment outer = {
				from - direction * 1000.0f + leftSide * 80.0f,
				to + direction * 1000.0f + leftSide * 80.0f,
			};
			X::Math::LineSegment inner = {
				from - direction * 1000.0f - leftSide * 80.0f,
				to + direction * 1000.0f - leftSide * 80.0f,
			};

			mNextOuter = outer;
			mNextInner = inner;
		}

		if (!X::IsMouseDown(X::Mouse::LBUTTON))
		{
			if (!mWayPoints.empty() && X::Math::Distance(mNextWayPoints, mWayPoints.front()) < 10.0f)
			{
				mNextWayPoints = mWayPoints.front();
				mFinished = true;
			}

			const size_t wallCount = mWalls.size();
			if (wallCount > 0)
			{
				auto& lastOuter = mWalls[wallCount - 2];
				auto& lastInner = mWalls[wallCount - 1];

				X::Math::Vector2 intersection;
				if (X::Math::Intersect(lastOuter, mNextOuter, &intersection))
				{
					lastOuter.to = intersection;
					mNextOuter.from = intersection;
				}
				if (X::Math::Intersect(lastInner, mNextInner, &intersection))
				{
					lastInner.to = intersection;
					mNextInner.from = intersection;
				}
			}

			if (mFinished)
			{
				auto& firstOuter = mWalls[0];
				auto& firstInner = mWalls[1];

				X::Math::Vector2 intersection;
				if (X::Math::Intersect(firstOuter, mNextOuter, &intersection))
				{
					firstOuter.from = intersection;
					mNextOuter.to = intersection;
				}
				if (X::Math::Intersect(firstInner, mNextInner, &intersection))
				{
					firstInner.from = intersection;
					mNextInner.to = intersection;
				}
			}

			if (!mWayPoints.empty())
			{
				mWalls.push_back(mNextOuter);
				mWalls.push_back(mNextInner);
				mCheckPoints.push_back({ mNextOuter.from, mNextInner.from });
			}
			mWayPoints.push_back(mNextWayPoints);
			mPlaceWayPoint = false;
		}
	}
	
	if (X::IsKeyPressed(X::Keys::C))
	{
		mWayPoints.clear();
		mWalls.clear();
		mCheckPoints.clear();
		mPlaceWayPoint = false;
		mFinished = false;
	}
	else if (X::IsKeyPressed(X::Keys::S))
	{
		Save();
	}
}

void Track::Render()
{
	for (size_t i = 0; i < mWayPoints.size(); ++i)
	{
		X::DrawScreenDiamond(mWayPoints[i], 5.0f, X::Colors::Yellow);
		if (i + 1 < mWayPoints.size())
			X::DrawScreenLine(mWayPoints[i], mWayPoints[i + 1], X::Colors::Green);
	}

	for (auto& wall : mWalls)
		X::DrawScreenLine(wall.from, wall.to, X::Colors::Cyan);

	for (auto& cp : mCheckPoints)
		X::DrawScreenLine(cp.from, cp.to, X::Colors::Blue);

	if (mPlaceWayPoint)
	{
		X::DrawScreenDiamond(mNextWayPoints, 5.0f, X::Colors::White);
		if (!mWayPoints.empty())
		{
			X::DrawScreenLine(mNextWayPoints, mWayPoints.back(), X::Colors::Pink);
			X::DrawScreenLine(mNextOuter.from, mNextOuter.to, X::Colors::Yellow);
			X::DrawScreenLine(mNextInner.from, mNextInner.to, X::Colors::Yellow);
		}
	}
}

X::Math::Vector2 Track::GetStartPosition() const
{
	return mWayPoints[0];
}

X::Math::Vector2 Track::GetStartDirection() const
{
	return X::Math::Normalize(mWayPoints[1] - mWayPoints[0]);
}

bool Track::IntersectWalls(const X::Math::LineSegment& line, X::Math::Vector2& intersection) const
{
	float closestSqr = FLT_MAX;
	for (const auto& wall : mWalls)
	{
		X::Math::Vector2 point;
		if (X::Math::Intersect(line, wall, &point))
		{
			float distSqr = X::Math::DistanceSqr(line.from, point);
			if (distSqr < closestSqr)
			{
				closestSqr = distSqr;
				intersection = point;
			}
		}
	}

	return closestSqr != FLT_MAX;
}

bool Track::ReachedCheckPoint(const X::Math::LineSegment& line, size_t& nextCheckPointIndex) const
{
	if (X::Math::Intersect(mCheckPoints[nextCheckPointIndex], line))
	{
		++nextCheckPointIndex;
		if (nextCheckPointIndex == mCheckPoints.size())
			nextCheckPointIndex = 0;
		return true;
	}
	return false;
}