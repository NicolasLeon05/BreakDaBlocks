#include "Scene_Pause.h"
#include "Constants.h"

namespace Pause
{
    Button::Button resume;
    Button::Button menu;

    void Init()
    {
        resume = Button::Create("Resume", screenWidth / 5 * 2 - resume.rectangle.width, screenHeight / 2, 250, 60);
        menu = Button::Create("Menu", screenWidth / 5 * 4 - menu.rectangle.width, screenHeight / 2, 250, 60);
    }


    void Draw()
    {
        if (resume.isSelected)
            RED
        else
            slSetForeColor(255, 0, 0, 0.65f);
        Button::Draw(resume);

        if (menu.isSelected)
            RED
        else
            slSetForeColor(255, 0, 0, 0.65f);
        Button::Draw(menu);
    }
}