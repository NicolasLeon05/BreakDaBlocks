#include "Game.h"
#include "sl.h"
#include "Constants.h"
#include "Scene_MainMenu.h"
#include "Scene_Controls.h"
#include "Scene_Gameplay.h"
#include "Scene_Pause.h"
#include "Scene_Result.h"
#include "Button.h"

using namespace Button;
using namespace MainMenu;
using namespace Pause;
using namespace Result;
using namespace Constants;
using namespace Controls;

namespace Game
{
	static void Init();

	static void Update();

	static void Draw();

	static void DeInit();

	static void ResetGameplay();

	int font;

	static bool viewingControls;
	static bool gameStarted;
	static bool gamePaused;
	static bool waitingToResume;
	static bool gameEnded;

	static float resumeTimer = 0.0f;
	static float pauseTimer = 0.0f;

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
		slSetFont(font, baseFontSize);
		slSetTextAlign(SL_ALIGN_CENTER);

		gameStarted = false;
		gamePaused = false;
		waitingToResume = false;
		gameEnded = false;
		viewingControls = false;

		MainMenu::Init();
		Controls::Init();
		Gameplay::Init();
		Pause::Init();
		Result::Init();
	}

	void Update()
	{
		if (gameEnded) //Result Scene
		{
			if (IsButtonPressed(playAgain))
			{
				ResetGameplay();
				gameStarted = true;
			}
			else if (IsButtonPressed(Result::goMenu))
			{
				ResetGameplay();
			}
		}
		else if (gameStarted) //Run gameplay
		{
			if (!gamePaused) //Gameplay Scene
			{
				if (!waitingToResume)
				{
					gameEnded = Gameplay::Update();
				}
				else
				{
					resumeTimer += slGetDeltaTime();
					if (resumeTimer >= 0.2f)
					{
						waitingToResume = false;
						resumeTimer = 0.0f;
					}
				}

				pauseTimer += slGetDeltaTime();
				if ((slGetKey(SL_KEY_ESCAPE) && pauseTimer > 0.2f)) //Pauses game
				{
					pauseTimer = 0.0f;
					gamePaused = true;
				}
			}
			else //Pause Scene
			{
				pauseTimer += slGetDeltaTime();
				if (IsButtonPressed(resume) || (slGetKey(SL_KEY_ESCAPE) && pauseTimer > 0.2f)) //Resume gampeplay
				{
					pauseTimer = 0.0f;
					waitingToResume = true;
					gamePaused = false;
				}
				else if (IsButtonPressed(Pause::goMenu)) //Go back to menu
				{
					gameStarted = false;
					ResetGameplay();
				}
			}
		}
		else //Menu
		{
			if (viewingControls && IsButtonPressed(Controls::goMenu))
				viewingControls = false;

			if (IsButtonPressed(controls)) //Controls scene
				viewingControls = true;

			if (IsButtonPressed(play)) //Gameplay scene
				gameStarted = true;
		}
	}

	void Draw()
	{
		if (gameEnded)//Result scene
		{		
			Result::Draw(Player::player);
		}
		else if (gameStarted) //Main Menu scene
		{
			if (gamePaused) //Pause scene 
				Pause::Draw();
			else			//Gameplay scene
				Gameplay::Draw();
		}
		else
		{
			if (!viewingControls)
				MainMenu::Draw();
			else
				Controls::Draw();	
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
		gameEnded = false;

		pauseTimer = 0.0f;
		resumeTimer = 0.0f;
	}
}