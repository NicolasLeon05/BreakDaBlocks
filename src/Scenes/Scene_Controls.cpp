#include "Scene_Controls.h"
#include "Constants.h"

namespace Bton = Button;
using namespace Bton;
using namespace Constants;

namespace Controls
{
    Bton::Button goMenu;

    void Init()
    {
        goMenu = Create("Menu", screenWidth / 2, 60, 250, 60);
    }


    void Draw()
    {
        slSetFontSize(baseFontSize);
        slText(screenWidth / 2, screenHeight / 14 * 12, "Controls:");
        slSetFontSize(baseFontSize / 1.6);
        slText(screenWidth / 2, screenHeight / 14 * 11, "<- and -> / A and D to move");
        slText(screenWidth / 2, screenHeight / 14 * 10, "Space to launch the ball");
        slText(screenWidth / 2, screenHeight / 14 * 9, "Escape to pause the game");
        slSetFontSize(baseFontSize);
        slText(screenWidth / 2, screenHeight / 14 * 7, "Special Modifiers:");
        slSetFontSize(baseFontSize / 1.6);
        slText(screenWidth / 2, screenHeight / 14 * 6, "Red block: Bigger paddle");
        slText(screenWidth / 2, screenHeight / 14 * 5, "Yellow block: Smaller paddle");
        slText(screenWidth / 2, screenHeight / 14 * 4, "Blue block: Faster paddle");
        slText(screenWidth / 2, screenHeight / 14 * 3, "White block: Slower paddle");

        slSetFontSize(baseFontSize);
        Draw(goMenu);
    }
}