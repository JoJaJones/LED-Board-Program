from ant.constants import *
from ant.Display import LEDDisplay
from ant.Ant import Ant
from ant.Board import Board
from ArrayManipulator import ArrayManipulator

class AntDisplay(ArrayManipulator):
    def __init__(self):
        super(AntDisplay, self).__init__()
        self.test_board = Board()
        self.test_board.add_ant(Ant(pos=(16, 16), direction=UP))
        self.displayObj = LEDDisplay(self.test_board.get_positions())

    def process_frame(self):
        for r, row in enumerate(self.displayObj.render(self.test_board.get_positions())):
            for c, col in enumerate(row):
                self._array[r][c] = col
        self.test_board.move_all_ants()

        return True

