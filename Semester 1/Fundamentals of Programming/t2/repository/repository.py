class RepositoryException(Exception):
    pass


class Repository:
    def __init__(self):
        self._data = dict()

    def search(self, entity_id):
        if entity_id not in self._data:
            raise RepositoryException("ID does not exist!")
        return self._data[entity_id]

    def add(self, entity):
        if entity.get_id() in self._data:
            raise RepositoryException("ID already existing!")
        self._data[entity.get_id()] = entity

    def update(self, entity):
        if entity.get_id() not in self._data:
            raise RepositoryException("ID does not exist!")
        self._data[entity.get_id()] = entity

    def remove(self, entity_id):
        if entity_id not in self._data:
            raise RepositoryException("ID does not exist!")
        del self._data[entity_id]

    def get_all(self):
        return self._data.values()

    def __len__(self):
        return len(self._data)
