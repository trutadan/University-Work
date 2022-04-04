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
