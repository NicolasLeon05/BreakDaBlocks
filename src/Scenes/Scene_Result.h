#pragma once
#include "Player.h"
#include "Button.h"

namespace Bton = Button;

namespace Result
{
	void Init();
	void Draw(Player::Player player);

	extern Bton::Button playAgain;
	extern Bton::Button goMenu;
}

