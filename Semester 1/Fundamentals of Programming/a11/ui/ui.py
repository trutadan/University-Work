import sys
from time import sleep

from ai.basicAI import BasicAI
from ai.complexAI import ComplexAI
from domain.ship import Ship
from exceptions import ShipException, BoardException
from settings.constants import *
from settings.settings import Settings


class UI:
    def __init__(self, player_board, computer_board):
        self.__player_board = player_board
        self.__computer_board = computer_board
        self.__ai = {"normal": BasicAI, "hard": ComplexAI}[Settings().get_ai_difficulty()]

    def ask_user_for_ship_placement_information(self):
        type_of_ships = {'carrier': 5, 'battleship': 4, 'destroyer': 3, 'submarine': 3, 'patrol boat': 2}

        while True:
            chosen_ship = input("Choose a ship you want to add: 'carrier', 'battleship', 'destroyer', 'submarine' or 'patrol boat'. ").lower()

            if chosen_ship == 'exit':
                print("\nThank you for playing! See you next time!")
                sys.exit()

            if chosen_ship in type_of_ships.keys():
                break
            print("Not a valid choice!\n")

        type_of_directions = ['north', 'east', 'south', 'west']

        while True:
            chosen_direction = input("Choose the direction in which you want the ship to be placed: 'north', 'east', 'south' and 'west'. ").lower()

            if chosen_direction == 'exit':
                print("Thank you for playing! See you next time!")
                sys.exit()

            if chosen_direction in type_of_directions:
                break
            print("Not a valid choice!\n")

        while True:
            chosen_position = input("Choose the position where you want the ship to be placed(example: A1). ").lower()

            if chosen_position == 'exit':
                print("Thank you for playing! See you next time!")
                sys.exit()

            try:
                start_x_coordinate, start_y_coordinate = self.__player_board.transform_position_into_coordinates(chosen_position)
                start_position = (start_x_coordinate, start_y_coordinate)

                length_of_ship = type_of_ships[chosen_ship]

                if chosen_direction == 'north':
                    end_x_coordinate = start_x_coordinate - length_of_ship + 1
                    end_y_coordinate = start_y_coordinate
                elif chosen_direction == 'east':
                    end_x_coordinate = start_x_coordinate
                    end_y_coordinate = start_y_coordinate + length_of_ship - 1
                elif chosen_direction == 'south':
                    end_x_coordinate = start_x_coordinate + length_of_ship - 1
                    end_y_coordinate = start_y_coordinate
                else:
                    end_x_coordinate = start_x_coordinate
                    end_y_coordinate = start_y_coordinate - length_of_ship + 1

                end_position = (end_x_coordinate, end_y_coordinate)
                self.__player_board.validate_position(end_position)

                ship_to_be_added = Ship(start_position, end_position)
                break

            except ShipException as ship_error:
                print(ship_error)
                print()
            except BoardException as grid_error:
                print(grid_error)
                print()

        return ship_to_be_added

    def position_the_ships_of_the_user(self):
        print("\nLet's start positioning your ships!")

        number_of_ships = list(Settings().get_number_of_ships().values())
        number_of_ships = {'carrier': number_of_ships[0], 'battleship': number_of_ships[1], 'destroyer': number_of_ships[2], 'patrol boat': number_of_ships[3]}

        while number_of_ships['carrier'] + number_of_ships['battleship'] + number_of_ships['destroyer'] + number_of_ships['patrol boat']:
            print("\n-- YOUR TABLE --")
            print(self.__player_board.get_table_for_positioning())
            print(f"You have {number_of_ships['carrier']} {'carrier' if number_of_ships['carrier'] == 1 else 'carriers'}, "
                  f"{number_of_ships['battleship']} {'battleship' if number_of_ships['battleship'] == 1 else 'battleships'}, "
                  f"{number_of_ships['destroyer']} {'destroyer' if number_of_ships['destroyer'] == 1 else 'destroyers'}, "
                  f"{number_of_ships['patrol boat']} {'patrol boat' if number_of_ships['patrol boat'] == 1 else 'patrol boats'}"
                  f" left, that have to be placed. ")

            ship = self.ask_user_for_ship_placement_information()
            type_of_ship = SHIP_NAMES[len(ship)]

            if number_of_ships[type_of_ship]:
                try:
                    self.__player_board.add_ship(ship)
                    number_of_ships[type_of_ship] -= 1
                except BoardException as grid_error:
                    print(grid_error)
                    continue
            else:
                print(f"You have no more {type_of_ship}s left! Choose other ship.")

        print("\n-- YOUR FINAL TABLE --")
        print(self.__player_board.get_table_for_positioning())

    @staticmethod
    def get_positioning_preference():
        while True:
            positioning_choice = input("Do you want to position the ships by yourself, or randomly generate them? "
                                       "Choose 'myself'/'random'. ").lower()

            if positioning_choice == 'exit':
                print("\nThank you for playing! See you next time!")
                sys.exit()

            if positioning_choice in ['myself', 'random']:
                return positioning_choice

    @staticmethod
    def get_the_first_move_preference_from_user():
        from random import choice
        player_choices = ['me', 'opponent']

        while True:
            first_move = input("\nWho would you prefer to launch the first attack? Choose between 'me', 'opponent' or 'random': ").lower()

            if first_move == 'exit':
                print("\nThank you for playing! See you next time!")
                sys.exit()

            if first_move in player_choices:
                print("\nYou will start the game!") if first_move == 'me' else print("\nYour opponent will start the game!")
                return first_move

            elif first_move == 'random':
                first_move = choice(['me', 'opponent'])
                print("\nYou have been randomly selected to start!") if first_move == 'me' else print("\nYour opponent has been randomly selected to start!")
                return first_move

            print("\nNot a valid choice!")

    def get_position_from_user_for_attack(self):
        while True:
            position_to_attack = input("What do you want to attack next? ").lower()

            if position_to_attack == 'exit':
                print("\nThank you for playing! See you next time!")
                sys.exit()

            try:
                x_coordinate, y_coordinate = self.__player_board.transform_position_into_coordinates(position_to_attack)
                visual_opponent_table = self.__computer_board.get_board()
                if visual_opponent_table[x_coordinate][y_coordinate] in (SEA, SHIP):
                    return x_coordinate, y_coordinate

                print("Not a valid position. Try again!\n")

            except BoardException as grid_error:
                print(grid_error)
                print()

    @staticmethod
    def ui_fire_shot(table, position):
        try:
            status_of_the_shot = table.fire_shot(position)
            if status_of_the_shot == 'hit':
                print("The bullet hit a ship!")
            elif status_of_the_shot == 'sunk':
                print("The bullet hit the last block of the ship. The ship has sunk. Keep going!")
            else:
                print("The shot has missed! Good luck next time.")

        except BoardException as grid_error:
            print(grid_error)
            print()

    def check_for_the_end_of_the_game(self):
        player_ship_blocks_left = self.__player_board.get_ship_blocks_left()
        computer_ship_blocks_left = self.__computer_board.get_ship_blocks_left()
        if computer_ship_blocks_left == 0:
            if player_ship_blocks_left == computer_ship_blocks_left:
                print("\nIt's a draw! Both players sunk all the enemy's ships.")
            else:
                print("\nCongratulations! You have won the game!")
            return True
        elif player_ship_blocks_left == 0:
            print("\nThat's unfortunate! You lost! More luck next time!")
            return True

        return False

    @staticmethod
    def transform_coordinates_into_position(coordinates):
        x_coordinate = coordinates[0]
        y_coordinate = coordinates[1]

        position = chr(x_coordinate + 65)
        position += str(y_coordinate + 1)

        return position

    def simulate_player_turn(self):
        sleep(2)
        print("\nYour turn!")
        print("-- OPPONENT'S TABLE (before the attack) --")
        print(self.__computer_board)

        coordinates = self.get_position_from_user_for_attack()
        print(f"\nA shot was fired at the position {self.transform_coordinates_into_position(coordinates)}!")
        self.ui_fire_shot(self.__computer_board, coordinates)
        sleep(3)

        print("\n-- OPPONENT'S TABLE (after the attack) --")
        print(self.__computer_board)

    def simulate_computer_turn(self):
        sleep(2)
        print("\nYour opponent's turn!")
        print("-- YOUR TABLE (before the attack)--")
        print(self.__player_board)

        sleep(3)
        coordinates = self.__ai(self.__player_board).find_the_best_next_move()
        print(f"\nA shot was fired at the position {self.transform_coordinates_into_position(coordinates)}!")
        self.ui_fire_shot(self.__player_board, coordinates)
        sleep(3)

        print("\n-- YOUR TABLE (after the attack)--")
        print(self.__player_board)

    def run_game(self):
        print("Welcome to the console Battleship game!")
        print("To close the game at any time, you need to type 'exit' in the console\n")
        self.__computer_board.generate_random_ships()

        position_preference = self.get_positioning_preference()
        if position_preference == 'myself':
            self.position_the_ships_of_the_user()
        else:
            self.__player_board.generate_random_ships()

        print("\nThe placement phase has ended. You and your opponent have successfully placed the ships on the game board!")
        print("We are entering attacking phase. Prepare yourselves!")
        first_move = self.get_the_first_move_preference_from_user()

        while True:
            if first_move == 'me':
                self.simulate_player_turn()
                self.simulate_computer_turn()
            else:
                self.simulate_computer_turn()
                self.simulate_player_turn()

            if self.check_for_the_end_of_the_game():
                break

        print("\nThank you for playing! See you next time!")
