from variables.variables import start_platform_sprite, HEIGHT
import pygame
class Start_platform(pygame.sprite.Sprite):
    def __init__(self, x:int):
        pygame.sprite.Sprite.__init__(self)
        self.image = start_platform_sprite

        self.rect = self.image.get_rect()
        self.rect.left = x 
        self.rect.bottom = HEIGHT

        self.mask = pygame.mask.from_surface(self.image) 

    def update(self, scroll:int):
        self.rect.x += scroll


        #deleting obstacles
        if self.rect.right<0:
            self.kill()