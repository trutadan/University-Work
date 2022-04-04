from unittest import TestCase

from controller.controller import Controller
from domain.domain import Bus, Route, BusDTO
from repository.repository import Repository, RepositoryException


class TestController(TestCase):
    def setUp(self) -> None:
        self.__bus_repository = Repository()
        self.__route_repository = Repository()
        self.__services = Controller(self.__bus_repository, self.__route_repository)
        self.__first_bus = Bus(1, 1, 'mercedes', 7)
        self.__first_route = Route(1, 10)
        self.__bus_repository.add(self.__first_bus)
        self.__route_repository.add(self.__first_route)

    def test_buses_for_given_route_code__non_existing_code__empty_list(self):
        self.assertEqual(self.__services.get_buses_for_given_route_code('3'), [])

    def test_buses_for_given_route_code__existing_code__correct_list_with_buses(self):
        self.assertEqual(self.__services.get_buses_for_given_route_code(1), [self.__first_bus])

    def test_increase_usage_of_a_bus__existing_id_and_code__bus_successfully_updated(self):
        self.__services.increase_usage_of_a_bus(1, 1)
        buses = self.__bus_repository.get_all()
        self.assertEqual(buses[0].get_usage(), 8)

    def test_increase_usage_of_a_bus__non_existing_id_and_code__throws_exception(self):
        with self.assertRaises(RepositoryException):
            self.__services.increase_usage_of_a_bus(1, 2)

    def test_find_buses_list_in_decreasing_order_of_kilometers_travelled__filled_repositories__correctly_sorted_list(
            self):
        second_bus = Bus(4, 1, 'electric', 12)
        self.__bus_repository.add(second_bus)
        expected_list = [120, 70]
        obtained_list = [
            self.__services.find_buses_list_in_decreasing_order_of_kilometers_travelled()[0].get_kilometers_travelled(),
            self.__services.find_buses_list_in_decreasing_order_of_kilometers_travelled()[1].get_kilometers_travelled()]

        self.assertEqual(expected_list, obtained_list)

    def tearDown(self) -> None:
        pass
