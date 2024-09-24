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
		slSetFontSize(100);
		RED
			slText(screenWidth / 2, screenHeight / 5 * 4, "BREAKOUT");
		slSetFontSize(baseFontSize);

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

		slSetFontSize(25);
		float textX = slGetTextWidth("Developed by: Nicolas Leon") / 2; 
		BLUE
			slText(textX + 25, 25, "Developed by: Nicolas Leon");
		slSetFontSize(baseFontSize);
	}
}
