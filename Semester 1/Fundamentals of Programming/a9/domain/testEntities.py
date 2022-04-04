import unittest

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from domain.rentalDTOs import RentalDTO, RentalMovieStatisticsDTO, RentalClientStatisticsDTO


class ClientDomainTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_client = Client("2", "Emma")
        self.__copy_test_client = Client("2", "Emma")

    def test_client_domain__get_client_id__correct_id(self):
        self.assertEqual(self.__test_client.get_id(), "2")

    def test_client_domain__get_client_name__correct_name(self):
        self.assertEqual(self.__test_client.get_name(), "Emma")

    def test_client_domain__set_client_name__name_changed(self):
        self.__test_client.set_name("Anne")
        self.assertEqual(self.__test_client.get_name(), "Anne")

    def test_client_domain__two_clients_same_attributes__equality_checked(self):
        self.assertEqual(self.__test_client, self.__copy_test_client)

    def test_client_domain__get_client_string_format__correct_string(self):
        self.assertEqual(self.__test_client.__str__(), "2 - Emma")

    def tearDown(self) -> None:
        pass


class MovieDomainTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_movie = Movie("5", "Titanic", "ship collision", "Drama")
        self.__copy_test_movie = Movie("5", "Titanic", "British passenger liner", "Drama")
        self.__another_test_movie = Movie("12", "The great Gatsby", "millionaire neighbor", "Romance")

    def test_movie_domain__get_movie_id__correct_id(self):
        self.assertEqual(self.__test_movie.get_id(), "5")

    def test_movie_domain__get_movie_title__correct_title(self):
        self.assertEqual(self.__another_test_movie.get_title(), "The great Gatsby")

    def test_movie_domain__set_movie_title__title_changed(self):
        self.__another_test_movie.set_title("great Gatsby")
        self.assertEqual(self.__another_test_movie.get_title(), "great Gatsby")

    def test_client_domain__get_movie_description__correct_description(self):
        self.assertEqual(self.__test_movie.get_description(), "ship collision")

    def test_client_domain__set_movie_description__description_changed(self):
        self.__test_movie.set_description("British passenger liner")
        self.assertEqual(self.__test_movie.get_description(), "British passenger liner")

    def test_client_domain__get_movie_genre__correct_genre(self):
        self.assertEqual(self.__another_test_movie.get_genre(), "Romance")

    def test_client_domain__set_movie_genre__genre_changed(self):
        self.__another_test_movie.set_genre("Drama")
        self.assertEqual(self.__another_test_movie.get_genre(), "Drama")

    def test_client_domain__two_clients_same_attributes__equality_checked(self):
        self.__copy_test_movie.set_description("ship collision")
        self.assertEqual(self.__test_movie, self.__copy_test_movie)

    def test_client_domain__get_client_string_format__correct_string(self):
        self.assertEqual(self.__test_movie.__str__(), "5 - Titanic - ship collision - Drama")

    def tearDown(self) -> None:
        pass


class RentalDomainTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_rental = Rental("2", "31", "49", "2021-02-08", "2022-03-01", "2021-11-12")
        self.__copy_test_rental = Rental("2", "31", "49", "2021-02-08", "2022-03-01", "2021-11-12")
        self.__another_test_rental = Rental("17", "1", "5", "2021-04-11", "2021-07-11", "2022-01-02")

    def test_rental_domain__get_rental_id__correct_id(self):
        self.assertEqual(self.__test_rental.get_id(), "2")

    def test_rental_domain__get_movie_id_from_rental__correct_movie_id(self):
        self.assertEqual(self.__another_test_rental.get_movie_id(), "1")

    def test_rental_domain__get_client_id_from_rental__correct_client_id(self):
        self.assertEqual(self.__test_rental.get_client_id(), "49")

    def test_rental_domain__get_rented_date__correct_date(self):
        self.assertEqual(self.__another_test_rental.get_rented_date(), "2021-04-11")

    def test_rental_domain__set_rented_date__changed_date(self):
        self.__another_test_rental.set_rented_date("2023-01-05")
        self.assertEqual(self.__another_test_rental.get_rented_date(), "2023-01-05")

    def test_rental_domain__get_due_date__correct_date(self):
        self.assertEqual(self.__test_rental.get_due_date(), "2022-03-01")

    def test_rental_domain__set_due_date__changed_date(self):
        self.__test_rental.set_due_date("2022-02-12")
        self.assertEqual(self.__test_rental.get_due_date(), "2022-02-12")

    def test_rental_domain__get_returned_date__correct_date(self):
        self.assertEqual(self.__another_test_rental.get_returned_date(), "2022-01-02")

    def test_rental_domain__set_returned_date__changed_date(self):
        self.__another_test_rental.set_returned_date("2011-11-11")
        self.assertEqual(self.__another_test_rental.get_returned_date(), "2011-11-11")

    def test_rental_domain__two_rentals_same_attributes__equality_checked(self):
        self.assertEqual(self.__test_rental, self.__copy_test_rental)

    def test_rental_domain__get_client_string_format__correct_string(self):
        self.assertEqual(self.__test_rental.__str__(), "2 - 31 - 49 - 2021-02-08 - 2022-03-01 - 2021-11-12")

    def tearDown(self) -> None:
        pass


class RentalDTOTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__rental_dto_test = RentalDTO(1, "Sett", "Titanic", "2021-02-08", "2022-03-01", "2021-11-12")

    def test_rental_dto_domain__rental_print__correct_string(self):
        self.assertEqual(self.__rental_dto_test.__str__(), "1 - Sett - Titanic - 2021-02-08 - 2022-03-01 - 2021-11-12")

    def tearDown(self) -> None:
        pass


class RentalMovieStatisticsDTOTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__rental_movie_statistics_dto_test_one_day = RentalMovieStatisticsDTO("Titanic", 1)
        self.__rental_movie_statistics_dto_test_multiple_days = RentalMovieStatisticsDTO("Titanic", 7)

    def test_rental_dto_domain__rental_print_one_day_passed__correct_string(self):
        self.assertEqual(self.__rental_movie_statistics_dto_test_one_day.__str__(), "Titanic - 1 day")

    def test_rental_dto_domain__print_rental_multiple_days_passed__correct_string(self):
        self.assertEqual(self.__rental_movie_statistics_dto_test_multiple_days.__str__(), "Titanic - 7 days")

    def tearDown(self) -> None:
        pass


class RentalClientStatisticsDTOTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__rental_client_statistics_dto_test_one_day = RentalClientStatisticsDTO("Sett", 1)
        self.__rental_client_statistics_dto_test_multiple_days = RentalClientStatisticsDTO("Sett", 7)

    def test_rental_dto_domain__rental_print_one_day_passed__correct_string(self):
        self.assertEqual(self.__rental_client_statistics_dto_test_one_day.__str__(), "Sett - 1 day")

    def test_rental_dto_domain__print_rental_multiple_days_passed__correct_string(self):
        self.assertEqual(self.__rental_client_statistics_dto_test_multiple_days.__str__(), "Sett - 7 days")

    def tearDown(self) -> None:
        pass
