#include "Scene_Gameplay.h"
#include "sl.h"
#include "Ball.h"
#include "Player.h"
#include "Constants.h"
#include "Block.h"
#include <cmath>
#include <string>;

namespace P = Player;
namespace B = Ball;

using namespace P;
using namespace B;
using namespace Blocks;
using namespace Rectangle;
using namespace std;


namespace Gameplay
{
	static bool lifeLost;

	static int blocksDestroyed;

	static float deathTimer;

	void CheckWallCollision();
	bool CheckRecCollision(Rec rectangle);
	void CollideWithPlayer();
	void CollideWithBlock(Block block);
	void CheckBlockDestruction(Block blocks[blockRows][blockCols]);

	void MoveBall();
	void LaunchBall();
	void AccelerateBall();

	void LoseLife();

	void MovePlayer();

	float Clamp(float value, float min, float max);

	//////////////////////////////////////////////////////////////////////////////////////////////
	void Init()
	{
		Blocks::Init();
		P::Init();
		B::Init();

		lifeLost = false;
		blocksDestroyed = 0;
		deathTimer = 0.0f;
	}

	bool Update()
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
				B::Init();
			}
		}
		return player.lives <= 0 || blocksDestroyed >= totalBlocks;
	}

	void Draw()
	{
		slSetFontSize(30);
		WHITE
		string lifeText = "Lives: " + to_string(player.lives);
		slText(70, screenHeight - 30, lifeText.data());

		string blockText = "Blocks: " + to_string(blocksDestroyed) + "/" + to_string(totalBlocks);
		slText(screenWidth - 240, screenHeight - 30, blockText.data());

		slSetFontSize(baseFontSize);
		P::Draw();
		B::Draw();
		Blocks::Draw();
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
				ball.x = limitRight - 1;

			if (ball.x <= limitLeft)
				ball.x = limitLeft + 1;
		}

		//Top/bottom collision
		if (ball.y >= limitUp || ball.y <= limitDown)
		{
			ball.speedY *= -1;
			if (ball.y >= limitUp)
			{
				ball.y = limitUp - 1;
			}

			if (ball.y <= limitDown)
			{
				ball.y = limitDown;
				LoseLife();
			}
		}
	}

	void LoseLife()
	{
		player.lives--;
		lifeLost = true;
	}

	bool CheckRecCollision(Rec rectangle)
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
		}
	}

	void CollideWithBlock(Blocks::Block block)
	{
		if (!ball.isColiding)
		{
			ball.isColiding = true;


			//collision on the sides
			if (ball.x < block.rectangle.x - block.rectangle.width / 2 || ball.x > block.rectangle.x + block.rectangle.width / 2)
			{
				ball.speedX *= -1;

				//Corrects ball position x
				if (ball.x < block.rectangle.x - block.rectangle.width / 2)
					ball.x = block.rectangle.x - block.rectangle.width / 2 - ball.radius - 1;
				else
					ball.x = block.rectangle.x + block.rectangle.width / 2 + ball.radius + 1;
			}
			else //Collision on the top/bottom
			{
				ball.speedY *= -1;
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
						blocksDestroyed++;
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
		ball.speedX *= accelerationRate;
	}

	float Clamp(float value, float min, float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
}