#include "Pipes.hpp"

Pipes::Pipes(float dist, sf::RenderWindow &window, float more)
{
    this->mm = more;
    this->window = &window;
    this->dist = dist;
    this->init_pipes();
}

void Pipes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();

    for(auto &it : this->pipes)
        target.draw(*it, states);
}

void Pipes::init_pipes()
{
    sf::Vector2u ws = this->window->getSize();

    int ww = ws.y - 350;
    float y = std::rand()%ww + 80;


    this->pipes.push_back(new Sprite(ws.x + mm, y + this->dist, 1.5f, 1.5f, "Sprite/tube2.png"));
    this->pipes.push_back(new Sprite(ws.x + mm, pipes[0]->getPosition().y - pipes[0]->getSize().y - this->dist, 1.5f, 1.5f, "Sprite/tube1.png"));

}
void Pipes::update()
{
    for(auto &it : pipes)
    {
        it->move(sf::Vector2f(VEL, 0));
        
        if(it->getPosition().x + it->getSize().x < 0)
        {
            it->live = false;
        }    
    }
}
std::vector<Sprite*>& Pipes::getPipesSprite()
{
    return this->pipes;
}