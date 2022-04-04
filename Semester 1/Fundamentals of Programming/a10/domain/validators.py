import datetime

from exceptions import ValidatorException


class ClientValidator:
    @staticmethod
    def validate(client):
        errors = []
        if client.get_id() < 0:
            errors.append("ID can not be a negative integer!")
        if client.get_name() == "":
            errors.append("Name field can not be empty!")
        if len(errors) != 0:
            raise ValidatorException(errors)


class MovieValidator:
    @staticmethod
    def validate(movie):
        errors = []
        if movie.get_id() < 0:
            errors.append("ID can not be a negative integer!")
        if movie.get_title() == "":
            errors.append("Title field can not be empty!")
        if movie.get_description() == "":
            errors.append("Description field can not be empty!")
        if movie.get_genre() == "":
            errors.append("Genre field can not be empty!")
        if len(errors) != 0:
            raise ValidatorException(errors)


class RentalValidator:
    @staticmethod
    def validate(rental):
        errors = []
        date_format = "%Y-%m-%d"
        if rental.get_id() < 0:
            errors.append("Rental ID can not be a negative integer!")
        if rental.get_movie_id() < 0:
            errors.append("Movie ID can not be a negative integer!")
        if rental.get_client_id() < 0:
            errors.append("Client ID can not be a negative integer!")
        if rental.get_rented_date() == "":
            errors.append("Rented date field can not be empty!")
        if rental.get_due_date() == "":
            errors.append("Due date field can not be empty!")
        if rental.get_returned_date() == "":
            errors.append("Returned date field can not be empty!")
        try:
            datetime_rented_date = datetime.datetime.strptime(rental.get_rented_date(), date_format)
            if rental.get_returned_date() != '"n/a"':
                datetime_returned_date = datetime.datetime.strptime(rental.get_returned_date(), date_format)
                if datetime_rented_date > datetime_returned_date:
                    errors.append("The return date should be done after the rental date!")
        except ValueError:
            errors.append("The date format provided is not correct. Try (year-month-day)!")
        if len(errors) != 0:
            raise ValidatorException(errors)
