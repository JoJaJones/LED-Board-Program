class Display:
    def __init__(self, board, num_of_displays, display_config, color_dict, display_adaptor):
        self._num_of_displays = num_of_displays
        self._color_processor = ColorProcessor(color_dict)
        self._shape_converter = ShapeConverter(num_of_displays, len(board), len(board[0]), display_config)
        self._color_transmitter = ColorTransmitter(display_adaptor)
