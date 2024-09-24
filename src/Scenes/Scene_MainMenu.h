#pragma once
#include "Button.h"

namespace Bton = Button;

namespace MainMenu
{
	void Init();
	void Draw();

	extern Bton::Button play;
	extern Bton::Button controls;
	extern Bton::Button exit;
}

