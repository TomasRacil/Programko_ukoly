import pygame
from variables.variables import flappy_sprite,GRAVITY,HEIGHT,move_speed,SCROLL_THRESH
from functions.first_obstacles import first_obstacles
from variables.variables import difficulty, jump_height,screen


obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top = first_obstacles()
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
    
flappy = Player(140, HEIGHT/2+100, difficulty)