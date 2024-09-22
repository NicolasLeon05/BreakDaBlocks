#include "Scene_MainMenu.h"
#include "Constants.h"

namespace MainMenu
{

	Button::Button play;
	Button::Button credits;
	Button::Button exit;

	void Init()
	{

		play = Button::Create("Play", screenWidth/2, screenHeight/2, 250, 60);
	}

	void Draw()
	{
		if (play.isSelected)
			RED
		else
			ORANGE

		slRectangleFill(play.rectangle.x, play.rectangle.y, play.rectangle.width, play.rectangle.height);
		//WHITE
		//slText(play.rectangle.x, play.rectangle.y, play.text);
	}
}
