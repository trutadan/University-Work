import unittest
from src.domain.client import Client
from src.domain.movie import Movie
from src.domain.rental import Rental, RentalDTO, RentalMovieStatisticsDTO, RentalClientStatisticsDTO

from src.exceptions_and_validators.exception import ValidatorException
from src.exceptions_and_validators.validator import ClientValidator, MovieValidator, RentalValidator

from src.repository.clientRepository import ClientRepository
from src.repository.movieRepository import MovieRepository
from src.repository.rentalRepository import RentalRepository
from src.exceptions_and_validators.exception import RepositoryException

from src.services.clientService import ClientServices
from src.services.movieService import MovieServices
from src.services.rentalService import RentalServices


class ClientDomainTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_client = Client(2, "Emma")
        self.__copy_test_client = Client(2, "Emma")

    def test_client_domain__get_client_id__correct_id(self):
        self.assertEqual(self.__test_client.get_id(), 2)

    def test_client_domain__get_client_name__correct_name(self):
        self.assertEqual(self.__test_client.get_name(), "Emma")

    def test_client_domain__set_client_name__name_changed(self):
        self.__test_client.set_name("Anne")
        self.assertEqual(self.__test_client.get_name(), "Anne")

    def test_client_domain__two_clients_same_attributes__equality_checked(self):
        self.assertTrue(self.__test_client.__eq__(self.__copy_test_client))

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


class ClientRepositoryTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_client_repository = ClientRepository()

    def test_search__existing_id__corresponding_client(self):
        client = Client("3", "Jane")
        self.__test_client_repository.add(client)
        self.assertEqual(self.__test_client_repository.search(client.get_id()), client)

    def test_search__not_existing_id__throws_exception(self):
        client = Client("3", "Jane")
        self.__test_client_repository.add(client)
        with self.assertRaises(RepositoryException):
            self.__test_client_repository.search("18")

    def test_add__new_client__client_successfully_added(self):
        client = Client("3", "Jane")
        self.__test_client_repository.add(client)
        self.assertEqual(len(self.__test_client_repository), 1)

    def test_add__existing_client_id__throws_exception(self):
        first_client_example = Client("3", "Jane")
        self.__test_client_repository.add(first_client_example)
        second_client_example = Client("3", "Roland")
        with self.assertRaises(RepositoryException):
            self.__test_client_repository.add(second_client_example)

    def test_update__existing_client__client_successfully_updated(self):
        client = Client("3", "Jane")
        self.__test_client_repository.add(client)
        updated_client = Client("3", "Roland")
        self.__test_client_repository.update(updated_client)
        self.assertEqual(self.__test_client_repository.search(client.get_id()), updated_client)

    def test_update__client_not_existing__throws_exception(self):
        first_client_example = Client("3", "Jane")
        self.__test_client_repository.add(first_client_example)
        second_client_example = Client("5", "Roland")
        with self.assertRaises(RepositoryException):
            self.__test_client_repository.update(second_client_example)

    def test_remove__existing_client__client_successfully_removed(self):
        client = Client("3", "Jane")
        self.__test_client_repository.add(client)
        self.__test_client_repository.remove("3")
        self.assertEqual(len(self.__test_client_repository), 0)

    def test_remove__client_not_existing__throws_exception(self):
        first_client_example = Client("3", "Jane")
        self.__test_client_repository.add(first_client_example)
        with self.assertRaises(RepositoryException):
            self.__test_client_repository.remove("5")

    def test_get_all__empty_repository__empty_list(self):
        self.assertEqual(str(self.__test_client_repository.get_all()), 'dict_values([])')

    def tearDown(self) -> None:
        pass


class MovieRepositoryTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_movie_repository = MovieRepository()

    def test_search__existing_id__corresponding_movie(self):
        movie = Movie("3", "The Godfather", "Description...", "Crime")
        self.__test_movie_repository.add(movie)
        self.assertEqual(self.__test_movie_repository.search(movie.get_id()), movie)

    def test_search__not_existing_id__throws_exception(self):
        movie = Movie("3", "The Godfather", "Description...", "Crime")
        self.__test_movie_repository.add(movie)
        with self.assertRaises(RepositoryException):
            self.__test_movie_repository.search("18")

    def test_add__new_movie__movie_successfully_added(self):
        movie = Movie("3", "The Godfather", "Description...", "Crime")
        self.__test_movie_repository.add(movie)
        self.assertEqual(len(self.__test_movie_repository), 1)

    def test_add__existing_movie_id__throws_exception(self):
        first_movie_example = Movie("3", "The Godfather", "The Godfather movie's description...", "Crime")
        self.__test_movie_repository.add(first_movie_example)
        second_movie_example = Movie("3", "Schindler's List", "Schindler's List movie's description...", "Drama")
        with self.assertRaises(RepositoryException):
            self.__test_movie_repository.add(second_movie_example)

    def test_update__existing_movie__movie_successfully_updated(self):
        movie = Movie("3", "The Godfather", "The Godfather movie's description...", "Crime")
        self.__test_movie_repository.add(movie)
        updated_movie = Movie("3", "Schindler's List", "Schindler's List movie's description...", "Drama")
        self.__test_movie_repository.update(updated_movie)
        self.assertEqual(self.__test_movie_repository.search(movie.get_id()), updated_movie)

    def test_update__movie_not_existing__throws_exception(self):
        first_movie_example = Movie("3", "The Godfather", "The Godfather movie's description...", "Crime")
        self.__test_movie_repository.add(first_movie_example)
        second_movie_example = Movie("5", "Schindler's List", "Schindler's List movie's description...", "Drama")
        with self.assertRaises(RepositoryException):
            self.__test_movie_repository.update(second_movie_example)

    def test_remove__existing_movie__movie_successfully_removed(self):
        movie = Movie("3", "The Godfather", "The Godfather movie's description...", "Crime")
        self.__test_movie_repository.add(movie)
        self.__test_movie_repository.remove("3")
        self.assertEqual(len(self.__test_movie_repository), 0)

    def test_remove__movie_not_existing__throws_exception(self):
        first_movie_example = Movie("3", "The Godfather", "The Godfather movie's description...", "Crime")
        self.__test_movie_repository.add(first_movie_example)
        with self.assertRaises(RepositoryException):
            self.__test_movie_repository.remove("5")

    def test_get_all__empty_repository__empty_list(self):
        self.assertEqual(str(self.__test_movie_repository.get_all()), 'dict_values([])')

    def tearDown(self) -> None:
        pass


class RentalRepositoryTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_rental_repository = RentalRepository()

    def test_search__existing_id__corresponding_rental(self):
        rental = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(rental)
        self.assertEqual(self.__test_rental_repository.search(rental.get_id()), rental)

    def test_search__not_existing_id__throws_exception(self):
        rental = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(rental)
        with self.assertRaises(RepositoryException):
            self.__test_rental_repository.search("18")

    def test_add__new_rental__rental_successfully_added(self):
        rental = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(rental)
        self.assertEqual(len(self.__test_rental_repository), 1)

    def test_add__existing_rental_id__throws_exception(self):
        first_rental_example = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(first_rental_example)
        second_rental_example = Rental("1", "11", "25", "2022-07-08", "2022-11-12", "2023-01-02")
        with self.assertRaises(RepositoryException):
            self.__test_rental_repository.add(second_rental_example)

    def test_update__existing_rental__rental_successfully_updated(self):
        rental = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(rental)
        updated_rental = Rental("1", "11", "25", "2022-07-08", "2022-11-12", "2023-01-02")
        self.__test_rental_repository.update(updated_rental)
        self.assertEqual(self.__test_rental_repository.search(rental.get_id()), updated_rental)

    def test_update__rental_not_existing__throws_exception(self):
        first_rental_example = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(first_rental_example)
        second_rental_example = Rental("3", "11", "25", "2022-07-08", "2022-11-12", "2023-01-02")
        with self.assertRaises(RepositoryException):
            self.__test_rental_repository.update(second_rental_example)

    def test_remove__existing_rental__rental_successfully_removed(self):
        rental = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(rental)
        self.__test_rental_repository.remove("1")
        self.assertEqual(len(self.__test_rental_repository), 0)

    def test_remove__rental_not_existing__throws_exception(self):
        rental = Rental("1", "3", "7", "2021-07-08", "2021-11-12", "2022-01-02")
        self.__test_rental_repository.add(rental)
        with self.assertRaises(RepositoryException):
            self.__test_rental_repository.remove("5")

    def test_get_all__empty_repository__empty_list(self):
        self.assertEqual(str(self.__test_rental_repository.get_all()), 'dict_values([])')

    def tearDown(self) -> None:
        pass


class ClientServicesTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_client_repository = ClientRepository()
        self.__client_services_test = ClientServices(self.__test_client_repository)

    def test_add_client_to_repository__client_with_empty_name_field__throws_validator_exception(self):
        try:
            self.__client_services_test.add_client_to_repository(14, "")
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_add_client_to_repository__client_with_already_existing_id__throws_repository_exception(self):
        self.__test_client_repository.add(Client(14, "Walter"))
        with self.assertRaises(RepositoryException):
            self.__client_services_test.add_client_to_repository(14, "Andrew")

    def test_add_client_to_repository__correct_client__client_successfully_added(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        clients = self.__client_services_test.get_all_clients()
        self.assertEqual(len(clients), 1)

    def test_remove_client_from_repository__client_with_negative_id__throws_validator_exception(self):
        try:
            self.__client_services_test.remove_client_from_repository(-14)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_remove_client_from_repository__client_with_non_existing_id__throws_repository_exception(self):
        with self.assertRaises(RepositoryException):
            self.__client_services_test.remove_client_from_repository(14)

    def test_remove_client_from_repository__correct_client__client_successfully_removed(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__client_services_test.remove_client_from_repository(14)
        clients = self.__client_services_test.get_all_clients()
        self.assertEqual(len(clients), 0)

    def test_update_client_from_repository__client_with_empty_name_field__throws_validator_exception(self):
        try:
            self.__client_services_test.update_client_from_repository(14, "")
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_update_client_from_repository__client_with_non_existing_id__throws_repository_exception(self):
        with self.assertRaises(RepositoryException):
            self.__client_services_test.update_client_from_repository(14, "Andrew")

    def test_update_client_from_repository__correct_client__client_successfully_updated(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__client_services_test.update_client_from_repository(14, "Walter")
        self.assertEqual(self.__client_services_test.search_clients_by_name("Walter"), [Client(14, "Walter")])

    def test_search_client_by_id__non_existing_id__None(self):
        self.assertEqual(self.__client_services_test.search_client_by_id(14), None)

    def test_search_client_by_id__existing_id__corresponding_client(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.assertEqual(self.__client_services_test.search_client_by_id(14), Client(14, "Andrew"))

    def test_search_clients_by_name__non_existing_name__empty_list(self):
        self.assertEqual(self.__client_services_test.search_clients_by_name("Andrew"), [])

    def test_search_clients_by_name__existing_name__corresponding_clients_list(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__client_services_test.add_client_to_repository(3, "Andrew")
        clients_list = [Client(14, "Andrew"), Client(3, "Andrew")]
        self.assertEqual(self.__client_services_test.search_clients_by_name("Andrew"), clients_list)

    def test_get_all_clients__empty_repository__empty_list(self):
        clients = self.__client_services_test.get_all_clients()
        self.assertEqual(len(clients), 0)

    def tearDown(self) -> None:
        pass


class MovieServicesTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_movie_repository = MovieRepository()
        self.__movie_services_test = MovieServices(self.__test_movie_repository)

    def test_add_movie_to_repository__movie_with_empty_title_field__throws_one_validator_exception(self):
        try:
            self.__movie_services_test.add_movie_to_repository(1, "", "movie's description", "drama")
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_add_movie_to_repository__movie_with_already_existing_id__throws_repository_exception(self):
        self.__test_movie_repository.add(Movie(1, "titanic", "titanic's description", "drama"))
        with self.assertRaises(RepositoryException):
            self.__movie_services_test.add_movie_to_repository(1, "the godfather", "the godfather movie's description", "action")

    def test_add_movie_to_repository__correct_movie__movie_successfully_added(self):
        self.__movie_services_test.add_movie_to_repository(1, "titanic", "titanic's description", "drama")
        clients = self.__movie_services_test.get_all_movies()
        self.assertEqual(len(clients), 1)

    def test_remove_movie_from_repository__movie_with_negative_id__throws_validator_exception(self):
        try:
            self.__movie_services_test.remove_movie_from_repository(-1)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_remove_movie_from_repository__movie_with_non_existing_id__throws_repository_exception(self):
        with self.assertRaises(RepositoryException):
            self.__movie_services_test.remove_movie_from_repository(1)

    def test_remove_movie_from_repository__correct_movie__movie_successfully_removed(self):
        self.__movie_services_test.add_movie_to_repository(1, "titanic", "titanic's description", "drama")
        self.__movie_services_test.remove_movie_from_repository(1)
        clients = self.__movie_services_test.get_all_movies()
        self.assertEqual(len(clients), 0)

    def test_update_movie_from_repository__movie_with_empty_title_field__throws_validator_exception(self):
        try:
            self.__movie_services_test.update_movie_from_repository(1, "", "movie's description", "drama")
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_update_movie_from_repository__movie_with_non_existing_id__throws_repository_exception(self):
        with self.assertRaises(RepositoryException):
            self.__movie_services_test.update_movie_from_repository(1, "titanic", "titanic's description", "drama")

    def test_update_movie_from_repository__correct_movie__movie_successfully_updated(self):
        self.__movie_services_test.add_movie_to_repository(1, "titanic", "titanic's description", "drama")
        self.__movie_services_test.update_movie_from_repository(1, "the godfather", "the godfather movie's description", "action")
        updated_movie = Movie(1, "the godfather", "the godfather movie's description", "action")
        self.assertEqual(self.__movie_services_test.search_movies_by_title("the godfather"), [updated_movie])

    def test_search_movie_by_id__non_existing_id__None(self):
        self.assertEqual(self.__movie_services_test.search_movie_by_id(14), None)

    def test_search_movie_by_id__existing_id__corresponding_movie(self):
        self.__movie_services_test.add_movie_to_repository(1, "titanic", "titanic's description", "drama")
        movie_found = Movie(1, "titanic", "titanic's description", "drama")
        self.assertEqual(self.__movie_services_test.search_movie_by_id(1), movie_found)

    def test_search_movies_by_title__non_existing_title__empty_list(self):
        self.assertEqual(self.__movie_services_test.search_movies_by_title("titanic"), [])

    def test_search_movies_by_title__existing_title__corresponding_movies_list(self):
        self.__movie_services_test.add_movie_to_repository(1, "titanic", "titanic's description", "drama")
        self.__movie_services_test.add_movie_to_repository(2, "titanic", "movie's description", "history")
        movies_list = [Movie(1, "titanic", "titanic's description", "drama"), Movie(2, "titanic", "movie's description", "history")]
        self.assertEqual(self.__movie_services_test.search_movies_by_title("titanic"), movies_list)

    def test_search_movies_by_description__non_existing_description__empty_list(self):
        self.assertEqual(self.__movie_services_test.search_movies_by_description("movie's description"), [])

    def test_search_movies_by_description__existing_description__corresponding_movies_list(self):
        self.__movie_services_test.add_movie_to_repository(1, "titanic", "movie's description", "drama")
        self.__movie_services_test.add_movie_to_repository(2, "the godfather", "movie's description", "action")
        movies_list = [Movie(1, "titanic", "movie's description", "drama"), Movie(2, "the godfather", "movie's description", "action")]
        self.assertEqual(self.__movie_services_test.search_movies_by_description("movie's description"), movies_list)

    def test_search_movies_by_genre__non_existing_genre__empty_list(self):
        self.assertEqual(self.__movie_services_test.search_movies_by_title("action"), [])

    def test_search_movies_by_genre__existing_genre__corresponding_movies_list(self):
        self.__movie_services_test.add_movie_to_repository(1, "titanic", "titanic movie's description", "drama")
        self.__movie_services_test.add_movie_to_repository(2, "the godfather", "the godfather movie's description", "drama")
        movies_list = [Movie(1, "titanic", "titanic movie's description", "drama"), Movie(2, "the godfather", "the godfather movie's description", "drama")]
        self.assertEqual(self.__movie_services_test.search_movies_by_genre("drama"), movies_list)

    def test_get_all_movies__empty_repository__empty_list(self):
        clients = self.__movie_services_test.get_all_movies()
        self.assertEqual(len(clients), 0)

    def tearDown(self) -> None:
        pass


class RentalServicesTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_client_repository = ClientRepository()
        self.__test_movie_repository = MovieRepository()
        self.__test_rental_repository = RentalRepository()
        self.__rental_services_test = RentalServices(self.__test_client_repository, self.__test_movie_repository, self.__test_rental_repository)

    def test_get_late_rentals_descending_order__no_late_rentals__empty_list(self):
        first_client = Client(1, "Andrew")
        self.__test_client_repository.add(first_client)
        second_client = Client(2, "Sett")
        self.__test_client_repository.add(second_client)

        first_movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(first_movie)
        second_movie = Movie(2, "the godfather", "the godfather movie's description", "drama")
        self.__test_movie_repository.add(second_movie)

        first_rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", "2021-04-08")
        self.__test_rental_repository.add(first_rental)
        second_rental = Rental(5, 2, 2, "2021-02-03", "2021-05-02", "2021-05-01")
        self.__test_rental_repository.add(second_rental)

        self.assertEqual(self.__rental_services_test.get_late_rentals_descending_order(), [])

    def test_get_all_rentals__one_rental_in_repository__output_format(self):
        client = Client(1, "Andrew")
        self.__test_client_repository.add(client)
        movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(movie)
        rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", '"n/a"')
        self.__test_rental_repository.add(rental)

        rentals = self.__rental_services_test.get_all_rentals()
        added_rental = rentals[0]

        self.assertEqual(added_rental.__str__(), '1 - Andrew - titanic - 2021-02-03 - 2021-05-02 - "n/a"')

    def tearDown(self) -> None:
        pass

