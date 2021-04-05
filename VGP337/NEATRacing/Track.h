#pragma once

#include <XEngine.h>

class Track
{
public:
	void Load();
	void Save();

	void RunEditor();

	void Render();

	X::Math::Vector2 GetStartPosition() const;
	X::Math::Vector2 GetStartDirection() const;

	bool IntersectWalls(const X::Math::LineSegment& line, X::Math::Vector2& intersection) const;
	bool ReachedCheckPoint(const X::Math::LineSegment& line, size_t& nextCheckPointIndex) const;

private:
	std::vector<X::Math::Vector2> mWayPoints;
	std::vector<X::Math::LineSegment> mWalls;
	std::vector<X::Math::LineSegment> mCheckPoints;

	// Editor
	X::Math::Vector2 mNextWayPoints;
	X::Math::LineSegment mNextOuter;
	X::Math::LineSegment mNextInner;
	bool mPlaceWayPoint = false;
	bool mFinished = false;
};