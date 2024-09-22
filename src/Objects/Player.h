#pragma once
#include "Rectangle.h"
#include "Constants.h"

using namespace Rectangle;

namespace Player
{
	struct Player
	{
		Rec paddle;
		float speed;
		int lives;
	};

	extern Player player;

	void Init();
	void Draw();
}
