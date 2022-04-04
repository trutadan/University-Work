import unittest

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from exceptions import ValidatorException
from domain.validators import ClientValidator, MovieValidator, RentalValidator


class ClientValidatorTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__validator = ClientValidator()
        self.__client_example_1 = Client(-2, "")
        self.__client_example_2 = Client(15, "")
        self.__client_example_3 = Client(15, "Gabe")

    def test_validate__empty_entry_fields__throws_two_exceptions(self):
        try:
            self.__validator.validate(self.__client_example_1)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 2)

    def test_validate__one_empty_field_one_string_field__throws_one_exceptions(self):
        try:
            self.__validator.validate(self.__client_example_2)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_validate__two_string_field_entries__throws_no_exceptions(self):
        try:
            self.__validator.validate(self.__client_example_3)
            assert True
        except ValidatorException:
            assert False

    def tearDown(self) -> None:
        pass


class MovieValidatorTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__validator = MovieValidator()
        self.__movie_example_1 = Movie(-3, "", "", "")
        self.__movie_example_2 = Movie(2, "", "", "Action")
        self.__movie_example_3 = Movie(15, "Titanic", "Ship crashes", "Drama")

    def test_validate__empty_entry_fields__throws_four_exceptions(self):
        try:
            self.__validator.validate(self.__movie_example_1)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 4)

    def test_validate__two_empty_fields_two_strings__throws_two_exceptions(self):
        try:
            self.__validator.validate(self.__movie_example_2)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 2)

    def test_validate__four_string_field_entries__throws_no_exceptions(self):
        try:
            self.__validator.validate(self.__movie_example_3)
            assert True
        except ValidatorException:
            assert False

    def tearDown(self) -> None:
        pass


class RentalValidatorTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__validator = RentalValidator()
        self.__rental_example_1 = Rental(-5, -11, -23, "", "", "")
        self.__rental_example_2 = Rental(2, -11, -23, "2021-05-11", "", "")
        self.__rental_example_3 = Rental(4, 14, 97, "", "", "")
        self.__rental_example_4 = Rental(19, 10, 3, "2021-05-11", "2021-06-08", "2021-03-09")
        self.__rental_example_5 = Rental(19, 10, 3, "2021-03-09", "2021-06-08", "2021-05-11")

    def test_validate__all_wrong_entry_fields__throws_seven_exceptions(self):
        try:
            self.__validator.validate(self.__rental_example_1)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 7)

    def test_validate__four_wrong_fields_one_empty_string_one_date___throws_five_exceptions(self):
        try:
            self.__validator.validate(self.__rental_example_2)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 5)

    def test_validate__empty_date_fields_correct_id_fields__throws_four_exceptions(self):
        try:
            self.__validator.validate(self.__rental_example_3)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 4)

    def test_validate__correct_fields_wrong_chronological_logic__throws_one_exception(self):
        try:
            self.__validator.validate(self.__rental_example_4)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_validate__correct_fields__throws_no_exceptions(self):
        try:
            self.__validator.validate(self.__rental_example_5)
            assert True
        except ValidatorException:
            assert False

    def tearDown(self) -> None:
        pass
