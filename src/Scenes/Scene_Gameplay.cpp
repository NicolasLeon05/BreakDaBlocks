#include "Scene_Gameplay.h"
#include "sl.h"
#include "Ball.h"
#include "Player.h"
#include "Constants.h"
#include "Block.h"
#include <cmath>


static const char KEY_SPACE = 32;
static float deathTimer = 0.0f;
static bool lifeLost = false;

void CheckWallCollision();
bool CheckRecCollision(Rectangle rectangle);
void CollideWithPlayer();
void CollideWithBlock(Block block);
void CheckBlockDestruction(Block blocks[blockRows][blockCols]);

void MoveBall();

void LoseLife();

void MovePlayer();

void LaunchBall();

void AccelerateBall();

float Clamp(float value, float min, float max);

//////////////////////////////////////////////////////////////////////////////////////////////
void InitGameplay() //Cambiar a Init solo y usar namespace
{
	InitPlayer();
	InitBall();
	InitBlocks();
}

void UpdateGameplay()
{
	if (!lifeLost)
	{
		MoveBall();
		CheckWallCollision();
		CollideWithPlayer();
		CheckBlockDestruction(blocks);
	}
	else
	{
		deathTimer += slGetDeltaTime();
		if (deathTimer > 1)
		{
			deathTimer = 0.0f;
			lifeLost = false;
			InitBall();
		}
	}

	MovePlayer();
}

void DrawGameplay()
{
	
	if (!lifeLost)
	{
		//Draw Ball
		RED
			slCircleFill(ball.x, ball.y, ball.radius, 100);
	}
	

	//Draw player
	BLUE
		slRectangleFill(player.paddle.x, player.paddle.y, player.paddle.width, player.paddle.height);

	//Draw blocks
	DrawBlocks();
}
//////////////////////////////////////////////////////////////////////////////////////////////


void MoveBall()
{
	//Ball follows player
	if (!ball.hasBeenLaunched)
	{
		ball.x = player.paddle.x;
	}
	else
	{
		ball.x += ball.speedX * slGetDeltaTime();
		ball.y += ball.speedY * slGetDeltaTime();
	}
}

void CheckWallCollision()
{
	//Lateral collision
	if (ball.x >= limitRight || ball.x <= limitLeft)
	{
		ball.speedX *= -1;
		if (ball.x >= limitRight)
			ball.x = limitRight - ball.radius;

		if (ball.x <= limitLeft)
			ball.x = limitLeft + ball.radius;
	}

	//Top/bottom collision
	if (ball.y >= limitUp || ball.y <= limitDown)
	{
		ball.speedY *= -1;
		if (ball.y >= limitUp)
		{
			ball.y = limitUp - ball.radius;
		}

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
	lifeLost = true;
}

bool CheckRecCollision(Rectangle rectangle)
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

void CollideWithPlayer()
{
	if (CheckRecCollision(player.paddle))
	{
		const float maxAngleDegrees = 60.0f;
		const float maxAngleRadians = maxAngleDegrees * (PI / 180.0f);

		//Relative position of the ball on the paddle
		float relativeX = (ball.x - player.paddle.x) / (player.paddle.width / 2);

		//Limits that value between -1 and 1
		relativeX = Clamp(relativeX, -1.0f, 1.0f);
		float bounceAngle = relativeX * maxAngleRadians;

		ball.speedX = ball.baseSpeed * sin(bounceAngle);
		ball.speedY = ball.baseSpeed * cos(bounceAngle);

		//Old collison
		/*if (!ball.isColiding)
		{
			ball.isColiding = true;
			ball.speedY *= -1;

			//collision on the sides
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
		*/
	}
}

void CollideWithBlock(Block block)
{
	if (!ball.isColiding)
	{
		ball.isColiding = true;
		ball.speedY *= -1;

		//collision on the sides
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

void CheckBlockDestruction(Block blocks[blockRows][blockCols])
{
	for (int i = 0; i < blockRows; i++)
	{
		for (int j = 0; j < blockCols; j++)
		{
			if (!blocks[i][j].isDestroyed)
			{
				if (CheckRecCollision(blocks[i][j].rectangle))
				{
					CollideWithBlock(blocks[i][j]);
					blocks[i][j].isDestroyed = true;
					AccelerateBall();
				}
			}
		}
	}
}

void MovePlayer()
{
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

void AccelerateBall()
{
	float accelerationRate = 1.05;
	ball.baseSpeed *= accelerationRate;
	ball.speedY *= accelerationRate;
	ball.speedX *= accelerationRate	;
}

float Clamp(float value, float min, float max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}