#include "Game.h"
#include "sl.h"
#include "Constants.h"
#include "Scene_Gameplay.h"
#include "Scene_MainMenu.h"
#include "Button.h"
#include <iostream>

namespace Game
{
	static void Init();

	static void Update();

	static void Draw();

	static void DeInit();

	static int font;
	static bool gameStarted = false;

	void Run()
	{
		Init();

		while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
		{
			Update();
			Draw();
		}

		DeInit();
	}

	void Init()
	{
		slWindow(screenWidth, screenHeight, "Breakout", false);
		//int font = slLoadFont("Silkscreen-Regular.ttf");
		//slSetFont(font, 100);
		//slSetTextAlign(SL_ALIGN_CENTER);

		MainMenu::Init();
		Gameplay::Init();
	}

	void Update()
	{
		if (gameStarted)
		{
			Gameplay::Update();
		}
		else
		{
			if (Button::IsButtonPressed(MainMenu::play))
			{
				gameStarted = true;
			}
		}
	}

	void Draw()
	{
		if (!gameStarted)
		{
			MainMenu::Draw();
		}
		else
		{
			Gameplay::Draw();
		}
		slRender();
	}

	void DeInit()
	{
		slClose();
	}
}