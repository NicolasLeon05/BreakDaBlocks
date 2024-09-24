#include "Scene_Result.h"

namespace Bton = Button;
using namespace Bton;
using namespace Constants;

namespace Result
{
	Bton::Button playAgain;
	Bton::Button goMenu;

	void Init()
	{		
		const float width = 400;
		float spaceBetween = GetSpaceBetween(width, 2);

		int playAgainX = spaceBetween + (width / 2);
		int goMenuX = playAgainX + width + spaceBetween;

		playAgain = Create("Play Again", playAgainX, screenHeight / 5 * 2, width, 60);
		goMenu = Create("Menu", goMenuX, screenHeight / 5 * 2, 250, 60);
	}

	void Draw(Player::Player player)
	{
		WHITE
			if (player.lives <= 0)
				slText(screenWidth / 2, screenHeight / 3 * 2, "YOU LOST!");
			else
					slText(screenWidth / 2, screenHeight / 3 * 2, "YOU WON!");

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