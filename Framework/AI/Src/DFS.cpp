#include"Precompiled.h"
#include"DFS.h"

using namespace KWSE::AI;


Path DFS::SearchDFS(const Graph & graph, Coord start, Coord end, std::function<bool(Coord)> tileBlock)
{
	openList.clear();
	closedList.clear();

	parent.clear();
	opened.clear();
	closed.clear();

	parent.resize(graph.GetColumns()*graph.GetRows());
	opened.resize(graph.GetColumns()*graph.GetRows());
	closed.resize(graph.GetColumns()*graph.GetRows());

	// Add start to the open list
	openList.push_back(start);
	opened[graph.GetIndex(start)] = true;
	//keep searching until we are done
	bool found = false;

	//DeMorgan's Theorem
	//!(A || B || C)===!A && !B && !C
	//!(A && B && C)===!A || !B || !C
	while (!found && !openList.empty())
	{
		// pick the next node from the open list
		Coord current = openList.front();
		openList.pop_front();
		// if node is end , we are done.
		if (current == end)
		{
			found = true;
		}
		//else, expand node
		else
		{
			auto currentNode = graph.GetNode(current);
			for (auto neighbor : currentNode->neighbors)
			{
				int neighborIndex = graph.GetIndex(neighbor);
				if (!opened[neighborIndex] && !tileBlock(neighbor))
				{
					openList.push_front(neighbor); //push front.
					opened[neighborIndex] = true;
					parent[neighborIndex] = current;
				}
			}
		}
		//colse node.
		closedList.push_back(current);
		closed[graph.GetIndex(start)] = true;

	}

	Path path;
	if (found)
	{
		std::list<Coord> trace;
		Coord next = end;
		while (next.IsValid())
		{
			trace.push_front(next);
			next = parent[graph.GetIndex(next)];
		}
		path.reserve(trace.size());
		for (auto node : trace)
		{
			path.push_back(node);
		}
	}
	return path;
}

