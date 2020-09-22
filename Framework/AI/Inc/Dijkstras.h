#pragma once


#include"Graph.h"
namespace KWSE::AI
{
	class Dijkstras
	{
	public:
		Path Search
		(const Graph& graph, 
			Coord start, Coord end, 
			std::function<bool(Coord)> tileBlock, 
			std::function<float(Coord,Coord)> getCost);

		const std::list<Coord>& GetClosedList() const { return closedList; }
		const std::vector<Coord>& GetParent() const { return parent; }

	private:
		std::list<Coord> openList;// checkList check which neighbor is opened.
		std::list<Coord> closedList; // closelist for the neighbor who is checked.
		std::vector<Coord> parent; // use to check back who is the parent.
		std::vector<float> g;// 
		std::vector<bool> opened;// 
		std::vector<bool> closed;


		//bool 1 byte= 8bits =[0000000]
		//bitarray [010101010101101110101]
	};

}

