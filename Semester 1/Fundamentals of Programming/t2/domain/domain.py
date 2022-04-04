class Taxi:
    def __init__(self, taxi_id, position, total_fare=0):
        self._taxi_id = taxi_id
        self._position = position
        self._total_fare = total_fare

    def get_id(self):
        return self._taxi_id

    def get_position(self):
        return self._position

    def set_position(self, position):
        self._position = position

    def get_total_fare(self):
        return self._total_fare

    def set_total_fare(self, total_fare):
        self._total_fare = total_fare

    def __str__(self):
        return str(self._taxi_id) + ' ' + str(self._position) + ' ' + str(self._total_fare)


class Ride:
    def __init__(self, start_position, end_position):
        self._start_position = start_position
        self._end_position = end_position

    def get_start_position(self):
        return self._start_position

    def get_end_position(self):
        return self._end_position
