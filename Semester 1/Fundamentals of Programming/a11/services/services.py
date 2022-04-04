from texttable import Texttable

from domain.ship import Ship
from exceptions import BoardException
from settings.constants import *
from settings.settings import Settings


class TableServices:
    def __init__(self, player, ship_repository, width=10, height=10):
        self.__player = player
        self.__ships = ship_repository
        self.__width = width
        self.__height = height
        self.__board = [[SEA for row in range(self.__width)] for column in range(self.__height)]
        self.__ship_blocks_left = 0

    def get_width(self):
        return self.__width

    def get_height(self):
        return self.__height

    def get_board(self):
        return self.__board

    def get_ship_blocks_left(self):
        return self.__ship_blocks_left

    def get_ships(self):
        return self.__ships.get_all()

    def validate_position(self, position):
        """
        Check if a position is on the board, raise exception if not.
        :param position: a tuple.
        """

        x_coordinate = position[0]
        y_coordinate = position[1]

        if x_coordinate < 0 or x_coordinate >= self.__width or y_coordinate < 0 or y_coordinate >= self.__height:
            raise BoardException("Position out of the game table!")

    def transform_position_into_coordinates(self, table_position):
        """
        Transform a position in string format into a tuple of coordinates.
        :param table_position: a string having a position format, the first character being a letter representing
        the y coordinate, and the others represent the x coordinate.
        :return: a tuple of integers representing coordinates.
        """

        table_position = table_position.upper()

        import re

        if not re.match("([A-Z])([0-9][0-9]*)$", table_position):
            raise BoardException("Not a valid move!")

        y_coordinate = int(table_position[1:]) - 1
        x_coordinate = ord(table_position[0]) - ord('A')

        if x_coordinate < 0 or x_coordinate >= self.__width or y_coordinate < 0 or y_coordinate >= self.__height:
            raise BoardException("Selected position is out of the table!")

        position = (x_coordinate, y_coordinate)

        return position

    def add_ship(self, ship):
        """
        Add the given ship to the repository, or raise exceptions if the position does not fit the table or it
        overlaps an already existing ship.
        :param ship: instance of the class Ship.
        """

        positions = ship.get_positions()

        for position in positions:
            x_coordinate = position[0]
            y_coordinate = position[1]
            if self.__board[x_coordinate][y_coordinate] is not SEA:
                raise BoardException("You can't place a ship there!")

        self.__ships.add(ship)

        for position in positions:
            x_coordinate = position[0]
            y_coordinate = position[1]
            self.__board[x_coordinate][y_coordinate] = SHIP

        self.__ship_blocks_left += len(positions)

    def __generate_one_random_ship(self, ship_length):
        """
        Generate one random Ship instance of the given length.
        :param ship_length: the length of the Ship instance that is going to be created.
        :return: the randomly generated Ship instance.
        """

        times_random_positioning_failed = 0
        from random import randrange, choice

        while True:
            times_random_positioning_failed += 1
            random_direction = choice(['south', 'east'])

            if random_direction == 'south':
                starting_x = randrange(self.__height)
                starting_y = randrange(self.__width - ship_length + 1)
                ending_x = starting_x
                ending_y = starting_y + ship_length - 1

            else:
                starting_x = randrange(self.__height - ship_length + 1)
                starting_y = randrange(self.__width)
                ending_x = starting_x + ship_length - 1
                ending_y = starting_y

            valid_coordinates = True

            for x_coordinate in range(starting_x, ending_x + 1):
                if not valid_coordinates:
                    break

                for y_coordinate in range(starting_y, ending_y + 1):
                    for ship_list in self.__ships.get_all():
                        for ship in ship_list:
                            if (x_coordinate, y_coordinate) in ship.get_positions():
                                valid_coordinates = False
                                break

            if not valid_coordinates:
                if times_random_positioning_failed > 100:
                    raise BoardException("Board is too small. Modify the settings.")
                continue

            start_position = (starting_x, starting_y)
            end_position = (ending_x, ending_y)

            return Ship(start_position, end_position)

    def generate_random_ships(self):
        """
        Generate random ships based on the information found in the settings.ini file,
        about the number of ships of each type.
        """

        for ship, number_of_ships in Settings().get_number_of_ships().items():
            for index in range(number_of_ships):
                ship_length = LENGTH_OF_SHIPS[ship]

                if ship_length > min(self.__height, self.__width):
                    raise BoardException("Board is too small. Modify the settings.")

                ship_to_be_added = self.__generate_one_random_ship(ship_length)

                self.add_ship(ship_to_be_added)

    def __table_to_output_format(self, translate_dictionary):
        """
        Given the matrix representing the board, transform it into a nice table format that will be easier to read.
        :param translate_dictionary: a dictionary that translates every value of the matrix into another one, that
        will be visible to the player.
        :return: the matrix representing the board in a nice table format.
        """

        text_table = Texttable()
        rows_columns_format = ["-"]

        for column_index in range(1, self.__width + 1):
            rows_columns_format += [column_index]

        text_table.add_row(rows_columns_format)

        for row_index in range(self.__height):
            rows_columns_format = [chr(ord('A') + row_index)]
            rows_columns_format += [translate_dictionary[element] for element in self.__board[row_index]]

            text_table.add_row(rows_columns_format)

        return text_table.draw()

    def __check_for_sunk_ships(self):
        """
        Check if there is any ship for which all the blocks contained by it were shot.
        :return: None if a new ship sunk, the instance of the Ship that has just been sunk otherwise.
        """

        for ships_list in self.__ships.get_all():
            for ship in ships_list:
                ship_sunk = True

                for position in ship.get_positions():
                    x_coordinate = position[0]
                    y_coordinate = position[1]
                    if self.__board[x_coordinate][y_coordinate] is not HIT:
                        ship_sunk = False

                if ship_sunk:
                    return ship

        return None

    def fire_shot(self, position):
        """
        Fire a shot at the given position on the board.
        :param position: tuple representing the coordinates of the element from the matrix that will be attacked.
        :return: the status of the position that was shot, in string format.
        """

        x_coordinate = position[0]
        y_coordinate = position[1]

        if self.__board[x_coordinate][y_coordinate] not in [SHIP, SEA]:
            raise BoardException("Chosen position has been already attacked!")

        if self.__board[x_coordinate][y_coordinate] is SHIP:
            self.__board[x_coordinate][y_coordinate] = HIT
            self.__ship_blocks_left -= 1
            sunk_ship = self.__check_for_sunk_ships()

            if sunk_ship is not None:
                for position in sunk_ship.get_positions():
                    sunk_ship_x_coordinate = position[0]
                    sunk_ship_y_coordinate = position[1]
                    self.__board[sunk_ship_x_coordinate][sunk_ship_y_coordinate] = SUNK_SHIP
                self.__ships.remove(sunk_ship)

                return 'sunk'

            return 'hit'

        else:
            self.__board[x_coordinate][y_coordinate] = MISS
            return 'miss'

    def check_if_all_ship_blocks_were_hit(self):
        """
        Check if all the blocks of the ships have been shot.
        :return: True if there are no blocks left, False otherwise.
        """

        return self.__ship_blocks_left == 0

    def get_table_for_positioning(self):
        return self.__table_to_output_format(POSITIONING_REPRESENTATION)

    def __str__(self):
        if self.__player is PLAYER:
            return self.__table_to_output_format(PLAYER_BOARD_REPRESENTATION)
        return self.__table_to_output_format(COMPUTER_BOARD_REPRESENTATION)

