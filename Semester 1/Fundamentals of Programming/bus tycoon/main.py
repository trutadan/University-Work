from controller.controller import Controller
from domain.domain import Bus, Route
from repository.repository import FileRepository
from ui.ui import UI


def main():
    bus_repository = FileRepository('buses.txt', Bus.from_line, Bus.to_line)
    route_repository = FileRepository('routes.txt', Route.from_line, Route.to_line)
    program_controller = Controller(bus_repository, route_repository)
    ui = UI(program_controller)

    ui.run_program()


main()
