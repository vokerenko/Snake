#include "stdafx.h"
#include "Game.h"

int main()
{
    Game game;
    while (game.isRunning())
    {
        game.update();
        game.render();
    }

    return EXIT_SUCCESS;
}
