import struct
import threading
import time
from collections import deque

import pygame
import serial

#Necessary state variables
PORT = "INSERT PORT HERE"
ARDUINO_AVAILABLE = True
running = True
mouse_down = False
prev_point = 0
new_point = 0
gap_offset = 10

screen = pygame.display.set_mode((300, 300))
screen.fill((255, 255, 255))

surface = pygame.display.get_surface()
pygame.display.flip()

#Queue for storing points. FILO (First in, Last out) data structure
point_queue = deque()

#Starts a new thread; Send_Serial is the function the thread runs
thread = threading.Thread(target=send_serial)

#Creates new Serial object: Used for communicating with main Arduino
arduino = serial.Serial(PORT, 9600, timeout = 1, write_timeout = 3)

def send_serial():
    global point_queue
    buffer = 0
    
    prev_response = None

    while True:

        arduino_response = arduino.read()

        try:
            arduino_response = int.from_bytes(arduino_response, 'little')
        except:
            #failsafe in the case that the Arduino hasn't given a response (maybe stuck calculating)
            arduino_response = prev_response

        if arduino_response == 1:
            ARDUINO_AVAILABLE = False
        else:
            ARDUINO_AVAILABLE = True

        if not ARDUINO_AVAILABLE:
            time.sleep(0.1)
        else:
            if len(point_queue) > 0 or buffer < 64:
                points = point_queue.popleft()
                for point in points:
                    #Since numbers are objects in python, this convert it into an unsigned char (1 byte, little endian)
                    arduino.write(struct.pack('<B', point))
            else:
                time.sleep(0.1)

        prev_response = arduino_response

#Starts Serial write thread
thread.start()

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
                point = str(new_point[0]) + str(new_point[1])
                point_queue.append(point)
                
                pygame.draw.line(surface, (0,0,0), prev_point, new_point, 5)
                pygame.display.flip()
            
        if event.type == pygame.QUIT:
            thread.end()
            print(event)
            pygame.display.quit()
pygame.quit()
