from classes.Obstacle_bottom import Obstacle_bottom
from classes.Obstacle_top import Obstacle_top
from classes.Start_platfrom import Start_platform
import pygame
def first_obstacles():
    crypto_bottom = Obstacle_bottom(450, 350, False)
    crypto_top = Obstacle_top(450, 350, False)
    obstacle_group_bottom = pygame.sprite.Group()
    obstacle_group_top = pygame.sprite.Group()
    obstacle_group_bottom.add(crypto_bottom)
    obstacle_group_top.add(crypto_top)
    start_group = pygame.sprite.Group()
    start_platform = Start_platform(0)
    start_group.add(start_platform)
    return obstacle_group_bottom, obstacle_group_top, start_group, crypto_bottom, crypto_top