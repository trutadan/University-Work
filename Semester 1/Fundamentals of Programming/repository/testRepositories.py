import unittest

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from repository.clientRepository import ClientRepository
from repository.movieRepository import MovieRepository
from repository.rentalRepository import RentalRepository
from exceptions import RepositoryException


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
