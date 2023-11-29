from variables.variables import screen
def text(text:str, x:int, y:int, font, text_color):
    image = font.render(text, True, text_color)
    screen.blit(image,(x,y))