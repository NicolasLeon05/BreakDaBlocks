#include "Player.h"
#include "Constants.h"
#include "sl.h"
#include "Color.h"

using namespace Colors;
using namespace Constants;

namespace Player
{
	Player player;

	void Init()
	{
		player.paddle.x = screenWidth / 2;
		player.paddle.y = 50.0f;
		player.paddle.width = screenWidth / 6;
		player.paddle.height = screenHeight / 32;
		player.speed = 750.0f;
		player.lives = 5;
	}
	void Draw()
	{
		SetColor(COLOR::BLUE);
		slRectangleFill(player.paddle.x, player.paddle.y, player.paddle.width, player.paddle.height);
	}
}
