import pygame
def jump_count(space_count:int)->int:
    space_count = 0
    key = pygame.key.get_pressed()
    if key[pygame.K_SPACE]:
        space_count = 1
    return space_count