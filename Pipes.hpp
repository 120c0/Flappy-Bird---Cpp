#ifndef PIPES
#define PIPES

#include "Sprite.hpp"
#include <vector>

#define VEL -5.f

class Pipes : public sf::Drawable, public sf::Transformable
{
private:
    std::vector<Sprite*> pipes;
    sf::RenderWindow *window;
    float mm;
    float dist;
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
public:
    Pipes(float, sf::RenderWindow &window, float = 50.f);
    void init_pipes();
    std::vector<Sprite*>& getPipesSprite();
    void update();
};

#endif