#include "game.h"

int main()
{
    Game *game = CreateGame();
    RunGame(game);
    FinishGame(game);
    return 0;
}