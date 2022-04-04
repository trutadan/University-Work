from settings.constants import SHIP, HIT, SEA


class BasicAI:
    def __init__(self, board):
        self._board = board

    def _hunt_for_next_hit_position(self):
        """
        The computer is in hunt mode, so it randomly fires into unknown locations with even parity.
        Because the minimum length of a ship is two units long, then we don't need to random search every
        location on the board. Even the shortest ship has to straddle two adjacent squares.
        This parity algorithm is only a slight improvement to the random one.
        """

        board_height = self._board.get_height()
        board_width = self._board.get_width()

        from random import randrange
        x_coordinate = randrange(board_height)
        y_coordinate = randrange(board_width)

        while self._board.get_board()[x_coordinate][y_coordinate] not in [SHIP, SEA] or (x_coordinate + y_coordinate) % 2 == 1:
            x_coordinate = randrange(board_height)
            y_coordinate = randrange(board_width)

        position = (x_coordinate, y_coordinate)
        return position

    @staticmethod
    def get_position_from_north(position):
        x_coordinate = position[0] - 1
        y_coordinate = position[1]
        position_from_north = (x_coordinate, y_coordinate)
        return position_from_north

    @staticmethod
    def get_position_from_east(position):
        x_coordinate = position[0]
        y_coordinate = position[1] + 1
        position_from_east = (x_coordinate, y_coordinate)
        return position_from_east

    @staticmethod
    def get_position_from_south(position):
        x_coordinate = position[0] + 1
        y_coordinate = position[1]
        position_from_south = (x_coordinate, y_coordinate)
        return position_from_south

    @staticmethod
    def get_position_from_west(position):
        x_coordinate = position[0]
        y_coordinate = position[1] - 1
        position_from_west = (x_coordinate, y_coordinate)
        return position_from_west

    def check_valid_position(self, position):
        x_coordinate = position[0]
        y_coordinate = position[1]

        board_height = self._board.get_height()
        board_width = self._board.get_width()

        return x_coordinate in range(0, board_height) and y_coordinate in range(0, board_width)

    def _target_next_position_based_on_hit(self, actual_position):
        """
        Once a ship has been hit, the computer switches to Target mode. After a hit, the four (or less than four
        if the cell was on an edge/corner) surrounding grid squares are added to a stack of 'potential' targets.
        Target mode the computer pops off the next potential target off the stack, fires a shot at this location,
        acts on this (either adding more potential targets to the stack, or popping the next target location off the stack),
        until either all ships have been sunk, or there are no more potential targets on the stack,
        at which point it returns to Hunt mode and starts firing at random again looking for another ship.
        """

        horizontal_direction = True
        vertical_direction = True

        def try_direction(direction, position):
            next_position = direction(position)
            x_coordinate = next_position[0]
            y_coordinate = next_position[1]
            while self.check_valid_position(next_position) and self._board.get_board()[x_coordinate][y_coordinate] is HIT:
                next_position = direction(next_position)
            if self.check_valid_position(next_position) and self._board.get_board()[x_coordinate][y_coordinate] in [SHIP, SEA]:
                return next_position

        def search_on_horizontal():
            if try_direction(self.get_position_from_west, actual_position):
                return try_direction(self.get_position_from_west, actual_position)
            if try_direction(self.get_position_from_east, actual_position):
                return try_direction(self.get_position_from_east, actual_position)

        def search_on_vertical():
            if try_direction(self.get_position_from_north, actual_position):
                return try_direction(self.get_position_from_north, actual_position)
            if try_direction(self.get_position_from_south, actual_position):
                return try_direction(self.get_position_from_south, actual_position)

        west_x_coordinate = self.get_position_from_west(actual_position)[0]
        west_y_coordinate = self.get_position_from_west(actual_position)[1]

        east_x_coordinate = self.get_position_from_east(actual_position)[0]
        east_y_coordinate = self.get_position_from_east(actual_position)[1]

        if (self.check_valid_position(self.get_position_from_west(actual_position)) and self._board.get_board()[west_x_coordinate][west_y_coordinate] is HIT) or\
                (self.check_valid_position(self.get_position_from_east(actual_position)) and self._board.get_board()[east_x_coordinate][east_y_coordinate] is HIT):
            vertical_direction = False

        north_x_coordinate = self.get_position_from_north(actual_position)[0]
        north_y_coordinate = self.get_position_from_north(actual_position)[1]

        south_x_coordinate = self.get_position_from_south(actual_position)[0]
        south_y_coordinate = self.get_position_from_south(actual_position)[1]

        if (self.check_valid_position(self.get_position_from_south(actual_position)) and self._board.get_board()[south_x_coordinate][south_y_coordinate] is HIT) or\
                (self.check_valid_position(self.get_position_from_north(actual_position)) and self._board.get_board()[north_x_coordinate][north_y_coordinate] is HIT):
            horizontal_direction = False

        if horizontal_direction:
            if search_on_horizontal():
                return search_on_horizontal()

        if vertical_direction:
            if search_on_vertical():
                return search_on_vertical()

        if search_on_horizontal():
            return search_on_horizontal()

        if search_on_vertical():
            return search_on_vertical()

        return None

    def find_the_best_next_move(self):
        """
        Once part of a ship has been hit, it's possible to search up, down, left and right looking for more of the same ship.
        If no more hits are registered, shots can be fired at random, taking into account the parity rule.
        """

        board_height = self._board.get_height()
        board_width = self._board.get_width()

        for x_coordinate in range(board_height):
            for y_coordinate in range(board_width):
                if self._board.get_board()[x_coordinate][y_coordinate] is HIT:

                    position_to_attack = self._target_next_position_based_on_hit((x_coordinate, y_coordinate))

                    if position_to_attack is not None:
                        return position_to_attack

        return self._hunt_for_next_hit_position()
