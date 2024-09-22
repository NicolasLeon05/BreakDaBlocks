#include "Scene_MainMenu.h"
#include "Constants.h"
#include "sl.h"

namespace MainMenu
{

	Button::Button play;
	Button::Button credits;
	Button::Button exit;

	void Init()
	{
		play = Button::Create("Play", screenWidth/2, screenHeight/5 * 3, 250, 60);
		credits = Button::Create("Credits", screenWidth / 2, screenHeight / 5 * 2, 250, 60);
		exit = Button::Create("Exit", screenWidth / 2, screenHeight / 5, 250, 60);
	}

	void Draw()
	{
		//Hacer funcion
		if (play.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Button::Draw(play);

		if (credits.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Button::Draw(credits);

		if (exit.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Button::Draw(exit);
	}
}
