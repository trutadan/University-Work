import random

from domain.domain import Taxi


class TaxiServices:
    def __init__(self, taxi_repository):
        self._taxi_repository = taxi_repository

    @staticmethod
    def calculate_Manhattan_distance(first_position, second_position):
        return abs(first_position[0] - second_position[0]) + abs(first_position[1] - second_position[1])

    def generate_random_taxis(self, number_of_taxis):
        for index in range(number_of_taxis):
            while True:
                position = (random.randint(0, 100), random.randint(0, 100))
                taxis = self._taxi_repository.get_all()
                valid_position = True
                for taxi in taxis:
                    if self.calculate_Manhattan_distance(taxi.get_position(), position) <= 5:
                        valid_position = False

                if valid_position:
                    self._taxi_repository.add(Taxi(index, position))
                    break

    def get_all_sorted(self):
        taxis = list(self._taxi_repository.get_all())
        taxis.sort(key=lambda taxi: taxi.get_total_fare(), reverse=True)
        return taxis


class RideServices:
    def __init__(self, taxi_repository):
        self._taxi_repository = taxi_repository

    @staticmethod
    def calculate_Manhattan_distance(first_position, second_position):
        return abs(first_position[0] - second_position[0]) + abs(first_position[1] - second_position[1])

    def add(self, ride):
        start_position = ride.get_start_position()
        end_position = ride.get_end_position()
        taxis = self._taxi_repository.get_all()
        minim_distance = 200

        for taxi in taxis:
            taxi_position = taxi.get_position()
            distance = self.calculate_Manhattan_distance(taxi_position, start_position)
            if distance < minim_distance:
                minim_distance = distance
                closest_taxi = taxi

        closest_taxi.set_position(end_position)
        actual_taxi_fare = closest_taxi.get_total_fare()
        actual_taxi_fare += minim_distance
        closest_taxi.set_total_fare(actual_taxi_fare)

        return closest_taxi
