#pragma once
#include "Rectangle.h"
#include "Constants.h"
#include "Modifier.h"

using namespace Constants;
using namespace Modifiers;
using namespace Rectangle;

namespace Blocks
{
	struct Block
	{
		Rec rectangle;
		MODIFIER modifier;
		bool hasModifier;
		bool isDestroyed;
	};

	extern Block blocks[blockRows][blockCols];

	void Init();

	void Draw();
}

