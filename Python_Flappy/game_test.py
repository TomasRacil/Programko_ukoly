#functions
from functions import *


#classes
from classes import *

#variables
from variables.variables import *

import pygame
import random
import os
from pygame import mixer

mixer.init()
pygame.init()

#score
if os.path.exists('High_score_easy.txt'):
	with open ("High_score_easy.txt", 'r') as file:
		high_score_easy = int(file.read())
else:
	high_score_easy =0

if os.path.exists('High_score_medium.txt'):
	with open ("High_score_medium.txt", 'r') as file:
		high_score_medium = int(file.read())
else:
	high_score_medium =0

if os.path.exists('High_score_hard.txt'):
	with open ("High_score_hard.txt", 'r') as file:
		high_score_hard = int(file.read())
else:
	high_score_hard =0


#-------------------------------------------------------------------------------------------------
#flappy = Player(140, HEIGHT/2+100, difficulty)


    
obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top = first_obstacles()


run = True

while run:
    
    clock.tick(FPS)
    

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
            break

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_RETURN:
                enter_count = return_count(enter_count)
            if event.key == pygame.K_SPACE:
                space_count = jump_count(space_count)
            if event.key == pygame.K_DOWN or event.key == pygame.K_UP:
                arrow_count = key_count(arrow_count)
                if game_over==True:
                    arrow_fx.play()

        
    if game_menu==True:
        if not dif:
            screen.blit(menu_bg_sprite,(0,0))
            draw_button(True, False)
            #screen.blit(main_text_sprite,(435,150))
            text("Main Menu",500,150,test_font,WHITE)
            #screen.blit(button_sprite,(435,300))
            text("Tutorial", 530,300,test_font,WHITE)
            #screen.blit(button_sprite,(435,400))
            text("Start game", 500,400,test_font,WHITE)
            #screen.blit(button_sprite,(435,500))
            text("Quit game", 505,500,test_font,WHITE)
            key = pygame.key.get_pressed()

            if arrow_count == 0:
                draw_arrow(arrow_count, True)
                if enter_count == 1:
                    pygame.mixer.music.play(-1,30)
                    s_count = 0
                    game_over = False
                    game_menu = False
                    enter_count = 0
                    difficulty = 3
                    flappy = Player(140, HEIGHT/2+100, difficulty,obstacle_group_bottom,obstacle_group_top,start_group)
        
        if arrow_count == 1 or dif:
            if not dif:
                draw_arrow(arrow_count, True)
            if enter_count == 1 or dif:
                screen.blit(menu_bg_sprite,(0,0))
                draw_button(True, False)
                text("Choose your difficulty",470,155,test_font2,WHITE)
                text("Easy", 550,300,test_font,WHITE)
                text("Medium", 520,400,test_font,WHITE)
                text("Hard", 550,500,test_font,WHITE)
                if not dif:
                    arrow_count = 0
                    enter_count=0
                dif=True
                if arrow_count==0:
                    draw_arrow(arrow_count, True)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        game_over = False
                        game_menu = False
                        enter_count = 0
                        difficulty = 0
                        flappy = Player(140, (HEIGHT/2)+100, difficulty,obstacle_group_bottom,obstacle_group_top,start_group)
                        dif = False
                        #break
                if arrow_count == 1:
                    draw_arrow(arrow_count, True)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        game_over = False
                        game_menu = False
                        enter_count = 0
                        difficulty = 1
                        flappy = Player(140, HEIGHT/2+100, difficulty,obstacle_group_bottom,obstacle_group_top,start_group)
                        dif = False
                        #break
                if arrow_count == 2:
                    draw_arrow(arrow_count, True)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        game_over = False
                        game_menu = False
                        enter_count = 0
                        difficulty = 2
                        flappy = Player(140, HEIGHT/2+100, difficulty,obstacle_group_bottom,obstacle_group_top,start_group)
                        dif = False
                        #break

        if not dif:
            if arrow_count == 2:
                draw_arrow(arrow_count, True)
                if enter_count == 1:
                    enter_count = 0
                    pygame.quit()
                    break

    else:
        if game_over==False:
            #music play
            pygame.mixer.music.set_volume(0.3)
            
            #platfrom generation
            if len(obstacle_group_bottom)<MAX_OBSTACLES:
                if difficulty==0 or difficulty==3:
                    o_height = random.randint(150,450)
                    crypto_bottom = Obstacle_bottom(crypto_bottom.rect.x + 500, o_height, False)
                    crypto_top = Obstacle_top(crypto_top.rect.x + 500, HEIGHT-o_height-200, False)
                if difficulty==1:
                    o_height = random.randint(150,450)
                    o_move = random.randint(0,1)
                    if o_move == 1:
                        o_move ==True
                    else:
                        o_move=False
                    crypto_bottom = Obstacle_bottom(crypto_bottom.rect.x + 450, o_height, o_move)
                    crypto_top = Obstacle_top(crypto_top.rect.x + 450, HEIGHT-o_height-150, o_move)
                
                if difficulty==2:
                    o_move_b = random.randint(0,1)
                    o_move_t = random.randint(0,1)
                    if o_move_b == 1:
                        o_move_b ==True
                    else:
                        o_move_b=False
                    if o_move_t == 1:
                        o_move_t ==True
                    else:
                        o_move_t=False
                    
                        
                    o_height = random.randint(100,500)
                    crypto_bottom = Obstacle_bottom(crypto_bottom.rect.x + 400, o_height, o_move_b)
                    crypto_top = Obstacle_top(crypto_top.rect.x + 400, HEIGHT-o_height-100, o_move_t)
                obstacle_group_bottom.add(crypto_bottom)
                obstacle_group_top.add(crypto_top)

            #moving player
            scroll=flappy.move()
            if space_count==1:
                space_count=0
                flappy.jump()

            #Score add
            for o in obstacle_group_bottom :
                if flappy.rect.x>o.rect.x and not o.passed:
                    score+=1
                    o.passed = True

            #drawing background/scrolling
            bg_scroll+=scroll
            if -bg_scroll>WIDTH*2:
                bg_scroll=0
                s_count=1
                
            draw_bg(bg_scroll)

            #drawing Obstacles
            obstacle_group_bottom.update(scroll)
            obstacle_group_bottom.draw(screen)
            obstacle_group_top.update(scroll)
            obstacle_group_top.draw(screen)

            #drawing start platform
            start_group.update(scroll)
            start_group.draw(screen)

            #draw score
            if difficulty !=3:
                screen.blit(pygame.transform.scale(main_text_sprite,(200,50)), (0,20))
                text("SCORE: "+str(score), 30,25,test_font3,WHITE)
            if difficulty == 3 and s_count==0:
                screen.blit(pygame.transform.scale(main_text_sprite,(410,50)), (20+bg_scroll,350))
                screen.blit(pygame.transform.scale(main_text_sprite,(425,50)), (560+bg_scroll,200))
                text("Press SPACE to jump",50+bg_scroll, 350, test_font, WHITE)
                text("<- Dodge the cryptonite!",580+bg_scroll,200,test_font,WHITE)
            #drawing player
            flappy.update_groups(obstacle_group_bottom,obstacle_group_top,start_group)  
            flappy.draw()

            #game over check
            if flappy.rect.bottom == HEIGHT:
                pygame.mixer.music.stop()
                death_fx.play()
                game_over=True
                arrow_count=0
                enter_count=0


        else:
            if difficulty==0:
                if score>high_score_easy:
                    high_score_easy = score
                    with open("High_score_easy.txt", 'w') as file:
                        file.write(str(high_score_easy))

            if difficulty==1:
                if score>high_score_medium:
                    high_score_medium = score
                    with open("High_score_medium.txt", 'w') as file:
                        file.write(str(high_score_medium))

            if difficulty==2:
                if score>high_score_hard:
                    high_score_hard = score
                    with open("High_score_hard.txt", 'w') as file:
                        file.write(str(high_score_hard))

            if end_scroll<WIDTH/2:
                end_scroll +=8

                surface = pygame.Surface((end_scroll, end_scroll * 3 / 4), pygame.SRCALPHA, 32)

                rect = pygame.Rect(0, 0, end_scroll, end_scroll * 3 / 4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (0, 0))

                rect = pygame.Rect(menu_bg_sprite.get_width() - end_scroll, 0, end_scroll, end_scroll*3/4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (WIDTH - end_scroll, 0))

                rect = pygame.Rect(0, menu_bg_sprite.get_height() - end_scroll*3/4, end_scroll, end_scroll*3/4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (0, HEIGHT - end_scroll*3/4))

                rect = pygame.Rect(menu_bg_sprite.get_width() - end_scroll, menu_bg_sprite.get_height() - end_scroll*3/4, end_scroll, end_scroll*3/4)
                surface.blit(menu_bg_sprite, (0, 0), rect)
                screen.blit(surface, (WIDTH - end_scroll, HEIGHT - end_scroll*3/4))
                

            else:
                screen.blit(menu_bg_sprite,(0,0))
                if difficulty!=3:
                    draw_button(False, False)
                    if difficulty ==0:
                        text("SCORE: "+str(score), 510,300,test_font,WHITE)
                        if score<high_score_easy:
                            text("HIGH SCORE: "+str(high_score_easy), 470,405,test_font3,WHITE)
                        if score>=high_score_easy:
                            text("NEW HIGH SCORE: "+str(high_score_easy), 465,410,test_font2,WHITE)
                    if difficulty ==1:
                        text("SCORE: "+str(score), 510,300,test_font,WHITE)
                        if score<high_score_medium:
                            text("HIGH SCORE: "+str(high_score_medium), 470,405,test_font3,WHITE)
                        if score>=high_score_medium:
                            text("NEW HIGH SCORE: "+str(high_score_medium), 465,410,test_font2,WHITE)

                    if difficulty ==2:
                        text("SCORE: "+str(score), 510,300,test_font,WHITE)
                        if score<high_score_hard:
                            text("HIGH SCORE: "+str(high_score_hard), 470,405,test_font3,WHITE)
                        if score>=high_score_hard:
                            text("NEW HIGH SCORE: "+str(high_score_hard), 465,410,test_font2,WHITE)
                
                else:
                    draw_button(False, True)

                text("Game Over !!",480,150,test_font,WHITE)
                text("Play again", 505,500,test_font,WHITE)
                text("Main menu", 500,600,test_font,WHITE)
                text("Quit game", 505,700,test_font,WHITE)
                

                #selection
                key = pygame.key.get_pressed()
                if arrow_count == 0:
                    draw_arrow(arrow_count, False)
                    if enter_count == 1:
                        pygame.mixer.music.play(-1,30)
                        enter_count = 0
                        obstacle_group_bottom.empty()
                        obstacle_group_top.empty()
                        flappy = Player(140, HEIGHT/2+100, difficulty,obstacle_group_bottom,obstacle_group_top,start_group)
                        obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top = first_obstacles()
                        game_over = False
                        pygame.mixer.music.set_volume(0.3)
                        arrow_count = 0
                        scroll=0
                        end_scroll=0
                        score=0
                        score_add = 0
                        bg_scroll=0
                        if difficulty == 3:
                            s_count = 0

                
                if arrow_count == 1:
                    draw_arrow(arrow_count, False)
                    if enter_count == 1:
                        enter_count = 0
                        game_menu=True
                        obstacle_group_bottom.empty()
                        obstacle_group_top.empty()
                        obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top = first_obstacles()
                        game_over = True
                        arrow_count = 0
                        scroll=0
                        end_scroll=0
                        score=0
                        score_add = 0
                        bg_scroll=0

                if arrow_count == 2:
                    draw_arrow(arrow_count, False)
                    if enter_count == 1:
                        enter_count = 0
                        pygame.quit()
                        break

    

        

        
    
            
    pygame.display.update()

pygame.quit()


