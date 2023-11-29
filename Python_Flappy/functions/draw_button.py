from variables.variables import screen, main_text_sprite, button_sprite
import pygame
def draw_button(main:bool, tutorial:bool):
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