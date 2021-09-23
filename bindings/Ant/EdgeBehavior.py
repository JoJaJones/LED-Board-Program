from ant.constants import *
from ant.MoveBehavior import MoveBehavior
from random import choice, randint


class EdgeBehavior:
    def __init__(self, turn_bx, move_bx, num_row, num_col):
        self._move_bx = move_bx
        self._turn_bx = turn_bx
        self._num_row = num_row
        self._num_col = num_col

    def is_edge(self, cur_pos, direction):
        next_pos = self._move_bx(cur_pos, direction)
        for i in range(2):
            if next_pos[i] < 0 or next_pos[i] >= SIZE_OF_BOARD:
                return True

        return False

    def adjust_pos(self, next_pos):
        n_row, n_col = next_pos
        n_row = max(min(n_row, SIZE_OF_BOARD - 1), 0)
        n_col = max(min(n_col, SIZE_OF_BOARD - 1), 0)
        return n_row, n_col

    def handle_edge(self, cur_pos, direction, pos_color):
        raise NotImplementedError


class TeleportEdgeBx(EdgeBehavior):
    def handle_edge(self, cur_pos, direction, pos_color):
        e_row, e_col = self._move_bx.move(cur_pos, direction)
        e_row += self._num_row
        e_col += self._num_col
        e_row %= self._num_row
        e_col %= self._num_col

        return (e_row, e_col), direction


class Wall(EdgeBehavior):
    def handle_edge(self, cur_pos, direction, pos_color):
        cur_pos = self.adjust_pos(self._move_bx.move(cur_pos, direction))
        in_corner = True

        while in_corner:
            next_dir = self._turn_bx.turn(pos_color, direction)
            in_corner = self.is_edge(cur_pos, next_dir)


class UTurn(Wall):  # TODO FIXME
    def handle_edge(self, cur_pos, direction, pos_color):
        cur_dir = DIRECTIONS.index(direction)
        cur_dir += len(DIRECTIONS) // 2
        cur_dir %= len(DIRECTIONS)

        return cur_pos, DIRECTIONS[cur_dir]


class RandomTeleport(EdgeBehavior):
    def handle_edge(self, cur_pos, direction, pos_color):
        return (randint(0, self._num_row), randint(0, self._num_col)), direction

class Death(EdgeBehavior):
    def __init__(self, turn_bx, move_bx, num_row, num_col, death_type):
        super().__init__(turn_bx, move_bx, num_row, num_col)
        self._type = death_type

    def handle_edge(self, cur_pos, direction, pos_color):
        if self._type == "R":
            return None
        elif self._type == "E":
            self.adjust_pos(self._move_bx.move(cur_pos, direction))

        self._move_bx.set_move_dist()


