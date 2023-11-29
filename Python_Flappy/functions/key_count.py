import pygame

def key_count(arrow_count:int)->int:

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