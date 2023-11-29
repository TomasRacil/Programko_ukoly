from variables.variables import  cryptonite_sprite,HEIGHT
import pygame,random
class Obstacle_bottom(pygame.sprite.Sprite):
    def __init__(self, x:int, height:int, move:bool):
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

    def update(self, scroll:int):
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