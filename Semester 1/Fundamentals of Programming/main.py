from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from repository.clientRepository import ClientTextFileRepository, ClientRepository, ClientBinaryFileRepository
from repository.movieRepository import MovieFileRepository, MovieRepository, MovieBinaryFileRepository
from repository.rentalRepository import RentalFileRepository, RentalRepository, RentalBinaryFileRepository
from services.clientService import ClientServices
from services.movieService import MovieServices
from services.rentalService import RentalServices
from services.undoRedoService import UndoRedoServices
from ui.ui import UI


def get_settings_for_initialization(file_name):
    with open(file_name) as settings_file:
        lines = [line.split("=") for line in settings_file.readlines()]
        settings_dictionary = {key.strip(): value.strip() for key, value in lines}
    return settings_dictionary


def main():

    settings_dictionary = get_settings_for_initialization("repository_files/settings.properties")

    try:
        repository_type = settings_dictionary['repository']
        clients_repository_file_name = "repository_files/" + settings_dictionary['clients'].strip('"')
        movies_repository_file_name = "repository_files/" + settings_dictionary['movies'].strip('"')
        rentals_repository_file_name = "repository_files/" + settings_dictionary['rentals'].strip('"')
    except KeyError:
        print("You need to check settings. Something is messed up!")
        return

    if repository_type == "inmemory":
        client_repository = ClientRepository()
        movie_repository = MovieRepository()
        rental_repository = RentalRepository()

        undo_redo_services = UndoRedoServices()

        rental_services = RentalServices(client_repository, movie_repository, rental_repository, undo_redo_services)
        movie_services = MovieServices(movie_repository, rental_services, undo_redo_services)
        client_services = ClientServices(client_repository, rental_services, undo_redo_services)

        client_services.generate_clients_data()
        movie_services.generate_movies_data()
        rental_services.generate_random_rental_data()

        ui = UI(client_services, movie_services, rental_services, undo_redo_services)

        ui.run_program()

    elif repository_type == "text-files":
        client_repository = ClientTextFileRepository(clients_repository_file_name, Client.from_line, Client.to_line)
        movie_repository = MovieFileRepository(movies_repository_file_name, Movie.from_line, Movie.to_line)
        rental_repository = RentalFileRepository(rentals_repository_file_name, Rental.from_line, Rental.to_line)

        undo_redo_services = UndoRedoServices()

        rental_services = RentalServices(client_repository, movie_repository, rental_repository, undo_redo_services)
        movie_services = MovieServices(movie_repository, rental_services, undo_redo_services)
        client_services = ClientServices(client_repository, rental_services, undo_redo_services)

        ui = UI(client_services, movie_services, rental_services, undo_redo_services)

        ui.run_program()

    elif repository_type == "binary files":
        client_repository = ClientBinaryFileRepository(clients_repository_file_name)
        movie_repository = MovieBinaryFileRepository(movies_repository_file_name)
        rental_repository = RentalBinaryFileRepository(rentals_repository_file_name)

        undo_redo_services = UndoRedoServices()

        rental_services = RentalServices(client_repository, movie_repository, rental_repository, undo_redo_services)
        movie_services = MovieServices(movie_repository, rental_services, undo_redo_services)
        client_services = ClientServices(client_repository, rental_services, undo_redo_services)

        ui = UI(client_services, movie_services, rental_services, undo_redo_services)

        ui.run_program()

    else:
        print("You need to check settings. Something is messed up!")
        return


if __name__ == '__main__':
    main()
