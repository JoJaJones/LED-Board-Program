from ant.constants import DIRECTIONS

class TurnBehavior:
    def __init__(self, turn_type = 1, num_colors = 2, color_list = ["white", "black"]):
        self._num_colors = num_colors
        self._turn_type = turn_type
        #load dir converter
        self._dir_converter = {}
        #color_to_num converter
        self._color_num_converter = {}
        #create color color_converter
        self._color_convert = {}
        self.create_converters(color_list)
        self.load_dir_convert()

    def turn(self, color: str, direction: str):
        cur_dir = self._dir_converter[direction]
        cur_color = self._color_num_converter[color]
        dir_change = self._color_convert[cur_color]

        cur_dir += dir_change + len(DIRECTIONS)
        cur_dir %= len(DIRECTIONS)

        return self._dir_converter[cur_dir]

    def create_converters(self, color_list):
        dir_shift = self._turn_type
        for i in range(self._num_colors):
            self._color_convert[i] = dir_shift
            dir_shift = -dir_shift
            if i & 1:
                dir_shift += 1

        for idx, color in enumerate(color_list):
            self._color_num_converter[color] = idx


    def load_dir_convert(self):
        for i in range(len(DIRECTIONS)):
            self._dir_converter[i] = DIRECTIONS[i]
            self._dir_converter[DIRECTIONS[i]] = i
