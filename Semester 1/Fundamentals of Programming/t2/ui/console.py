import random
import re

from domain.domain import Ride


class UI:
    def __init__(self, taxi_services, ride_services):
        self._taxi_services = taxi_services
        self._ride_services = ride_services

    @staticmethod
    def print_menu():
        print("add ride from x,y to a,b")
        print("simulate x rides")
        print("exit")

    def run_program(self):
        while True:
            operational_taxis = input("Enter a number of taxis between 0 and 10: ")

            try:
                operational_taxis = int(operational_taxis)
            except ValueError:
                continue

            if 1 <= operational_taxis <= 10:
                break

        print(f"{operational_taxis} taxis has been generated.")
        self._taxi_services.generate_random_taxis(operational_taxis)

        while True:
            self.print_menu()
            command = input("Enter a command: ").lower()

            if command == 'exit':
                break

            split_command = re.findall(r'\w+', command)
            if split_command[0] == 'add' and split_command[1] == 'ride':

                start_position = (int(split_command[3]), int(split_command[4]))
                end_position = (int(split_command[6]), int(split_command[7]))

                if start_position[0] < 0 or start_position[0] > 100:
                    print("not valid coordinates.")
                    continue

                if end_position[0] < 0 or end_position[0] > 100:
                    print("not valid coordinates.")
                    continue

                ride = Ride(start_position, end_position)
                closest_taxi = self._ride_services.add(ride)
                print("The ride has been successfully made!")
                print(f"ID: {closest_taxi.get_id()}, start_position: {start_position}, end_position: {end_position}.")

                taxis = self._taxi_services.get_all_sorted()
                for taxi in taxis:
                    print(taxi)

            elif split_command[0] == 'simulate' and split_command[2] == 'rides' and split_command[1].isnumeric():
                number_of_rides = int(split_command[1])

                if number_of_rides < 0:
                    print("negative number!")
                    continue

                index = 0
                while index < number_of_rides:
                    start_position = (random.randint(0, 100), random.randint(0, 100))
                    end_position = (random.randint(0, 100), random.randint(0, 100))
                    if self._taxi_services.calculate_Manhattan_distance(start_position, end_position) < 10:
                        print("The length of ride must be at least 10!")
                        continue

                    ride = Ride(start_position, end_position)
                    closest_taxi = self._ride_services.add(ride)
                    print("The ride has been successfully made!")
                    print(f"ID: {closest_taxi.get_id()}, start_position: {start_position}, end_position: {end_position}.")

                    taxis = self._taxi_services.get_all_sorted()
                    for taxi in taxis:
                        print(taxi)

                    index += 1

            else:
                continue
