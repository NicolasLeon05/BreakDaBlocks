#include "Button.h"
#include "Constants.h"
#include <iostream>

using namespace Constants;

namespace Button
{
	void Draw(Button button)
	{
		slRectangleFill(button.rectangle.x, button.rectangle.y, button.rectangle.width, button.rectangle.height);
		WHITE
			slText(button.rectangle.x - 5, button.rectangle.y - (button.rectangle.height / 3) + 5, button.text);
	}

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
		bool pressed = false;

		if (slGetMouseButton(SL_MOUSE_BUTTON_1) || slGetKey(SL_KEY_ENTER))
			pressed = true;

		if (IsButtonSelected(button) && pressed)
			return true;
		else
			return false;
	}

	float GetSpaceBetween(float width, int buttons)
	{
		float totalRectanglesWidth = width * buttons;
		float remainingSpace = screenWidth - totalRectanglesWidth;

		return remainingSpace / (buttons + 1);
	}

}
