from ant.constants import *



class ColorProcessor:
    def __init__(self, color_dict):
        self._color_dict = color_dict

    def process_colors(self, color_board):
        for r, row in enumerate(color_board):
            for c, cell in enumerate(row):
                if color_board[r][c] in self._color_dict:
                    color_board[r][c] = self._color_dict[cell]


class ScreenColorProcessor(ColorProcessor):
    def __init__(self):
        super().__init__(SCREEN_COLOR_DICT)

class LEDColorProcessor(ColorProcessor):
    def __init__(self):
        super().__init__(LED_COLOR_DICT)
