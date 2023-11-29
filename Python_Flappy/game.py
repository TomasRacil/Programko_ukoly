
import pygame
import random
import os
from pygame import mixer
from os.path import realpath, dirname, join


mixer.init()
pygame.init()

#screen
WIDTH = 1200
HEIGHT = 900

#barvy
WHITE=(255,255,255)
CYAN=(0, 139, 139)
YELLOW=(255,255,0)
BLACK=(0,0,0)

#fonts
test_font=pygame.font.SysFont("arialunicode", 36)
test_font2=pygame.font.SysFont("arialunicode", 24)
test_font3=pygame.font.SysFont("arialunicode", 30)

#game window
pygame.display.set_caption("Budget Flappy")
screen = pygame.display.set_mode((WIDTH, HEIGHT))

#fps cap
clock = pygame.time.Clock()
FPS=60

#score
if os.path.exists('High_score_easy.txt'):
	with open ("High_score_easy.txt", 'r') as file:
		high_score_easy = int(file.read())
else:
	high_score_easy =0

if os.path.exists('High_score_medium.txt'):
	with open ("High_score_medium.txt", 'r') as file:
		high_score_medium = int(file.read())
else:
	high_score_medium =0

if os.path.exists('High_score_hard.txt'):
	with open ("High_score_hard.txt", 'r') as file:
		high_score_hard = int(file.read())
else:
	high_score_hard =0

#global variables
SCROLL_THRESH = WIDTH/3
GRAVITY = 1
MAX_OBSTACLES = 10
game_over = True
game_menu = True
dif = False
move_speed = 2
jump_height=17
scroll = 0
bg_scroll=0
end_scroll = 0
triangle_y=160
triangle_x1 = 450
triangle = 760
arrow_count = 0
enter_count = 0
score = 0
score_add = 0
difficulty = 0
space_count = 0
s_count = 0


#sprites
flappy_sprite = pygame.image.load(join(dirname(realpath(__file__)), "assets/superman.png")).convert_alpha()
join(dirname(realpath(__file__)), "assets/game_bg.png")
game_bg_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/game_bg.png")), (WIDTH, HEIGHT)).convert_alpha()
menu_bg_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/menu_bg.png")),(WIDTH,HEIGHT)).convert_alpha()
cryptonite_sprite = pygame.image.load(join(dirname(realpath(__file__)), "assets/pixel_kryptonite.png")).convert_alpha()
start_platform_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/starting_platform.png")), (200, 310)).convert_alpha()
button_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/button.png")),(300, 50)).convert_alpha()
arrow_sprite = pygame.image.load(join(dirname(realpath(__file__)), "assets/arrow.png")).convert_alpha()
main_text_sprite = pygame.image.load(join(dirname(realpath(__file__)), "assets/main_text.png")).convert_alpha()
earth_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/earth.png")),(130,130)).convert_alpha()
jupiter_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/jupiter.png")),(200,200)).convert_alpha()
saturn_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/saturn.png")),(250,250)).convert_alpha()
comet_sprite = pygame.transform.scale(pygame.image.load(join(dirname(realpath(__file__)), "assets/comet.png")),(100,100)).convert_alpha()
#music
pygame.mixer.music.load(join(dirname(realpath(__file__)), "assets/bg_music.mp3"))
pygame.mixer.music.set_volume(0.3)
death_fx = pygame.mixer.Sound(join(dirname(realpath(__file__)), "assets/death.wav"))
death_fx.set_volume(0.3)
arrow_fx = pygame.mixer.Sound(join(dirname(realpath(__file__)), "assets/arrow_press.mp3"))
arrow_fx.set_volume(0.3)

#text
def text(text, x, y, font, text_color):
    image = font.render(text, True, text_color)
    screen.blit(image,(x,y))

#bg
def draw_bg(bg_scroll):

    for i in range(3):
        screen.blit(game_bg_sprite, (i*WIDTH+bg_scroll, 0 ))
        
    screen.blit(comet_sprite,(-130-bg_scroll*0.7, 120-bg_scroll))
    screen.blit(comet_sprite,(-50-bg_scroll*0.7, -400-bg_scroll*0.7))
    screen.blit(earth_sprite,(-100-bg_scroll*0.7, 100))
    screen.blit(jupiter_sprite,(-300-bg_scroll*0.6, 150))
    screen.blit(saturn_sprite,(1200+bg_scroll*1.2, 600))
    
    

def key_count(arrow_count):

    key = pygame.key.get_pressed()
    if key[pygame.K_DOWN]:
        arrow_count+=1

    if key[pygame.K_UP]:
        arrow_count-=1

    if arrow_count>2:
        arrow_count = 0

    if arrow_count<0:
        arrow_count=2

    return arrow_count

def return_count(enter_count):
    enter_count = 0
    key = pygame.key.get_pressed()
    if key[pygame.K_RETURN]:
        enter_count = 1
    return enter_count

def jump_count(space_count):
    space_count = 0
    key = pygame.key.get_pressed()
    if key[pygame.K_SPACE]:
        space_count = 1
    return space_count


def draw_arrow(arrow_count, main_menu):
    if arrow_count == 0 and main_menu:
        screen.blit(arrow_sprite,(350,300))
        screen.blit(pygame.transform.flip(arrow_sprite,True,False),(742,300))
            
    if arrow_count == 1 and main_menu:
            screen.blit(arrow_sprite,(350,400))
            screen.blit(pygame.transform.flip(arrow_sprite,True,False),(742,400))
    if arrow_count == 2 and main_menu:
            screen.blit(arrow_sprite,(350,500))
            screen.blit(pygame.transform.flip(arrow_sprite,True,False),(742,500))
    if arrow_count == 0 and not main_menu:
            screen.blit(arrow_sprite,(350,500))
            screen.blit(pygame.transform.flip(arrow_sprite,True,False),(742,500))
    if arrow_count == 1 and not main_menu:
            screen.blit(arrow_sprite,(350,600))
            screen.blit(pygame.transform.flip(arrow_sprite,True,False),(742,600))
    if arrow_count == 2 and not main_menu:
            screen.blit(arrow_sprite,(350,700))
            screen.blit(pygame.transform.flip(arrow_sprite,True,False),(742,700))

def first_obstacles():

    crypto_bottom = Obstacle_bottom(450, 350, False)
    crypto_top = Obstacle_top(450, 350, False)
    obstacle_group_bottom = pygame.sprite.Group()
    obstacle_group_top = pygame.sprite.Group()
    obstacle_group_bottom.add(crypto_bottom)
    obstacle_group_top.add(crypto_top)
    start_group = pygame.sprite.Group()
    start_platform = Start_platform(0)
    start_group.add(start_platform)
    return obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top

def draw_button(main, tutorial):
    if main:
        screen.blit(main_text_sprite,(435,150))
        for i in range(3):
            screen.blit(button_sprite,(435,i*100+300))
    else:
        screen.blit(main_text_sprite,(435,150))
        if not tutorial:
            for i in range(2):
                screen.blit(main_text_sprite,(435,i*100+300))
        for i in range(3):
            screen.blit(button_sprite,(435,i*100+500))
        

        
    


class Player():
    def __init__(self, x, y, difficulty):
        self.image = pygame.transform.scale(flappy_sprite, (100, 60))
        self.width = 25
        self.height = 40
        self.rect = pygame.Rect(0, 0, self.width, self.height)
        self.rect.center = (x,y)
        self.vel_y = 0
        self.fall=0
        self.dy = 0
        self.dx = 0
        self.moving = True
        self.start_moving = False
        self.grav = False
        self.dif = difficulty


    def move(self):


        self.dy = 0
        self.dx=0  
        scroll = 0

        #GRAVITY
        if self.grav == True:
            self.vel_y += GRAVITY
            self.dy += self.vel_y

        

        #collision check (out of screen)
        if self.rect.top + self.dy < 0:
            self.rect.top = 0 - self.dy
            self.moving = False
        if self.rect.bottom + self.dy > HEIGHT:
            self.rect.bottom = HEIGHT - self.dy
            self.moving = False

        #collision check with obstacles
        for obstacle_b in obstacle_group_bottom:
            for obstacle_t in obstacle_group_top:
                 if pygame.sprite.collide_mask(flappy,obstacle_b) or pygame.sprite.collide_mask(flappy,obstacle_t):
                    self.moving=False

        #collision with starting platform
        for s in start_group:
            if pygame.sprite.collide_mask(flappy, s):
                self.rect.bottom = s.rect.top - self.dy


        key = pygame.key.get_pressed()
        if key[pygame.K_SPACE]:
            self.start_moving = True
            self.grav = True

        #movement(right)
        if self.start_moving == True:
            if self.moving == True:
                if self.dif == 0:
                    self.dx+=move_speed*2
                if self.dif == 1:
                    self.dx+=move_speed*3
                if self.dif == 2:
                    self.dx+=move_speed*4
                if self.dif == 3:
                    self.dx+=move_speed

        # Pokud jsem 350 pixelu od prave strany obrazovky, tak se posune
        if self.rect.right >= SCROLL_THRESH:
            scroll = -self.dx

        


        # update pozice
        if self.start_moving == True:
            self.rect.x += self.dx + scroll
            self.rect.y += self.dy
             
        self.mask = pygame.mask.from_surface(self.image)

        return scroll

    def jump(self):

        key = pygame.key.get_pressed()
        if self.moving==True:
            if key[pygame.K_SPACE]:
                self.vel_y = -jump_height
                self.dy=0
                


    def draw(self):
        screen.blit(self.image, (self.rect.x-12, self.rect.y-5))
        #pygame.draw.rect(screen, WHITE, self.rect, 2)
         



class Obstacle_bottom(pygame.sprite.Sprite):
    def __init__(self, x, height, move):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.transform.scale(cryptonite_sprite, (200,height))
        self.mask = pygame.mask.from_surface(self.image)
        self.moving = move
        self.move_counter = random.randint(0,25) 
        self.direction = random.choice([-1,1])

        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.bottom = HEIGHT+40

       

        self.height = height
        self.passed=False

        self.mask = pygame.mask.from_surface(self.image)

    def update(self, scroll):
        self.rect.x += scroll

        if self.moving ==True:
            self.move_counter +=1
            self.rect.y+= self.direction

        if self.move_counter >=50 or self.rect.bottom<=HEIGHT:
            self.direction *=-1
            self.move_counter=0
        #deleting obstacles
        if self.rect.right<0:
            self.kill()



class Obstacle_top(pygame.sprite.Sprite):
    def __init__(self, x,  height, move):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.transform.scale(cryptonite_sprite, (200,height))
        self.image = pygame.transform.flip(self.image, False, True)
        self.moving = move
        self.move_counter = random.randint(0,25) 
        self.direction = random.choice([-1,1])

        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.top = 0-40 

        self.height = height
        

        self.mask = pygame.mask.from_surface(self.image)

    def update(self, scroll):
        self.rect.x += scroll


        if self.moving ==True:
            self.move_counter +=1
            self.rect.y+= self.direction

        if self.move_counter >=50 or self.rect.top>=0:
            self.direction *=-1
            self.move_counter=0

        #deleting obstacles
        if self.rect.right<0:
            self.kill()


class Start_platform(pygame.sprite.Sprite):
    def __init__(self, x):
        pygame.sprite.Sprite.__init__(self)
        self.image = start_platform_sprite

        self.rect = self.image.get_rect()
        self.rect.left = x 
        self.rect.bottom = HEIGHT

        self.mask = pygame.mask.from_surface(self.image) 

    def update(self, scroll):
        self.rect.x += scroll


        #deleting obstacles
        if self.rect.right<0:
            self.kill()



    
    

        

    


#-------------------------------------------------------------------------------------------------

obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top = first_obstacles()



run = True

while run:
    
    clock.tick(FPS)
    

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
            break

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_RETURN:
                enter_count = return_count(enter_count)
            if event.key == pygame.K_SPACE:
                space_count = jump_count(space_count)
            if event.key == pygame.K_DOWN or event.key == pygame.K_UP:
                arrow_count = key_count(arrow_count)
                if game_over==True:
                    arrow_fx.play()

           
    if game_menu==True:
        if not dif:
            screen.blit(menu_bg_sprite,(0,0))
            draw_button(True, False)
            #screen.blit(main_text_sprite,(435,150))
            text("Main Menu",500,150,test_font,WHITE)
            #screen.blit(button_sprite,(435,300))
            text("Tutorial", 530,300,test_font,WHITE)
            #screen.blit(button_sprite,(435,400))
            text("Start game", 500,400,test_font,WHITE)
            #screen.blit(button_sprite,(435,500))
            text("Quit game", 505,500,test_font,WHITE)
            key = pygame.key.get_pressed()

            if arrow_count == 0:
                draw_arrow(arrow_count, True)
                if enter_count == 1:
                    pygame.mixer.music.play(-1,30)
                    s_count = 0
                    game_over = False
                    game_menu = False
                    enter_count = 0
                    difficulty = 3
                    flappy = Player(140, HEIGHT/2+100, difficulty)
        
        if arrow_count == 1 or dif:
            if not dif:
                draw_arrow(arrow_count, True)
            if enter_count == 1 or dif:
                screen.blit(menu_bg_sprite,(0,0))
                draw_button(True, False)
                text("Choose your difficulty",470,155,test_font2,WHITE)
                text("Easy", 550,300,test_font,WHITE)
                text("Medium", 520,400,test_font,WHITE)
                text("Hard", 550,500,test_font,WHITE)
                if not dif:
                    arrow_count = 0
                    enter_count=0
                dif=True
                if arrow_count==0:
                    draw_arrow(arrow_count, True)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        game_over = False
                        game_menu = False
                        enter_count = 0
                        difficulty = 0
                        flappy = Player(140, (HEIGHT/2)+100, difficulty)
                        dif = False
                        #break
                if arrow_count == 1:
                    draw_arrow(arrow_count, True)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        game_over = False
                        game_menu = False
                        enter_count = 0
                        difficulty = 1
                        flappy = Player(140, HEIGHT/2+100, difficulty)
                        dif = False
                        #break
                if arrow_count == 2:
                    draw_arrow(arrow_count, True)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        game_over = False
                        game_menu = False
                        enter_count = 0
                        difficulty = 2
                        flappy = Player(140, HEIGHT/2+100, difficulty)
                        dif = False
                        #break

        if not dif:
            if arrow_count == 2:
                draw_arrow(arrow_count, True)
                if enter_count == 1:
                    enter_count = 0
                    pygame.quit()
                    break

    else:
        if game_over==False:
            #music play
            pygame.mixer.music.set_volume(0.3)
            
            #platfrom generation
            if len(obstacle_group_bottom)<MAX_OBSTACLES:
                if difficulty==0 or difficulty==3:
                    o_height = random.randint(150,450)
                    crypto_bottom = Obstacle_bottom(crypto_bottom.rect.x + 500, o_height, False)
                    crypto_top = Obstacle_top(crypto_top.rect.x + 500, HEIGHT-o_height-200, False)
                if difficulty==1:
                    o_height = random.randint(150,450)
                    o_move = random.randint(0,1)
                    if o_move == 1:
                        o_move ==True
                    else:
                        o_move=False
                    crypto_bottom = Obstacle_bottom(crypto_bottom.rect.x + 450, o_height, o_move)
                    crypto_top = Obstacle_top(crypto_top.rect.x + 450, HEIGHT-o_height-150, o_move)
                
                if difficulty==2:
                    o_move_b = random.randint(0,1)
                    o_move_t = random.randint(0,1)
                    if o_move_b == 1:
                        o_move_b ==True
                    else:
                        o_move_b=False
                    if o_move_t == 1:
                        o_move_t ==True
                    else:
                        o_move_t=False
                    
                        
                    o_height = random.randint(100,500)
                    crypto_bottom = Obstacle_bottom(crypto_bottom.rect.x + 400, o_height, o_move_b)
                    crypto_top = Obstacle_top(crypto_top.rect.x + 400, HEIGHT-o_height-100, o_move_t)
                obstacle_group_bottom.add(crypto_bottom)
                obstacle_group_top.add(crypto_top)

            #moving player
            scroll=flappy.move()
            if space_count==1:
                space_count=0
                flappy.jump()

            #Score add
            for o in obstacle_group_bottom :
                if flappy.rect.x>o.rect.x and not o.passed:
                    score+=1
                    o.passed = True

            #drawing background/scrolling
            bg_scroll+=scroll
            if -bg_scroll>WIDTH*2:
                bg_scroll=0
                s_count=1
                
            print (bg_scroll)
            draw_bg(bg_scroll)

            #drawing Obstacles
            obstacle_group_bottom.update(scroll)
            obstacle_group_bottom.draw(screen)
            obstacle_group_top.update(scroll)
            obstacle_group_top.draw(screen)

            #drawing start platform
            start_group.update(scroll)
            start_group.draw(screen)

            #draw score
            if difficulty !=3:
                screen.blit(pygame.transform.scale(main_text_sprite,(200,50)), (0,20))
                text("SCORE: "+str(score), 30,25,test_font3,WHITE)
            if difficulty == 3 and s_count==0:
                screen.blit(pygame.transform.scale(main_text_sprite,(410,50)), (20+bg_scroll,350))
                screen.blit(pygame.transform.scale(main_text_sprite,(425,50)), (560+bg_scroll,200))
                text("Press SPACE to jump",50+bg_scroll, 350, test_font, WHITE)
                text("<- Dodge the cryptonite!",580+bg_scroll,200,test_font,WHITE)
            #drawing player
            flappy.draw()

            #game over check
            if flappy.rect.bottom == HEIGHT:
                pygame.mixer.music.stop()
                death_fx.play()
                game_over=True
                arrow_count=0
                enter_count=0


        else:
            if difficulty==0:
                if score>high_score_easy:
                    high_score_easy = score
                    with open("High_score_easy.txt", 'w') as file:
                        file.write(str(high_score_easy))

            if difficulty==1:
                if score>high_score_medium:
                    high_score_medium = score
                    with open("High_score_medium.txt", 'w') as file:
                        file.write(str(high_score_medium))

            if difficulty==2:
                if score>high_score_hard:
                    high_score_hard = score
                    with open("High_score_hard.txt", 'w') as file:
                        file.write(str(high_score_hard))

            if end_scroll<WIDTH/2:
                end_scroll +=8

                surface = pygame.Surface((end_scroll, end_scroll * 3 / 4), pygame.SRCALPHA, 32)

                rect = pygame.Rect(0, 0, end_scroll, end_scroll * 3 / 4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (0, 0))

                rect = pygame.Rect(menu_bg_sprite.get_width() - end_scroll, 0, end_scroll, end_scroll*3/4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (WIDTH - end_scroll, 0))

                rect = pygame.Rect(0, menu_bg_sprite.get_height() - end_scroll*3/4, end_scroll, end_scroll*3/4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (0, HEIGHT - end_scroll*3/4))

                rect = pygame.Rect(menu_bg_sprite.get_width() - end_scroll, menu_bg_sprite.get_height() - end_scroll*3/4, end_scroll, end_scroll*3/4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (WIDTH - end_scroll, HEIGHT - end_scroll*3/4))
                

            else:
                screen.blit(menu_bg_sprite,(0,0))
                if difficulty!=3:
                    draw_button(False, False)
                    if difficulty ==0:
                        text("SCORE: "+str(score), 510,300,test_font,WHITE)
                        if score<high_score_easy:
                            text("HIGH SCORE: "+str(high_score_easy), 470,405,test_font3,WHITE)
                        if score>=high_score_easy:
                            text("NEW HIGH SCORE: "+str(high_score_easy), 465,410,test_font2,WHITE)
                    if difficulty ==1:
                        text("SCORE: "+str(score), 510,300,test_font,WHITE)
                        if score<high_score_medium:
                            text("HIGH SCORE: "+str(high_score_medium), 470,405,test_font3,WHITE)
                        if score>=high_score_medium:
                            text("NEW HIGH SCORE: "+str(high_score_medium), 465,410,test_font2,WHITE)

                    if difficulty ==2:
                        text("SCORE: "+str(score), 510,300,test_font,WHITE)
                        if score<high_score_hard:
                            text("HIGH SCORE: "+str(high_score_hard), 470,405,test_font3,WHITE)
                        if score>=high_score_hard:
                            text("NEW HIGH SCORE: "+str(high_score_hard), 465,410,test_font2,WHITE)
                
                else:
                    draw_button(False, True)

                text("Game Over !!",480,150,test_font,WHITE)
                text("Play again", 505,500,test_font,WHITE)
                text("Main menu", 500,600,test_font,WHITE)
                text("Quit game", 505,700,test_font,WHITE)
                

                #selection
                key = pygame.key.get_pressed()
                if arrow_count == 0:
                    draw_arrow(arrow_count, False)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        enter_count = 0
                        obstacle_group_bottom.empty()
                        obstacle_group_top.empty()
                        flappy = Player(140, HEIGHT/2+100, difficulty)
                        obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top = first_obstacles()
                        game_over = False
                        pygame.mixer.music.set_volume(0.3)
                        arrow_count = 0
                        scroll=0
                        end_scroll=0
                        score=0
                        score_add = 0
                        bg_scroll=0
                        if difficulty == 3:
                            s_count = 0

                
                if arrow_count == 1:
                    draw_arrow(arrow_count, False)
                    if enter_count == 1:
                        enter_count = 0
                        game_menu=True
                        obstacle_group_bottom.empty()
                        obstacle_group_top.empty()
                        obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top = first_obstacles()
                        game_over = True
                        arrow_count = 0
                        scroll=0
                        end_scroll=0
                        score=0
                        score_add = 0
                        bg_scroll=0

                if arrow_count == 2:
                    draw_arrow(arrow_count, False)
                    if enter_count == 1:
                        enter_count = 0
                        pygame.quit()
                        break

        

        
    
            
    pygame.display.update()

pygame.quit()