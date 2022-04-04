class Route:
    def __init__(self, code, length):
        self.__code = code
        self.__length = length

    def get_code(self):
        return self.__code

    def get_length(self):
        return self.__length

    def __eq__(self, other):
        return self.__code == other.get_code() and self.__length == other.get_length()

    def __str__(self):
        return f"{self.__code},{self.__length}"

    @staticmethod
    def from_line(line):
        elements_from_line = line.split(',')

        route_code = elements_from_line[0]
        route_length = int(elements_from_line[1])

        return Route(route_code, route_length)

    @staticmethod
    def to_line(route):
        return str(route)


class Bus:
    def __init__(self, bus_id, code, model, usage):
        self.__bus_id = bus_id
        self.__route_code = code
        self.__model = model
        self.__usage = usage

    def get_id(self):
        return self.__bus_id

    def get_code(self):
        return self.__route_code

    def get_model(self):
        return self.__model

    def get_usage(self):
        return self.__usage

    def set_usage(self, usage):
        self.__usage = usage

    def __eq__(self, other):
        return self.__bus_id == other.get_id() and self.__route_code == other.get_code()

    def __str__(self):
        return f"{self.__bus_id},{self.__route_code},{self.__model},{self.__usage}"

    @staticmethod
    def from_line(line):
        elements = line.split(",")

        bus_id = elements[0]
        route_code = elements[1]
        bus_model = elements[2]
        times_used = int(elements[3])

        return Bus(bus_id, route_code, bus_model, times_used)

    @staticmethod
    def to_line(bus):
        return str(bus)


class BusDTO:
    def __init__(self, bus_instance, kilometers_travelled):
        self.__bus = bus_instance
        self.__kilometers_travelled = kilometers_travelled

    def get_kilometers_travelled(self):
        return self.__kilometers_travelled

    def __str__(self):
        return f"{str(self.__bus)} - {self.__kilometers_travelled} kilometers travelled"
