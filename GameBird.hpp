#ifndef GAMEBIRD
#define GAMEBIRD

#include <iostream>
#include <SFML/Graphics.hpp>

class GameBird
{
public:
    sf::Vector2f acc = sf::Vector2f(0.f,0.f);
    float angle = 0.f;
};

#endif