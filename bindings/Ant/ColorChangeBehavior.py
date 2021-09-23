class ColorChangeBehavior:
    def __init__(self, colors: list = ["white", "black"], direction: int = 1):  # TODO potential problems with this setup
        self._color_list = colors
        self._color_shift = direction

    def handle_swap(self, cur_color):
        color = self._color_list.index(cur_color)
        color = (color + self._color_shift + len(self._color_list)) % len(self._color_list)
        return self._color_list[color]
