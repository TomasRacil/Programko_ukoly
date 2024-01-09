// functions.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
//#include "/Users/denis-macbook/Desktop/Programko/Cpp_Flappy/Global_variables/globals.h"
#include "/Users/denis-macbook/Desktop/Programko/Cpp_Flappy/classes/Player.h"
#include "vector"
#include "/Users/denis-macbook/Desktop/Programko/Cpp_Flappy/classes/Obstacle.h"

using namespace sf;
using namespace std;

// Window
// Variables
extern int difficulty,arrow_count,enter_count;

// Textures
extern Texture* bgTexture;
extern Texture* cometTexture;
extern Texture* earthTexture;
extern Texture* jupiterTexture;
extern Texture* saturnTexture;
extern Texture* menuBgTexture;
extern Texture* buttonTexture;
extern Texture* arrowTexture;
extern Texture* mainTextTexture;
extern Texture* startPlatfromTexture;

// Fonts
extern Font test_font;

//Objects
extern Player* flappy;
extern vector<Obstacle*> obstacles;

void setup();
void destroy();
void update();
void handleEvent(Event& event);
void draw_bg(float bg_scroll);
void drawButtons(bool main, bool tutorial);
void drawArrows(int arrow_count, bool main_menu);
void drawMenuBg();
void drawMainButton(int x, int y);
void text(string text, float x, float y, Font font, Color text_color, int char_size);