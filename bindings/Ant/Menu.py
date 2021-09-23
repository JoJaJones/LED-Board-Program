from Board import Board
from Display import ScreenDisplay

class Menu:
    def __init__(self):
        self.board = Board()
        self.display = ScreenDisplay(self.board.get_positions())

    def main_menu(self):
        run = True
        while run:
            choice = input("1 - Run Langston's Ant Simulation\n"
                           "0 - Quit")
            try:
                choice = int(choice)
            except:
                print("Invalid entry please try again")

            if choice == 1:
                self.ant_menu()
            elif choice == 0:
                run = False

    def ant_menu(self):
        invalid = True
        while invalid:
            invalid = False

            num_steps = input("How many steps would you like the simulation to run for (0 for endless)? ")
            try:
                num_steps = int(num_steps)
            except:
                print("Invalid selection please input a whole number")
                invalid = True

        self.setup_ant_sim()

        self.run_ant_run(num_steps)

    def run_ant_run(self, num_steps):
        while num_steps != 0:
            self.board.move_all_ants()
            self.display.render(self.board.get_positions())

            num_steps -= 1

    def setup_ant_sim(self):
        # TODO implment
        raise NotImplementedError

    def make_ant(self, pos: tuple = None, direction: str = None, color: str = None):
        # TODO implment
        raise NotImplementedError

    def get_ant_settings(self, default_color: str = None):
        # TODO implment
        raise NotImplementedError

    def design_menu(self):
        # present the options
        invalid = True
        while invalid:
            invalid = False
            try:
                design_type = int(input("1 - radial symmetry\n"
                                        "2 - choose specific design\n"))
            except:
                invalid = True

            if (design_type != 1 and design_type != 2) or invalid:
                print("Invalid selection please choose from the options listed")

        # radial symmetry
            # invalid = True
            # while invalid:
                # invalid = False
                # num_sym_axes = input("How many axes of symmetry do you want (2 or 4)?")
                # num_ants_to_pick = input("How many ants would you like to set per axis?")
                # try:
                    # num_sym_axes = int(num_sym_axes)
                    # num_ants_to_pick = int(num_ants_to_pick)
                # except:
                    # invalid = True

                # if (num_sym_axes != 2 and num_sym_axes != 4) or invalid:
                    # print("Invalid selection please input valid whole number choices")
            # get option for user selected ants
            # make ants

        # specific design
            # invalid = True
            # while invalid:
                # invalid = False
                # prompt = ""
                # for num, pattern in DESIGN_DICT.items():
                    # prompt += f"{num} - {pattern[0]}\n"
                # try:
                    # which_pattern = int(input(prompt))
                # except:
                    # invalid = True

                # if invalid or which_pattern not in DESIGN_DICT:
                    # print("Invalid selection please choose from the options listed")
        # use chosen options to setup the sim
        raise NotImplementedError

if __name__ == "__main__":
    menu = Menu()
    menu.main_menu()