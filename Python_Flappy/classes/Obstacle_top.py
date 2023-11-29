import pygame,random
from variables.variables import cryptonite_sprite
class Obstacle_top(pygame.sprite.Sprite):
    def __init__(self, x:int,  height:int, move:bool):
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

    def update(self, scroll:int):
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