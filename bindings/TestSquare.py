from ArrayManipulator import ArrayManipulator
from random import randint
from constants import *

class TestSquare(ArrayManipulator):
    def __init__(self, *args, **kwargs):
        super(TestSquare, self).__init__(*args, **kwargs)
        self._forever = True
        for r in range(NUM_ROWS):
            for _ in range(len(self._array[r])):
                self._array[r].append(randint(0x888888, 0xFFFFFF))

    def process_frame(self):
        greater_than_zero = False
        for row in self._array:
            for col in range(len(row)):
                r = (row[col]&0xff0000)>>16
                g = (row[col]&0xff00)>>8
                b = row[col]&0xff
                #if row == self._array[0] and col == 0:
                 #   print(r,g,b, row[col])
                which = randint(0,2)
                if which == 0:
                    r = randint(r//2, r)
                    if r == 0 and self._forever:
                        r = 0xff
                elif which == 1:
                    g = randint(g//2, g)
                    if g == 0 and self._forever:
                        g = 0xff
                else:
                    b = randint(b//2, b)
                    if b == 0 and self._forever:
                        b = 0xff

                r<<=16
                g<<=8
                row[col] = r + g + b
                #if row == self._array[0] and col == 0:
                 #   print(r,g,b, row[col])

                if row[col] > 0:
                    greater_than_zero = True

        return greater_than_zero
