#include "Obstacle.h"


Obstacle::Obstacle(int x, int height, bool mv)
{
    kryptTexture = new Texture();
    kryptTexture->loadFromFile("assets/pixel_kryptonite.png");
    this->x = x;
    y=500;
    height_bottom=height;
    height_top=900-height_bottom-200;
    passed = false;
    move = mv;
    move_counter = rand()% 25+0;
    direction = (rand()%2==0) ? -1 : 1;
    y=0;
}

Sprite Obstacle::getSprite_bot() const
{
    Sprite kryptSprite(*kryptTexture);
    kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,height_bottom/kryptSprite.getLocalBounds().height);
    kryptSprite.setPosition(x,900-height_bottom+40);
    return kryptSprite;
}

Sprite Obstacle::getSprite_top() const
{
    Sprite kryptSprite(*kryptTexture);
    kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,-(height_top/kryptSprite.getLocalBounds().height));
    kryptSprite.setPosition(x,height_top-40);
    return kryptSprite;
}

int Obstacle::getX()
{
    return x;
}

bool Obstacle::getPassed()
{
    return passed;
}

bool Obstacle::isOffScreen() const 
{
    return x+200 < 0;
}

void Obstacle::setPassed(bool passed)
{
    this->passed = passed;
}

void Obstacle::update()
{
    x+=flappy->getScroll();
    if (move) 
    {
        y += direction;
        move_counter++;
        if (move_counter >= 50) 
        {
            direction *= -1; // Change direction
            move_counter = 0;
        }
    }
}

void Obstacle::draw() const
{
    
    Sprite kryptSprite(*kryptTexture);
    kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,height_bottom/kryptSprite.getLocalBounds().height);
    kryptSprite.setPosition(x,y+900-height_bottom+40);
    window->draw(kryptSprite);

    kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,-(height_top/kryptSprite.getLocalBounds().height));
    kryptSprite.setPosition(x,y+height_top-40);
    window->draw(kryptSprite);
}