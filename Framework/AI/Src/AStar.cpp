#include"Precompiled.h"
#include"AStar.h"

using namespace KWSE::AI;


Path AStar::Search(const Graph & graph, Coord start, Coord end, std::function<bool(Coord)> tileBlock, std::function<float(Coord, Coord)> getCost, std::function<float(Coord, Coord)> getHeuristic)
{
	openList.clear();
	closedList.clear();
	g.clear();
	h.clear();
	parent.clear();
	opened.clear();
	closed.clear();

	const int nodeCount = graph.GetColumns()*graph.GetRows();

	parent.resize(graph.GetColumns()*graph.GetRows());
	g.resize(nodeCount, 0.0f);
	h.resize(nodeCount, 0.0f);
	opened.resize(graph.GetColumns()*graph.GetRows());
	closed.resize(graph.GetColumns()*graph.GetRows());

	// Add start to the open list
	openList.push_back(start);
	opened[graph.GetIndex(start)] = true;
	h[graph.GetIndex(start)] = getHeuristic(start, end);
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
				// if the neighbor is blocked or closed, skip it.
				int neighborIndex = graph.GetIndex(neighbor);
				if (tileBlock(neighbor) || closed[neighborIndex])
				{
					continue;
				}
				const float cost = g[graph.GetIndex(current)] + getCost(current, neighbor);
				const float heuristic = getHeuristic(neighbor, end);
				if (!opened[neighborIndex])
				{
					openList.push_back(neighbor);
					opened[neighborIndex] = true;
					parent[neighborIndex] = current;
					g[neighborIndex] = cost;
					//h[neighborIndex] = getHeuristic(neighbor, end);
					h[neighborIndex] = heuristic;

					////wrong! CAN NOT JUST ADD TO BACK
					////OPENLIST.PUSH_BACK(NEIGHBOR);

					//for()
					// check if (cost+heuristic )<(g[i]+h[i])
					//insert
					std::list<AI::Coord>::iterator iter;
					for (iter = openList.begin(); iter != openList.end(); iter++)
					{
						int getIterIndex = graph.GetIndex({ iter->x,iter->y });
						if ((cost + heuristic) < (g[getIterIndex] + h[getIterIndex]))
						{
							openList.insert(iter, neighbor);
							break;
						}
					}
				}

				else if (cost < g[neighborIndex])
				{
					//updated parent
					parent[neighborIndex] = current;
					// updated g
					g[neighborIndex] = cost;
					//keep h (no code)

					//remove and re-insert using new f= g+h to sort.
					openList.remove(neighbor);
					std::list<AI::Coord>::iterator iter;
					for (iter = openList.begin(); iter != openList.end(); ++iter)
					{
						int getIterIndex = graph.GetIndex({ iter->x,iter->y });
						if ((cost + heuristic) < (g[getIterIndex] + h[getIterIndex]))
						{
							openList.insert(iter, neighbor);
							break;
						}
					}
				}
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

//float AI::AStar::AStarSearchMode(Coord heurfrom, Coord heurto, HeuristicMode mode)
//{
//	if (mode == ManhattanDistance)
//	{
//		return abs(heurfrom.x - heurto.x) + abs(heurfrom.y - heurto.y);
//	}
//	if (mode == DiagonalDistance)
//	{
//		return X::Math::Max(abs(heurfrom.x - heurto.x),abs(heurfrom.y - heurto.y));
//	}
//	if (mode == EuclideanDistance)
//	{
//		return sqrt((heurfrom.x - heurto.x) *(heurfrom.x - heurto.x) + (heurfrom.y - heurto.y) *(heurfrom.y - heurto.y));
//	}
//}


