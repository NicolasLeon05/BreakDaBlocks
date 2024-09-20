#pragma once
#include "Constants.h"

struct Ball
{
	const int radius = limitDown;
	const float baseSpeed = 400.0f;
	float x;
	float y;
	float speedX;
	float speedY;
	bool isColiding;
	bool hasBeenLaunched;
};

extern Ball ball;

void InitBall();