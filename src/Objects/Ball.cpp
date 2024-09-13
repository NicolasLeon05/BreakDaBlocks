#include "Ball.h"
#include "Player.h"

Ball ball;

void InitBall()
{
	ball.x = player.paddle.x;
	ball.y = player.paddle.y + player.paddle.height / 2 + ball.radius + 5;
	ball.speedX = ball.baseSpeed;
	ball.speedY = ball.baseSpeed;
	ball.isColiding = false;
	ball.hasBeenLaunched = false;
}