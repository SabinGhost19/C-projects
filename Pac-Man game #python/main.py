# Build Pac-Man from Scratch in Python with PyGame!!
import copy
from pygame.locals import *
from board import boards
from board3 import boards3
import pygame,sys
import math
import time
import random
import button
pygame.init()





paused=False
Latime = 900
Inaltime = 950
screen = pygame.display.set_mode([Latime, Inaltime])
timer = pygame.time.Clock()
fps = 60
font = pygame.font.Font('freesansbold.ttf', 20)
level = copy.deepcopy(boards)
color = 'yellow'
PI = math.pi
square_x = random.randint(0, Latime - 30)
square_y = random.randint(0, Inaltime - 30)
player_images = []
for i in range(1, 5):
    player_images.append(pygame.transform.scale(pygame.image.load(f'assets/player_file/{i}.png'), (45, 45)))
ghost1_img = pygame.transform.scale(pygame.image.load(f'assets/ghost_images/ghost1.png'), (55, 55))
ghost4_img = pygame.transform.scale(pygame.image.load(f'assets/ghost_images/ghost4.png'), (55, 55))
ghost2_img = pygame.transform.scale(pygame.image.load(f'assets/ghost_images/ghost2.png'), (55, 55))
ghost3_img = pygame.transform.scale(pygame.image.load(f'assets/ghost_images/ghost3.png'), (55, 55))
spooked_img = pygame.transform.scale(pygame.image.load(f'assets/ghost_images/scared.png'), (55, 55))
dead_img = pygame.transform.scale(pygame.image.load(f'assets/ghost_images/dead.png'), (55, 55))
#ghost1 -blinky    ghost2-inky    ghost3-clyde    ghost4-pinky
player_x = 200
player_y = 600
direction = 0
ghost1_x = 200
ghost1_y = 200
ghost1_direction = 0
ghost2_x = 410
ghost2_y = 388
ghost2_direction= 2
ghost4_x = 420
ghost4_y = 400
ghost4_direction = 2
ghost3_x = 440
ghost3_y = 438
ghost3_direction = 2
counter = 0
flicker = False
# R, L, U, D
turns_allowed = [False, False, False, False]
direction_command = 0
player_speed = 2
score = 0
powerup = False
power_counter = 0
eaten_ghost = [False, False, False, False]
targets = [(player_x, player_y), (player_x, player_y), (player_x, player_y), (player_x, player_y)]
ghost1_dead = False
ghost2_dead = False
ghost3_dead = False
ghost4_dead = False
ghost1_box = False
ghost2_box = False
ghost3_box = False
ghost4_box = False
moving = False
ghost_speeds = [2, 2, 2, 2]
startup_counter = 0
lives = 3
game_over = False
game_won = False
class Ghost:
    def __init__(self, x_coord, y_coord, target, speed, img, direct, dead, box, id):
        self.x_pos = x_coord
        self.y_pos = y_coord
        self.center_x = self.x_pos + 22
        self.center_y = self.y_pos + 22
        self.target = target
        self.speed = speed
        self.img = img
        self.direction = direct
        self.dead = dead
        self.in_box = box
        self.id = id
        self.turns, self.in_box = self.check_collisions()
        self.rect = self.draw()

    def draw(self):
        if (not powerup and not self.dead) or (eaten_ghost[self.id] and powerup and not self.dead):
            screen.blit(self.img, (self.x_pos, self.y_pos))
        elif powerup and not self.dead and not eaten_ghost[self.id]:
            screen.blit(spooked_img, (self.x_pos, self.y_pos))
        else:
            screen.blit(dead_img, (self.x_pos, self.y_pos))
        ghost_rect = pygame.rect.Rect((self.center_x - 18, self.center_y - 18), (36, 36))
        return ghost_rect

    def check_collisions(self):
        num1 = ((Inaltime - 50) // 32)
        num2 = (Latime // 30)
        num3 = 15
        self.turns = [False, False, False, False]
        if 0 < self.center_x // 30 < 29:
            if level[(self.center_y - num3) // num1][self.center_x // num2] == 9:
                self.turns[2] = True
            if level[self.center_y // num1][(self.center_x - num3) // num2] < 3 \
                    or (level[self.center_y // num1][(self.center_x - num3) // num2] == 9 and (
                    self.in_box or self.dead)):
                self.turns[1] = True
            if level[self.center_y // num1][(self.center_x + num3) // num2] < 3 \
                    or (level[self.center_y // num1][(self.center_x + num3) // num2] == 9 and (
                    self.in_box or self.dead)):
                self.turns[0] = True
            if level[(self.center_y + num3) // num1][self.center_x // num2] < 3 \
                    or (level[(self.center_y + num3) // num1][self.center_x // num2] == 9 and (
                    self.in_box or self.dead)):
                self.turns[3] = True
            if level[(self.center_y - num3) // num1][self.center_x // num2] < 3 \
                    or (level[(self.center_y - num3) // num1][self.center_x // num2] == 9 and (
                    self.in_box or self.dead)):
                self.turns[2] = True

            if self.direction == 2 or self.direction == 3:
                if 12 <= self.center_x % num2 <= 18:
                    if level[(self.center_y + num3) // num1][self.center_x // num2] < 3 \
                            or (level[(self.center_y + num3) // num1][self.center_x // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[3] = True
                    if level[(self.center_y - num3) // num1][self.center_x // num2] < 3 \
                            or (level[(self.center_y - num3) // num1][self.center_x // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[2] = True
                if 12 <= self.center_y % num1 <= 18:
                    if level[self.center_y // num1][(self.center_x - num2) // num2] < 3 \
                            or (level[self.center_y // num1][(self.center_x - num2) // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[1] = True
                    if level[self.center_y // num1][(self.center_x + num2) // num2] < 3 \
                            or (level[self.center_y // num1][(self.center_x + num2) // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[0] = True

            if self.direction == 0 or self.direction == 1:
                if 12 <= self.center_x % num2 <= 18:
                    if level[(self.center_y + num3) // num1][self.center_x // num2] < 3 \
                            or (level[(self.center_y + num3) // num1][self.center_x // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[3] = True
                    if level[(self.center_y - num3) // num1][self.center_x // num2] < 3 \
                            or (level[(self.center_y - num3) // num1][self.center_x // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[2] = True
                if 12 <= self.center_y % num1 <= 18:
                    if level[self.center_y // num1][(self.center_x - num3) // num2] < 3 \
                            or (level[self.center_y // num1][(self.center_x - num3) // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[1] = True
                    if level[self.center_y // num1][(self.center_x + num3) // num2] < 3 \
                            or (level[self.center_y // num1][(self.center_x + num3) // num2] == 9 and (
                            self.in_box or self.dead)):
                        self.turns[0] = True
        else:
            self.turns[0] = True
            self.turns[1] = True
        if 350 < self.x_pos < 550 and 370 < self.y_pos < 480:
            self.in_box = True
        else:
            self.in_box = False
        return self.turns, self.in_box

    def move_ghost3(self):
        # "cel mai periculos" , mereu pt urmarire, mereu unde e avantajos
        if self.direction == 0:
            if self.target[0] > self.x_pos and self.turns[0]:
                self.x_pos += self.speed
            elif not self.turns[0]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
            elif self.turns[0]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                if self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                else:
                    self.x_pos += self.speed
        elif self.direction == 1:
            if self.target[1] > self.y_pos and self.turns[3]:
                self.direction = 3
            elif self.target[0] < self.x_pos and self.turns[1]:
                self.x_pos -= self.speed
            elif not self.turns[1]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[1]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                if self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                else:
                    self.x_pos -= self.speed
        elif self.direction == 2:
            if self.target[0] < self.x_pos and self.turns[1]:
                self.direction = 1
                self.x_pos -= self.speed
            elif self.target[1] < self.y_pos and self.turns[2]:
                self.direction = 2
                self.y_pos -= self.speed
            elif not self.turns[2]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[2]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                else:
                    self.y_pos -= self.speed
        elif self.direction == 3:
            if self.target[1] > self.y_pos and self.turns[3]:
                self.y_pos += self.speed
            elif not self.turns[3]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[3]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                else:
                    self.y_pos += self.speed
        if self.x_pos < -30:
            self.x_pos = 900
        elif self.x_pos > 900:
            self.x_pos - 30
        return self.x_pos, self.y_pos, self.direction

    def move_ghost1(self):
        # se va intoarce mereu cand are coliziune cu peretii, in mod normal merge drept
        if self.direction == 0:
            if self.target[0] > self.x_pos and self.turns[0]:
                self.x_pos += self.speed
            elif not self.turns[0]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
            elif self.turns[0]:
                self.x_pos += self.speed
        elif self.direction == 1:
            if self.target[0] < self.x_pos and self.turns[1]:
                self.x_pos -= self.speed
            elif not self.turns[1]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[1]:
                self.x_pos -= self.speed
        elif self.direction == 2:
            if self.target[1] < self.y_pos and self.turns[2]:
                self.direction = 2
                self.y_pos -= self.speed
            elif not self.turns[2]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
            elif self.turns[2]:
                self.y_pos -= self.speed
        elif self.direction == 3:
            if self.target[1] > self.y_pos and self.turns[3]:
                self.y_pos += self.speed
            elif not self.turns[3]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
            elif self.turns[3]:
                self.y_pos += self.speed
        if self.x_pos < -30:
            self.x_pos = 900
        elif self.x_pos > 900:
            self.x_pos - 30
        return self.x_pos, self.y_pos, self.direction

    def move_ghost2(self):
        # se va intoarce sus sau jos oriunde pt a urmari dar stanga si dreapta la coliziuni
        if self.direction == 0:
            if self.target[0] > self.x_pos and self.turns[0]:
                self.x_pos += self.speed
            elif not self.turns[0]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
            elif self.turns[0]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                if self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                else:
                    self.x_pos += self.speed
        elif self.direction == 1:
            if self.target[1] > self.y_pos and self.turns[3]:
                self.direction = 3
            elif self.target[0] < self.x_pos and self.turns[1]:
                self.x_pos -= self.speed
            elif not self.turns[1]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[1]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                if self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                else:
                    self.x_pos -= self.speed
        elif self.direction == 2:
            if self.target[1] < self.y_pos and self.turns[2]:
                self.direction = 2
                self.y_pos -= self.speed
            elif not self.turns[2]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[2]:
                self.y_pos -= self.speed
        elif self.direction == 3:
            if self.target[1] > self.y_pos and self.turns[3]:
                self.y_pos += self.speed
            elif not self.turns[3]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[3]:
                self.y_pos += self.speed
        if self.x_pos < -30:
            self.x_pos = 900
        elif self.x_pos > 900:
            self.x_pos - 30
        return self.x_pos, self.y_pos, self.direction

    def move_ghost4(self):
        # se va intoarce stanga sau dreapta cand ii este mai avantajos dar sus si jos cand e coliziune
        if self.direction == 0:
            if self.target[0] > self.x_pos and self.turns[0]:
                self.x_pos += self.speed
            elif not self.turns[0]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
            elif self.turns[0]:
                self.x_pos += self.speed
        elif self.direction == 1:
            if self.target[1] > self.y_pos and self.turns[3]:
                self.direction = 3
            elif self.target[0] < self.x_pos and self.turns[1]:
                self.x_pos -= self.speed
            elif not self.turns[1]:
                if self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[1]:
                self.x_pos -= self.speed
        elif self.direction == 2:
            if self.target[0] < self.x_pos and self.turns[1]:
                self.direction = 1
                self.x_pos -= self.speed
            elif self.target[1] < self.y_pos and self.turns[2]:
                self.direction = 2
                self.y_pos -= self.speed
            elif not self.turns[2]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] > self.y_pos and self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[3]:
                    self.direction = 3
                    self.y_pos += self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[2]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                else:
                    self.y_pos -= self.speed
        elif self.direction == 3:
            if self.target[1] > self.y_pos and self.turns[3]:
                self.y_pos += self.speed
            elif not self.turns[3]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.target[1] < self.y_pos and self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[2]:
                    self.direction = 2
                    self.y_pos -= self.speed
                elif self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                elif self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
            elif self.turns[3]:
                if self.target[0] > self.x_pos and self.turns[0]:
                    self.direction = 0
                    self.x_pos += self.speed
                elif self.target[0] < self.x_pos and self.turns[1]:
                    self.direction = 1
                    self.x_pos -= self.speed
                else:
                    self.y_pos += self.speed
        if self.x_pos < -30:
            self.x_pos = 900
        elif self.x_pos > 900:
            self.x_pos - 30
        return self.x_pos, self.y_pos, self.direction
def draw_texts():

    score_text = font.render(f'Score: {score}', True, 'white')
    screen.blit(score_text, (30,310))
    pygame.draw.circle(screen, 'blue', (140, 930), 15)
    for i in range(lives):
        screen.blit(pygame.transform.scale(player_images[0], (15, 15)), (40 + i * 40, 360))
    if game_over:
        pygame.draw.rect(screen, 'white', [50, 200, 800, 300],0, 10)
        pygame.draw.rect(screen, 'black', [70, 220, 760, 260], 0, 10)
        gameover_text = font.render('Game over! Space bar to restart!', True, 'red')
        screen.blit(gameover_text, (100, 300))
    if game_won:
        pygame.draw.rect(screen, 'white', [50, 200, 800, 300],0, 10)
        pygame.draw.rect(screen, 'black', [70, 220, 760, 260], 0, 10)
        gameover_text = font.render('Victory! Space bar to CONTINUE!', True, 'green')
        screen.blit(gameover_text, (100, 300))
def check_collisions(scor, power, power_count, eaten_ghosts):
    num1 = (Inaltime - 50) // 32
    num2 = Latime // 30
    if 0 < player_x < 870:
        if level[center_y // num1][center_x // num2] == 1 or  level[center_y // num1][center_x // num2] == 11:
            level[center_y // num1][center_x // num2] = 0
            scor += 10
        if level[center_y // num1][center_x // num2] == 2:
            level[center_y // num1][center_x // num2] = 0
            scor += 50
            power = True
            power_count = 0
            eaten_ghosts = [False, False, False, False]
    return scor, power, power_count, eaten_ghosts
def draw_board():
    num1 = ((Inaltime - 50) // 32)
    num2 = (Latime // 30)
    for i in range(len(level)):
        for j in range(len(level[i])):
            if level[i][j] == 1 or level[i][j]==11:
                pygame.draw.circle(screen, 'white', (j * num2 + (0.5 * num2), i * num1 + (0.5 * num1)), 4)
            if level[i][j] == 2 and not flicker:
                pygame.draw.circle(screen, 'green', (j * num2 + (0.5 * num2), i * num1 + (0.5 * num1)), 10)
            if level[i][j] == 3:
                pygame.draw.line(screen, color, (j * num2 + (0.5 * num2), i * num1),
                                 (j * num2 + (0.5 * num2), i * num1 + num1), 3)
            if level[i][j] == 4:
                pygame.draw.line(screen, color, (j * num2, i * num1 + (0.5 * num1)),
                                 (j * num2 + num2, i * num1 + (0.5 * num1)), 3)
            if level[i][j] == 5:
                pygame.draw.arc(screen, color, [(j * num2 - (num2 * 0.4)) - 2, (i * num1 + (0.5 * num1)), num2, num1],
                                0, PI / 2, 3)
            if level[i][j] == 6:
                pygame.draw.arc(screen, color,
                                [(j * num2 + (num2 * 0.5)), (i * num1 + (0.5 * num1)), num2, num1], PI / 2, PI, 3)
            if level[i][j] == 7:
                pygame.draw.arc(screen, color, [(j * num2 + (num2 * 0.5)), (i * num1 - (0.4 * num1)), num2, num1], PI,
                                3 * PI / 2, 3)
            if level[i][j] == 8:
                pygame.draw.arc(screen, color,
                                [(j * num2 - (num2 * 0.4)) - 2, (i * num1 - (0.4 * num1)), num2, num1], 3 * PI / 2,
                                2 * PI, 3)
            if level[i][j] == 9:
                pygame.draw.line(screen, 'white', (j * num2, i * num1 + (0.5 * num1)),
                                 (j * num2 + num2, i * num1 + (0.5 * num1)), 3)
def draw_player():
    # 0-DREAPTA, 1-STANGA, 2-SUS, 3-JOS
    if direction == 0:
        screen.blit(player_images[counter // 5], (player_x, player_y))
    elif direction == 1:
        screen.blit(pygame.transform.flip(player_images[counter // 5], True, False), (player_x, player_y))
    elif direction == 2:
        screen.blit(pygame.transform.rotate(player_images[counter // 5], 90), (player_x, player_y))
    elif direction == 3:
        screen.blit(pygame.transform.rotate(player_images[counter // 5], 270), (player_x, player_y))
def check_position(centerx, centery):
    turns = [False, False, False, False]
    num1 = (Inaltime - 50) // 32
    num2 = (Latime // 30)
    num3 = 15
    # pe baza lui center x si center y folosing si factorul de diferenta- num3==15, dintre centru si raza characterului
    if centerx // 30 < 29:
        if direction == 0:
            if level[centery // num1][(centerx - num3) // num2] < 3 or level[centery // num1][(centerx - num3) // num2] ==11:
                turns[1] = True
        if direction == 1:
            if level[centery // num1][(centerx + num3) // num2] < 3 or level[centery // num1][(centerx + num3) // num2]==11:
                turns[0] = True
        if direction == 2:
            if level[(centery + num3) // num1][centerx // num2] < 3 or level[(centery + num3) // num1][centerx // num2] ==11:
                turns[3] = True
        if direction == 3:
            if level[(centery - num3) // num1][centerx // num2] < 3 or level[(centery - num3) // num1][centerx // num2] ==11:
                turns[2] = True

        if direction == 2 or direction == 3:
            if 12 <= centerx % num2 <= 18:
                if level[(centery + num3) // num1][centerx // num2] < 3  or level[(centery + num3) // num1][centerx // num2]==11:
                    turns[3] = True
                if level[(centery - num3) // num1][centerx // num2] < 3 or  level[(centery - num3) // num1][centerx // num2]==11:
                    turns[2] = True
            if 12 <= centery % num1 <= 18:
                if level[centery // num1][(centerx - num2) // num2] < 3 or level[centery // num1][(centerx - num2) // num2]==11:
                    turns[1] = True
                if level[centery // num1][(centerx + num2) // num2] < 3 or level[centery // num1][(centerx + num2) // num2]==11:
                    turns[0] = True
        if direction == 0 or direction == 1:
            if 12 <= centerx % num2 <= 18:
                if level[(centery + num1) // num1][centerx // num2] < 3 or level[(centery + num1) // num1][centerx // num2] ==11:
                    turns[3] = True
                if level[(centery - num1) // num1][centerx // num2] < 3 or level[(centery - num1) // num1][centerx // num2] ==11:
                    turns[2] = True
            if 12 <= centery % num1 <= 18:
                if level[centery // num1][(centerx - num3) // num2] < 3 or level[centery // num1][(centerx - num3) // num2]==11:
                    turns[1] = True
                if level[centery // num1][(centerx + num3) // num2] < 3 or level[centery // num1][(centerx + num3) // num2] ==11:
                    turns[0] = True
    else:
        turns[0] = True
        turns[1] = True

    return turns
def move_player(play_x, play_y):
    if direction == 0 and turns_allowed[0]:
        play_x += player_speed
    elif direction == 1 and turns_allowed[1]:
        play_x -= player_speed
    if direction == 2 and turns_allowed[2]:
        play_y -= player_speed
    elif direction == 3 and turns_allowed[3]:
        play_y += player_speed
    return play_x, play_y
def get_targets(ghost1_x, ghost1_y, ghost2_x, ghost2_y, ghost4_x, ghost4_y, ghost3_x, ghost3_y):
    if player_x < 450:
        runaway_x = 900
    else:
        runaway_x = 0
    if player_y < 450:
        runaway_y = 900
    else:
        runaway_y = 0
    return_target = (380, 400)
    if powerup:
        if not ghost1.dead and not eaten_ghost[0]:
            ghost1_target = (runaway_x, runaway_y)
        elif not ghost1.dead and eaten_ghost[0]:
            if 340 < ghost1_x < 560 and 340 < ghost1_y < 500:
                ghost1_target = (400, 100)
            else:
                ghost1_target = (player_x, player_y)
        else:
            ghost1_target = return_target
        if not ghost2.dead and not eaten_ghost[1]:
            ghost2_target = (runaway_x, player_y)
        elif not ghost2.dead and eaten_ghost[1]:
            if 340 < ghost2_x < 560 and 340 < ghost2_y < 500:
                ghost2_target = (400, 100)
            else:
                ghost2_target = (player_x, player_y)
        else:
            ghost2_target = return_target
        if not ghost4.dead:
            ghost4_target = (player_x, runaway_y)
        elif not ghost4.dead and eaten_ghost[2]:
            if 340 < ghost4_x < 560 and 340 < ghost4_y < 500:
                ghost4_target = (400, 100)
            else:
                ghost4_target = (player_x, player_y)
        else:
            ghost4_target = return_target
        if not ghost3.dead and not eaten_ghost[3]:
            ghost3_target = (450, 450)
        elif not ghost3.dead and eaten_ghost[3]:
            if 340 < ghost3_x < 560 and 340 < ghost3_y < 500:
                ghost3_target = (400, 100)
            else:
                ghost3_target = (player_x, player_y)
        else:
            ghost3_target = return_target
    else:
        if not ghost1.dead:
            if 340 < ghost1_x < 560 and 340 < ghost1_y < 500:
                ghost1_target = (400, 100)
            else:
                ghost1_target = (player_x, player_y)
        else:
            ghost1_target = return_target
        if not ghost2.dead:
            if 340 < ghost2_x < 560 and 340 < ghost2_y < 500:
                ghost2_target = (400, 100)
            else:
                ghost2_target = (player_x, player_y)
        else:
            ghost2_target = return_target
        if not ghost4.dead:
            if 340 < ghost4_x < 560 and 340 < ghost4_y < 500:
                ghost4_target = (400, 100)
            else:
                ghost4_target = (player_x, player_y)
        else:
            ghost4_target = return_target
        if not ghost3.dead:
            if 340 < ghost3_x < 560 and 340 < ghost3_y < 500:
                ghost3_target = (400, 100)
            else:
                ghost3_target = (player_x, player_y)
        else:
            ghost3_target = return_target
    return [ghost1_target, ghost2_target, ghost4_target, ghost3_target]



menu_state = "main"
buttons_color = (255, 255, 255)
#load button images
resume_img = pygame.image.load("assets/buttons/button_resume.png").convert_alpha()
quit_img = pygame.image.load("assets/buttons/button_quit.png").convert_alpha()


#create button instances
resume_button = button.Button(300, 300, resume_img, 1)
quit_button = button.Button(330, 500, quit_img, 1)


def draw_text(text, font, text_col, x, y):
  img = font.render(text, True, text_col)
  screen.blit(img, (x, y))




run = True
while run:
    if paused == False:
        timer.tick(fps)
        if counter < 19:
            counter += 1
            if counter > 3:
                flicker = False
        else:
            counter = 0
            flicker = True
        if powerup and power_counter < 600:
            power_counter += 1
        elif powerup and power_counter >= 600:
            power_counter = 0
            powerup = False
            eaten_ghost = [False, False, False, False]
        if startup_counter < 180 and not game_over and not game_won:
            moving = False
            startup_counter += 1
        else:
            moving = True

        screen.fill('black')
        draw_board()
        center_x = player_x + 23
        center_y = player_y + 24

        if powerup:
            ghost_speeds = [1, 1, 1, 1]
        else:
            ghost_speeds = [2, 2, 2, 2]
        if eaten_ghost[0]:
            ghost_speeds[0] = 2
        if eaten_ghost[1]:
            ghost_speeds[1] = 2
        if eaten_ghost[2]:
            ghost_speeds[2] = 2
        if eaten_ghost[3]:
            ghost_speeds[3] = 2
        if ghost1_dead:
            ghost_speeds[0] = 4
        if ghost2_dead:
            ghost_speeds[1] = 4
        if ghost4_dead:
            ghost_speeds[2] = 4
        if ghost3_dead:
            ghost_speeds[3] = 4

        game_won = True
        for i in range(len(level)):
            if 1 in level[i] or 2 in level[i]:
                game_won = False

        player_circle = pygame.draw.circle(screen, 'black', (center_x, center_y), 20, 2)
        draw_player()

        ghost1 = Ghost(ghost1_x, ghost1_y, targets[0], ghost_speeds[0], ghost1_img, ghost1_direction, ghost1_dead,
                       ghost1_box, 0)
        ghost2 = Ghost(ghost2_x, ghost2_y, targets[1], ghost_speeds[1], ghost2_img, ghost2_direction, ghost2_dead,
                     ghost2_box, 1)
        ghost4 = Ghost(ghost4_x, ghost4_y, targets[2], ghost_speeds[2], ghost4_img, ghost4_direction, ghost4_dead,
                      ghost4_box, 2)
        ghost3 = Ghost(ghost3_x, ghost3_y, targets[3], ghost_speeds[3], ghost3_img, ghost3_direction, ghost3_dead,
                      ghost3_box, 3)
        draw_texts()
        targets = get_targets(ghost1_x, ghost1_y, ghost2_x, ghost2_y, ghost4_x, ghost4_y, ghost3_x, ghost3_y)

        turns_allowed = check_position(center_x, center_y)
        if moving:
            player_x, player_y = move_player(player_x, player_y)
            if not ghost1_dead and not ghost1.in_box:
                ghost1_x, ghost1_y, ghost1_direction = ghost1.move_ghost1()
            else:
                ghost1_x, ghost1_y, ghost1_direction = ghost1.move_ghost3()
            if not ghost4_dead and not ghost4.in_box:
                ghost4_x, ghost4_y, ghost4_direction = ghost4.move_ghost4()
            else:
                ghost4_x, ghost4_y, ghost4_direction = ghost4.move_ghost3()
            if not ghost2_dead and not ghost2.in_box:
                ghost2_x, ghost2_y, ghost2_direction = ghost2.move_ghost2()
            else:
                ghost2_x, ghost2_y, ghost2_direction = ghost2.move_ghost3()
            ghost3_x, ghost3_y, ghost3_direction = ghost3.move_ghost3()
        score, powerup, power_counter, eaten_ghost = check_collisions(score, powerup, power_counter, eaten_ghost)
        # add to if not powerup to check if eaten ghosts
        if not powerup:
            if (player_circle.colliderect(ghost1.rect) and not ghost1.dead) or \
                    (player_circle.colliderect(ghost2.rect) and not ghost2.dead) or \
                    (player_circle.colliderect(ghost4.rect) and not ghost4.dead) or \
                    (player_circle.colliderect(ghost3.rect) and not ghost3.dead):
                if lives > 0:
                    lives -= 1
                    startup_counter = 0
                    powerup = False
                    power_counter = 0
                    player_x = 450
                    player_y = 663
                    direction = 0
                    direction_command = 0
                    ghost1_x = 200
                    ghost1_y = 200
                    ghost1_direction = 0
                    ghost2_x = 410
                    ghost2_y = 388
                    ghost2_direction = 2
                    ghost4_x = 400
                    ghost4_y = 420
                    ghost4_direction = 2
                    ghost3_x = 440
                    ghost3_y = 438
                    ghost3_direction = 2
                    eaten_ghost = [False, False, False, False]
                    ghost1_dead = False
                    ghost2_dead = False
                    ghost3_dead = False
                    ghost4_dead = False
                else:
                    game_over = True
                    moving = False
                    startup_counter = 0
        if powerup and player_circle.colliderect(ghost1.rect) and eaten_ghost[0] and not ghost1.dead:
            if lives > 0:
                powerup = False
                power_counter = 0
                lives -= 1
                startup_counter = 0
                player_x = 450
                player_y = 663
                direction = 0
                direction_command = 0
                ghost1_x = 200
                ghost1_y = 200
                ghost1_direction = 0
                ghost2_x = 410
                ghost2_y = 388
                ghost2_direction = 2
                ghost4_x = 420
                ghost4_y = 400
                ghost4_direction = 2
                ghost3_x = 440
                ghost3_y = 438
                ghost3_direction = 2
                eaten_ghost = [False, False, False, False]
                ghost1_dead = False
                ghost2_dead = False
                ghost3_dead = False
                ghost4_dead = False
            else:
                game_over = True
                moving = False
                startup_counter = 0
        if powerup and player_circle.colliderect(ghost2.rect) and eaten_ghost[1] and not ghost2.dead:
            if lives > 0:
                powerup = False
                power_counter = 0
                lives -= 1
                startup_counter = 0
                player_x = 450
                player_y = 663
                direction = 0
                direction_command = 0
                ghost1_x = 200
                ghost1_y = 200
                ghost1_direction = 0
                ghost2_x = 440
                ghost2_y = 388
                ghost2_direction = 2
                ghost4_x = 420
                ghost4_y = 400
                ghost4_direction = 2
                ghost3_x = 440
                ghost3_y = 438
                ghost3_direction = 2
                eaten_ghost = [False, False, False, False]
                ghost1_dead = False
                ghost2_dead = False
                ghost3_dead = False
                ghost4_dead = False
            else:
                game_over = True
                moving = False
                startup_counter = 0
        if powerup and player_circle.colliderect(ghost4.rect) and eaten_ghost[2] and not ghost4.dead:
            if lives > 0:
                powerup = False
                power_counter = 0
                lives -= 1
                startup_counter = 0
                player_x = 450
                player_y = 663
                direction = 0
                direction_command = 0
                ghost1_x = 200
                ghost1_y = 200
                ghost1_direction = 0
                ghost2_x = 400
                ghost2_y = 388
                ghost2_direction = 2
                ghost4_x = 440
                ghost4_y = 400
                ghost4_direction = 2
                ghost3_x = 420
                ghost3_y = 430
                ghost3_direction = 2
                eaten_ghost = [False, False, False, False]
                ghost1_dead = False
                ghost2_dead = False
                ghost3_dead = False
                ghost4_dead = False
            else:
                game_over = True
                moving = False
                startup_counter = 0
        if powerup and player_circle.colliderect(ghost3.rect) and eaten_ghost[3] and not ghost3.dead:
            if lives > 0:
                powerup = False
                power_counter = 0
                lives -= 1
                startup_counter = 0
                player_x = 450
                player_y = 663
                direction = 0
                direction_command = 0
                ghost1_x = 200
                ghost1_y = 200
                ghost1_direction = 0
                ghost2_x = 430
                ghost2_y = 388
                ghost2_direction = 2
                ghost4_x = 420
                ghost4_y = 400
                ghost4_direction = 2
                ghost3_x = 440
                ghost3_y = 438
                ghost3_direction = 2
                eaten_ghost = [False, False, False, False]
                ghost1_dead = False
                ghost2_dead = False
                ghost3_dead = False
                ghost4_dead = False
            else:
                game_over = True
                moving = False
                startup_counter = 0
        if powerup and player_circle.colliderect(ghost1.rect) and not ghost1.dead and not eaten_ghost[0]:
            ghost1_dead = True
            eaten_ghost[0] = True
            score += (2 ** eaten_ghost.count(True)) * 100
        if powerup and player_circle.colliderect(ghost2.rect) and not ghost2.dead and not eaten_ghost[1]:
            ghost2_dead = True
            eaten_ghost[1] = True
            score += (2 ** eaten_ghost.count(True)) * 100
        if powerup and player_circle.colliderect(ghost4.rect) and not ghost4.dead and not eaten_ghost[2]:
            ghost4_dead = True
            eaten_ghost[2] = True
            score += (2 ** eaten_ghost.count(True)) * 100
        if powerup and player_circle.colliderect(ghost3.rect) and not ghost3.dead and not eaten_ghost[3]:
            ghost3_dead = True
            eaten_ghost[3] = True
            score += (2 ** eaten_ghost.count(True)) * 100

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.KEYDOWN:
                # if event.key==pygame.K_f:
                #     screen = pygame.display.set_mode((700, 750), FULLSCREEN)
                if event.key==pygame.K_s:
                    player_speed+=1
                if event.key==pygame.K_a:
                     player_speed -= 1
                if event.key == pygame.K_RIGHT:
                    direction_command = 0
                if event.key == pygame.K_LEFT:
                    direction_command = 1
                if event.key == pygame.K_UP:
                    direction_command = 2
                if event.key == pygame.K_DOWN:
                    direction_command = 3
                if event.key == pygame.K_SPACE:
                    paused = True

                if event.key == pygame.K_SPACE and game_over:
                    powerup = False
                    power_counter = 0
                    lives -= 1
                    startup_counter = 0
                    player_x = 450
                    player_y = 663
                    direction = 0
                    direction_command = 0
                    ghost1_x = 200
                    ghost1_y = 200
                    ghost1_direction = 0
                    ghost2_x = 400
                    ghost2_y = 388
                    ghost2_direction = 2
                    ghost4_x = 440
                    ghost4_y = 408
                    ghost4_direction = 2
                    ghost3_x = 420
                    ghost3_y = 438
                    ghost3_direction = 2
                    eaten_ghost = [False, False, False, False]
                    ghost1_dead = False
                    ghost2_dead = False
                    ghost3_dead = False
                    ghost4_dead = False
                    score = 0
                    color='yellow'
                    lives = 3
                    level = copy.deepcopy(boards)
                    game_over = False
                    game_won = False
                if event.key == pygame.K_SPACE and game_won:
                 powerup = False
                 power_counter = 0
                 lives -= 1
                 startup_counter = 0
                 player_x = 450
                 player_y = 663
                 direction = 0
                 direction_command = 0
                 ghost1_x = 200
                 ghost1_y = 200
                 ghost1_direction = 0
                 ghost2_x = 440
                 ghost2_y = 388
                 ghost2_direction = 2
                 ghost4_x = 430
                 ghost4_y = 400
                 ghost4_direction = 2
                 ghost3_x = 420
                 ghost3_y = 438
                 ghost3_direction = 2
                 eaten_ghost = [False, False, False, False]
                 ghost1_dead = False
                 ghost2_dead = False
                 ghost3_dead = False
                 ghost4_dead = False
                 score = 0
                 lives = 3
                 color='red'
                 level = copy.deepcopy(boards3)
                 game_over = False
                 game_won = False

            if event.type == pygame.KEYUP:
                if event.key == pygame.K_RIGHT and direction_command == 0:
                    direction_command = direction
                if event.key == pygame.K_LEFT and direction_command == 1:
                    direction_command = direction
                if event.key == pygame.K_UP and direction_command == 2:
                    direction_command = direction
                if event.key == pygame.K_DOWN and direction_command == 3:
                    direction_command = direction

        if direction_command == 0 and turns_allowed[0]:
            direction = 0
        if direction_command == 1 and turns_allowed[1]:
            direction = 1
        if direction_command == 2 and turns_allowed[2]:
            direction = 2
        if direction_command == 3 and turns_allowed[3]:
            direction = 3

        if player_x > 900:
            player_x = -47
        elif player_x < -50:
            player_x = 897

        if ghost1.in_box and ghost1_dead:
            ghost1_dead = False
        if ghost2.in_box and ghost2_dead:
            ghost2_dead = False
        if ghost4.in_box and ghost4_dead:
            ghost4_dead = False
        if ghost3.in_box and ghost3_dead:
            ghost3_dead = False
    else:
        event=pygame.event.wait()
        screen.fill((0, 0, 0))
        if resume_button.draw(screen):
            paused = False
        if quit_button.draw(screen):
            run = False

    if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                paused = False

    pygame.display.flip()



pygame.quit()