import pickle

from exceptions import RepositoryException


class RentalRepository:
    def __init__(self):
        self._rental_data = dict()

    def search(self, rental_id):
        if rental_id not in self._rental_data:
            raise RepositoryException("Rental ID does not exist!")
        return self._rental_data[rental_id]

    def add(self, rental):
        if rental.get_id() in self._rental_data:
            raise RepositoryException("Rental ID already existing!")
        self._rental_data[rental.get_id()] = rental

    def update(self, rental):
        if rental.get_id() not in self._rental_data:
            raise RepositoryException("Rental ID does not exist!")
        self._rental_data[rental.get_id()] = rental

    def remove(self, rental_id):
        if rental_id not in self._rental_data:
            raise RepositoryException("Rental ID does not exist!")
        del self._rental_data[rental_id]

    def get_all(self):
        return self._rental_data.values()

    def __len__(self):
        return len(self._rental_data)


class RentalFileRepository(RentalRepository):
    def __init__(self, file_path, read_rental, write_rental):
        self.__file_path = file_path
        self.__read_rental = read_rental
        self.__write_rental = write_rental
        RentalRepository.__init__(self)

    def __read_all_from_file(self):
        with open(self.__file_path, 'r') as file:
            self._rental_data.clear()
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if len(line):
                    rental = self.__read_rental(line)
                    self._rental_data[rental.get_id()] = rental

    def __write_all_to_file(self):
        with open(self.__file_path, 'w') as file:
            for rental_id in self._rental_data:
                file.write(self.__write_rental(self._rental_data[rental_id]) + '\n')

    def __append_to_file(self, rental):
        with open(self.__file_path, 'a') as file:
            file.write(self.__write_rental(rental) + '\n')

    def search(self, rental_id):
        self.__read_all_from_file()
        return RentalRepository.search(self, rental_id)

    def add(self, rental):
        self.__read_all_from_file()
        RentalRepository.add(self, rental)
        self.__append_to_file(rental)

    def remove(self, rental_id):
        self.__read_all_from_file()
        RentalRepository.remove(self, rental_id)
        self.__write_all_to_file()

    def update(self, rental):
        self.__read_all_from_file()
        RentalRepository.update(self, rental)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return RentalRepository.get_all(self)

    def __len__(self):
        self.__read_all_from_file()
        return RentalRepository.__len__(self)


class RentalBinaryFileRepository(RentalRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_rentals_from_file(self):
        with open(self.__file_path, 'rb') as file:
            try:
                self._rental_data = pickle.load(file)
            except EOFError:
                pass

    def __write_rentals_to_file(self):
        with open(self.__file_path, 'wb') as file:
            pickle.dump(self._rental_data, file)

    def __append_rentals_to_file(self):
        with open(self.__file_path, 'wb') as file:
            pickle.dump(self._rental_data, file)

    def search(self, rental_id):
        self.__read_rentals_from_file()
        return super().search(rental_id)

    def add(self, rental):
        self.__read_rentals_from_file()
        super().add(rental)
        self.__append_rentals_to_file()

    def remove(self, rental_id):
        self.__read_rentals_from_file()
        super().remove(rental_id)
        self.__write_rentals_to_file()

    def update(self, rental):
        self.__read_rentals_from_file()
        super().update(rental)
        self.__write_rentals_to_file()

    def get_all(self):
        self.__read_rentals_from_file()
        return super().get_all()

    def __len__(self):
        self.__read_rentals_from_file()
        return super().__len__()
