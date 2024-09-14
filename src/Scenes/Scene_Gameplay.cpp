#include "Scene_Gameplay.h"
#include "Ball.h"
#include "Player.h"
#include "Constants.h"
#include "sl.h"

const char KEY_SPACE = 32;

void MoveBall();

void CheckWallColission();

void CheckPaddleColission();

void MovePlayer();

void LaunchBall();

void LoseLife();

//////////////////////////////////////////////////////////////////////////////////////////////
void InitGameplay()
{
	InitPlayer();
	InitBall();
}

void UpdateGameplay()
{
	//La pelota se deberia mover solo cuando presiono start

	if(ball.hasBeenLaunched)
		MoveBall();

	MovePlayer();

	CheckWallColission();
	CheckPaddleColission();
}

void DrawGameplay()
{
	//Draw Ball
	RED
		slCircleFill(ball.x, ball.y, ball.radius, 100);

	//Draw player
	BLUE
		slRectangleFill(player.paddle.x, player.paddle.y, player.paddle.width, player.paddle.height);

}
//////////////////////////////////////////////////////////////////////////////////////////////


void MoveBall()
{
	ball.x += ball.speedX * slGetDeltaTime();
	ball.y += ball.speedY * slGetDeltaTime();
}

void CheckWallColission()
{
	//Lateral colission
	if (ball.x >= limitRight || ball.x <= limitLeft)
	{
		ball.speedX *= -1;
		if (ball.x >= limitRight)
			ball.x = limitRight - ball.radius;

		if (ball.x <= limitLeft)
			ball.x = limitLeft + ball.radius;
	}

	//Top/bottom colission
	if (ball.y >= limitUp || ball.y <= limitDown)
	{
		ball.speedY *= -1;
		if (ball.y >= limitUp)
			ball.y = limitUp - ball.radius;

		if (ball.y <= limitDown)
		{
			ball.y = limitDown + ball.radius;
			LoseLife();
		}

	}

}

void CheckPaddleColission()
{
	if (player.paddle.x + player.paddle.width / 2 >= ball.x - ball.radius &&
		player.paddle.x - player.paddle.width / 2 <= ball.x + ball.radius &&
		player.paddle.y + player.paddle.height / 2 >= ball.y - ball.radius &&
		player.paddle.y - player.paddle.height / 2 <= ball.y + ball.radius)
	{
		if (!ball.isColiding)
		{
			ball.isColiding = true;
			ball.speedY *= -1;

			//Colission on the sides of the paddle
			if (ball.x < player.paddle.x - player.paddle.width / 2 || ball.x > player.paddle.x + player.paddle.width / 2)
			{
				ball.speedX *= -1;
				//Corrects ball position y
				if (ball.x < player.paddle.x - player.paddle.width / 2)
					ball.x = player.paddle.x - player.paddle.width / 2 - ball.radius - 1;
				else
					ball.x = player.paddle.x + player.paddle.width / 2 + ball.radius + 1;
			}
			else
			{
				//Corrects ball position X
			}
		}
	}
	else
	{
		ball.isColiding = false;
	}
}

void MovePlayer()
{
	//Ball follows player
	if (!ball.hasBeenLaunched)
		ball.x = player.paddle.x;

	if (slGetKey(SL_KEY_LEFT))
	{
		if (player.paddle.x - player.paddle.width / 2 <= 0)
			player.paddle.x = player.paddle.width / 2;
		else
			player.paddle.x -= player.speed * slGetDeltaTime();
	}
	else if (slGetKey(SL_KEY_RIGHT))
	{
		if (player.paddle.x + player.paddle.width / 2 >= screenWidth)
			player.paddle.x = screenWidth - player.paddle.width / 2;
		else
			player.paddle.x += player.speed * slGetDeltaTime();
	}
	else if (slGetKey(KEY_SPACE))
		LaunchBall();
}

void LaunchBall()
{
	if (!ball.hasBeenLaunched)
		ball.hasBeenLaunched = true;
}

void LoseLife()
{
	player.lives--;
	InitBall();
}
