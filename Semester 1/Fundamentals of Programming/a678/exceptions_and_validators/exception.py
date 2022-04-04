class RepositoryException(Exception):
    pass


class DateValidatorException(Exception):
    pass


class ValidatorException(Exception):
    def __init__(self, errors):
        self.errors = errors

    def get_errors(self):
        return self.errors
