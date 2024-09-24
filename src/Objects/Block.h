#pragma once
#include "Rectangle.h"
#include "Constants.h"

using namespace Constants;

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

