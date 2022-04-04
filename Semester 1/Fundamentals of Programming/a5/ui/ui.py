from src.services.services import ExpenseServices


class ExpensesUI:
    def __init__(self):
        self._expense_data_functions = ExpenseServices()

    @staticmethod
    def get_expense_day_input(user_input_message):

        valid_input = False
        expense_day = 0

        while valid_input is False:
            try:
                expense_day = int(input(user_input_message))
                valid_input = True

                if expense_day < 1 or expense_day > 30:
                    valid_input = False
                    raise ValueError("Not a valid day. Enter an integer between 1 and 30!")
                else:
                    valid_input = True

            except ValueError:
                print("Not a valid day. The input should be an integer!")

        return expense_day

    def ask_user_for_expense_day(self):

        expense_day_input_message = "Day the expense was made: "

        return self.get_expense_day_input(expense_day_input_message)

    @staticmethod
    def get_expense_amount_input(user_input_message):

        valid_input = False
        expense_amount = 0

        while valid_input is False:
            try:
                expense_amount = int(input(user_input_message))
                valid_input = True

                if expense_amount < 1:
                    valid_input = False
                    print("Not a valid amount. Enter a positive integer!")

                else:
                    valid_input = True

            except ValueError:
                print("Not a valid amount. The input should be an integer!")

        return expense_amount

    def ask_user_for_expense_amount(self):

        expense_amount_input_message = "Amount of money spent: "

        return self.get_expense_amount_input(expense_amount_input_message)

    @staticmethod
    def get_expense_type_input(user_input_message):

        valid_input = False
        expense_types = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']
        expense_type = ""

        while valid_input is False:

            expense_type = input(user_input_message)

            if expense_type in expense_types:
                valid_input = True

            else:
                print("Not a valid type. Choose between: housekeeping, food, transport, clothing, internet, others.")

        return expense_type.lower()

    def ask_user_for_expense_type(self):

        expense_type_input_message = "Type of the expense: "

        return self.get_expense_type_input(expense_type_input_message)

    def create_expense_instance_passed_by_user(self):
        print("In order to add an expense to the list, you need to provide a day number, an amount and a type.")

        expense_day = self.ask_user_for_expense_day()
        expense_amount = self.ask_user_for_expense_amount()
        expense_type = self.ask_user_for_expense_type()

        new_expense = self._expense_data_functions.create_expense_entity(expense_day, expense_amount, expense_type)

        return new_expense

    def add_expense_data_entered_by_user(self):

        self._expense_data_functions.add_expense_to_repository(self.create_expense_instance_passed_by_user())

        print("\nThe expense has been successfully added!\n")

    def display_the_list_of_expenses(self):

        expense_data_list = self._expense_data_functions.expenses_repository
        print("The list of current expenses made:\n")

        for student in expense_data_list:
            print(student)
        print()

    def get_amount_to_filter_expenses_above_that_value(self):

        print("Enter a value and the expense list will be filtered "
              "so it will contain only expenses above the entered value.")

        user_input_message = "The amount value: "
        filter_expense_amount = self.get_expense_amount_input(user_input_message)

        return filter_expense_amount

    def delete_expenses_above_given_amount_value(self):
        filter_expense_amount = self.get_amount_to_filter_expenses_above_that_value()

        self._expense_data_functions.filter_expenses_above_given_amount_value(filter_expense_amount)

        print("\nThe expense data has been successfully filtered!\n")

    def undo_the_last_operation_performed(self):

        self._expense_data_functions.switch_to_the_data_used_before_last_operation_performed()

        print("The last operation performed has been successfully undone!\n")

    @staticmethod
    def print_welcome_message():
        print("Welcome to your expenses list manager! Choose one of the options below.\n")

    @staticmethod
    def print_departure_message():
        print("Thank you for using the application! See you next time!")

    @staticmethod
    def show_start_interface_commands():
        print("1. Add an expense. You need to provide a day, an amount and a type.")
        print("2. Display the list of expenses.")
        print("3. Filter the list so that it contains only expenses above a certain value you provide.")
        print("4. Undo the last operation that modified the program data.")
        print("5. Exit the program.\n")

    def start_menu(self):

        self.print_welcome_message()
        self._expense_data_functions.generate_random_entries_in_the_application_at_start()
        self._expense_data_functions.sort_the_chronological_order_expenses_in_ascending_order_of_amount()

        while True:
            self.show_start_interface_commands()
            user_option = input("Enter an option: ")
            print()
            try:
                if user_option == '1':
                    self._expense_data_functions.add_current_data_set_to_repository_history()
                    self.add_expense_data_entered_by_user()
                    self._expense_data_functions.sort_the_chronological_order_expenses_in_ascending_order_of_amount()

                elif user_option == '2':
                    self.display_the_list_of_expenses()

                elif user_option == '3':
                    self._expense_data_functions.add_current_data_set_to_repository_history()
                    self.delete_expenses_above_given_amount_value()
                    self._expense_data_functions.sort_the_chronological_order_expenses_in_ascending_order_of_amount()

                elif user_option == '4':
                    self.undo_the_last_operation_performed()

                elif user_option == '5':
                    break

                else:
                    print("Option does not exist. Choose an integer number between 1 and 5.\n")

            except ValueError as ve:
                print(ve)

        self.print_departure_message()
