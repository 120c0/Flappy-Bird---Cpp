#ifndef GAME
#define GAME

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "GameBird.hpp"
#include "Sprite.hpp"
#include "Pipes.hpp"

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 600

#define JUMP_FORCE -12
#define FALLING_FORCE 1.5f

#define BACKGROUND_VEL -4.f
#define TIME_TUBE 2

class Game final : public GameBird
{
private:
    sf::RenderWindow *window;
    sf::Event event;
    sf::VideoMode videMode;
    bool lose = false, jumped = false;
    Sprite *bird;
    std::vector<Sprite*> background;
    std::vector<Sprite*> ground;
    std::vector<Pipes*> pipes;
    sf::SoundBuffer flap_buffer;

    sf::Clock clock_tube;
    sf::Sound flap;

    sf::Font font_score;
    sf::Text text_score;
    int score = 0;
    sf::Clock timeg;
public:

    Game();
    virtual ~Game();

    void init_window();
    void init_variables();
    void init_bird();
    void init_background();
    void init_ground();
    void init_tube();
    void init_sounds();
    void init_font();

    void update();
    void render();
    void events();

    const bool isOpen() const;

    //========Bird Function=========
    void bird_update();
    void deg_bird_update();

    //========Background============
    void background_update();
    void ground_update();

    //========Pipes Update===========
    void update_pipes();
};

#endif