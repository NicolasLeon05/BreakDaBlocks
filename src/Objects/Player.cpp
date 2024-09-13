#include "Player.h"
#include "Constants.h"

Player player;

void InitPlayer()
{
	//InitPlayer
	player.paddle.x = screenWidth / 2;
	player.paddle.y = 50.0f;
	player.paddle.width = screenWidth / 6;
	player.paddle.height = 20.0f;
	player.speed = 500.0f;
	player.lives = 5;
}