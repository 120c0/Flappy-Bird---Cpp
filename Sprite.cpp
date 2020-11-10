#include "Sprite.hpp"

Sprite::Sprite(float x, float y, float width, float height, const char *filename)
{
    if( !this->texture.loadFromFile(filename) )
        std::cout << "Error file: Sprite/" << filename << std::endl;
    
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(x, y);
    this->sprite.setScale(width, height);  
}

Sprite::~Sprite()
{

}

void Sprite::setPosition(sf::Vector2f position)
{
    this->sprite.setPosition(position);
}

sf::Vector2f Sprite::getPosition()
{
    return this->sprite.getPosition();
}


sf::Vector2f Sprite::getScale()
{
    return this->sprite.getScale();
}

void Sprite::setScale(sf::Vector2f scale)
{
    this->sprite.setScale(scale);
}


sf::Vector2f Sprite::getSize()
{
    return sf::Vector2f(this->getScale().x * this->sprite.getLocalBounds().width,
                        this->getScale().y * this->sprite.getLocalBounds().height);
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    target.draw(this->sprite, states);
}

void Sprite::move(sf::Vector2f to)
{
    this->sprite.move(to);
}

sf::Sprite & Sprite::getSprite()
{
    return this->sprite;
}