import random
import copy
from src.domain.domain import Expense


class ExpenseServices:

    def __init__(self):
        self._expenses_repository = []
        self._expenses_repository_history = []

    @property
    def expenses_repository(self):
        """
        Get the current repository which stores the expense data.
        :return: the repository in use.
        """
        return self._expenses_repository

    def add_expense_to_repository(self, expense_to_be_added):
        """
        Given the expense information in an Expense object, check if there is already an expense with
        the same type, which was made in the same day, and if not, add it to the expense repository.
        :param expense_to_be_added: the expense data that needs to be added.
        :precondition: expense_to_be_added must be an Expense object.
        """

        for i in range(len(self._expenses_repository)):
            expense_list_data = self._expenses_repository[i]

            if expense_list_data.expense_day == expense_to_be_added.expense_day and \
                    expense_list_data.expense_type == expense_to_be_added.expense_type:
                raise ValueError("\nCannot add! Expense already exists in repository.\n")

        self._expenses_repository.append(expense_to_be_added)

    def generate_random_entries_in_the_application_at_start(self):
        """
        Create and initialize the repository of expenses. We know that the day number should be between 1 and 30,
        the expense type should be one of from the list below, and we choose arbitrary to generate an amount,
        which is restricted to be a positive integer, but we choose it to be smaller than 1000.
        """

        expense_types = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']

        for entry in range(1, 16):
            expense_day = random.randint(1, 30)
            expense_amount = random.randint(1, 1000)
            expense_type = random.choice(expense_types)

            # in case the new expense's day and type are similar to one that already exists in the expenses list
            try:
                self.add_expense_to_repository(Expense(expense_day, expense_amount, expense_type))
            except ValueError:
                pass

    def generate_expense_list_to_use_for_tests(self):
        """
        Create 10 default expenses in order to make tests with this data.
        """
        self.add_expense_to_repository(Expense(1, 175, "food"))
        self.add_expense_to_repository(Expense(4, 200, "others"))
        self.add_expense_to_repository(Expense(8, 10, "transport"))
        self.add_expense_to_repository(Expense(10, 44, "housekeeping"))
        self.add_expense_to_repository(Expense(14, 231, "food"))
        self.add_expense_to_repository(Expense(15, 10, "others"))
        self.add_expense_to_repository(Expense(19, 155, "clothing"))
        self.add_expense_to_repository(Expense(22, 35, "transport"))
        self.add_expense_to_repository(Expense(27, 20, "internet"))
        self.add_expense_to_repository(Expense(27, 500, "housekeeping"))

    @staticmethod
    def create_expense_entity(expense_day, expense_amount, expense_type):
        """
        Create an expense object.
        :param expense_day: day the expense was made.
        :param expense_amount: amount of money spent of expense.
        :param expense_type: the type of the expense.
        :return: expense object.
        :precondition: expense_day should be an integer between 1 and 30, expense_amount should be
        a positive integer and expense_type a string from a pre-mentioned list of possibilities.
        """
        return Expense(expense_day, expense_amount, expense_type)

    def sort_the_expenses_in_chronological_order(self):
        """
        Given the list with the expense data, sort the repository in chronological order.
        """

        for expense_index in range(1, len(self._expenses_repository)):

            current_expense_day = self._expenses_repository[expense_index].expense_day
            current_expense_position = expense_index
            current_expense_information = self._expenses_repository[expense_index]

            while current_expense_position > 0 and \
                    self._expenses_repository[current_expense_position - 1].expense_day > current_expense_day:
                self._expenses_repository[current_expense_position] = \
                    self._expenses_repository[current_expense_position - 1]
                current_expense_position -= 1

            self._expenses_repository[current_expense_position] = current_expense_information

    def sort_the_chronological_order_expenses_in_ascending_order_of_amount(self):
        """
        Given the list with the expense data, which is sorted in chronological order, sort
        the repository again, in ascending order of the amount spent on each type.
        """
        self._expenses_repository = sorted(self._expenses_repository, key=lambda x: (x.expense_day, x.expense_type))

    def add_current_data_set_to_repository_history(self):
        """
        Once an operation that modifies the list is called, save the current expense data
        to the expense repository history, which is used for the undo operation.
        """

        copy_of_current_repository = copy.deepcopy(self._expenses_repository)
        self._expenses_repository_history.append(copy_of_current_repository)

    def switch_to_the_data_used_before_last_operation_performed(self):
        """
        If in the repository history exists a copy of the expense data, that means
        at least an operation has been done before. In that case, change the actual expense repository
        to the one used before operation.
        """

        if len(self._expenses_repository_history) == 0:
            raise ValueError("There are no more operations to be undone. You need to add/filter before using undone.\n")

        the_last_data_set_from_history_repository = copy.deepcopy(self._expenses_repository_history[-1])
        self._expenses_repository = the_last_data_set_from_history_repository

        # delete the data using now from the history repository
        self._expenses_repository_history.pop()

    def filter_expenses_above_given_amount_value(self, filter_expense_amount):
        """
        Given an amount, delete all expenses with the amount value smaller than the given one.
        :param filter_expense_amount: the value above which the expenses should be filtered.
        :precondition: filter_expense_amount should be a positive integer.
        """

        if filter_expense_amount <= 0:
            raise ValueError("Not a valid amount. The filter amount should be a positive integer!")

        expense_index = 0

        while expense_index < len(self._expenses_repository):

            if self._expenses_repository[expense_index].expense_amount < filter_expense_amount:
                del self._expenses_repository[expense_index]
                expense_index -= 1

            expense_index += 1
