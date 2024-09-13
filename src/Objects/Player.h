#pragma once
#include "Rectangle.h"
#include "Constants.h"

struct Player
{
	Rectangle paddle;
	float speed;
	int lives;
};

extern Player player;

void InitPlayer();