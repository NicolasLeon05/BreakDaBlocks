#pragma once
#include "Constants.h"

struct Ball
{
	const int radius = limitDown;
	float x;
	float y;
	const float baseSpeed = 400.0f;
	float speedX;
	float speedY;
	bool isColiding;
	bool hasBeenLaunched;
};

extern Ball ball;

void InitBall();