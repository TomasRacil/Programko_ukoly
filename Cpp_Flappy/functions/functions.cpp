// functions.cpp
#include "functions.h"



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

void update()
{
    
    flappy->update();
    for(const auto& obstacle : obstacles)
    {
        obstacle->update();
    }
    
    
}

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