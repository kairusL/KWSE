#pragma once


#include"Graph.h"
namespace KWSE::AI
{
	//auto ManhattanDistanceFunc = [](Coord heurfrom, Coord heurto) -> float
	//{
	//	return abs(heurfrom.x - heurto.x) + abs(heurfrom.y - heurto.y);
	//};
	//auto DiagonalDistanceFunc = [](Coord heurfrom, Coord heurto) -> float
	//{
	//	return X::Math::Max(abs(heurfrom.x - heurto.x), abs(heurfrom.y - heurto.y));
	//};
	//auto EuclideanDistanceFunc = [](Coord heurfrom, Coord heurto) -> float
	//{
	//	return sqrt((heurfrom.x - heurto.x) *(heurfrom.x - heurto.x) + (heurfrom.y - heurto.y) *(heurfrom.y - heurto.y));
	//};
	//
	class AStar
	{
	public:
		//enum HeuristicMode
		//{
		//	ManhattanDistance,
		//	DiagonalDistance,
		//	EuclideanDistance
		//};


		Path Search
		(const Graph& graph, 
			Coord start, Coord end, 
			std::function<bool(Coord)> tileBlock, 
			std::function<float(Coord, Coord)> getCost,
			std::function<float(Coord, Coord)> getHeuristic);

		const std::list<Coord>& GetClosedList() const { return closedList; }
		const std::vector<Coord>& GetParent() const { return parent; }


		//float AStarSearchMode(Coord heurfrom, Coord heurto,HeuristicMode mode);

	private:
		std::list<Coord> openList;// checkList check which neighbor is opened.
		std::list<Coord> closedList; // closelist for the neighbor who is checked.
		std::vector<Coord> parent; // use to check back who is the parent.
		std::vector<float> g;// 
		std::vector<float> h;// 
		std::vector<bool> opened;// 
		std::vector<bool> closed;


		//bool 1 byte= 8bits =[0000000]
		//bitarray [010101010101101110101]
	};

}