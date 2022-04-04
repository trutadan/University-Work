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
        return self.__rental_id == other.__rental_id and self.__movie_id == other.__movie_id and \
               self.__client_id == other.__client_id and self.__rented_date == other.__rented_date and \
               self.__due_date == other.__due_date and self.__returned_date == other.__returned_date

    def __str__(self):
        return f"{self.__rental_id} - {self.__movie_id} - {self.__client_id} - " \
               f"{self.__rented_date} - {self.__due_date} - {self.__returned_date}"


class RentalDTO:
    def __init__(self, rental_id, client_name, movie_title, rental_date, due_date, returned_date):
        self.__rental_id = rental_id
        self.__client_name = client_name
        self.__movie_title = movie_title
        self.__rental_date = rental_date
        self.__due_date = due_date
        self.__returned_date = returned_date

    def __str__(self):
        return f"{self.__rental_id} - {self.__client_name} - {self.__movie_title}" \
               f" - {self.__rental_date} - {self.__due_date} - {self.__returned_date}"


class RentalMovieStatisticsDTO:
    def __init__(self, movie_title, number_of_days):
        self.__movie_title = movie_title
        self.__number_of_days = number_of_days

    def __str__(self):
        movie_and_number_of_days_format = f"{self.__movie_title} - {self.__number_of_days}"
        movie_and_number_of_days_format += " day" if self.__number_of_days == 1 else " days"
        return movie_and_number_of_days_format


class RentalClientStatisticsDTO:
    def __init__(self, client_name, number_of_days):
        self.__client_name = client_name
        self.__number_of_days = number_of_days

    def __str__(self):
        client_and_number_of_days_format = f"{self.__client_name} - {self.__number_of_days}"
        client_and_number_of_days_format += " day" if self.__number_of_days == 1 else " days"
        return client_and_number_of_days_format
