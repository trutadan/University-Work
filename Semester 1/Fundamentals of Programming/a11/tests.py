import unittest

from domain.ship import Ship
from exceptions import BoardException
from repository.repository import ShipRepository
from services.services import TableServices
from settings.constants import PLAYER, SEA


class ShipDomainTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_ship = Ship((1, 2), (1, 5))
        self.__copy_test_ship = Ship((1, 5), (1, 2))

    def test_ship_domain__get_start_position__correct_tuple(self):
        self.assertEqual(self.__test_ship.get_start_position(), (1, 2))

    def test_ship_domain__get_end_position__correct_tuple(self):
        self.assertEqual(self.__test_ship.get_end_position(), (1, 5))

    def test_ship_domain__get_positions__correct_list_of_tuples(self):
        positions_occupied_by_ship = [(1, 2), (1, 3), (1, 4), (1, 5)]
        self.assertEqual(self.__test_ship.get_positions(), positions_occupied_by_ship)

    def test_ship_domain__get_length_of_the_ship__correct_length(self):
        self.assertEqual(len(self.__test_ship), 4)

    def test_ship_domain__two_ships_same_positions__equality_checked(self):
        self.assertEqual(self.__test_ship, self.__copy_test_ship)

    def test_ship_domain__ship_instance_with_integer__equality_not_checked(self):
        self.assertFalse(self.__test_ship == 1)

    def tearDown(self) -> None:
        pass


class ShipRepositoryTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_ship_repository = ShipRepository()

    def test_search__existing_length__corresponding_ships(self):
        clear_ships_list = list()
        self.assertEqual(self.__test_ship_repository.search(2), clear_ships_list)

    def test_search__non_existing_length__throws_exception(self):
        with self.assertRaises(BoardException):
            self.__test_ship_repository.search(10)

    def test_add__new_ship_with_existing_length__ship_successfully_added(self):
        ship = Ship((1, 2), (1, 5))
        self.__test_ship_repository.add(ship)
        self.assertEqual(len(self.__test_ship_repository), 4)

    def test_add__non_existing_ship_length__throws_exception(self):
        ship = Ship((1, 2), (1, 7))
        with self.assertRaises(BoardException):
            self.__test_ship_repository.add(ship)

    def test_remove__existing_ship__ship_successfully_removed(self):
        ship = Ship((1, 2), (1, 5))
        self.__test_ship_repository.add(ship)
        self.__test_ship_repository.remove(ship)
        self.assertEqual(self.__test_ship_repository.search(4), list())

    def test_remove__ship_not_existing__throws_exception(self):
        ship = Ship((1, 2), (1, 5))
        with self.assertRaises(BoardException):
            self.__test_ship_repository.remove(ship)

    def test_get_all__empty_repository__empty_list_of_empty_lists(self):
        self.assertEqual(self.__test_ship_repository.get_all(), [[], [], [], []])

    def tearDown(self) -> None:
        pass


class TableServicesTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__test_ship_repository = ShipRepository()
        self.__test_table_services = TableServices(PLAYER, ship_repository=self.__test_ship_repository)

    def test_table_properties__get_width__correct_value(self):
        self.assertEqual(self.__test_table_services.get_width(), 10)

    def test_table_properties__get_height__correct_value(self):
        self.assertEqual(self.__test_table_services.get_height(), 10)

    def test_table_properties__get_board__correct_matrix(self):
        width = self.__test_table_services.get_width()
        height = self.__test_table_services.get_height()
        matrix = [[SEA for row in range(width)] for column in range(height)]
        self.assertEqual(self.__test_table_services.get_board(), matrix)

    def test_table_properties__get_ship_blocks_left__correct_value(self):
        self.assertEqual(self.__test_table_services.get_ship_blocks_left(), 0)

    def test_table_properties__get_ships__list_of_empty_lists(self):
        self.assertEqual(self.__test_table_services.get_ships(), [[], [], [], []])

    def test_validate_position__invalid_table_coordinates_tuple__throws_exception(self):
        with self.assertRaises(BoardException):
            self.__test_table_services.validate_position((1, -3))

    def test_transform_position_into_coordinates__invalid_position_format__throws_exception(self):
        with self.assertRaises(BoardException):
            self.__test_table_services.transform_position_into_coordinates('ab4')

    def test_transform_position_into_coordinates__table_position_out_of_table__throws_exception(self):
        with self.assertRaises(BoardException):
            self.__test_table_services.transform_position_into_coordinates('X4')

    def test_transform_position_into_coordinates__valid_table_position__correct_coordinates_tuple(self):
        coordinates = (0, 3)
        self.assertEqual(self.__test_table_services.transform_position_into_coordinates('A4'), coordinates)

    def test_add_ship__overlaps_other_ship__throws_exception(self):
        ship = Ship((1, 2), (1, 5))
        self.__test_table_services.add_ship(ship)

        other_ship = Ship((0, 2), (3, 2))
        with self.assertRaises(BoardException):
            self.__test_table_services.add_ship(other_ship)

    def test_add_ship__invalid_ship_length__throws_exception(self):
        ship = Ship((1, 2), (1, 8))
        with self.assertRaises(BoardException):
            self.__test_table_services.add_ship(ship)

    def test_add_ship__ship_fits_the_table__successfully_added(self):
        ship = Ship((1, 2), (1, 5))
        self.__test_table_services.add_ship(ship)
        self.assertEqual(self.__test_table_services.get_ship_blocks_left(), 4)

    def test_fire_shot__position_already_attacked__throws_exception(self):
        self.__test_table_services.fire_shot((1, 2))
        with self.assertRaises(BoardException):
            self.__test_table_services.fire_shot((1, 2))

    def test_fire_shot__attacked_ship_sunk__string_sunk(self):
        ship = Ship((1, 2), (1, 3))
        self.__test_table_services.add_ship(ship)

        self.__test_table_services.fire_shot((1, 2))
        self.assertEqual(self.__test_table_services.fire_shot((1, 3)), 'sunk')

    def test_fire_shot__shot_hit_ship__string_hit(self):
        ship = Ship((1, 2), (1, 3))
        self.__test_table_services.add_ship(ship)

        self.assertEqual(self.__test_table_services.fire_shot((1, 2)), 'hit')

    def test_fire_shot__shot_missed_ship__string_miss(self):
        ship = Ship((1, 2), (1, 3))
        self.__test_table_services.add_ship(ship)

        self.assertEqual(self.__test_table_services.fire_shot((0, 2)), 'miss')

    def test_check_if_all_ship_blocks_were_hit__no_more_ship_blocks_left__True(self):
        self.assertEqual(self.__test_table_services.check_if_all_ship_blocks_were_hit(), True)

    def test_check_if_all_ship_blocks_were_hit__still_existing_ship_blocks__False(self):
        ship = Ship((1, 2), (1, 5))
        self.__test_table_services.add_ship(ship)
        self.assertEqual(self.__test_table_services.check_if_all_ship_blocks_were_hit(), False)

    def tearDown(self) -> None:
        pass
