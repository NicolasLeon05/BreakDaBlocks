#include "Button.h"

namespace Button
{
	Button Create(std::string text, float recX, float recY, float recWidth, float recHeight)
	{
		Button newButton;
		newButton.text = text;
		newButton.rectangle.x = recX;
		newButton.rectangle.y = recY;
		newButton.rectangle.width = recWidth;
		newButton.rectangle.height = recHeight;
	}
}
