import pathlib
import random
import typing as tp

import pygame
from pygame.locals import *

Cell = tp.Tuple[int, int]
Cells = tp.List[int]
Grid = tp.List[Cells]


class GameOfLife:
    def __init__(
        self,
        size: tp.Tuple[int, int],
        randomize: bool = True,
        max_generations: tp.Optional[float] = float("inf"),
    ) -> None:
        # Размер клеточного поля
        self.rows, self.cols = size
        # Предыдущее поколение клеток
        self.prev_generation = self.create_grid()
        # Текущее поколение клеток
        self.curr_generation = self.create_grid(randomize=randomize)
        # Максимальное число поколений
        self.max_generations = max_generations
        # Текущее число поколений
        self.generations = 1

    def create_grid(self, randomize: bool = False) -> Grid:
        grid = [
            [random.randint(0, 1) if randomize else 0 for _ in range(self.cols)]
            for _ in range(self.rows)
        ]
        return grid

    def get_neighbours(self, cell: Cell) -> Cells:
        row, col = cell
        neighbours = []
        
        for i in range(max(0, row - 1), min(self.rows, row + 2)):
            for j in range(max(0, col - 1), min(self.cols, col + 2)):
                if (i, j) != (row, col):
                    neighbours.append(self.curr_generation[i][j])

        return neighbours

    def get_next_generation(self) -> Grid:
        new_generation = self.create_grid()

        for row in range(self.rows):
            for col in range(self.cols):
                alive_neighbours = sum(self.get_neighbours((row, col)))

                if self.curr_generation[row][col] == 1:
                    new_generation[row][col] = 1 if alive_neighbours in [2, 3] else 0
                else:
                    new_generation[row][col] = 1 if alive_neighbours == 3 else 0

        return new_generation

    def step(self) -> None:
        self.prev_generation = self.curr_generation
        self.curr_generation = self.get_next_generation()
        self.generations += 1

    @property
    def is_max_generations_exceeded(self) -> bool:
        return self.generations >= self.max_generations

    @property
    def is_changing(self) -> bool:
        return self.curr_generation != self.prev_generation
    @staticmethod
    def from_file(filename: pathlib.Path) -> "GameOfLife":
        with open(filename, "r") as file:
            grid = [
                [int(char) for char in line.strip()]
                for line in file.readlines()
            ]
        size = (len(grid), len(grid[0])) if grid else (0, 0)
        game = GameOfLife(size, randomize=False)
        game.curr_generation = grid
        return game

    def save(self, filename: pathlib.Path) -> None:
        with open(filename, "w") as file:
            for row in self.curr_generation:
                file.write("".join(map(str, row)) + "\n")
