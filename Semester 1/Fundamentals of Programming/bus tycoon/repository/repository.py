class RepositoryException(Exception):
    pass


class Repository:
    def __init__(self):
        self._repository = list()

    def add(self, entity):
        # used only for testing
        self._repository.append(entity)

    def update(self, entity):
        entity_index = 0

        entity_found = False

        for iteration_entity in self._repository:
            if iteration_entity == entity:
                entity_found = True
                break
            entity_index += 1

        if entity_found:
            self._repository[entity_index] = entity

        else:
            raise RepositoryException("There is no entity for given information.")

    def get_all(self):
        return self._repository


class FileRepository(Repository):
    def __init__(self, file_path, read_entity, write_entity):
        self.__file_path = file_path
        self.__read_entity = read_entity
        self.__write_entity = write_entity
        Repository.__init__(self)

    def __read_entities_from_file(self):
        with open(self.__file_path, 'r') as file:
            lines = file.readlines()
            self._repository.clear()

            for line in lines:
                line = line.strip()

                if len(line):
                    entity = self.__read_entity(line)
                    self._repository.append(entity)

    def __write_entities_to_file(self):
        with open(self.__file_path, 'w') as file:
            entities = self._repository

            for entity in entities:
                file.write(self.__write_entity(entity) + "\n")

    def update(self, entity):
        self.__read_entities_from_file()
        Repository.update(self, entity)
        self.__write_entities_to_file()

    def get_all(self):
        self.__read_entities_from_file()
        return Repository.get_all(self)
