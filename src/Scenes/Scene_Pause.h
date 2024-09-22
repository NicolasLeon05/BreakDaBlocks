#pragma once
#include "Button.h"

namespace Bton = Button;

namespace Pause
{
	void Init();
	void Draw();

	extern Bton::Button resume;
	extern Bton::Button goMenu;
}