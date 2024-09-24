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
        Draw(goMenu);
    }
}