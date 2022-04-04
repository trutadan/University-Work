from src.domain.client import Client
from src.exceptions_and_validators.validator import ClientValidator


class ClientServices:
    def __init__(self, repository_client):
        self.__client_repository = repository_client

    def generate_clients_data(self):
        """Create 21 procedurally generated clients in the application at startup."""
        self.__client_repository.add(Client(14, "Walter"))
        self.__client_repository.add(Client(1, "Seth"))
        self.__client_repository.add(Client(17, "Jerry"))
        self.__client_repository.add(Client(25, "Shawn"))
        self.__client_repository.add(Client(79, "Paul"))
        self.__client_repository.add(Client(13, "Bruce"))
        self.__client_repository.add(Client(22, "George"))
        self.__client_repository.add(Client(5, "Conner"))
        self.__client_repository.add(Client(11, "Roberto"))
        self.__client_repository.add(Client(74, "Lewis"))
        self.__client_repository.add(Client(65, "Ethan"))
        self.__client_repository.add(Client(51, "Dave"))
        self.__client_repository.add(Client(49, "Peter"))
        self.__client_repository.add(Client(42, "Harold"))
        self.__client_repository.add(Client(38, "Ramon"))
        self.__client_repository.add(Client(34, "Miles"))
        self.__client_repository.add(Client(27, "Liam"))
        self.__client_repository.add(Client(9, "Riley"))
        self.__client_repository.add(Client(99, "Ivan"))
        self.__client_repository.add(Client(91, "Jorge"))
        self.__client_repository.add(Client(50, "Claude"))

    def add_client_to_repository(self, client_id, client_name):
        client = Client(client_id, client_name)
        ClientValidator.validate(client)
        self.__client_repository.add(client)

    def remove_client_from_repository(self, client_id):
        client = Client(client_id, "Test")
        ClientValidator.validate(client)
        self.__client_repository.remove(client_id)

    def update_client_from_repository(self, client_id, client_name):
        client = Client(client_id, client_name)
        ClientValidator.validate(client)
        self.__client_repository.update(client)

    def search_client_by_id(self, client_id):
        clients = self.__client_repository.get_all()
        for client in clients:
            if client.get_id() == client_id:
                return client
        return None

    def search_clients_by_name(self, client_name):
        clients = self.__client_repository.get_all()
        clients_with_given_name = list()
        for client in clients:
            if client.get_name().lower() == client_name.lower() or client_name.lower() in client.get_name().lower():
                clients_with_given_name.append(client)
        return clients_with_given_name

    def get_all_clients(self):
        return self.__client_repository.get_all()
