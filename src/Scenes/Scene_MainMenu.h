#pragma once
#include <sl.h>
#include "Button.h"

namespace MainMenu
{
	void Init();
	void Draw();

	extern Button::Button play;
	extern Button::Button credits;
	extern Button::Button exit;
}

