import copy
import re

from domain.client import Client
from domain.validators import ClientValidator
from services.undoRedoService import Call, Operation, ComplexOperation
from data_structure.dataStructure import IterableDataStructure


class ClientServices:
    def __init__(self, repository_client, rental_services, undo_redo_services):
        self.__client_repository = repository_client
        self.__undo_redo_services = undo_redo_services
        self.__rental_services = rental_services

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
        """
        Add a new client to the client data list, by creating a new instance of the Client class and passing
        it to the add function from the Repository class.
        :param client_id: the id of the client entered.
        :param client_name: the name of the client entered.
        :pre-condition: client_id must be a numeric string(positive integer), client_name must be a string.
        """
        client = Client(client_id, client_name)
        ClientValidator.validate(client)
        self.__client_repository.add(client)

        undo_call = Call(self.__client_repository.remove, client_id)
        redo_call = Call(self.__client_repository.add, client)

        self.__undo_redo_services.record(Operation(undo_call, redo_call))

    def remove_client_from_repository(self, client_id):
        """
        Remove an existing client from the client data list, by creating a new instance of the Client class with the
        given id and passing it to the remove function from the Repository class.
        :param client_id: the id of the client entered.
        :pre-condition: client_id must be a numeric string(positive integer).
        """
        client = Client(client_id, "Test")
        ClientValidator.validate(client)

        client_found = self.__client_repository.search(client_id)

        self.__client_repository.remove(client_id)

        undo_call = Call(self.__client_repository.add, client_found)
        redo_call = Call(self.__client_repository.remove, client_id)

        undo_redo_operations = list()
        undo_redo_operations.append(Operation(undo_call, redo_call))

        rentals = self.__rental_services.get_all_rentals()

        self.__rental_services.remove_rentals_for_given_client_id(client_id)

        for rental in rentals:
            if rental.get_client_id() == client_id:
                redo_call = Call(self.__rental_services.remove_rentals_for_given_client_id, client_id)
                undo_call = Call(self.__rental_services.add_rental_to_repository, rental)
                undo_redo_operations.append(Operation(undo_call, redo_call))

        self.__undo_redo_services.record(ComplexOperation(undo_redo_operations))

    def update_client_from_repository(self, client_id, client_name):
        """
        Update an existing client to the client data list, by creating a new instance of the Client class with the
        new given data and passing it to the update function from the Repository class.
        :param client_id: the id of the client entered.
        :param client_name: the name of the client entered.
        :pre-condition: client_id must be a numeric string(positive integer), client_name must be a string.
        """
        client = Client(client_id, client_name)
        ClientValidator.validate(client)

        client_before_update = copy.deepcopy(self.__client_repository.search(client_id))
        self.__client_repository.update(client)

        undo_call = Call(self.__client_repository.update, client_before_update)
        redo_call = Call(self.__client_repository.update, client)

        self.__undo_redo_services.record(Operation(undo_call, redo_call))

    def search_client_by_id(self, client_id):
        """
        Given the id of a client, search through the repository and find if there exists a client with this id.
        :param client_id:
        :return: the matching item for the given id.
        """
        clients = self.__client_repository.get_all()

        # for client in clients:
        #     if client.get_id() == client_id:
        #         return client
        # return None

        client_found = IterableDataStructure.filter_elements_from_a_list(clients, lambda person: int(person.get_id()) == client_id)
        if not len(client_found):
            return None
        else:
            return client_found[0]

    def search_clients_by_name(self, client_name):
        """
        Given the name of a client, search through the repository and find if there exist clients with this name.
        The search will be case-insensitive, partial string matching.
        :param client_name: the name of the client after which we must look.
        :return: the matching items for the given name.
        """
        clients = self.__client_repository.get_all()

        # clients_with_given_name = list()
        # for client in clients:
        #     if client.get_name().lower() == client_name.lower() or client_name.lower() in client.get_name().lower():
        #         clients_with_given_name.append(client)

        clients_with_given_name = IterableDataStructure.filter_elements_from_a_list(clients, lambda client: re.findall(client_name.lower(), client.get_name().lower()))
        return clients_with_given_name

    def get_all_clients(self):
        """
        Get all the data about clients from the Repository class.
        :return: all the client information from the repository.
        """
        return self.__client_repository.get_all()
