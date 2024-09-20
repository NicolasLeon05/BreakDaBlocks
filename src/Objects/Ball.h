#pragma once
#include "Constants.h"

struct Ball
{
	const int radius = limitDown;
	float baseSpeed;
	float x;
	float y;
	float speedX;
	float speedY;
	float maxBounceAngle;
	bool isColiding;
	bool hasBeenLaunched;
};

extern Ball ball;

void InitBall();