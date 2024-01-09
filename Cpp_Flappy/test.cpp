#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include "Collision.h"
#include "classes/Obstacle.h"
#include "classes/Player.h"
//#include "Global_variables/globals.h"
#include "functions/functions.h"
using namespace std;
using namespace sf;


//g++ main.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main
//g++ -std=c++17 Collision.cpp main.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main
//g++ -std=c++17 Collision.cpp /Users/denis-macbook/Desktop/Programko/Cpp_Flappy/functions/functions.cpp /Users/denis-macbook/Desktop/Programko/Cpp_Flappy/classes/Player.cpp /Users/denis-macbook/Desktop/Programko/Cpp_Flappy/classes/Obstacle.cpp test.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main
//g++ -std=c++17 Collision.cpp Global_variables/globals.cpp functions/functions.cpp classes/Player.cpp classes/Obstacle.cpp test.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main
//g++ -std=c++17 Collision.cpp functions/functions.cpp classes/Player.cpp classes/Obstacle.cpp main.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main

//Music

RenderWindow* window;

// Variables
const int max_obstacles = 100;
bool game_over = false;
bool game_menu = true;
bool dif = false;
float bg_scroll = 0.f;
int end_scroll = 0;
int arrow_count = 0;
int enter_count = 0;
int difficulty = 0;
int s_count = 0;
int o_count = 0;
int score = 0;
int high_score_easy = 0;
int high_score_medium = 0;
int high_score_hard = 0;

// Textures
Texture* bgTexture;
Texture* cometTexture;
Texture* earthTexture;
Texture* jupiterTexture;
Texture* saturnTexture;
Texture* menuBgTexture;
Texture* buttonTexture;
Texture* arrowTexture;
Texture* mainTextTexture;
Texture* startPlatfromTexture;

// Fonts
Font test_font;

Player* flappy;
vector<Obstacle*> obstacles;


int main()
{
    srand (time(NULL));
    // File
    ifstream rfile;
    ofstream wfile;
    setup();
    Obstacle* temp_obstacle = new Obstacle(800, 350,false);
    obstacles.push_back(temp_obstacle); 
    game_over=false;
    game_menu=true;

    //Score
    rfile.open("High_score_easy.txt");
    if (rfile.is_open())
    {
        string line;
        getline(rfile, line);
        high_score_easy = stoi(line);
        rfile.close();
    }

    rfile.open("High_score_medium.txt");
    if (rfile.is_open())
    {
        string line;
        getline(rfile, line);
        high_score_medium = stoi(line);
        rfile.close();
    }

    rfile.open("High_score_hard.txt");
    if (rfile.is_open())
    {
        string line;
        getline(rfile, line);
        high_score_hard = stoi(line);
        rfile.close();
    }

    
    
    //Game loop
    while (window->isOpen())
    {
        Event event;

        while (window->pollEvent(event))
        {
            handleEvent(event);
        }

        Obstacle* temp_obstacle = nullptr;
        if (o_count==0)
        {
            temp_obstacle = new Obstacle(800, 350,false);
            obstacles.push_back(temp_obstacle);
            o_count=1;
        }
        // Generování nových překážek, pokud je jich méně než max_obstacles
        while (obstacles.size() < max_obstacles)
        {
            if (difficulty==0 || difficulty==3)
            {
                int o_height = rand() % 450 + 150;
                temp_obstacle = new Obstacle(temp_obstacle->getX() + 500, o_height,false);
            }

            if (difficulty==1)
            {
                bool o_move;
                int o_height = rand() % 450 + 150;
                int o_temp = rand() % 2;
                if (o_temp ==1)
                    o_move=true;
                else
                    o_move=false;
                temp_obstacle = new Obstacle(temp_obstacle->getX() + 450, o_height,o_move);
            }
            if (difficulty==2)
            {
                bool o_move;
                int o_height = rand() % 500 + 100;
                int o_temp = rand() % 2;
                if (o_temp ==1)
                    o_move=true;
                else
                    o_move=false;
                temp_obstacle = new Obstacle(temp_obstacle->getX() + 400, o_height,o_move);
            }
            obstacles.push_back(temp_obstacle);
        }
        

        

        
        //Collision check
        for (auto& obstacle : obstacles)
        {
                if (Collision::PixelPerfectTest(flappy->getSprite(), obstacle->getSprite_bot()) || Collision::PixelPerfectTest(flappy->getSprite(), obstacle->getSprite_top()))
                {
                    flappy->setMoving(false);
                }
        }

        if (flappy->getY()>850)
        {
            flappy->setGrav(false);
            flappy->setMoving(false);
            game_over=true;
        }

        /* for (auto it = obstacles.begin(); it != obstacles.end(); )
        {
            Obstacle* obstacle = *it;

            if (obstacle->isOffScreen()) 
            {
                delete obstacle;
                it = obstacles.erase(it);
            } 
            else 
            {
                ++it;
            }
        } */
        update();
        
               
        if (game_menu)
        {
            Sprite menuBgSprite (*menuBgTexture);
            menuBgSprite.setScale(1200/menuBgSprite.getLocalBounds().width,(900/menuBgSprite.getLocalBounds().height));
            if (!dif)
            {
                
                window->draw(menuBgSprite);
                drawButtons(true, false);
                text("Main Menu",500,150,test_font,Color::White,36);
                text("Tutorial", 530,300,test_font,Color::White,36);
                text("Start game", 500,400,test_font,Color::White,36);
                text("Quit game", 505,500,test_font,Color::White,36);

                if (arrow_count == 0)
                {
                    drawArrows(arrow_count, true);
                    if (enter_count == 1)
                    {
                        //music.play();
                        s_count = 0;
                        game_over = false;
                        game_menu = false;
                        enter_count = 0;
                        arrow_count = 0;
                        difficulty = 3;
                        flappy = new Player(difficulty);
                    }
                }
            }

            if (arrow_count == 1 || dif)
            {
                if (!dif)
                {
                    drawArrows(arrow_count, true);
                }
                if (enter_count == 1 || dif)
                {
                    window->draw(menuBgSprite);
                    drawButtons(true, false);
                    text("Choose your difficulty",470,160,test_font,Color::White,24);
                    text("Easy", 550,300,test_font,Color::White,36);
                    text("Medium", 520,400,test_font,Color::White,36);
                    text("Hard", 550,500,test_font,Color::White,36);
                    if (!dif)
                    {
                        arrow_count = 0;
                        enter_count=0;
                    }
                    dif=true;
                    if (arrow_count==0)
                    {
                        drawArrows(arrow_count, true);
                        if (enter_count == 1)
                        {
                            //music.play();
                            game_over = false;
                            game_menu = false;
                            enter_count = 0;
                            arrow_count = 0;
                            difficulty = 0;
                            flappy = new Player(difficulty);
                            dif = false;
                        }
                    }
                    if (arrow_count == 1)
                    {
                        drawArrows(arrow_count, true);
                        if (enter_count == 1)
                        {
                            //music.play();
                            game_over = false;
                            game_menu = false;
                            enter_count = 0;
                            arrow_count = 0;
                            difficulty = 1;
                            flappy = new Player(difficulty);
                            dif = false;
                        }
                    }
                    if (arrow_count == 2)
                    {
                        drawArrows(arrow_count, true);
                        if (enter_count == 1)
                        {
                            //music.play();
                            game_over = false;
                            game_menu = false;
                            enter_count = 0;
                            arrow_count = 0;
                            difficulty = 2;
                            flappy = new Player(difficulty);
                            dif = false;
                        }
                    }
                }
            }

            if (!dif)
            {
                if (arrow_count == 2)
                {
                    drawArrows(arrow_count, true);
                    if (enter_count == 1)
                    {
                        enter_count = 0;
                        window->close();
                    }
                 }
            }
        }

        else
        { 
            if(game_over==false)
            {    
                //Clearig old screen
                window->clear();

                //Updating bg_scroll based on scroll 
                bg_scroll += flappy->getScroll();
                if (-bg_scroll >= 2400.f)
                {
                    bg_scroll = 0.f;
                    //Condition, so we draw starting platfrom only once
                    s_count = 1;
                }

                for (Obstacle* obstacle : obstacles)
                {
                    if(flappy->getX()>(obstacle->getX()+50) && !obstacle->getPassed())
                    {
                        score+=1;  
                        obstacle->setPassed(true);
                    }
                }

                draw_bg(bg_scroll);
                Sprite startPlatfromSprite(*startPlatfromTexture);
                if (s_count==0)
                {
                    startPlatfromSprite.setScale(1.f,0.7f);
                    startPlatfromSprite.setPosition(50+bg_scroll,512.f);
                    window->draw(startPlatfromSprite);
                }

                for (const auto& obstacle : obstacles)
                {
                    obstacle->draw();
                }

                if (difficulty !=3)
                {
                    Sprite mainTextSprite (*mainTextTexture);
                    mainTextSprite.setScale(200/mainTextSprite.getLocalBounds().width,(50/mainTextSprite.getLocalBounds().height));
                    mainTextSprite.setPosition(0,20);
                    window->draw(mainTextSprite);
                    text("SCORE: "+to_string(score), 30,25,test_font,Color::White,30);
                }
                else if (difficulty == 3 and s_count==0)
                {
                    drawMainButton(20+bg_scroll,350);
                    drawMainButton(420+bg_scroll,200);
                    text("Press SPACE to jump",50+bg_scroll, 350, test_font, Color::White,36);
                    text("Dodge the cryptonite -->",440+bg_scroll,200,test_font,Color::White,36);
                }
                
                flappy->draw();
            }

            else if(game_over==true)
            {
                if (difficulty == 0)
                {
                    if (score > high_score_easy)
                    {
                        high_score_easy = score;
                        wfile.open("High_score_easy.txt");
                        if (wfile.is_open())
                        {
                            wfile << high_score_easy;
                            wfile.close();
                        }
                    }
                }

                if (difficulty == 1)
                {
                    if (score > high_score_medium)
                    {
                        high_score_medium = score;
                        wfile.open("High_score_medium.txt");
                        if (wfile.is_open())
                        {
                            wfile << high_score_medium;
                            wfile.close();
                        }
                    }
                }

                if (difficulty == 2)
                {
                    if (score > high_score_hard)
                    {
                        high_score_hard = score;
                        wfile.open("High_score_hard.txt");
                        if (wfile.is_open())
                        {
                            wfile << high_score_hard;
                            wfile.close();
                        }
                    }
                }
            
                if (end_scroll<600)
                {    
                    end_scroll+=8;

                    //From leftUp corner to middle
                    Sprite menuBgSpriteLU(*menuBgTexture, IntRect(0,0,end_scroll,end_scroll*3/4));
                    menuBgSpriteLU.setScale(end_scroll/menuBgSpriteLU.getLocalBounds().width,(end_scroll*3/4)/menuBgSpriteLU.getLocalBounds().height);
                    window->draw(menuBgSpriteLU);

                    //From rightUp corner to middle
                    Sprite menuBgSpriteRU(*menuBgTexture, IntRect(1200 - end_scroll, 0, end_scroll, end_scroll*3/4));
                    menuBgSpriteRU.setScale(end_scroll/menuBgSpriteRU.getLocalBounds().width,(end_scroll*3/4)/menuBgSpriteRU.getLocalBounds().height);
                    menuBgSpriteRU.setPosition(1200 - menuBgSpriteRU.getGlobalBounds().width, 0);
                    window->draw(menuBgSpriteRU);

                    //From leftDown corner to middle
                    Sprite menuBgSpriteLD(*menuBgTexture, IntRect(0, 900 - end_scroll*3/4, end_scroll, end_scroll*3/4));
                    menuBgSpriteLD.setScale(end_scroll/menuBgSpriteLD.getLocalBounds().width,(end_scroll*3/4)/menuBgSpriteLD.getLocalBounds().height);
                    menuBgSpriteLD.setPosition(0, 900 - menuBgSpriteLD.getGlobalBounds().height);
                    window->draw(menuBgSpriteLD);

                    //From rightDown corner to middle
                    Sprite menuBgSpriteRD(*menuBgTexture, IntRect(1200 - end_scroll, 900 - end_scroll*3/4, end_scroll, end_scroll*3/4));
                    menuBgSpriteRD.setScale(end_scroll/menuBgSpriteRD.getLocalBounds().width, (end_scroll*3/4)/menuBgSpriteRD.getLocalBounds().height);
                    menuBgSpriteRD.setPosition(1200 - menuBgSpriteRD.getGlobalBounds().width, 900 - menuBgSpriteRD.getGlobalBounds().height);
                    window->draw(menuBgSpriteRD);
                }
                else
                {
                    //Clearig old screen
                    window->clear();

                    //Menu
                    Sprite menuBgSprite(*menuBgTexture);
                    menuBgSprite.setScale(1200/menuBgSprite.getLocalBounds().width,900/menuBgSprite.getLocalBounds().height);
                    window->draw(menuBgSprite);

                    if (difficulty != 3)
                    {
                        drawButtons(false, false);
                        if (difficulty == 0)
                        {
                            text("SCORE: " + std::to_string(score), 510, 300, test_font, Color::White,36);
                            if (score < high_score_easy)
                            {
                                text("HIGH SCORE: " + std::to_string(high_score_easy), 495, 410, test_font, Color::White,30);
                            }
                            if (score >= high_score_easy)
                            {
                                text("NEW HIGH SCORE: " + std::to_string(high_score_easy), 465, 410, test_font, Color::White,24);
                            }
                        }
                        if (difficulty == 1)
                        {
                            text("SCORE: " + std::to_string(score), 510, 300, test_font, Color::White,36);
                            if (score < high_score_medium)
                            {
                                text("HIGH SCORE: " + std::to_string(high_score_medium), 495, 410, test_font, Color::White,24);
                            }
                            if (score >= high_score_medium)
                            {
                                text("NEW HIGH SCORE: " + std::to_string(high_score_medium), 465, 410, test_font, Color::White,24);
                            }
                        }
                        if (difficulty == 2)
                        {
                            text("SCORE: " + std::to_string(score), 510, 300, test_font, Color::White,36);
                            if (score < high_score_hard)
                            {
                                text("HIGH SCORE: " + std::to_string(high_score_hard), 495, 410, test_font, Color::White,30);
                            }
                            if (score >= high_score_hard)
                            {
                                text("NEW HIGH SCORE: " + std::to_string(high_score_hard), 465, 410, test_font, Color::White,24);
                            }
                        }
                    }
                    else
                    {
                        drawButtons(false, true);
                    }


                    //arrows
                    
                    text("Game Over!!",480,150,test_font,Color::White, 36);
                    text("Play again", 505,500,test_font,Color::White,36);
                    text("Main menu", 500,600,test_font,Color::White,36);
                    text("Quit game", 505,700,test_font,Color::White,36);

                    if (arrow_count==0)
                    {
                        drawArrows(arrow_count,false);
                        if (enter_count==1)
                        {
                            enter_count=0;
                            obstacles.clear();
                            Obstacle* temp_obstacle = new Obstacle(800, 350,false);
                            obstacles.push_back(temp_obstacle);
                            // Generování nových překážek, pokud je jich méně než max_obstacles
                            while (obstacles.size() < max_obstacles)
                            {
                                if (difficulty==0 || difficulty==3)
                                {
                                    int o_height = rand() % 450 + 150;
                                    temp_obstacle = new Obstacle(temp_obstacle->getX() + 500, o_height,false);
                                }

                                if (difficulty==1)
                                {
                                    bool o_move;
                                    int o_height = rand() % 450 + 150;
                                    int o_temp = rand() % 2;
                                    if (o_temp ==1)
                                        o_move=true;
                                    else
                                        o_move=false;
                                    temp_obstacle = new Obstacle(temp_obstacle->getX() + 450, o_height,o_move);
                                }
                                if (difficulty==2)
                                {
                                    bool o_move;
                                    int o_height = rand() % 500 + 100;
                                    int o_temp = rand() % 2;
                                    if (o_temp ==1)
                                        o_move=true;
                                    else
                                        o_move=false;
                                    temp_obstacle = new Obstacle(temp_obstacle->getX() + 400, o_height,o_move);
                                }
                                obstacles.push_back(temp_obstacle);
                            }
                            flappy = new Player(difficulty);
                            arrow_count=0;
                            bg_scroll=0;
                            s_count=0;
                            end_scroll=0;
                            o_count=0;
                            score=0;
                            game_over=false;
                        }
                    }

                    if (arrow_count == 1)
                    {
                        drawArrows(arrow_count, false);
                        if (enter_count == 1)
                        {
                            enter_count = 0;
                            game_menu = true;
                            obstacles.clear();
                            Obstacle* temp_obstacle = new Obstacle(800, 350,false);
                            obstacles.push_back(temp_obstacle);
                            // Generování nových překážek, pokud je jich méně než max_obstacles
                            while (obstacles.size() < max_obstacles)
                            {
                                if (difficulty==0 || difficulty==3)
                                {
                                    int o_height = rand() % 450 + 150;
                                    temp_obstacle = new Obstacle(temp_obstacle->getX() + 500, o_height,false);
                                }

                                if (difficulty==1)
                                {
                                    bool o_move;
                                    int o_height = rand() % 450 + 150;
                                    int o_temp = rand() % 1 + 0;
                                    if (o_temp ==1)
                                        o_move=true;
                                    else
                                        o_move=false;
                                    temp_obstacle = new Obstacle(temp_obstacle->getX() + 450, o_height,o_move);
                                }
                                if (difficulty==2)
                                {
                                    bool o_move;
                                    int o_height = rand() % 500 + 100;
                                    int o_temp = rand() % 1 + 0;
                                    if (o_temp ==1)
                                        o_move=true;
                                    else
                                        o_move=false;
                                    temp_obstacle = new Obstacle(temp_obstacle->getX() + 500, o_height,o_move);
                                }
                                obstacles.push_back(temp_obstacle);
                            }
                            game_over = true;
                            arrow_count = 0;
                            end_scroll = 0;
                            score = 0;
                            bg_scroll = 0;
                            s_count=0;
                            o_count=0;
                        }
                    }

                    if (arrow_count == 2)
                    {
                        drawArrows(arrow_count, false);
                        if (enter_count == 1)
                        {
                            enter_count = 0;
                            window->close();
                        }
                    }

                }
            }
        }

        window->display();
        
    }

    destroy();

    return 0;
}