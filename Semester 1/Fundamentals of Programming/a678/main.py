from repository.clientRepository import ClientRepository
from repository.movieRepository import MovieRepository
from repository.rentalRepository import RentalRepository
from services.clientService import ClientServices
from services.movieService import MovieServices
from services.rentalService import RentalServices
from ui.ui import UI

client_repository = ClientRepository()
movie_repository = MovieRepository()
rental_repository = RentalRepository()

rental_services = RentalServices(client_repository, movie_repository, rental_repository)
movie_services = MovieServices(movie_repository)
client_services = ClientServices(client_repository)

ui = UI(client_services, movie_services, rental_services)

ui.run_program()
