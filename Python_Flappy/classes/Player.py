import pygame
from variables.variables import flappy_sprite,GRAVITY,HEIGHT,move_speed,SCROLL_THRESH,jump_height,screen


class Player:
    def __init__(self, x:int, y:int, difficulty:int,obstacle_group_bottom:list,obstacle_group_top:list,start_group:list):
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
        self.obstacle_group_bottom = obstacle_group_bottom
        self.start_group = start_group
        self.obstacle_group_top = obstacle_group_top


    def move(self)->int:
        """Function that moves player based on dx(right movement) and dy(Gravity, up and down) variable.
            Checks for collision between Player and Obstacles
        Returns:
            int: scroll, variable that is used to move draw player correctly on the screen, later on used for bg_scroll
        """
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
        for obstacle_b in self.obstacle_group_bottom:
            for obstacle_t in self.obstacle_group_top:
                 if pygame.sprite.collide_mask(self,obstacle_b) or pygame.sprite.collide_mask(self,obstacle_t):
                    self.moving=False

        #collision with starting platform
        for s in self.start_group:
            if pygame.sprite.collide_mask(self, s):
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
                

    def update_groups(self,obstacle_group_bottom,obstacle_group_top,start_group):
        self.obstacle_group_bottom = obstacle_group_bottom
        self.obstacle_group_top = obstacle_group_top
        self.start_group = start_group


    def draw(self):
        screen.blit(self.image, (self.rect.x-12, self.rect.y-5))
        #pygame.draw.rect(screen, WHITE, self.rect, 2)
