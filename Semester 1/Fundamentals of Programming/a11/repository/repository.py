from exceptions import BoardException


class ShipRepository:
    def __init__(self):
        self.__ships = {2: [],
                        3: [],
                        4: [],
                        5: []}

    def search(self, ship_length):
        if ship_length not in self.__ships.keys():
            raise BoardException("Ship of given length does not exist!")
        return self.__ships[ship_length]

    def add(self, ship):
        if len(ship) not in self.__ships.keys():
            raise BoardException("Ship of given length does not exist!")
        self.__ships[len(ship)].append(ship)

    def remove(self, ship):
        if ship not in [item for sublist in list(self.__ships.values()) for item in sublist]:
            raise BoardException("Ship of given length does not exist!")
        self.__ships[len(ship)].remove(ship)

    def get_all(self):
        return list(self.__ships.values())

    def __len__(self):
        return len(self.__ships.values())
