#pragma once
#include "Player.h"


namespace Modifiers
{
	enum class MODIFIER
	{
		NONE, BIGGER, SMALLER, FASTER, SLOWER
	};

	void ApplyModifier(Player::Player& player, MODIFIER modifier);
};

