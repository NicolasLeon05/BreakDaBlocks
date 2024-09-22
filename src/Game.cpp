#include "Game.h"
#include "sl.h"
#include "Constants.h"
#include "Scene_Gameplay.h"
#include "Scene_MainMenu.h"
#include "Scene_Pause.h"
#include "Button.h"

namespace Game
{
	static void Init();

	static void Update();

	static void Draw();

	static void DeInit();

	static void ResetGameplay();

	int font;

	static bool gameStarted;
	static bool gamePaused;
	static bool waitingToResume;

	static float resumeTimer = 0.0f;

	void Run()
	{
		Init();

		while (!slShouldClose() && !Button::IsButtonPressed(MainMenu::exit))
		{
			Update();
			Draw();
		}

		DeInit();
	}

	void Init()
	{
		slWindow(screenWidth, screenHeight, "Breakout", false);
		font = slLoadFont("res/Fonts/Silkscreen-Regular.ttf");
		slSetFont(font, 50);
		slSetTextAlign(SL_ALIGN_CENTER);

		gameStarted = false;
		gamePaused = false;
		waitingToResume = false;

		MainMenu::Init();
		Gameplay::Init();
		Pause::Init();
	}

	void Update()
	{
		if (gameStarted)
		{
			if (!gamePaused) //Run gameplay
			{
				if (!waitingToResume)
				{
					Gameplay::Update();
				}
				else
				{
					resumeTimer += slGetDeltaTime();
					if (resumeTimer >= 1)
					{
						waitingToResume = false;
						resumeTimer = 0.0f;
					}
				}

				if (slGetKey(SL_KEY_ESCAPE)) //Pauses game
					gamePaused = true;
			}
			else //Show pause menu
			{
				if (Button::IsButtonPressed(Pause::resume) || slGetKey(SL_KEY_ESCAPE)) //Resume gampeplay
				{
					waitingToResume = true;
					gamePaused = false;
				}
				else if (Button::IsButtonPressed(Pause::menu)) //Go back to menu
				{
					gameStarted = false;
					ResetGameplay();
				}
			}
		}
		else if (Button::IsButtonPressed(MainMenu::play)) //Starts game
		{
			gameStarted = true;
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
			if (gamePaused)
				Pause::Draw();
			else
				Gameplay::Draw();
		}

		slRender();
	}

	void DeInit()
	{
		slClose();
	}

	void ResetGameplay()
	{
		Gameplay::Init();

		gameStarted = false;
		gamePaused = false;
		waitingToResume = false;

		resumeTimer = 0.0f;
	}
}