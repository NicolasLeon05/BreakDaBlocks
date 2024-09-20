#include "Ball.h"
#include "Player.h"
#include <cmath>

Ball ball;

void InitBall()
{
	const double pi = 3.141592653589793;

	ball.x = player.paddle.x;
	ball.y = player.paddle.y + player.paddle.height / 2 + ball.radius + 5;
	ball.baseSpeed = 400.0f;
	ball.speedX = ball.baseSpeed;
	ball.speedY = ball.baseSpeed;
	ball.maxBounceAngle = (5.0 * pi) / 12.0;
	ball.isColiding = false;
	ball.hasBeenLaunched = false;
}