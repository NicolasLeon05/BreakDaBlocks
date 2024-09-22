#include "Scene_Gameplay.h"
#include "sl.h"
#include "Ball.h"
#include "Player.h"
#include "Constants.h"
#include "Block.h"
#include <cmath>

namespace Gameplay
{
	static const char KEY_SPACE = 32;
	static float deathTimer = 0.0f;
	static bool lifeLost = false;
	//static Ball::Ball ball = Ball::ball;
	//static Player::Player player = Player::player;
	//static Blocks::Block blocks[blockRows][blockCols] = Blocks::blocks;


	void CheckWallCollision();
	bool CheckRecCollision(Rectangle rectangle);
	void CollideWithPlayer();
	void CollideWithBlock(Blocks::Block block);
	void CheckBlockDestruction(Blocks::Block blocks[blockRows][blockCols]);

	void MoveBall();
	void LaunchBall();
	void AccelerateBall();

	void LoseLife();

	void MovePlayer();

	float Clamp(float value, float min, float max);

	//////////////////////////////////////////////////////////////////////////////////////////////
	void Init() //Cambiar a Init solo y usar namespace
	{
		Player::Init();
		Ball::Init();
		Blocks::Init();
	}

	void Update()
	{
		MovePlayer();

		if (!lifeLost)
		{
			MoveBall();
			CheckWallCollision();
			CollideWithPlayer();
			CheckBlockDestruction(Blocks::blocks);
		}
		else
		{
			deathTimer += slGetDeltaTime();
			if (deathTimer > 1)
			{
				deathTimer = 0.0f;
				lifeLost = false;
				Ball::Init();
			}
		}
	}

	void Draw()
	{
		Ball::Draw();
		Player::Draw();
		Blocks::Draw();
	}
	//////////////////////////////////////////////////////////////////////////////////////////////


	void MoveBall()
	{
		//Ball follows player
		if (!Ball::ball.hasBeenLaunched)
		{
			Ball::ball.x = Player::player.paddle.x;
		}
		else
		{
			Ball::ball.x += Ball::ball.speedX * slGetDeltaTime();
			Ball::ball.y += Ball::ball.speedY * slGetDeltaTime();
		}
	}

	void CheckWallCollision()
	{
		//Lateral collision
		if (Ball::ball.x >= limitRight || Ball::ball.x <= limitLeft)
		{
			Ball::ball.speedX *= -1;
			if (Ball::ball.x >= limitRight)
				Ball::ball.x = limitRight - 1;

			if (Ball::ball.x <= limitLeft)
				Ball::ball.x = limitLeft + 1;
		}

		//Top/bottom collision
		if (Ball::ball.y >= limitUp || Ball::ball.y <= limitDown)
		{
			Ball::ball.speedY *= -1;
			if (Ball::ball.y >= limitUp)
			{
				Ball::ball.y = limitUp - 1;
			}

			if (Ball::ball.y <= limitDown)
			{
				Ball::ball.y = limitDown;
				LoseLife();
			}
		}
	}

	void LoseLife()
	{
		Player::player.lives--;
		lifeLost = true;
	}

	bool CheckRecCollision(Rectangle rectangle)
	{
		if (rectangle.x + rectangle.width / 2 >= Ball::ball.x - Ball::ball.radius &&
			rectangle.x - rectangle.width / 2 <= Ball::ball.x + Ball::ball.radius &&
			rectangle.y + rectangle.height / 2 >= Ball::ball.y - Ball::ball.radius &&
			rectangle.y - rectangle.height / 2 <= Ball::ball.y + Ball::ball.radius)
		{
			return true;
		}
		else
		{
			Ball::ball.isColiding = false;
			return false;
		}
	}

	void CollideWithPlayer()
	{
		if (CheckRecCollision(Player::player.paddle))
		{
			const float maxAngleDegrees = 60.0f;
			const float maxAngleRadians = maxAngleDegrees * (PI / 180.0f);

			//Relative position of the ball on the paddle
			float relativeX = (Ball::ball.x - Player::player.paddle.x) / (Player::player.paddle.width / 2);

			//Limits that value between -1 and 1
			relativeX = Clamp(relativeX, -1.0f, 1.0f);
			float bounceAngle = relativeX * maxAngleRadians;

			Ball::ball.speedX = Ball::ball.baseSpeed * sin(bounceAngle);
			Ball::ball.speedY = Ball::ball.baseSpeed * cos(bounceAngle);
		}
	}

	void CollideWithBlock(Blocks::Block block)
	{
		if (!Ball::ball.isColiding)
		{
			Ball::ball.isColiding = true;


			//collision on the sides
			if (Ball::ball.x < block.rectangle.x - block.rectangle.width / 2 || Ball::ball.x > block.rectangle.x + block.rectangle.width / 2)
			{
				Ball::ball.speedX *= -1;

				//Corrects ball position x
				if (Ball::ball.x < block.rectangle.x - block.rectangle.width / 2)
					Ball::ball.x = block.rectangle.x - block.rectangle.width / 2 - Ball::ball.radius - 1;
				else
					Ball::ball.x = block.rectangle.x + block.rectangle.width / 2 + Ball::ball.radius + 1;
			}
			else //Collision on the top/bottom
			{
				Ball::ball.speedY *= -1;
			}
		}
	}

	void CheckBlockDestruction(Blocks::Block blocks[blockRows][blockCols])
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
			if (Player::player.paddle.x - Player::player.paddle.width / 2 <= 0)
				Player::player.paddle.x = Player::player.paddle.width / 2;
			else
				Player::player.paddle.x -= Player::player.speed * slGetDeltaTime();
		}
		else if (slGetKey(SL_KEY_RIGHT))
		{
			if (Player::player.paddle.x + Player::player.paddle.width / 2 >= screenWidth)
				Player::player.paddle.x = screenWidth - Player::player.paddle.width / 2;
			else
				Player::player.paddle.x += Player::player.speed * slGetDeltaTime();
		}

		if (slGetKey(KEY_SPACE))
			LaunchBall();
	}

	void LaunchBall()
	{
		if (!Ball::ball.hasBeenLaunched)
			Ball::ball.hasBeenLaunched = true;
	}

	void AccelerateBall()
	{
		float accelerationRate = 1.05;
		Ball::ball.baseSpeed *= accelerationRate;
		Ball::ball.speedY *= accelerationRate;
		Ball::ball.speedX *= accelerationRate;
	}

	float Clamp(float value, float min, float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
}