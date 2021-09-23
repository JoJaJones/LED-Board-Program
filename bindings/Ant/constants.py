UP = "UP"
RIGHT = "RIGHT"
DOWN = "DOWN"
LEFT = "LEFT"

SIZE_OF_BOARD = 32
NUM_ROWS = 32
NUM_COLS = 32

DIRECTIONS = [UP, RIGHT, DOWN, LEFT]

DIR_DICT = {UP: (-1, 0), DOWN: (1, 0), LEFT: (0, -1), RIGHT: (0, 1)}

ALIVE = "alive"
DEAD = "dead"
NEW = "new"

SCREEN_COLOR_DICT = {"white": 40, "red": 41, "green": 42, "blue": 44, "purple": 45, "teal": 46,
                     "dark gray": 100, "light red": 101, "yellow": 103,
                     "cyan": 106, "black": 107}

LED_COLOR_DICT = {"white": 0xff4635, "black": 0x0, "red": 0xFF0000, "green": 0xFF00, "blue": 0x5a35ff}


DESIGN_DICT = {1: ["cyclic flower"], 2: ["star"], 3: ["flower"]}