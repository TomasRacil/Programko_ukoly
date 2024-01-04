#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include <vector>
#include<ctime>
#include <fstream>
#include<string>
#include"Collision.h"
using namespace std;
using namespace sf;


//g++ main.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main
//g++ Collision.cpp main.cpp $(pkg-config --libs --cflags sfml-window sfml-system sfml-graphics) -o main

//Music



//Window
RenderWindow* window;

//Variables
const int max_obstacles = 4;
bool game_over = false;
bool game_menu=true;
bool dif=false;
float bg_scroll = 0.f;
int end_scroll=0;
int arrow_count=0;
int enter_count=0;
int difficulty;
int s_count=0;
int o_count=0;
int score=0;
int high_score_easy,high_score_medium,high_score_hard;

//Textures
Texture* bgTexture;
Texture* cometTexture;
Texture* earthTexture;
Texture* jupiterTexture;
Texture* saturnTexture;
Texture* menuBgTexture;
Texture* buttonTexture;
Texture* arrowTexture;
Texture* mainTextTexture;

//FONTS
Font test_font;

//Score
ifstream rfile;
ofstream wfile;


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
    //Constructor
    Player(int dif)
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

    

    //GETTER
    float getScroll()
    {
        return scroll;
    }

    Sprite getSprite()
    {
        Sprite flappySprite(*flappyTexture);
        flappySprite.setScale(100/flappySprite.getLocalBounds().width,60/flappySprite.getLocalBounds().height);
        flappySprite.setPosition(x, y);
        return flappySprite;
    }

    float getX()
    {
        return x;
    }

    float getY()
    {
        return y;
    }

    float getMoving()
    {
        return moving;
    }

    //SETTER
    bool setGrav(bool cond)
    {
        this->grav = cond;
    }

    bool setStartMoving(bool cond)
    {
        this->start_moving = cond;
    }

    bool setMoving(bool cond)
    {
        this->moving = cond;
    }


    
    //Other functions
    void move()
    {
        //RESET VARIABLES
        dx=0;
        dy=0;

        //Right movement
        if (start_moving == true && moving == true && difficulty==0)
            dx+=4;
        else if (start_moving == true && moving == true && difficulty==1)
            dx+=6;
        else if (start_moving == true && moving == true && difficulty==2)
            dx+=10;
        else if (start_moving == true && moving == true && difficulty==3)
            dx+=2;
        
        
        //Scroll update
        if (x>=400)
            scroll= -dx;
            x+=dx+scroll;

        //Gravity
        if (grav == true)
        {
            vel_y+=1;
            dy+=vel_y;
            y+=dy;
        }
        
    }

    void jump()
    {
        if (moving==true)
        {
            vel_y=-17;
        }
    }

    void draw()
    {
        Sprite flappySprite(*flappyTexture);
        flappySprite.setScale(0.25f,0.2f);
        flappySprite.setPosition(x,y);

        window->draw(flappySprite);
    }

    void update()
    {
        move();
        
        
    }

    ~Player()
    {
        delete flappyTexture;
    }


};
Player* flappy;


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
    Obstacle(int x, int height, bool mv)//int x, int height
    {
        kryptTexture = new Texture();
        kryptTexture->loadFromFile("assets/pixel_kryptonite.png");
        
        //x= (float)(800); //start position
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

    Sprite getSprite_bot() const
    {
        Sprite kryptSprite(*kryptTexture);
        kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,height_bottom/kryptSprite.getLocalBounds().height);
        kryptSprite.setPosition(x,900-height_bottom+40);
        return kryptSprite;
    }

    Sprite getSprite_top() const
    {
        Sprite kryptSprite(*kryptTexture);
        kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,-(height_top/kryptSprite.getLocalBounds().height));
        kryptSprite.setPosition(x,height_top-40);
        return kryptSprite;
    }

    //Getter
    int getX()
    {
        return x;
    }

    bool getPassed()
    {
        return passed;
    }

    //Setter
    bool isOffScreen() const 
    {
        return x+200 < 0;
    }

    bool setPassed(bool passed)
    {
        this->passed = passed;
    }

    void update()
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

    void draw() const
    {
        //Bottom obstacle
        Sprite kryptSprite(*kryptTexture);
        kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,height_bottom/kryptSprite.getLocalBounds().height);
        kryptSprite.setPosition(x,y+900-height_bottom+40);//HEIGHT - height + 40

        window->draw(kryptSprite);

        //Top obstacle
        kryptSprite.setScale(200/kryptSprite.getLocalBounds().width,-(height_top/kryptSprite.getLocalBounds().height));
        kryptSprite.setPosition(x,y+height_top-40);//0 + height - 150 - 40

        window->draw(kryptSprite);

        
    }

};
vector<Obstacle*> obstacles;

//Creating variables to load images into
Texture* startPlatfromTexture;
void setup()
{   
    //Random
    srand((unsigned int) time(nullptr));

    //Screen setup
    window = new RenderWindow(VideoMode(1200,900), "Budget flappy");

    //Fps cap
    window->setFramerateLimit(60);

    //Creating flappy
    flappy = new Player(difficulty);

    //Loading images
    bgTexture = new Texture();
    bgTexture->loadFromFile("assets/game_bg.png");
    startPlatfromTexture = new Texture();
    startPlatfromTexture->loadFromFile("assets/starting_platform.png");
    earthTexture = new Texture();
    earthTexture->loadFromFile("assets/earth.png");
    cometTexture = new Texture();
    cometTexture->loadFromFile("assets/comet.png");
    jupiterTexture = new Texture();
    jupiterTexture->loadFromFile("assets/jupiter.png");
    saturnTexture = new Texture();
    saturnTexture->loadFromFile("assets/saturn.png");
    menuBgTexture = new Texture();
    menuBgTexture->loadFromFile("assets/menu_bg.png");
    buttonTexture = new Texture();
    buttonTexture->loadFromFile("assets/button.png");
    arrowTexture = new Texture();
    arrowTexture->loadFromFile("assets/arrow.png");
    mainTextTexture = new Texture();
    mainTextTexture->loadFromFile("assets/main_text.png");

    //Loading fonts
    test_font.loadFromFile("assets/arialunicode.ttf");
    
    
}

// "Destructor" so we don`t run out of memory
void destroy()
{
    delete window;

    delete flappy;

    delete bgTexture;
    delete startPlatfromTexture;
    delete earthTexture;
    delete cometTexture;
    delete jupiterTexture;
    delete saturnTexture;
    delete buttonTexture;
    delete menuBgTexture;
}

//Function for updating position etc.
void update()
{
    
    flappy->update();
    for(const auto& obstacle : obstacles)
    {
        obstacle->update();
    }
    
    
}

//Function for handeling events, important for Game loop
void handleEvent(Event& event)
{
    if(event.type==Event::Closed)
        window->close();

    if (event.type==Event::KeyPressed)
    {
        if(event.key.scancode == Keyboard::Scan::Space)
        if (flappy->getMoving()==true)
        {
            flappy->jump();
            flappy->setStartMoving(true);
            flappy->setGrav(true);
        }

        if(event.key.scancode == Keyboard::Scan::Down)
        {
            arrow_count+=1;
            if (arrow_count>2)
                arrow_count = 0;
        }

        else if(event.key.scancode == Keyboard::Scan::Up)
        {
            arrow_count-=1;
             if (arrow_count<0)
                arrow_count=2;
        }
        else if(event.key.scancode == Keyboard::Scan::Enter)
        {
            enter_count=1;
        }
    
    }
}






void draw_bg(float bg_scroll)
{
    // Draw the background
    for (int i = 0; i < 3; i++)
    {
        Sprite bgSprite(*bgTexture);
        bgSprite.setScale(1.34f, 1.f);
        bgSprite.setPosition(i * window->getSize().x + bg_scroll, 0);
        window->draw(bgSprite);
    }

    // Draw the comets
    Sprite cometSprite(*cometTexture);
    cometSprite.setScale(1.8f, 1.8f);
    cometSprite.setPosition(-130 - bg_scroll * 0.7, 120 - bg_scroll);
    window->draw(cometSprite);
    cometSprite.setPosition(-50 - bg_scroll * 0.7, -400 - bg_scroll * 0.7);
    window->draw(cometSprite);

    // Draw the planets
    Sprite earthSprite(*earthTexture);
    earthSprite.setScale(3.f, 3.f);
    earthSprite.setPosition(-100 - bg_scroll * 0.7, 100);
    window->draw(earthSprite);

    Sprite jupiterSprite(*jupiterTexture);
    jupiterSprite.setScale(4.5f, 4.5f);
    jupiterSprite.setPosition(-300 - bg_scroll * 0.6, 150);
    window->draw(jupiterSprite);

    Sprite saturnSprite(*saturnTexture);
    saturnSprite.setScale(6.f, 6.f);
    saturnSprite.setPosition(1200 + bg_scroll * 1.2, 600);
    window->draw(saturnSprite);
}

void drawButtons(bool main, bool tutorial)
{
    if(main)
    {
        Sprite mainTextSprite(*mainTextTexture);
        mainTextSprite.setScale(300/mainTextSprite.getLocalBounds().width,50/mainTextSprite.getLocalBounds().height);
        mainTextSprite.setPosition(435,150);
        window->draw(mainTextSprite);
        for(int i=0;i<3;i++)
        {
            Sprite buttonSprite(*buttonTexture);
            buttonSprite.setScale(300/buttonSprite.getLocalBounds().width,50/buttonSprite.getLocalBounds().height);
            buttonSprite.setPosition(435,i*100+300);
            window->draw(buttonSprite);
            
        }
    }
    else
    {
        Sprite mainTextSprite(*mainTextTexture);
        mainTextSprite.setScale(300/mainTextSprite.getLocalBounds().width,50/mainTextSprite.getLocalBounds().height);
        mainTextSprite.setPosition(435,150);
        window->draw(mainTextSprite);
        if(!tutorial)
        {
            for(int i=0;i<2;i++)
            {
                Sprite mainTextSprite(*mainTextTexture);
                mainTextSprite.setScale(300/mainTextSprite.getLocalBounds().width,50/mainTextSprite.getLocalBounds().height);
                mainTextSprite.setPosition(435,i*100+300);
                window->draw(mainTextSprite);
                
            }
        }
        for (int i=0;i<3;i++)
        {
            Sprite buttonSprite(*buttonTexture);
            buttonSprite.setScale(300/buttonSprite.getLocalBounds().width,50/buttonSprite.getLocalBounds().height);
            buttonSprite.setPosition(435,i*100+500);
            window->draw(buttonSprite);
        }

    }
    
}

void drawArrows(int arrow_count, bool main_menu)
{
    if (arrow_count == 0 && main_menu)
    {   
        Sprite arrowSpriteL(*arrowTexture);
        arrowSpriteL.setPosition(350,300);
        window->draw(arrowSpriteL);
        Sprite arrowSpriteR(*arrowTexture);
        arrowSpriteR.setScale(-1.f,1.f);
        arrowSpriteR.setPosition(817,300);
        window->draw(arrowSpriteR);
    }
    else if (arrow_count == 1 && main_menu)
    {
        Sprite arrowSpriteL(*arrowTexture);
        arrowSpriteL.setPosition(350,400);
        window->draw(arrowSpriteL);
        Sprite arrowSpriteR(*arrowTexture);
        arrowSpriteR.setScale(-1.f,1.f);
        arrowSpriteR.setPosition(817,400);
        window->draw(arrowSpriteR);
    }
    else if (arrow_count == 2 && main_menu)
    {
        Sprite arrowSpriteL(*arrowTexture);
        arrowSpriteL.setPosition(350,500);
        window->draw(arrowSpriteL);
        Sprite arrowSpriteR(*arrowTexture);
        arrowSpriteR.setScale(-1.f,1.f);
        arrowSpriteR.setPosition(817,500);
        window->draw(arrowSpriteR);
    }
    if (arrow_count == 0 && !main_menu)
    {   
        Sprite arrowSpriteL(*arrowTexture);
        arrowSpriteL.setPosition(350,500);
        window->draw(arrowSpriteL);
        Sprite arrowSpriteR(*arrowTexture);
        arrowSpriteR.setScale(-1.f,1.f);
        arrowSpriteR.setPosition(817,500);
        window->draw(arrowSpriteR);
    }
    else if (arrow_count == 1 && !main_menu)
    {
        Sprite arrowSpriteL(*arrowTexture);
        arrowSpriteL.setPosition(350,600);
        window->draw(arrowSpriteL);
        Sprite arrowSpriteR(*arrowTexture);
        arrowSpriteR.setScale(-1.f,1.f);
        arrowSpriteR.setPosition(817,600);
        window->draw(arrowSpriteR);
    }
    else if (arrow_count == 2 && !main_menu)
    {
        Sprite arrowSpriteL(*arrowTexture);
        arrowSpriteL.setPosition(350,700);
        window->draw(arrowSpriteL);
        Sprite arrowSpriteR(*arrowTexture);
        arrowSpriteR.setScale(-1.f,1.f);
        arrowSpriteR.setPosition(817,700);
        window->draw(arrowSpriteR);
    }
    
}

void drawMenuBg()
{
    Sprite menuBgSprite (*menuBgTexture);
    menuBgSprite.setScale(1200/menuBgSprite.getLocalBounds().width,(900/menuBgSprite.getLocalBounds().height));
    window->draw(menuBgSprite);
}

void drawMainButton(int x, int y)//Coordinates
{
    Sprite mainTextSprite (*mainTextTexture);
    mainTextSprite.setScale(410/mainTextSprite.getLocalBounds().width,(50/mainTextSprite.getLocalBounds().height));
    mainTextSprite.setPosition(x,y);
    window->draw(mainTextSprite);
}

void text(string text, float x, float y, Font font, Color text_color, int char_size)
{
    Text image;
    image.setFont(test_font);
    image.setString(text);
    image.setFillColor(text_color);
    image.setCharacterSize(char_size);
    image.setPosition(x,y);
    window->draw(image);
}

int main()
{
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

        
        if (o_count==0)
        {
            Obstacle* temp_obstacle = new Obstacle(800, 350,false);
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

        for (auto it = obstacles.begin(); it != obstacles.end(); )
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
        }
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