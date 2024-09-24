#include "Scene_Controls.h"
#include "Constants.h"

using namespace Constants;

namespace Controls
{
    Button::Button goMenu;

    void Init()
    {
        goMenu = Button::Create("Menu", screenWidth / 2, 60, 250, 60);
    }


    void Draw()
    {
        if (goMenu.isSelected)
            RED
        else
            slSetForeColor(255, 0, 0, 0.65f);
        Button::Draw(goMenu);
    }
}