class ValidatorException(Exception):
    def __init__(self, errors):
        self.__errors = errors

    def get_errors(self):
        return self.__errors


class DateValidatorException(Exception):
    pass


class RepositoryException(Exception):
    pass


class UndoServiceException(Exception):
    pass
