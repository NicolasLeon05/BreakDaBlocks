#include "Game.h"
#include "sl.h"
#include "Constants.h"
#include "Scene_Gameplay.h"
#include "Scene_MainMenu.h"
#include "Scene_Pause.h"
#include "Button.h"

using namespace Button;
using namespace MainMenu;
using namespace Pause;

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
	static bool gameEnded;

	static float resumeTimer = 0.0f;

	void Run()
	{
		Init();

		while (!slShouldClose() && !IsButtonPressed(MainMenu::exit))
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
		gameEnded = false;;

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
					gameEnded = Gameplay::Update();
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
				if (IsButtonPressed(resume) || slGetKey(SL_KEY_ESCAPE)) //Resume gampeplay
				{
					waitingToResume = true;
					gamePaused = false;
				}
				else if (IsButtonPressed(menu)) //Go back to menu
				{
					gameEnded = true;
					gameStarted = false;
					ResetGameplay();
				}
			}
		}
		else if (IsButtonPressed(play)) //Starts game
		{
			gameStarted = true;
		}
	}

	void Draw()
	{
		if (gameEnded)
		{
			//Win/Lose scene
			WHITE
				slText(screenWidth / 2, screenHeight / 2, "button.text");
		}
		else if (!gameStarted)
		{
			MainMenu::Draw();
		}
		else
		{
			if (gamePaused)
				Draw();
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