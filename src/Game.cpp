#include "Game.h"
#include "sl.h"
#include "Constants.h"
#include "Scene_Gameplay.h"

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

	slClose();
}

void Init()
{
	// set up our window and a few resources we need
	slWindow(screenWidth, screenHeight, "Simple SIGIL Example", false);
	slSetTextAlign(SL_ALIGN_CENTER);

	InitGameplay();
}

void Update()
{
	UpdateGameplay();
}

void Draw()
{
	DrawGameplay();
	slRender();
}


