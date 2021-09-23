# unneeded
from constants import *

color = {40: "white", 41: "red", 42: "green", 43: "yellow", 44: "blue", 45: "purple", 46: "teal",
         47: "light gray", 100: "dark gray", 101: "light red", 102: "light green", 103: "light yellow",
         104: "light blue", 105: "magenta", 106: "cyan", 107: "black"}


to_color = {}

for key, value in color.items():
    to_color[value] = key


for i in range(40, 56):
    if i > 47:
        i += 52
    for j in range(30, 46):
        if j > 37:
            j += 52
        print(f"\033[{j};{i}m {j:3}, {i:3}", end=" ")
        if j % 10 == 7:
            print(f"\033[0m {color[i]}")


color_list = [key for key in to_color if type(key) == str]
count = 0
for color in color_list:
    for other_color in color_list:
        if count % 8 == 0:
            print()
        print(f"\033[{to_color[color]}m    \033[{to_color[other_color]}m    \033[m", end="\t")
        count += 1
