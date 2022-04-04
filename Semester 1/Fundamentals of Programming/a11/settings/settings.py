from configparser import ConfigParser

from exceptions import SettingsException
from settings.constants import *


class Settings:
    def __init__(self):
        self.__settings_parser = ConfigParser()
        self.__settings_parser.read(SETTINGS_FILE_PATH)

    def validate_entered_settings(self):
        self.get_width()
        self.get_height()
        self.get_number_of_ships()

    def get_width(self):
        grid_width = int(self.__settings_parser.get("settings", "width"))
        if grid_width not in range(2, 20):
            raise SettingsException("Invalid width!")
        return grid_width

    def set_width(self, grid_width):
        if grid_width not in range(2, 20):
            raise SettingsException("Invalid height!")
        self.__settings_parser.set("settings", "width", str(grid_width))
        self.__save_settings()

    def get_height(self):
        grid_height = int(self.__settings_parser.get("settings", "height"))
        if grid_height not in range(2, 20):
            raise SettingsException("Invalid height!")
        return grid_height

    def set_height(self, grid_height):
        if grid_height not in range(2, 20):
            raise SettingsException("Invalid height!")
        self.__settings_parser.set("settings", "height", str(grid_height))
        self.__save_settings()

    def get_number_of_ships(self):
        number_of_carriers = int(self.__settings_parser.get("settings", "carriers"))
        if number_of_carriers not in range(0, 10):
            raise SettingsException("Invalid number of carriers!")

        number_of_battleships = int(self.__settings_parser.get("settings", "battleships"))
        if number_of_battleships not in range(0, 10):
            raise SettingsException("Invalid number of battleships!")

        number_of_destroyers = int(self.__settings_parser.get("settings", "destroyers"))
        if number_of_destroyers not in range(0, 10):
            raise SettingsException("Invalid number of destroyers!")

        number_of_patrol_boats = int(self.__settings_parser.get("settings", "patrol boats"))
        if number_of_patrol_boats not in range(0, 10):
            raise SettingsException("Invalid number of patrol boats!")

        return {CARRIER: number_of_carriers, BATTLESHIP: number_of_battleships, DESTROYER: number_of_destroyers, PATROL_BOAT: number_of_patrol_boats}

    def set_number_of_ships(self, dictionary_with_number_of_ships):
        for value in dictionary_with_number_of_ships.values():
            if value not in range(0, 10):
                raise SettingsException("Invalid number of ships!")

        self.__settings_parser.set("settings", "carriers", str(dictionary_with_number_of_ships[CARRIER]))
        self.__settings_parser.set("settings", "battleships", str(dictionary_with_number_of_ships[BATTLESHIP]))
        self.__settings_parser.set("settings", "destroyers", str(dictionary_with_number_of_ships[DESTROYER]))
        self.__settings_parser.set("settings", "patrol boat", str(dictionary_with_number_of_ships[PATROL_BOAT]))

        self.__save_settings()

    def get_ai_difficulty(self):
        ai = self.__settings_parser.get("settings", "difficulty")
        if ai not in ("normal", "hard"):
            raise SettingsException("Invalid AI choice.")
        return ai

    def set_ai_difficulty(self, ai_difficulty):
        if ai_difficulty not in ("normal", "hard"):
            raise SettingsException("Invalid AI choice.")
        self.__settings_parser.set("settings", "difficulty", ai_difficulty)

        self.__save_settings()

    def __save_settings(self):
        with open("settings.ini", "w") as file:
            self.__settings_parser.write(file)
