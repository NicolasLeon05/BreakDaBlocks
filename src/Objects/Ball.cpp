#include "Ball.h"
#include "Player.h"
#include <iostream>
#include "sl.h"

using namespace Player;

namespace Ball
{
	Ball ball;

	float GenerateRandomAngle();

	void Init()
	{
		float randomAngle = GenerateRandomAngle();

		ball.x = player.paddle.x;
		ball.y = player.paddle.y + player.paddle.height / 2 + ball.radius + 5;
		ball.baseSpeed = 400.0f;
		ball.speedX = ball.baseSpeed * cos(randomAngle);
		ball.speedY = ball.baseSpeed * sin(randomAngle);
		ball.isColiding = false;
		ball.hasBeenLaunched = false;
	}

	void Draw()
	{
		RED
			slCircleFill(ball.x, ball.y, ball.radius, 100);
	}

	float GenerateRandomAngle()
	{
		int randomAngle;
		bool angleFound;

		do
		{
			angleFound = true;

			randomAngle = rand() % 131 + 25;
		} while (!angleFound);

		float angleRadians = randomAngle * (PI / 180.0f);

		return angleRadians;
	}
}
