from collections import deque
import pygame, serial

screen = pygame.display.set_mode((300, 300))
pygame.display.flip()

screen.fill((255, 255, 255))

surface = pygame.display.get_surface()

gap_offset = 10

pygame.display.flip()

running = True
mouse_down = False

prev_point = 0
new_point = 0

point_queue = deque()


arduino = serial.Serial('COM3', 19200, write_timeout = 3)

while running:
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONUP:
            mouse_down = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            new_point = (event.pos[0], event.pos[1])
            mouse_down = True
        if mouse_down and event.type == pygame.MOUSEMOTION:
            prev_point = new_point

            old_x = prev_point[0]
            new_x = event.pos[0]
            old_y = prev_point[1]
            new_y = event.pos[1]

            if (new_x > old_x + gap_offset or new_x < old_x - gap_offset) or (new_y > old_y + gap_offset or new_y < old_y - gap_offset):
                new_point = (event.pos[0], event.pos[1])
                point = str(new_point[0]) + str(new_point[1)]
                point_queue.append(point)
                
                pygame.draw.line(surface, (0,0,0), prev_point, new_point, 5)
                pygame.display.flip()
            
        if event.type == pygame.QUIT:
            print(event)
            pygame.display.quit()
            pygame.quit()
            
