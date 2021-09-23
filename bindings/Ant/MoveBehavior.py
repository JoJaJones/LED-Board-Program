from ant.constants import *


class MoveBehavior:
    def __init__(self, distance):
        self._move_distance = distance

    def move(self, cur_pos, direction):
        s_row, s_col = cur_pos
        e_row = s_row + self._move_distance * DIR_DICT[direction][0]
        e_col = s_col + self._move_distance * DIR_DICT[direction][1]
        return e_row, e_col

    def set_move_dist(self, new_move_distance: int = 0):
        self._move_distance = new_move_distance

    def get_move_dist(self):
        return self._move_distance

    def get_move_distance(self):
        return self._move_distance