import pickle

from domain.client import Client
from exceptions import RepositoryException


class ClientRepository:
    def __init__(self):
        self._client_data = dict()

    def search(self, client_id):
        if client_id not in self._client_data:
            raise RepositoryException("Client ID does not exist!")
        return self._client_data[client_id]

    def add(self, client):
        if client.get_id() in self._client_data:
            raise RepositoryException("Client ID already existing!")
        self._client_data[client.get_id()] = client

    def update(self, client):
        if client.get_id() not in self._client_data:
            raise RepositoryException("Client ID does not exist!")
        self._client_data[client.get_id()] = client

    def remove(self, client_id):
        if client_id not in self._client_data:
            raise RepositoryException("Client ID does not exist!")
        del self._client_data[client_id]

    def get_all(self):
        return self._client_data.values()

    def __len__(self):
        return len(self._client_data)


class ClientTextFileRepository(ClientRepository):
    def __init__(self, file_path, read_client, write_client):
        self.__file_path = file_path
        self.__read_client = read_client
        self.__write_client = write_client
        ClientRepository.__init__(self)

    def __read_all_from_file(self):
        with open(self.__file_path, 'r') as file:
            self._client_data.clear()
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if len(line):
                    client = self.__read_client(line)
                    self._client_data[client.get_id()] = client

    def __write_all_to_file(self):
        with open(self.__file_path, 'w') as file:
            for client_id in self._client_data:
                file.write(self.__write_client(self._client_data[client_id]) + '\n')

    def __append_to_file(self, client):
        with open(self.__file_path, 'a') as file:
            file.write(self.__write_client(client) + '\n')

    def search(self, client_id):
        self.__read_all_from_file()
        return ClientRepository.search(self, client_id)

    def add(self, client):
        self.__read_all_from_file()
        ClientRepository.add(self, client)
        self.__append_to_file(client)

    def remove(self, client_id):
        self.__read_all_from_file()
        ClientRepository.remove(self, client_id)
        self.__write_all_to_file()

    def update(self, client):
        self.__read_all_from_file()
        ClientRepository.update(self, client)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return ClientRepository.get_all(self)

    def __len__(self):
        self.__read_all_from_file()
        return ClientRepository.__len__(self)


class ClientBinaryFileRepository(ClientRepository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path

    def __read_clients_from_file(self):
        with open(self.__file_path, 'rb') as f:
            try:
                self._client_data = pickle.load(f)
            except EOFError:
                pass

    def __write_clients_to_file(self):
        with open(self.__file_path, 'wb') as file:
            pickle.dump(self._client_data, file)

    def __append_clients_to_file(self):
        with open(self.__file_path, 'wb') as file:
            pickle.dump(self._client_data, file)

    def search(self, client_id):
        self.__read_clients_from_file()
        return super().search(client_id)

    def add(self, client):
        self.__read_clients_from_file()
        super().add(client)
        self.__append_clients_to_file()

    def remove(self, client_id):
        self.__read_clients_from_file()
        super().remove(client_id)
        self.__write_clients_to_file()

    def update(self, client):
        self.__read_clients_from_file()
        super().update(client)
        self.__write_clients_to_file()

    def get_all(self):
        self.__read_clients_from_file()
        return super().get_all()

    def __len__(self):
        self.__read_clients_from_file()
        return super().__len__()
