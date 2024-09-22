#include "Scene_Result.h"

namespace Bton = Button;
using namespace Bton;

namespace Result
{
	Bton::Button playAgain;
	Bton::Button goMenu;

	void Init()
	{
		playAgain = Create("Play Again", screenWidth / 5 * 2 - playAgain.rectangle.width, screenHeight / 2, 400, 60);
		goMenu = Create("Menu", screenWidth / 5 * 4 - goMenu.rectangle.width, screenHeight / 2, 250, 60);
	}

	void Draw(Player::Player player)
	{
		WHITE
			if (player.lives <= 0)
				slText(screenWidth / 2, screenHeight / 2, "YOU LOST");
			else
					slText(screenWidth / 2, screenHeight / 2, "YOU WON");

		if (playAgain.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Draw(playAgain);

		if (goMenu.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Draw(goMenu);
	}
}