#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
//#include "/Users/denis-macbook/Desktop/Programko/Cpp_Flappy/Global_variables/globals.h"

using namespace sf;
extern Player* flappy;
class Obstacle
{
private:
    Texture* kryptTexture;
    float dy;
    float dx;
    float x,y;
    float vel_y;
    float scroll;
    int height_bottom;
    int height_top;
    bool passed;
    bool move;
    int move_counter;
    int direction;

public:
    Obstacle(int x, int height, bool mv);
    Sprite getSprite_bot() const;
    Sprite getSprite_top() const;
    int getX();
    bool getPassed();
    bool isOffScreen() const;
    void setPassed(bool passed);
    void update();
    void draw() const;
};
