class Ship:
    def __init__(self, start_position, end_position):
        self.__start_position = start_position
        self.__end_position = end_position
        self.__initialize_coordinates_occupied()

    def __initialize_coordinates_occupied(self):
        self.__positions = list()

        if self.__start_position > self.__end_position:
            self.__start_position, self.__end_position = self.__end_position, self.__start_position

        for row in range(self.__start_position[0], self.__end_position[0]+1):
            for column in range(self.__start_position[1], self.__end_position[1]+1):
                self.__positions.append((row, column))

    def get_start_position(self):
        return self.__start_position

    def get_end_position(self):
        return self.__end_position

    def get_positions(self):
        return self.__positions

    def __len__(self):
        return len(self.__positions)

    def __eq__(self, other):
        if not isinstance(other, Ship):
            return False

        return self.__positions == other.get_positions()
