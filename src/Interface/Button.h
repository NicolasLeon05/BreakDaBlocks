#pragma once
#include <sl.h>
#include "Rectangle.h"

namespace Button
{
	struct Button
	{
		Rectangle rectangle;
		const char* text;
		bool isSelected;
	};

	Button Create(const char* text, float recX, float recY, float recWidth, float recHeight);

	void IsButtonSelected(Button& button);

	bool IsButtonPressed(Button button);
}

