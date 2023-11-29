from variables.variables import screen,arrow_sprite
import pygame
def draw_arrow(arrow_count:int, main_menu:bool):
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