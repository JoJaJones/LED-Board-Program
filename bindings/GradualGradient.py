from ArrayManipulator import ArrayManipulator
from constants import NUM_ROWS, NUM_COLS, CHAIN_LEN

class GradualGradient(ArrayManipulator):
    def __init__(self):
        super(GradualGradient, self).__init__()
        self._array[0][0] = 0xffffff

        self.cur_x = 1
        self.cur_y = 0
        self._shifts = [16, 8, 0]
        self._shift_idxs = [0, 1]

    def reset_array(self):
        for row in range(len(self._array)):
            for col in range(len(self._array[row])):
                self._array[row][col] = 0

        self._array[0][0] = 0xffffff

        self.cur_x = 0
        self.cur_y = 0

    def process_frame(self):
        y = self.cur_y
        x = self.cur_x

        if y == 0:
            prev = self._array[y][x-1]

            self._array[y][x] = prev - ((0xff//(NUM_COLS*CHAIN_LEN))<<self._shifts[self._shift_idxs[0]])
 
        elif y < NUM_ROWS:
            prev = self._array[y-1][x]

            self._array[y][x] = prev - ((0xff//NUM_ROWS)<<self._shifts[self._shift_idxs[1]])
        else:
            self.reset_array()
            prev = self._array[0][0]
            for idx in range(len(self._shift_idxs)):
                self._shift_idxs[idx] += 1
                self._shift_idxs[idx] %= len(self._shifts)
        
                
        self.cur_x += 1
        if self.cur_x == NUM_COLS * CHAIN_LEN:
            self.cur_x = 0
            self.cur_y += 1

        return True
