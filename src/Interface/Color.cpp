#include "Color.h"
#include "sl.h"

namespace Colors
{
	void SetColor(COLOR color)
	{
		switch (color)
		{
		case COLOR::BLACK:
		{
			slSetForeColor(0, 0, 0, 1);
			break;
		}

		case COLOR::WHITE:
		{
			slSetForeColor(255, 255, 255, 1);
			break;
		}

		case COLOR::BLUE:
		{
			slSetForeColor(0, 0, 255, 1);
			break;
		}

		case COLOR::GREEN:
		{
			slSetForeColor(0, 255, 0, 1);
			break;
		}

		case COLOR::RED:
		{
			slSetForeColor(255, 0, 0, 1);
			break;
		}

		case COLOR::DARK_RED:
		{
			slSetForeColor(255, 0, 0, 0.65f);
			break;
		}

		default:
			slSetForeColor(255, 255, 255, 1);
			break;
		}
	}
}
