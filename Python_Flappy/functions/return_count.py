import pygame
def return_count(enter_count:int)->int:
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