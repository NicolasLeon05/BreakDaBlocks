#pragma once
#include "Rectangle.h"
#include "Constants.h"

namespace Blocks
{
	struct Block
	{
		Rectangle::Rec rectangle;
		bool isDestroyed;
	};

	extern Block blocks[blockRows][blockCols];

	void Init();

	void Draw();

}

