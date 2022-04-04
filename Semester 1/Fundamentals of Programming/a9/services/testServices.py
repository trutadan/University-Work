import unittest

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from repository.clientRepository import ClientRepository
from repository.movieRepository import MovieRepository
from repository.rentalRepository import RentalRepository
from services.clientService import ClientServices
from services.movieService import MovieServices
from exceptions import RepositoryException, ValidatorException
from services.rentalService import RentalServices
from services.undoRedoService import UndoRedoServices, UndoServiceException


class ClientServicesTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_client_repository = ClientRepository()
        self.__test_movie_repository = MovieRepository()
        self.__test_rental_repository = RentalRepository()
        self.__undo_redo_test_services = UndoRedoServices()
        self.__test_rental_services = RentalServices(self.__test_client_repository, self.__test_movie_repository, self.__test_rental_repository, self.__undo_redo_test_services)
        self.__client_services_test = ClientServices(self.__test_client_repository, self.__test_rental_services, self.__undo_redo_test_services)

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

    def test_undo__add_client_to_repository__client_removed(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__undo_redo_test_services.undo()
        self.assertEqual(self.__client_services_test.search_clients_by_name("Andrew"), [])

    def test_undo_redo__add_client_to_repository__client_added_again(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__undo_redo_test_services.undo()
        self.__undo_redo_test_services.redo()
        self.assertEqual(len(self.__client_services_test.get_all_clients()), 1)

    def test_undo__remove_client_from_repository__client_added(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__client_services_test.remove_client_from_repository(14)
        self.__undo_redo_test_services.undo()
        self.assertEqual(len(self.__client_services_test.get_all_clients()), 1)

    def test_undo_redo__remove_client_from_repository__client_removed_again(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__client_services_test.remove_client_from_repository(14)
        self.__undo_redo_test_services.undo()
        self.__undo_redo_test_services.redo()
        self.assertEqual(len(self.__client_services_test.get_all_clients()), 0)

    def test_undo_redo__remove_client_from_repository__client_added_again(self):
        self.__client_services_test.add_client_to_repository(14, "Andrew")
        self.__undo_redo_test_services.undo()
        self.__undo_redo_test_services.redo()
        self.assertEqual(len(self.__client_services_test.get_all_clients()), 1)

    def test_undo__no_action_done__throws_exception(self):
        with self.assertRaises(UndoServiceException):
            self.__undo_redo_test_services.undo()

    def tearDown(self) -> None:
        pass


class MovieServicesTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_client_repository = ClientRepository()
        self.__test_movie_repository = MovieRepository()
        self.__test_rental_repository = RentalRepository()
        self.__undo_redo_test_services = UndoRedoServices()
        self.__test_rental_services = RentalServices(self.__test_client_repository, self.__test_movie_repository, self.__test_rental_repository, self.__undo_redo_test_services)
        self.__test_movie_repository = MovieRepository()
        self.__movie_services_test = MovieServices(self.__test_movie_repository, self.__test_rental_services, self.__undo_redo_test_services)

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
        movies = self.__movie_services_test.get_all_movies()
        self.assertEqual(len(movies), 1)

    def test_remove_movie_from_repository__movie_with_negative_id__throws_validator_exception(self):
        try:
            self.__movie_services_test.remove_movie_from_repository(-1)
            assert False
        except ValidatorException as exception:
            self.assertEqual(len(exception.get_errors()), 1)

    def test_remove_movie_from_repository__movie_with_non_existing_id__throws_repository_exception(self):
        with self.assertRaises(RepositoryException):
            self.__movie_services_test.remove_movie_from_repository(1)

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
        self.__undo_redo_test_services = UndoRedoServices()
        self.__rental_services_test = RentalServices(self.__test_client_repository, self.__test_movie_repository, self.__test_rental_repository, self.__undo_redo_test_services)

    def test_add_rental_to_repository__already_existing_rental__throws_exception(self):
        first_client = Client(1, "Andrew")
        self.__test_client_repository.add(first_client)

        first_movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(first_movie)

        first_rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", "2021-04-08")
        self.__test_rental_repository.add(first_rental)

        second_client = Client(2, "Sett")
        self.__test_client_repository.add(second_client)

        second_movie = Movie(2, "the godfather", "the godfather movie's description", "drama")
        self.__test_movie_repository.add(second_movie)

        second_rental = Rental(1, 2, 2, "2021-02-03", "2021-05-02", "2021-05-01")

        with self.assertRaises(RepositoryException):
            self.__rental_services_test.add_rental_to_repository(second_rental)

    def test_add_rental_to_repository__new_rental__rental_successfully_added(self):
        first_client = Client(1, "Andrew")
        self.__test_client_repository.add(first_client)
        second_client = Client(2, "Sett")
        self.__test_client_repository.add(second_client)

        first_movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(first_movie)
        second_movie = Movie(2, "the godfather", "the godfather movie's description", "drama")
        self.__test_movie_repository.add(second_movie)

        first_rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", "2021-04-08")
        self.__rental_services_test.add_rental_to_repository(first_rental)
        second_rental = Rental(5, 2, 2, "2021-02-03", "2021-05-02", "2021-05-01")
        self.__rental_services_test.add_rental_to_repository(second_rental)

        self.assertEqual(len(self.__rental_services_test.get_all_rentals()), 2)

    def test_remove_rentals_for_given_client_id__existing_id__rentals_successfully_removed(self):
        first_client = Client(1, "Andrew")
        self.__test_client_repository.add(first_client)

        first_movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(first_movie)
        second_movie = Movie(2, "the godfather", "the godfather movie's description", "drama")
        self.__test_movie_repository.add(second_movie)

        first_rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", "2021-04-08")
        self.__rental_services_test.add_rental_to_repository(first_rental)
        second_rental = Rental(5, 2, 1, "2021-02-03", "2021-05-02", "2021-05-01")
        self.__rental_services_test.add_rental_to_repository(second_rental)

        self.__rental_services_test.remove_rentals_for_given_client_id(1)

        self.assertEqual(len(self.__rental_services_test.get_all_rentals()), 0)

    def test_remove_rentals_for_given_movie_id__existing_id__rentals_successfully_removed(self):
        first_client = Client(1, "Andrew")
        self.__test_client_repository.add(first_client)
        second_client = Client(2, "Sett")
        self.__test_client_repository.add(second_client)

        first_movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(first_movie)

        first_rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", "2021-04-08")
        self.__rental_services_test.add_rental_to_repository(first_rental)
        second_rental = Rental(5, 1, 2, "2021-02-03", "2021-05-02", "2021-05-01")
        self.__rental_services_test.add_rental_to_repository(second_rental)

        self.__rental_services_test.remove_rentals_for_given_movie_id(1)

        self.assertEqual(len(self.__rental_services_test.get_all_rentals()), 0)

    def test_rent_new_movie__new_rental_id__rental_successfully_added(self):
        client = Client(1, "Andrew")
        self.__test_client_repository.add(client)

        movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(movie)

        self.__rental_services_test.rent_new_movie(1, 1, 1, "2021-02-03")
        self.assertEqual(self.__rental_services_test.get_all_rentals_dto()[0].__str__(), '1 - Andrew - titanic - 2021-02-03 - 2021-05-04 - "n/a"')

    def test_return_movie__existing_rental_id__rental_successfully_updated(self):
        client = Client(1, "Andrew")
        self.__test_client_repository.add(client)

        movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(movie)

        self.__rental_services_test.rent_new_movie(1, 1, 1, "2021-02-03")

        self.__rental_services_test.return_a_movie(1, "2022-01-01")

        self.assertEqual(self.__rental_services_test.get_all_rentals_dto()[0].__str__(), '1 - Andrew - titanic - 2021-02-03 - 2021-05-04 - 2022-01-01')

    def test_return_movie__non_existing_rental_id__throws_exception(self):
        with self.assertRaises(RepositoryException):
            self.__rental_services_test.return_a_movie(2, "2022-01-01")

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

        rentals = self.__rental_services_test.get_all_rentals_dto()
        added_rental = rentals[0]

        self.assertEqual(added_rental.__str__(), '1 - Andrew - titanic - 2021-02-03 - 2021-05-02 - "n/a"')

    def test_get_all_rentals_dto__empty_repository__empty_list(self):
        self.assertEqual(self.__rental_services_test.get_all_rentals_dto(), [])

    def test_get_all_rentals_dto__repository_with_client__corresponding_format(self):
        first_client = Client(1, "Andrew")
        self.__test_client_repository.add(first_client)

        first_movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(first_movie)

        first_rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", "2021-04-08")
        self.__test_rental_repository.add(first_rental)

        first_rental_output_format = self.__rental_services_test.get_all_rentals_dto()[0]

        self.assertEqual(first_rental_output_format.__str__(), "1 - Andrew - titanic - 2021-02-03 - 2021-05-02 - 2021-04-08")

    def test_get_all_rentals__one_rental_in_repository__length_one(self):
        first_client = Client(1, "Andrew")
        self.__test_client_repository.add(first_client)

        first_movie = Movie(1, "titanic", "titanic movie's description", "drama")
        self.__test_movie_repository.add(first_movie)

        first_rental = Rental(1, 1, 1, "2021-02-03", "2021-05-02", "2021-04-08")
        self.__test_rental_repository.add(first_rental)

        self.assertEqual(len(self.__rental_services_test.get_all_rentals()), 1)

    def tearDown(self) -> None:
        pass
