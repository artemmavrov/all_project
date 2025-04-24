import random
import typing as tp

import pygame
from pygame.locals import *

Cell = tp.Tuple[int, int]
Cells = tp.List[int]
Grid = tp.List[Cells]


class GameOfLife:
    def __init__(
        self, width: int = 640, height: int = 480, cell_size: int = 10, speed: int = 10
    ) -> None:
        self.width = width
        self.height = height
        self.cell_size = cell_size

        # Устанавливаем размер окна
        self.screen_size = width, height
        # Создание нового окна
        self.screen = pygame.display.set_mode(self.screen_size)

        # Вычисляем количество ячеек по вертикали и горизонтали
        self.cell_width = self.width // self.cell_size
        self.cell_height = self.height // self.cell_size

        # Скорость протекания игры
        self.speed = speed

    def draw_lines(self) -> None:
        """ Отрисовать сетку """
        for x in range(0, self.width, self.cell_size):
            pygame.draw.line(self.screen, pygame.Color("black"), (x, 0), (x, self.height))
        for y in range(0, self.height, self.cell_size):
            pygame.draw.line(self.screen, pygame.Color("black"), (0, y), (self.width, y))

    def run(self) -> None:
        """ Запустить игру """
        pygame.init()
        clock = pygame.time.Clock()
        pygame.display.set_caption("Game of Life")
        self.screen.fill(pygame.Color("white"))

        # Создание списка клеток
        # PUT YOUR CODE HERE

        running = True
        while running:
            for event in pygame.event.get():
                if event.type == QUIT:
                    running = False
            self.draw_lines()

            # Отрисовка списка клеток
            # Выполнение одного шага игры (обновление состояния ячеек)
            # PUT YOUR CODE HERE

            pygame.display.flip()
            clock.tick(self.speed)
        pygame.quit()

    def create_grid(self, randomize: bool = False) -> Grid:
        grid = []
        if randomize:
            for i in range(self.cell_height):
                row = []
                for j in range(self.cell_width):
                    row.append(random.randint(0, 1))
                grid.append(row)
        else:
            grid = [[0 for i in range(self.cell_height)] for j in range(self.cell_width)]
        return grid   
    
    def draw_grid(self, screen) -> None:
        black = (0, 0, 0)
        white = (255, 255, 255)
        blue = (0, 0, 255)

        for row in range(self.rows):
            for col in range(self.cols):
                rect = pygame.Rect(col * self.cell_size, row * self.cell_size, self.cell_size, self.cell_size)
                if self.matrix[row][col]:
                    pygame.draw.rect(screen, blue, rect)
                else:
                    pygame.draw.rect(screen, white, rect)
                pygame.draw.rect(screen, black, rect, 1)

    def get_neighbours(self, cell: Cell) -> Cells:
        row, col = cell
        neighbours = []

        for i in range(row - 1, row + 2):
            for j in range(col - 1, col + 2):
                if (0 <= i < self.cell_height and 0 <= j < self.cell_width) and (i, j) != (row, col):
                    neighbours.append(self.grid[i][j])  

        return neighbours
        

    def get_next_generation(self) -> Grid:
        new_grid = [[0 for _ in range(self.cell_width)] for _ in range(self.cell_height)]
        
        for row in range(self.cell_height):
            for col in range(self.cell_width):
                cell = (row, col)
                neighbours = self.get_neighbours(cell)
                alive_neighbours = sum(neighbours) 

                if self.grid[row][col] == 1:
                    if alive_neighbours < 2 or alive_neighbours > 3:
                        new_grid[row][col] = 0 
                    else:
                        new_grid[row][col] = 1 
                else:
                    if alive_neighbours == 3:
                        new_grid[row][col] = 1 

        return new_grid