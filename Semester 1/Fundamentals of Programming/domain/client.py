class Client:
    def __init__(self, client_id, name):
        self.__client_id = client_id
        self.__name = name

    def get_id(self):
        return self.__client_id

    def get_name(self):
        return self.__name

    def set_name(self, name):
        self.__name = name

    def __eq__(self, other):
        return self.__client_id == other.__client_id and self.__name == other.__name

    def __str__(self):
        return f"{self.__client_id} - {self.__name}"

    @staticmethod
    def from_line(line):
        parts_of_line = line.split(" - ")
        client_id = int(parts_of_line[0])
        client_name = parts_of_line[1]
        return Client(client_id, client_name)

    @staticmethod
    def to_line(client):
        line = f"{client.__client_id} - {client.__name}"
        return line
