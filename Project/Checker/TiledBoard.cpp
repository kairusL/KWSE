#include "TiledBoard.h"

using namespace KWSE;
using namespace KWSE::Graphics;
void TiledBoard::Load()
{
	// Textures
	 mTextureIds[0].Initialize("");//board tile 1
	 mTextureIds[1].Initialize("");// board tile 2
	 mTextureIds[2].Initialize("");// checker 1
	 mTextureIds[3].Initialize("");// checker 2

}

void TiledBoard::UnLoad()
{
}

void TiledBoard::Update(float deltaTime)
{
	float offset = mTileSize * 0.5f; 
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			// go through x,y  and put index, find where is it in 2dArray.
			const int index = GetIndex(x, y);

			//KWSE::Graphics::SimpleDraw::AddScreenCircle(offset, offset, offset, Colors::Brown);
			if (index % 2 == 0)
			{
				KWSE::Graphics::SimpleDraw::AddScreenRect(x - mTileSize, y - mTileSize, x + mTileSize, y + mTileSize, Colors::DarkGray);
			}
			else
			{
				KWSE::Graphics::SimpleDraw::AddScreenRect(x - mTileSize, y - mTileSize, x + mTileSize, y + mTileSize, Colors::LightGray);
			}
		}
	}
}

void TiledBoard::Render()
{
	
}

int TiledBoard::GetIndex(int x, int y) const
{
	return 0;
}
