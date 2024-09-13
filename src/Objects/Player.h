#pragma once
#include "Rectangle.h"

struct Player
{
	Rectangle paddle;
	float speed;
};

extern Player player;

void InitPlayer();