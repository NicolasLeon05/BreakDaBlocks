#include "Scene_MainMenu.h"
#include "Constants.h"
#include "sl.h"

using namespace Constants;

namespace MainMenu
{

	Button::Button play;
	Button::Button controls;
	Button::Button exit;

	void Init()
	{
		const float width = 300;
		play = Button::Create("Play", screenWidth/2, screenHeight/5 * 3, width, 60);
		controls = Button::Create("Controls", screenWidth / 2, screenHeight / 5 * 2, width, 60);
		exit = Button::Create("Exit", screenWidth / 2, screenHeight / 5, width, 60);
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

		if (controls.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Button::Draw(controls);

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
