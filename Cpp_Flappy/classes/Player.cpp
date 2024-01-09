#include "Player.h"

Player::Player(int dif)
{
    flappyTexture = new Texture();
    flappyTexture->loadFromFile("assets/superman.png");
    dy=0;
    dx=0;
    x=50;
    y=400;
    scroll=0;
    vel_y=0;
    moving = true;
    start_moving = false;
    grav = false;
    this->difficulty = dif;
}

float Player::getScroll()
{
    return scroll;
}

Sprite Player::getSprite()
{
    Sprite flappySprite(*flappyTexture);
    flappySprite.setScale(100/flappySprite.getLocalBounds().width,60/flappySprite.getLocalBounds().height);
    flappySprite.setPosition(x, y);
    return flappySprite;
}

float Player::getX()
{
    return x;
}

float Player::getY()
{
    return y;
}

float Player::getMoving()
{
    return moving;
}

void Player::setGrav(bool cond)
{
    this->grav = cond;
}

void Player::setStartMoving(bool cond)
{
    this->start_moving = cond;
}

void Player::setMoving(bool cond)
{
    this->moving = cond;
}

void Player::move()
{
    dx=0;
    dy=0;

    if (start_moving == true && moving == true && difficulty==0)
        dx+=4;
    else if (start_moving == true && moving == true && difficulty==1)
        dx+=6;
    else if (start_moving == true && moving == true && difficulty==2)
        dx+=10;
    else if (start_moving == true && moving == true && difficulty==3)
        dx+=2;
    
    if (x>=400)
        scroll= -dx;
        x+=dx+scroll;

    if (grav == true)
    {
        vel_y+=1;
        dy+=vel_y;
        y+=dy;
    }
}

void Player::jump()
{
    if (moving==true)
    {
        vel_y=-17;
    }
}

void Player::draw()
{
    Sprite flappySprite(*flappyTexture);
    flappySprite.setScale(0.25f,0.2f);
    flappySprite.setPosition(x,y);

    window->draw(flappySprite);
}

void Player::update()
{
    move();
}

Player::~Player()
{
    delete flappyTexture;
}