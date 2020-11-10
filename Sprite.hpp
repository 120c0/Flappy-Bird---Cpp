#ifndef SPRITE
#define SPRITE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Sprite : public sf::Drawable, public sf::Transformable
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

public:
    bool live = true;
    Sprite(float, float, float, float, const char*);
    virtual ~Sprite();
    
    virtual void setPosition(sf::Vector2f);
    virtual sf::Vector2f getPosition();

    virtual void setScale(sf::Vector2f);
    virtual sf::Vector2f getScale();

    virtual sf::Vector2f getSize();
    virtual void move(sf::Vector2f);

    virtual sf::Sprite& getSprite();
};

#endif