#include "Block.h"
#include "sl.h"

namespace Blocks
{
	Block blocks[blockRows][blockCols];

	void Init()
	{
		float startPosX = blockWidth / 2;
		float startPosY = limitUp - blockHeight * 2;

		for (int i = 0; i < blockRows; i++)
		{
			for (int j = 0; j < blockCols; j++)
			{
				blocks[i][j].rectangle.height = blockHeight;
				blocks[i][j].rectangle.width = blockWidth;
				blocks[i][j].rectangle.x = startPosX + (blockWidth * j);
				blocks[i][j].rectangle.y = startPosY - (blockHeight * i);
				blocks[i][j].isDestroyed = false;
			}
		}
	}

	void Draw()
	{
		for (int i = 0; i < blockRows; i++)
		{
			for (int j = 0; j < blockCols; j++)
			{
				if (!blocks[i][j].isDestroyed)
				{
					GREEN
						slRectangleFill(blocks[i][j].rectangle.x, blocks[i][j].rectangle.y, blocks[i][j].rectangle.width, blocks[i][j].rectangle.height);
					BLACK
						slRectangleOutline(blocks[i][j].rectangle.x, blocks[i][j].rectangle.y, blocks[i][j].rectangle.width, blocks[i][j].rectangle.height);
				}
			}
		}
	}
}