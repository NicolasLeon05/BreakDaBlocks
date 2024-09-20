#include "Scene_Gameplay.h"
#include "sl.h"
#include "Ball.h"
#include "Player.h"
#include "Constants.h"
#include "Block.h"

const char KEY_SPACE = 32;

void MoveBall();

void CheckWallColission();

bool CheckRecColission(Rectangle rectangle, Ball& ball);

void CheckBlockDestruction(Block blocks[blockRows][blockCols]);

void MovePlayer();

void LaunchBall();

void LoseLife();

//////////////////////////////////////////////////////////////////////////////////////////////
void InitGameplay()
{
	InitPlayer();
	InitBall();
	InitBlocks();
}

void UpdateGameplay()
{
	//La pelota se deberia mover solo cuando presiono space

	if(ball.hasBeenLaunched)
		MoveBall();

	MovePlayer();

	CheckWallColission();
	CheckRecColission(player.paddle, ball);
	CheckBlockDestruction(blocks);
}

void DrawGameplay()
{
	//Draw Ball
	RED
		slCircleFill(ball.x, ball.y, ball.radius, 100);

	//Draw player
	BLUE
		slRectangleFill(player.paddle.x, player.paddle.y, player.paddle.width, player.paddle.height);

	//Draw blocks
	DrawBlocks();
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

bool CheckRecColission(Rectangle rectangle, Ball& ball)
{
	if (rectangle.x + rectangle.width / 2 >= ball.x - ball.radius &&
		rectangle.x - rectangle.width / 2 <= ball.x + ball.radius &&
		rectangle.y + rectangle.height / 2 >= ball.y - ball.radius &&
		rectangle.y - rectangle.height / 2 <= ball.y + ball.radius)
	{
		if (!ball.isColiding)
		{
			ball.isColiding = true;
			ball.speedY *= -1;

			//Colission on the sides of the paddle
			if (ball.x < rectangle.x - rectangle.width / 2 || ball.x > rectangle.x + rectangle.width / 2)
			{
				ball.speedX *= -1;
				//Corrects ball position y
				if (ball.x < rectangle.x - rectangle.width / 2)
					ball.x = rectangle.x - rectangle.width / 2 - ball.radius - 1;
				else
					ball.x = rectangle.x + rectangle.width / 2 + ball.radius + 1;
			}
			else
			{
				//Corrects ball position X
			}
		}
		return true;
	}
	else
	{
		ball.isColiding = false;
		return false;
	}
}

void CheckBlockDestruction(Block blocks[blockRows][blockCols])
{
	for (int i = 0; i < blockRows; i++)
	{
		for (int j = 0; j < blockCols; j++)
		{
			if (CheckRecColission(blocks[i][j].rectangle, ball))
				blocks[i][j].isDestroyed = true;

		}
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
