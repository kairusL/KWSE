#pragma once

#include"Graph.h"
namespace KWSE::AI
{
	class BFS
	{
	public:
		Path SearchBFS(const Graph& graph, Coord start, Coord end, std::function<bool(Coord)> tileBlock);
		const std::list<Coord>& GetClosedList() const { return closedList; }
		const std::vector<Coord>& GetParent() const { return parent; }

	private:
		std::list<Coord> openList;// checkList check which neighbor is opened.
		std::list<Coord> closedList; // closelist for the neighbor who is checked.
		std::vector<Coord> parent; // use to check back who is the parent.
		std::vector<bool> opened;// 
		std::vector<bool> closed;
	};

}