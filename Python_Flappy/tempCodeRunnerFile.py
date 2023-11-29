def jump(self):

        key = pygame.key.get_pressed()
        if self.moving==True:
            if key[pygame.K_SPACE]:
                self.vel_y = -jump_height
                self.dy=0
                


    def draw(self):
        screen.blit(self.image, (self.rect.x-12, self.rect.y-5))
        #pygame.draw.rect(screen, WHITE, self.rect, 2)