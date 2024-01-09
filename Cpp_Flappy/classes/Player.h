#pragma once

#include <SFML/Graphics.hpp>
//#include "/Users/denis-macbook/Desktop/Programko/Cpp_Flappy/Global_variables/globals.h"

using namespace sf;

extern RenderWindow* window;
class Player
{
private:
    Texture* flappyTexture;
    float dy;
    float dx;
    float x,y;
    float vel_y;
    float scroll;
    bool moving;
    bool start_moving;
    bool grav;
    int difficulty;
public:
    Player(int dif);
    float getScroll();
    Sprite getSprite();
    float getX();
    float getY();
    float getMoving();
    void setGrav(bool cond);
    void setStartMoving(bool cond);
    void setMoving(bool cond);
    void move();
    void jump();
    void draw();
    void update();
    ~Player();
};
