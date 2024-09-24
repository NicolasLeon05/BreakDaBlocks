#include "Scene_Result.h"

namespace Bton = Button;
using namespace Bton;
using namespace Constants;

namespace Result
{
	Bton::Button playAgain;
	Bton::Button goMenu;

	void Init()
	{
		int width = 400;
		// Suma del ancho de ambos rectángulos
		int totalRectanglesWidth = width + width;

		// Espacio restante en la pantalla
		int remainingSpace = screenWidth - totalRectanglesWidth;

		// Dividir el espacio restante entre 3 (dos espacios laterales y uno intermedio)
		int spaceBetween = remainingSpace / 3;

		// Calcular las posiciones de los rectángulos
		int playAgainX = spaceBetween + (width / 2);  // Posición del primer rectángulo (playAgain)
		int goMenuX = playAgainX + width + spaceBetween;  // Posición del segundo rectángulo (goMenu)

		playAgain = Create("Play Again", playAgainX, screenHeight / 5 * 2, 400, 60);
		goMenu = Create("Menu", goMenuX, screenHeight / 5 * 2, 250, 60);
	}

	void Draw(Player::Player player)
	{
		WHITE
			if (player.lives <= 0)
				slText(screenWidth / 2, screenHeight / 3 * 2, "YOU LOST!");
			else
					slText(screenWidth / 2, screenHeight / 3 * 2, "YOU WON!");

		if (playAgain.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Draw(playAgain);

		if (goMenu.isSelected)
			RED
		else
			slSetForeColor(255, 0, 0, 0.65f);
		Draw(goMenu);
	}
}