#pragma once
#include "Rectangle.h"
#include "Constants.h"

namespace Blocks
{
	struct Block
	{
		Rectangle rectangle;
		bool isDestroyed;
	};

	extern Block blocks[blockRows][blockCols];

	void Init();

	void Draw();

}

