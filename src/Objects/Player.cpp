#include "Player.h"
#include "Constants.h"


namespace Player
{
	Player player;

	void Init()
	{
		//InitPlayer
		player.paddle.x = screenWidth / 2;
		player.paddle.y = 50.0f;
		player.paddle.width = screenWidth / 6;
		player.paddle.height = screenHeight / 32;
		player.speed = 750.0f;
		player.lives = 5;
	}
}
