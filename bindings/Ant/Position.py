from ant.ColorChangeBehavior import ColorChangeBehavior
from ant.Ant import Ant
from ant.constants import *


class Position:
    def __init__(self, color="black", ant_color="blue", swap_rule = ColorChangeBehavior()):
        self.color = color
        self.first_change = True
        self.second_visit = False
        self.first_color = "white"
        self.ant_color = ant_color
        self.old_ants = []
        self.new_ants = []
        self.dead_ants = []
        self.color_swapper = swap_rule

    def add_ant(self, ant: Ant, which_list: str = ALIVE):
        if which_list == DEAD:
            self.dead_ants.append(ant)
        elif which_list == NEW:
            self.new_ants.append(ant)
        else:
            self.old_ants.append(ant)

    def move_ant(self):
        cur_ant = self.old_ants[0]
        self.old_ants = self.old_ants[1:]
        move_res = cur_ant.move_ant(self.color)
        if move_res is not None:
            return cur_ant

        return None

    def is_occupied(self):
        return len(self.old_ants) > 0

    def change_color(self):
        self.color = self.color_swapper.handle_swap(self.color)

    def finalize_pos(self):
        self.old_ants = self.new_ants
        self.new_ants = []

    def get_color(self, for_display: bool = True): # todo (first change color)
        if len(self.old_ants) + len(self.dead_ants) > 0 and for_display:
            # if self.second_visit:
            #     self.second_visit = False
            return self.ant_color
        else:
            # if for_display and self.first_change and self.color != "black":
            #     self.first_change = False
            #     self.second_visit = True
            #     return self.first_color
            # elif for_display and self.second_visit:
            #     return self.first_color
            return self.color
