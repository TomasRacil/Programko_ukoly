import pygame
pygame.init()
#screen
WIDTH = 1200
HEIGHT = 900

#barvy
WHITE=(255,255,255)
CYAN=(0, 139, 139)
YELLOW=(255,255,0)
BLACK=(0,0,0)

#fonts
test_font=pygame.font.SysFont("arialunicode", 36)
test_font2=pygame.font.SysFont("arialunicode", 24)
test_font3=pygame.font.SysFont("arialunicode", 30)

#game window
pygame.display.set_caption("Budget Flappy")
screen = pygame.display.set_mode((WIDTH, HEIGHT))

#fps cap
clock = pygame.time.Clock()
FPS=60

#global variables
SCROLL_THRESH = WIDTH/3
GRAVITY = 1
MAX_OBSTACLES = 10
game_over = True
game_menu = True
dif = False
move_speed = 2
jump_height=17
scroll = 0
bg_scroll=0
end_scroll = 0
triangle_y=160
triangle_x1 = 450
triangle = 760
arrow_count = 0
enter_count = 0
score = 0
score_add = 0
difficulty = 0
space_count = 0
s_count = 0


#sprites
flappy_sprite = pygame.image.load("assets/superman.png").convert_alpha()
game_bg_sprite = pygame.transform.scale(pygame.image.load("assets/game_bg.png"), (WIDTH, HEIGHT)).convert_alpha()
menu_bg_sprite = pygame.transform.scale(pygame.image.load("assets/menu_bg.png"),(WIDTH,HEIGHT)).convert_alpha()
cryptonite_sprite = pygame.image.load("assets/pixel_kryptonite.png").convert_alpha()
start_platform_sprite = pygame.transform.scale(pygame.image.load("assets/starting_platform.png"), (200, 310)).convert_alpha()
button_sprite = pygame.transform.scale(pygame.image.load("assets/button.png"),(300, 50)).convert_alpha()
arrow_sprite = pygame.image.load("assets/arrow.png").convert_alpha()
main_text_sprite = pygame.image.load("assets/main_text.png").convert_alpha()
earth_sprite = pygame.transform.scale(pygame.image.load("assets/earth.png"),(130,130)).convert_alpha()
jupiter_sprite = pygame.transform.scale(pygame.image.load("assets/jupiter.png"),(200,200)).convert_alpha()
saturn_sprite = pygame.transform.scale(pygame.image.load("assets/saturn.png"),(250,250)).convert_alpha()
comet_sprite = pygame.transform.scale(pygame.image.load("assets/comet.png"),(100,100)).convert_alpha()

#music """
pygame.mixer.music.load("assets/bg_music.mp3")
pygame.mixer.music.set_volume(0.3)
death_fx = pygame.mixer.Sound("assets/death.wav")
death_fx.set_volume(0.3)
arrow_fx = pygame.mixer.Sound("assets/arrow_press.mp3")
arrow_fx.set_volume(0.3)


