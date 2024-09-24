#include "Scene_Pause.h"
#include "Constants.h"

namespace Bton = Button;
using namespace Bton;
using namespace Constants;

namespace Pause
{
    Bton::Button resume;
    Bton::Button goMenu;

    void Init()
    {
        const float width = 250;
        float spaceBetween = GetSpaceBetween(width, 2);

        int resumeX = spaceBetween + (width / 2);
        int goMenuX = resumeX + width + spaceBetween;
        resume = Create("Resume", resumeX, screenHeight / 2, width, 60);
        goMenu = Create("Menu", goMenuX, screenHeight / 2, width, 60);
    }


    void Draw()
    {
        Bton::Draw(resume);
        Bton::Draw(goMenu);
    }
}