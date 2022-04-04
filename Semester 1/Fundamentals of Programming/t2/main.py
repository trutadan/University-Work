from repository.repository import Repository
from services.services import RideServices, TaxiServices
from ui.console import UI

if __name__ == '__main__':
    taxi_repository = Repository()
    ride_repository = Repository()

    taxi_services = TaxiServices(taxi_repository)
    ride_services = RideServices(taxi_repository)

    console = UI(taxi_services, ride_services)

    console.run_program()
