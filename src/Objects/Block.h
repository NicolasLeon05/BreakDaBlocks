#pragma once
#include "Rectangle.h"
#include "Constants.h"

struct Block
{
	Rectangle rectangle;
	bool isDestroyed;
};

extern Block blocks[blockRows][blockCols];

void InitBlocks();

void DrawBlocks();

