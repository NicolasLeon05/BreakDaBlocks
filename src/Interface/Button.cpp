#include "Button.h"
#include <iostream>

namespace Button
{
	Button Create(const char* text, float recX, float recY, float recWidth, float recHeight)
	{
		Button newButton;
		newButton.text = text;
		newButton.rectangle.x = recX;
		newButton.rectangle.y = recY;
		newButton.rectangle.width = recWidth;
		newButton.rectangle.height = recHeight;
		newButton.isSelected = false;

		return newButton;
	}

	bool IsButtonSelected(Button& button)
	{		
		//Mouse hover
		if (slGetMouseX() > button.rectangle.x - (button.rectangle.width / 2) &&
			slGetMouseX() < button.rectangle.x + (button.rectangle.width / 2) &&
			slGetMouseY() < button.rectangle.y + (button.rectangle.height / 2) &&
			slGetMouseY() > button.rectangle.y - (button.rectangle.height / 2))
		{
			button.isSelected = true;
			return true;
		}
		else
		{
			button.isSelected = false;
			return false;
		}
	}

	bool IsButtonPressed(Button& button)
	{
		if (IsButtonSelected(button))
			if (slGetMouseButton(SL_MOUSE_BUTTON_1) || slGetKey(SL_KEY_ENTER))
				return true;
		else
			return false;
	}	
}