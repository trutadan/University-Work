class Expense:
    """
    Each expense has a day (integer between 1 and 30), amount of money (positive integer) and expense type (string).
    """

    def __init__(self, expense_day, expense_amount, expense_type):
        self._expense_day = expense_day
        self._expense_amount = expense_amount
        self._expense_type = expense_type

    # getters

    @property
    def expense_day(self):
        return self._expense_day

    @property
    def expense_amount(self):
        return self._expense_amount

    @property
    def expense_type(self):
        return self._expense_type

    @expense_day.setter
    def expense_day(self, new_expense_day):
        if isinstance(new_expense_day, int):

            if new_expense_day < 1 or new_expense_day > 30:
                raise ValueError("The new day number should be an integer between 1 and 30.")
            self._expense_day = new_expense_day

        else:
            raise ValueError("The new day is not integer.")

    # setters

    @expense_amount.setter
    def expense_amount(self, new_expense_amount):
        if isinstance(new_expense_amount, int):

            if new_expense_amount < 0:
                raise ValueError("The new expense amount should be a positive integer.")
            self._expense_amount = new_expense_amount

        else:
            raise ValueError("The new expense amount is not integer.")

    @expense_type.setter
    def expense_type(self, new_expense_type):
        possible_expense_types = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']

        if isinstance(new_expense_type, str):

            if new_expense_type not in possible_expense_types:
                raise ValueError("The new expense type is not a valid option. Choose "
                                 "between 'housekeeping', 'food', 'transport', 'clothing', 'internet', 'others'.")
            self._expense_amount = new_expense_type

        else:
            raise ValueError("The new expense type is not a word.")

    def __str__(self):
        return f'In the day {self._expense_day}, the expense "{self._expense_type}" ' \
               f'was made for the amount of {self._expense_amount}.'
