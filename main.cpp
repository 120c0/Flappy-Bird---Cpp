#include "Game.hpp"

int main(int argc, char const *argv[])
{
    std::srand(time(NULL));
    Game game;
    while(game.isOpen())
    {
        game.update();
        game.render();
    }   
    return 0;
}
