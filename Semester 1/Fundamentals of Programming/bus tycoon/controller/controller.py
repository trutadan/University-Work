from domain.domain import BusDTO, Bus
from repository.repository import RepositoryException


class Controller:
    def __init__(self, bus_repository, route_repository):
        self.__bus_repository = bus_repository
        self.__route_repository = route_repository

    def get_buses_for_given_route_code(self, route_code):
        """
        Given a route code, get all the buses from the repository that contain that given code.
        :param route_code: is a
        :return: a list filled up with all buses that have the given route code.
        """

        all_buses = self.__bus_repository.get_all()

        buses_for_given_code = list()

        for bus in all_buses:
            if bus.get_code() == route_code:
                buses_for_given_code.append(bus)

        return buses_for_given_code

    def increase_usage_of_a_bus(self, bus_id, route_code):
        """
        Given an bus id and a route code, increase the number of usages for that bus by 1.
        :param bus_id: the id of the bus.
        :param route_code: the route code of the bus.
        :return: an exception error in case there was no bus found for the given information.
        """

        all_buses = self.__bus_repository.get_all()

        bus_found_flag = False

        for bus in all_buses:
            if bus.get_code() == route_code and bus.get_id() == bus_id:

                bus_found_flag = True

                bus_found = Bus(bus.get_id(), bus.get_code(), bus.get_model(), bus.get_usage()+1)

                self.__bus_repository.update(bus_found)

                break

        if bus_found_flag is False:
            raise RepositoryException("There is no bus for the given id and code.")

    def find_buses_list_in_decreasing_order_of_kilometers_travelled(self):
        """
        Sort the list of buses according to the numbers of kilometers travelled.
        :return: the sorted list of buses in decreasing order of kilometers travelled and the number of the kilometers travelled.
        """

        all_buses = self.__bus_repository.get_all()
        all_routes = self.__route_repository.get_all()

        all_buses_and_kilometers_travelled = list()

        for bus in all_buses:
            bus_route_code = bus.get_code()
            bus_usage = bus.get_usage()
            kilometers_travelled_per_usage = 0

            for route in all_routes:
                if route.get_code() == bus_route_code:
                    kilometers_travelled_per_usage = route.get_length()
                    break

            total_kilometers_travelled = bus_usage * kilometers_travelled_per_usage

            all_buses_and_kilometers_travelled.append(BusDTO(bus, total_kilometers_travelled))

        all_buses_and_kilometers_travelled = sorted(all_buses_and_kilometers_travelled, key=lambda entity: entity.get_kilometers_travelled(), reverse=True)

        return all_buses_and_kilometers_travelled
