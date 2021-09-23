from constants import NUM_ROWS, NUM_COLS, CHAIN_LEN

class ArrayManipulator(object):
    def __init__(self):
        self._array = []
        for r in range(NUM_ROWS):
            self._array.append([])
            for _ in range(NUM_COLS*CHAIN_LEN):
                self._array[r].append(0)

    def get_canvas(self):
        return self._array

    def process_frame(self):
        pass
