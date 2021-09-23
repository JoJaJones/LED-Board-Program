class ShapeConverter:
    def __init__(self, num_of_displays, num_of_rows, num_of_cols, display_config):
        pass

    def convert_shape(self, board):
        raise NotImplementedError


class BasicShapeConverter(ShapeConverter):
    def __init__(self, num_rows, num_cols):
        super().__init__(1, num_rows, num_cols, [])


    def convert_shape(self, board):
        copy = [row[:] for row in board]

        for r, row in enumerate(copy):
            for c, col in enumerate(row):
                copy[r][c] = col.get_color()

        return copy


class LEDShapeConverter(ShapeConverter):
    def __init__(self, num_of_displays, num_of_rows, num_of_cols, display_config):
        super().__init__(num_of_displays, num_of_rows, num_of_cols, display_config)
