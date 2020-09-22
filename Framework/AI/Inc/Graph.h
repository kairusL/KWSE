#pragma once
#include"Common.h"

namespace KWSE::AI
{
	struct Coord
	{
		// change to -1 , because when create a parent , it didnt have value yet. so set it to nullvalue. (for the start point.)
		int x = -1;    
		int y = -1;

		bool IsValid() const
		{
			return x != -1 && y != -1;
		}
		bool operator==(const Coord& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
	};


	using Path = std::vector<Coord>;

	class Graph
	{
	public:
		
		struct Node
		{
			std::vector<Coord> neighbors;  // deep copy vector is not a good idea. (up to 8, maybe less) // because NB with (x,y) so use coord type.
		};

		void Resize(int columns,int rows);

		//Node*   can be null.
		//Node& === Node*const // can not be change. must be something returning. cant be null
		Node* GetNode(const Coord coord);
		const Node* GetNode(const Coord coord) const;

		int GetColumns()const ;
		int GetRows()	const ;
		int GetIndex(Coord coord)const;
	private:
		std::vector<Node> mNodes; // tiled map. 
		int mColumns=0;
		int mRows=0;
	};



}