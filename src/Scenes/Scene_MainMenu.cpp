#include "Scene_MainMenu.h"
#include "Constants.h"
#include "sl.h"

namespace MainMenu
{

	Button::Button play;
	Button::Button tutorial;
	Button::Button exit;

	void Init()
	{
		play = Button::Create("Play", screenWidth/2, screenHeight/5 * 3, 270, 60);
		tutorial = Button::Create("Tutorial", screenWidth / 2, screenHeight / 5 * 2, 270, 60);
		exit = Button::Create("Exit", screenWidth / 2, screenHeight / 5, 270, 60);
	}

	void Draw()
	{
		//Hacer funcion
		if (play.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Button::Draw(play);

		if (tutorial.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Button::Draw(tutorial);

		if (exit.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Button::Draw(exit);
	}
}
