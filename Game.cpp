#include "Game.hpp"

Game::Game()
{
    this->init_variables();
}

Game::~Game()
{
    delete this->window;
}

//===============Init====================

void Game::init_variables()
{
    this->init_window();
    this->init_bird();
    this->init_background();
    this->init_ground();
    this->init_tube();
    this->init_font();
}
void Game::init_window()
{
    this->videMode.width = WINDOW_WIDTH;
    this->videMode.height = WINDOW_HEIGHT;
    this->window = new sf::RenderWindow(this->videMode, "Flappy Bird - C++");
    this->window->setPosition(sf::Vector2i(500, 100));
}
void Game::init_font()
{
    this->font_score.loadFromFile("Font/Flappy-Bird.ttf");

    this->text_score.setPosition(this->window->getSize().x / 2 - (this->text_score.getGlobalBounds().width * this->text_score.getScale().x)/2,20.f);
    this->text_score.setCharacterSize(120);
    this->text_score.setFont(this->font_score);
    
    
}
void Game::init_bird()
{
    this->bird = new Sprite(50.f, 100.f, 0.08f, 0.08f, "Sprite/bird.png");

    this->bird->getSprite().setOrigin(sf::Vector2f(this->bird->getSize().x / 2, this->bird->getSize().y / 2));
    this->angle = -45.f;
}
void Game::init_background()
{
    std::srand(time(NULL));
    const char* filename;
    if(std::rand()%2 == 0)
        filename = "Sprite/bg.png";
    else
        filename = "Sprite/bg_night.png";
    
    this->background.push_back(new Sprite(0,0,1.f,1.f, filename));
    this->background.push_back(new Sprite(0,0,1.f,1.f, filename));
    
    this->background[1]->setPosition(sf::Vector2f(this->background[0]->getSize().x, 0));
}

void Game::init_ground()
{
    for(int i = 0; i < 2; i++)
        this->ground.push_back(new Sprite(0,this->videMode.height - 100.f,1.5f,1.5f, "Sprite/ground.png"));
    this->ground[1]->setPosition(sf::Vector2f(this->ground[0]->getSize().x,this->videMode.height - 100.f));
}

void Game::init_sounds()
{
    this->flap_buffer.loadFromFile("Sounds/sfx_wing.wav");
    this->flap.setBuffer(this->flap_buffer);
}

void Game::init_tube()
{
    
}

//=======================================

//==========Game Logic===================

void Game::update()
{
    this->events();
    if(!lose)
    {
        this->bird_update();
        this->background_update();
        this->ground_update();
        if(!this->pipes.empty())
            for(auto &it : this->pipes)
                it->update();
        if(this->clock_tube.getElapsedTime().asSeconds() > TIME_TUBE)
        {
            this->pipes.push_back(new Pipes(150.f, *this->window));
            this->clock_tube.restart();        
        }
        this->update_pipes();
    }
}

void Game::render()
{
    this->window->clear();

    for(auto it : this->background)
        this->window->draw(*it);

    if(!this->pipes.empty())
        for(auto it : this->pipes)
            this->window->draw(*it);


    for(auto it : this->ground)
        this->window->draw(*it);

    this->window->draw(*this->bird);
    
    

    this->text_score.setString(std::to_string(this->score));
    this->text_score.setPosition(this->window->getSize().x / 2 - (this->text_score.getGlobalBounds().width * this->text_score.getScale().x)/2,20.f);
    this->window->draw(this->text_score);

    this->window->display();
    this->window->setFramerateLimit(30);
}

void Game::events()
{
    while(this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::MouseButtonPressed:
                this->flap.play();
                this->jumped = true;
                this->acc.y = JUMP_FORCE;
                if(this->lose)
                {
                    this->background.clear();
                    this->ground.clear();

                    this->init_bird();
                    this->init_ground();
                    this->init_background();
                    
                    lose = false;

                    this->pipes.clear();
                    this->score = 0;
                }
            default:
                break;
        }
    }
}

//==============Bird Logic===============

void Game::bird_update()
{
    this->acc.y += FALLING_FORCE;
    this->bird->move(acc);
    this->deg_bird_update();
    this->bird->getSprite().setRotation(this->angle);

    for(auto it : this->ground)
        if(this->bird->getSprite().getGlobalBounds().intersects(it->getSprite().getGlobalBounds()))
            this->lose = true;

    for(auto it : this->pipes)
        for(auto pipe : it->getPipesSprite())
        {
            sf::Vector2f
                p = pipe->getPosition(),
                b = this->bird->getPosition();
            if(b.x + this->bird->getSize().x > p.x && b.x < p.x + pipe->getSize().x) {
                if(this->timeg.getElapsedTime().asSeconds() >= 2)
                {
                    this->score++;
                    this->timeg.restart();
                }
            }
        }


}

void Game::deg_bird_update()
{
    if(this->jumped)
    {
        this->angle -= 25.f;
        if(this->angle < -45.f) this->angle = -45.f;
    }
    if(this->acc.y > 0)
    {
        jumped = false;
        this->angle += 6.f;
    }
    if(this->angle >= 80.f)
        this->angle = 80.f;

    
}

//=======================================

//==============Backgroudn Logic=========

void Game::background_update()
{
    for(auto &it : this->background)
    {
        it->move(sf::Vector2f(BACKGROUND_VEL + 3.f, 0));
        if(it->getPosition().x < -it->getSize().x)
            it->setPosition(sf::Vector2f(it->getSize().x-10, 0));
    }
}
void Game::ground_update()
{
    for(auto &it : this->ground)
    {
        it->move(sf::Vector2f(BACKGROUND_VEL, 0));
        if(it->getPosition().x < -it->getSize().x)
            it->setPosition(sf::Vector2f(it->getSize().x-10, it->getPosition().y));
    }
}

void Game::update_pipes()
{
    for(auto i : this->pipes)
        for(auto it : i->getPipesSprite())
            if(it->live)
            {
                if( this->bird->getSprite().getGlobalBounds().intersects(it->getSprite().getGlobalBounds()) )
                    this->lose = true;

            }
}

//=======================================

//=============Tube Logic================




//=======================================

//=============Getting Fuction===========

const bool Game::isOpen() const
{
    return this->window->isOpen();
}
