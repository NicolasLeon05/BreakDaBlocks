#include "Scene_Gameplay.h"
#include "sl.h"
#include "Ball.h"
#include "Player.h"
#include "Constants.h"
#include "Block.h"

const char KEY_SPACE = 32;
float deathTimer = 0.0f;

void CheckWallColission(Ball& ball);
bool CheckRecColission(Rectangle rectangle, Ball& ball);
void CollideWithPlayer(Player player, Ball& ball);
void CollideWithBlock(Block block, Ball& ball);
void CheckBlockDestruction(Block blocks[blockRows][blockCols], Ball& ball);

void MoveBall();

void LoseLife();

void MovePlayer();

void LaunchBall();

void AccelerateBall(Ball& ball);

//////////////////////////////////////////////////////////////////////////////////////////////
void InitGameplay() //Cambiar a Init solo y usar namespace
{
	InitPlayer();
	InitBall();
	InitBlocks();
}

void UpdateGameplay()
{
	if(ball.hasBeenLaunched)
		MoveBall();

	MovePlayer();

	CheckWallColission(ball);
	CollideWithPlayer(player, ball);
	CheckBlockDestruction(blocks, ball);
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

void CheckWallColission(Ball& ball)
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

void LoseLife()
{
	player.lives--;

	InitBall();
}

bool CheckRecColission(Rectangle rectangle, Ball& ball)
{
	if (rectangle.x + rectangle.width / 2 >= ball.x - ball.radius &&
		rectangle.x - rectangle.width / 2 <= ball.x + ball.radius &&
		rectangle.y + rectangle.height / 2 >= ball.y - ball.radius &&
		rectangle.y - rectangle.height / 2 <= ball.y + ball.radius)
	{
		return true;
	}
	else
	{
		ball.isColiding = false;
		return false;
	}
}

void CollideWithPlayer(Player player, Ball& ball)
{
	if (CheckRecColission(player.paddle, ball))
	{
		if (!ball.isColiding)
		{
			ball.isColiding = true;
			ball.speedY *= -1;

			//Colission on the sides
			if (ball.x < player.paddle.x - player.paddle.width / 2 || ball.x > player.paddle.x + player.paddle.width / 2)
			{
				ball.speedX *= -1;
				//Corrects ball position x
				if (ball.x < player.paddle.x - player.paddle.width / 2)
					ball.x = player.paddle.x - player.paddle.width / 2 - ball.radius - 1;
				else
					ball.x = player.paddle.x + player.paddle.width / 2 + ball.radius + 1;
			}
			else if(player.paddle.y + player.paddle.height / 2 >= ball.y - ball.radius)
			{
				//Corrects ball position y
				ball.y = player.paddle.y + player.paddle.height / 2 + ball.radius + 1;
			}
		}
	}
	
}

void CollideWithBlock(Block block, Ball& ball)
{
	if (!ball.isColiding)
	{
		ball.isColiding = true;
		ball.speedY *= -1;

		//Colission on the sides
		if (ball.x < block.rectangle.x - block.rectangle.width / 2 || ball.x > block.rectangle.x + block.rectangle.width / 2)
		{
			ball.speedX *= -1;
			ball.speedY *= -1;
			//Corrects ball position x
			if (ball.x < block.rectangle.x - block.rectangle.width / 2)
				ball.x = block.rectangle.x - block.rectangle.width / 2 - ball.radius - 1;
			else
				ball.x = block.rectangle.x + block.rectangle.width / 2 + ball.radius + 1;
		}
		else
		{
			//Corrects ball position y
		}
	}
}

void CheckBlockDestruction(Block blocks[blockRows][blockCols], Ball& ball)
{
	for (int i = 0; i < blockRows; i++)
	{
		for (int j = 0; j < blockCols; j++)
		{
			if (!blocks[i][j].isDestroyed)
			{
				if (CheckRecColission(blocks[i][j].rectangle, ball))
				{
					CollideWithBlock(blocks[i][j], ball);
					blocks[i][j].isDestroyed = true;
					AccelerateBall(ball);
				}
			}
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

	if (slGetKey(KEY_SPACE))
		LaunchBall();
}

void LaunchBall()
{
	if (!ball.hasBeenLaunched)
		ball.hasBeenLaunched = true;
}

void AccelerateBall(Ball& ball)
{
	float accelerationRate = 1.03;
	ball.speedY *= accelerationRate;
	ball.speedX *= accelerationRate;
}
