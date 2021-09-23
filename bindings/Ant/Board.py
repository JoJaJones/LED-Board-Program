from ant.Ant import Ant
from ant.Position import Position
from ant.constants import *

class Board:
    def __init__(self, ant_list: list = None):
        self.occupied_pos = set()
        self.positions = []

        self.init_board()

        if ant_list is not None:
            for ant in ant_list:
                self.add_ant(ant)

    def move_all_ants(self):
        new_pos = set()
        for pos in self.occupied_pos:
            r, c = pos
            self.positions[r][c].change_color()

        for pos in self.occupied_pos:
            r, c = pos
            while self.positions[r][c].is_occupied():
                ant = self.positions[r][c].move_ant()
                if ant is not None:
                    ant_r, ant_c = ant.get_pos()
                    if ant.is_dead():
                        self.positions[ant_r][ant_c].add_ant(ant, DEAD)
                    else:
                        ant.change_direction(self.positions[ant_r][ant_c].get_color(False))
                        self.positions[ant_r][ant_c].add_ant(ant, NEW)
                        new_pos.add((ant_r, ant_c))

        for pos in new_pos:
            r, c = pos
            self.positions[r][c].finalize_pos()

        self.occupied_pos = new_pos

    def init_board(self):
        for r in range(NUM_ROWS):
            self.positions.append([])

            for c in range(NUM_COLS):
                self.positions[r].append(Position())

    def add_ant(self, ant: Ant):
        r, c = pos = ant.get_pos()
        self.positions[r][c].add_ant(ant)
        self.occupied_pos.add(pos)

    def get_positions(self):
        return self.positions

