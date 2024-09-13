#include "sl.h"

//Esto va en constants.h

//Screen size
const int screenWidth = 1280;
const int screenHeight = 720;

//Screen Limits
const int limitDown = 15;
const int limitUp = screenHeight - limitDown;
const int limitLeft = limitDown;
const int limitRight = screenWidth - limitLeft;

const int paddleSpeed = 700;

const int lives = 5;
/////////////////////////////////////////////////////////
//Ball
struct Ball
{
    const int radius = limitDown;
    float x;
    float y;
    const float baseSpeed = 800.0f;
    float speedX;
    float speedY;
    bool isColiding;
};
Ball ball;


//Rectangle
struct Rectangle
{
    float x;
    float y;
    float width;
    float height;
};


//Player
struct Player 
{
    Rectangle paddle;
    float speed;
};
Player player;


void MoveBall();

void CheckWallColission();

void MovePlayer();

int main(int args, char* argv[])
{
    
    //InitBall
    ball.x = 500;
    ball.y = 500;
    ball.speedX = ball.baseSpeed;
    ball.speedY = ball.baseSpeed;

    //InitPlayer
    player.paddle.x = screenWidth / 2;
    player.paddle.y = 50.0f;
    player.paddle.width = screenWidth / 5;
    player.paddle.height = 20.0f;
    player.speed = 500.0f;


    // set up our window and a few resources we need
    slWindow(screenWidth, screenHeight, "Simple SIGIL Example", false);
    slSetTextAlign(SL_ALIGN_CENTER);

    while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
    {
        slCircleFill(ball.x, ball.y, ball.radius, 100);
        slRectangleFill(player.paddle.x, player.paddle.y, player.paddle.width, player.paddle.height);
        MoveBall();
        MovePlayer();
        CheckWallColission();

        slRender();
    }
    slClose();
    return 0;
}


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
			ball.y = limitDown + ball.radius;
	}

}

void MovePlayer()
{
    if (slGetKey(SL_KEY_LEFT) && player.paddle.x - player.paddle.width / 2 > 0)
    {
        player.paddle.x -= player.speed * slGetDeltaTime();
    }
    else if (player.paddle.x - player.paddle.width / 2 < 0)
    {
        player.paddle.x = player.paddle.width / 2;
    }
    else if (slGetKey(SL_KEY_RIGHT) && player.paddle.x + player.paddle.width / 2 < screenWidth)
    {
        player.paddle.x += player.speed * slGetDeltaTime();
    }
    else if (player.paddle.x + player.paddle.width / 2 > screenWidth)
    {
        player.paddle.x = screenWidth - player.paddle.width / 2;
    }
}
