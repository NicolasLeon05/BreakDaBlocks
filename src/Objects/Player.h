#pragma once
#include "Rectangle.h"
#include "Constants.h"

namespace Player
{
	struct Player
	{
		Rectangle paddle;
		float speed;
		int lives;
	};

	extern Player player;

	void Init();
	void Draw();
}
