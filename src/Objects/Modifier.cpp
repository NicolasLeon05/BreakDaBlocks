#include "Modifier.h"

namespace Modifiers
{
	void ApplyModifier(Player::Player& player, MODIFIER modifier)
	{
		switch (modifier)
		{
		case MODIFIER::NONE:
		{
			break;
		}

		case MODIFIER::BIGGER:
		{
			player.paddle.width += 30;
			break;
		}

		case MODIFIER::SMALLER:
		{
			if (player.paddle.width -30 >= 30)
				player.paddle.width -= 30;
			break;
		}

		case MODIFIER::FASTER:
		{
			player.speed *= 1.25f;
			break;
		}

		case MODIFIER::SLOWER:
		{
			player.speed *= 0.75f;
			break;
		}

		default:

			break;
		}
	}
}
