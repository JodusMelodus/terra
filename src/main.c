#include "game.h"
#include "utils.h"

int main()
{
    Game *game = CreateGame();
    GenerateWorld(game, 12345);
    RunGame(game);
    FinishGame(game);
    return 0;
}