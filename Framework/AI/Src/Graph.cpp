#include "Precompiled.h"
#include"Graph.h"

using namespace KWSE::AI;
void Graph::Resize(int columns, int rows)
{
	mColumns = columns;
	mRows = rows;
	mNodes.resize(columns*rows);

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			// hw connect neighbors to each node (up to 8, maybe less)mNodes
			int index = GetIndex(Coord{ x, y });

			Coord coordTL{ x - 1, y - 1 };
			Coord coordTR{ x + 1, y - 1 };
			Coord coordBL{ x - 1, y + 1 };
			Coord coordBR{ x + 1, y + 1 };
			Coord coordL{ x - 1, y };
			Coord coordR{ x + 1, y };
			Coord coordT{ x , y - 1 };
			Coord coordB{ x , y + 1 };

			Node* neighborTL = GetNode(coordTL); // use getnode ck if in bound, and pass value to struct to return it back to getnode(coord). 
			if (neighborTL != nullptr)
			{
				mNodes[index].neighbors.push_back(coordTL);
			}

			Node* neighborTR = GetNode(Coord{ coordTR });
			if (neighborTR != nullptr)
			{
				mNodes[index].neighbors.push_back(coordTR);
			}

			Node* neighborBL = GetNode(Coord{ coordBL });
			if (neighborBL != nullptr)
			{
				mNodes[index].neighbors.push_back(coordBL);
			}

			Node* neighborBR = GetNode(Coord{ coordBR });
			if (neighborBR != nullptr)
			{
				mNodes[index].neighbors.push_back(coordBR);
			}

			Node* neighborL = GetNode(Coord{ coordL });
			if (neighborL != nullptr)
			{
				mNodes[index].neighbors.push_back(coordL);
			}

			Node* neighborR = GetNode(Coord{ coordR });
			if (neighborR != nullptr)
			{
				mNodes[index].neighbors.push_back(coordR);
			}

			Node* neighborT = GetNode(Coord{ coordT });
			if (neighborT != nullptr)
			{
				mNodes[index].neighbors.push_back(coordT);
			}

			Node* neighborB = GetNode(Coord{ coordB });
			if (neighborB != nullptr)
			{
				mNodes[index].neighbors.push_back(coordB);
			}

		}
	}
}

Graph::Node* Graph::GetNode(const Coord coord)
{
	//const Graph* constMe = this;
	//return const_cast<Node*>(constMe->GetNode(coord));
	return const_cast<Node*>(static_cast<const Graph*>(this)->GetNode(coord));
}

const Graph::Node * KWSE::AI::Graph::GetNode(const Coord coord) const
{
	//hw do bound check , then either return & of node , or nullptr.// check tilemap 
	if (coord.x >= 0 && coord.x < mColumns
		&&
		coord.y >= 0 && coord.y < mRows)
	{
		return &mNodes[GetIndex(coord)];// getindex(int) with coord(1d array pos)
	}
	return nullptr;
}

int Graph::GetColumns()const { return mColumns; }
int Graph::GetRows()	const { return  mRows; }

int Graph::GetIndex(Coord coord)const
{
	return coord.x + (coord.y*mColumns);
}