#include "Game.h"
#include "sl.h"
#include "Constants.h"
#include "Scene_Gameplay.h"

namespace Game
{
	static void Init();

	static void Update();

	static void Draw();

	static void DeInit(); //Completar


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
		// set up our window and a few resources we need
		slWindow(screenWidth, screenHeight, "Simple SIGIL Example", false);
		slSetTextAlign(SL_ALIGN_CENTER);

		Gameplay::Init();
	}

	void Update()
	{
		Gameplay::Update();
	}

	void Draw()
	{
		Gameplay::Draw();
		slRender();
	}

	void DeInit()
	{
		slClose();
	}
}