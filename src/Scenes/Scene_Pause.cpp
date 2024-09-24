#include "Scene_Pause.h"
#include "Constants.h"

using namespace Constants;

namespace Pause
{
    Button::Button resume;
    Button::Button goMenu;

    void Init()
    {
        resume = Button::Create("Resume", screenWidth / 5 * 2 - resume.rectangle.width, screenHeight / 2, 250, 60);
        goMenu = Button::Create("Menu", screenWidth / 5 * 4 - goMenu.rectangle.width, screenHeight / 2, 250, 60);
    }


    void Draw()
    {
        if (resume.isSelected)
            RED
        else
            slSetForeColor(255, 0, 0, 0.65f);
        Button::Draw(resume);

        if (goMenu.isSelected)
            RED
        else
            slSetForeColor(255, 0, 0, 0.65f);
        Button::Draw(goMenu);
    }
}