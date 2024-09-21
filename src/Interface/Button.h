#pragma once
#include <sl.h>
#include "Rectangle.h"
#include <iostream>

namespace Button
{
	struct Button
	{
		Rectangle rectangle;
		std::string text;
		bool isSelected;
	};

	Button Create(std::string text, float recX, float recY, float recWidth, float recHeight);
}

