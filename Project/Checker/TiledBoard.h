#pragma once
#include "KWSE/Inc/KWSE.h"
class TiledBoard
{
public:
	void Load();
	void UnLoad();
	void Update(float deltaTime);
	void Render();
private:


	int GetIndex(int x, int y) const;

	 std::array<KWSE::Graphics::Texture, 4> mTextureIds;  // know the size -> use array.
	const std::array<int,64> mTiles;
	const	int mColumns = 8;
	const	int mRows = 8;
	float mTileSize = 32.f;

};
