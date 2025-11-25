#include "game.h"
#include "utils.h"

int main()
{
    struct Game *game = CreateGame();
    GenerateWorld(game, 9999999999999999);
    RunGame(game);
    FinishGame(game);
    return 0;
}