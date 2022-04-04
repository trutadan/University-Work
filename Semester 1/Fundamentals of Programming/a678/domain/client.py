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
