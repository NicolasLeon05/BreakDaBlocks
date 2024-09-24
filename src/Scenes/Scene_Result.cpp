#include "Scene_Result.h"
#include "Color.h"

namespace Bton = Button;
using namespace Bton;
using namespace Constants;
using namespace Colors;
using namespace Colors;


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
		SetColor(COLOR::WHITE);
		if (player.lives <= 0)
			slText(screenWidth / 2, screenHeight / 3 * 2, "YOU LOST!");
		else
			slText(screenWidth / 2, screenHeight / 3 * 2, "YOU WON!");

		Draw(playAgain);
		Draw(goMenu);
	}
}