import pathlib
import typing as tp
import random

T = tp.TypeVar("T")


def read_sudoku(path: tp.Union[str, pathlib.Path]) -> tp.List[tp.List[str]]:
    """ Прочитать Судоку из указанного файла """
    path = pathlib.Path(path)
    with path.open() as f:
        puzzle = f.read()
    return create_grid(puzzle)


def create_grid(puzzle: str) -> tp.List[tp.List[str]]:
    digits = [c for c in puzzle if c in "123456789."]
    grid = group(digits, 9)
    return grid


def display(grid: tp.List[tp.List[str]]) -> None:
    """Вывод Судоку """
    width = 2
    line = "+".join(["-" * (width * 3)] * 3)
    for row in range(9):
        print(
            "".join(
                grid[row][col].center(width) + ("|" if str(col) in "25" else "") for col in range(9)
            )
        )
        if str(row) in "25":
            print(line)
    print()


def group(values: tp.List[T], n: int) -> tp.List[tp.List[T]]:
    matrix = [values[i * n:i * n + n] for i in range(n)]
    return matrix


def get_row(grid: tp.List[tp.List[str]], pos: tp.Tuple[int, int]) -> tp.List[str]:
    return grid[pos[0]]


def get_col(grid: tp.List[tp.List[str]], pos: tp.Tuple[int, int]) -> tp.List[str]:
    return [i [pos[1]] for i in grid]

def nearest_n(x, n):
    while x % n != 0:
        x -= 1
    return x

def get_block(grid: tp.List[tp.List[str]], pos: tp.Tuple[int, int]) -> tp.List[str]:
    row, col = pos
    block_row_start = (row // 3) * 3
    block_col_start = (col // 3) * 3
    
    return [grid[r][c] for r in range(block_row_start, block_row_start + 3) for c in range(block_col_start, block_col_start + 3)]


def find_empty_positions(grid: tp.List[tp.List[str]]) -> tp.Optional[tp.Tuple[int, int]]:
    for row in range(len(grid)):
        for col in range(len(grid[row])):
            if grid[row][col] == '.':
                return (row, col)
    return None


def find_possible_values(grid: tp.List[tp.List[str]], pos: tp.Tuple[int, int]) -> tp.Set[str]:
    possible_values = set('123456789')
    possible_values -= set(get_row(grid, pos))
    possible_values -= set(get_col(grid, pos))
    possible_values -= set(get_block(grid, pos))
    return possible_values


def solve(grid: tp.List[tp.List[str]]) -> tp.Optional[tp.List[tp.List[str]]]:
    empty_pos = find_empty_positions(grid)
    if empty_pos is None:
        return grid
    row, col = empty_pos
    possible_values = find_possible_values(grid, empty_pos)
    for value in possible_values:
        grid[row][col] = value
        if solve(grid):
            return grid
        grid[row][col] = '.'
    return None

def check_solution(solution: tp.List[tp.List[str]]) -> bool:
    numbers = set('123456789')
    for row in solution:
        if set(row) != numbers:
            return False
    for col in range(9):
        if set(get_col(solution, (0, col))) != numbers:
            return False
    for row in range(0, 9, 3):
        for col in range(0, 9, 3):
            if set(get_block(solution, (row, col))) != numbers:
                return False
    return True


def generate_sudoku(N: int) -> tp.List[tp.List[str]]:
    grid = [['.' for _ in range(9)] for _ in range(9)]
    solve(grid)
    num_to_remove = 81 - N
    while num_to_remove > 0:
        row, col = random.randint(0, 8), random.randint(0, 8)
        if grid[row][col] != '.':
            grid[row][col] = '.'
            num_to_remove -= 1
    
    return grid

sudoku = generate_sudoku(40)
display(sudoku)

if __name__ == "__main__":
    for fname in ["puzzle1.txt", "puzzle2.txt", "puzzle3.txt"]:
        grid = read_sudoku(fname)
        display(grid)
        solution = solve(grid)
        if not solution:
            print(f"Puzzle {fname} can't be solved")
        else:
            display(solution)