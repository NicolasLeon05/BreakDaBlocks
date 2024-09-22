#pragma once
#include "Button.h"

namespace Bton = Button;

namespace MainMenu
{
	void Init();
	void Draw();

	extern Bton::Button play;
	extern Bton::Button tutorial;
	extern Bton::Button exit;
}

