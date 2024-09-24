#include "Block.h"
#include "sl.h"
#include "Color.h"
#include <iostream>

using namespace Colors;

namespace Blocks
{
	Block blocks[blockRows][blockCols];

	void Init()
	{
		srand(time(NULL));

		int modifierChance = 20;
		float startPosX = blockWidth / 2;
		float startPosY = limitUp - blockHeight * 2;

		for (int i = 0; i < blockRows; i++)
		{
			for (int j = 0; j < blockCols; j++)
			{
				blocks[i][j].rectangle.height = blockHeight;
				blocks[i][j].rectangle.width = blockWidth;
				blocks[i][j].rectangle.x = startPosX + (blockWidth + blockSpacing) * j;
				blocks[i][j].rectangle.y = startPosY - (blockHeight + blockSpacing) * i;
				blocks[i][j].isDestroyed = false;

				if (rand() % 100 + 1 <= modifierChance)
				{
					blocks[i][j].hasModifier = true;
					blocks[i][j].modifier = MODIFIER(rand() % 4 + 1);
				}
				else
				{
					blocks[i][j].hasModifier = false;
					blocks[i][j].modifier = MODIFIER::NONE;
				}
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
					switch (blocks[i][j].modifier)
					{
					case MODIFIER::NONE:
					{
						SetColor(COLOR::GREEN);
						break;
					}

					case MODIFIER::BIGGER:
					{
						SetColor(COLOR::RED);
						break;
					}

					case MODIFIER::SMALLER:
					{
						SetColor(COLOR::YELLOW);
						break;
					}

					case MODIFIER::FASTER:
					{
						SetColor(COLOR::BLUE);
						break;
					}

					case MODIFIER::SLOWER:
					{
						SetColor(COLOR::WHITE);
						break;
					}

					default:
						SetColor(COLOR::BLACK);
						break;
					}
					slRectangleFill(blocks[i][j].rectangle.x, blocks[i][j].rectangle.y, blocks[i][j].rectangle.width, blocks[i][j].rectangle.height);
					SetColor(COLOR::BLACK);
					slRectangleOutline(blocks[i][j].rectangle.x, blocks[i][j].rectangle.y, blocks[i][j].rectangle.width, blocks[i][j].rectangle.height);
				}
			}
		}
	}
}