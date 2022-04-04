class Rental:
    def __init__(self, rental_id, movie_id, client_id, rented_date, due_date, returned_date):
        self.__rental_id = rental_id
        self.__movie_id = movie_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        self.__due_date = due_date
        self.__returned_date = returned_date

    def get_id(self):
        return self.__rental_id

    def get_movie_id(self):
        return self.__movie_id

    def get_client_id(self):
        return self.__client_id

    def get_rented_date(self):
        return self.__rented_date

    def set_rented_date(self, rented_date):
        self.__rented_date = rented_date

    def get_due_date(self):
        return self.__due_date

    def set_due_date(self, due_date):
        self.__due_date = due_date

    def get_returned_date(self):
        return self.__returned_date

    def set_returned_date(self, returned_date):
        self.__returned_date = returned_date

    def __eq__(self, other):
        if not isinstance(other, Rental):
            return False

        return self.__rental_id == other.__rental_id and self.__movie_id == other.__movie_id and \
               self.__client_id == other.__client_id and self.__rented_date == other.__rented_date and \
               self.__due_date == other.__due_date and self.__returned_date == other.__returned_date

    def __str__(self):
        return f"{self.__rental_id} - {self.__movie_id} - {self.__client_id} - " \
               f"{self.__rented_date} - {self.__due_date} - {self.__returned_date}"

    def to_dictionary(self):
        return {"rental_id": self.__rental_id, "movie_id": self.__movie_id, "client_id": self.__client_id, "rent_date": self.__rented_date, "due_date": self.__due_date, "return_date": self.__returned_date}

    @staticmethod
    def from_line(line):
        parts_of_line = line.split(" - ")
        rental_id = int(parts_of_line[0])
        movie_id = int(parts_of_line[1])
        client_id = int(parts_of_line[2])
        rental_date = parts_of_line[3]
        due_date = parts_of_line[4]
        return_date = parts_of_line[5]
        return Rental(rental_id, movie_id, client_id, rental_date, due_date, return_date)

    @staticmethod
    def to_line(rental):
        line = f"{rental.__rental_id} - {rental.__movie_id} - {rental.__client_id} - " \
               f"{rental.__rented_date} - {rental.__due_date} - {rental.__returned_date}"
        return line
