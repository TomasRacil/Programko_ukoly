from variables.variables import screen,comet_sprite,earth_sprite,jupiter_sprite,saturn_sprite,game_bg_sprite,WIDTH

def draw_bg(bg_scroll:int):
    for i in range(3):
        screen.blit(game_bg_sprite, (i*WIDTH+bg_scroll, 0 ))
        
    screen.blit(comet_sprite,(-130-bg_scroll*0.7, 120-bg_scroll))
    screen.blit(comet_sprite,(-50-bg_scroll*0.7, -400-bg_scroll*0.7))
    screen.blit(earth_sprite,(-100-bg_scroll*0.7, 100))
    screen.blit(jupiter_sprite,(-300-bg_scroll*0.6, 150))
    screen.blit(saturn_sprite,(1200+bg_scroll*1.2, 600))
