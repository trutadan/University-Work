from src.services.services import ExpenseServices, Expense


def tests_for_service_functionalities():
    tests_for_filter_expenses_above_given_amount_value()
    tests_for_add_expense_to_repository()
    tests_for_sorting_expenses_algorithms()


def tests_for_filter_expenses_above_given_amount_value():
    filter_expenses_above_given_amount_value__input_amount_is_negative__throws_exception()
    filter_expenses_above_given_amount_value__input_amount_bigger_than_all_expenses_amount__empty_list()
    filter_expenses_above_given_amount_value__input_amount_bigger_than_all_expenses_amount__initial_list()
    filter_expenses_above_given_amount_value__correct_input_amount__filtered_list_with_three_expenses()


def filter_expenses_above_given_amount_value__input_amount_is_negative__throws_exception():
    test = ExpenseServices()
    test.generate_expense_list_to_use_for_tests()
    try:
        test.filter_expenses_above_given_amount_value(-5)
        assert False
    except ValueError:
        assert True


def filter_expenses_above_given_amount_value__input_amount_bigger_than_all_expenses_amount__empty_list():
    test = ExpenseServices()
    test.generate_expense_list_to_use_for_tests()
    test.filter_expenses_above_given_amount_value(800)
    assert test.expenses_repository == []


def filter_expenses_above_given_amount_value__input_amount_bigger_than_all_expenses_amount__initial_list():
    first_test_copy = ExpenseServices()
    first_test_copy.generate_expense_list_to_use_for_tests()
    first_test_copy.filter_expenses_above_given_amount_value(2)
    filtered_expense_list = first_test_copy.expenses_repository

    second_test_copy = ExpenseServices()
    second_test_copy.generate_expense_list_to_use_for_tests()
    initial_expense_list = second_test_copy.expenses_repository

    expense_index = 0

    while expense_index < len(filtered_expense_list):
        assert filtered_expense_list[expense_index].expense_day == initial_expense_list[expense_index].expense_day
        assert filtered_expense_list[expense_index].expense_amount == initial_expense_list[expense_index].expense_amount
        assert filtered_expense_list[expense_index].expense_type == initial_expense_list[expense_index].expense_type

        expense_index += 1


def filter_expenses_above_given_amount_value__correct_input_amount__filtered_list_with_three_expenses():
    test = ExpenseServices()
    test.generate_expense_list_to_use_for_tests()
    test.filter_expenses_above_given_amount_value(185)

    expense_list = test.expenses_repository

    assert expense_list[0].expense_day == 4
    assert expense_list[0].expense_amount == 200
    assert expense_list[0].expense_type == "others"

    assert expense_list[1].expense_day == 14
    assert expense_list[1].expense_amount == 231
    assert expense_list[1].expense_type == "food"

    assert expense_list[2].expense_day == 27
    assert expense_list[2].expense_amount == 500
    assert expense_list[2].expense_type == "housekeeping"


def tests_for_add_expense_to_repository():
    add_expense_to_repository__correct_expense_input__expense_added_to_repository()
    add_expense_to_repository__already_existing_expense__throws_exception()


def add_expense_to_repository__correct_expense_input__expense_added_to_repository():
    test = ExpenseServices()
    test.add_expense_to_repository(Expense(11, 257, "housekeeping"))
    expense_data = test.expenses_repository

    assert len(expense_data) == 1
    assert expense_data[0].expense_day == 11
    assert expense_data[0].expense_amount == 257
    assert expense_data[0].expense_type == "housekeeping"


def add_expense_to_repository__already_existing_expense__throws_exception():
    test = ExpenseServices()
    test._expenses_repository = [Expense(11, 257, "housekeeping")]
    try:
        test.add_expense_to_repository(Expense(11, 102, "housekeeping"))
        assert False
    except ValueError:
        assert True


def tests_for_sorting_expenses_algorithms():
    sort_the_expenses_in_chronological_order__correct_expense_list__chronologically_sorted_expense_list()
    sort_the_chronological_order_expenses_in_ascending_order_of_amount__correct_expense_list__chronologically_and_amount_sorted_expense_list()


def sort_the_expenses_in_chronological_order__correct_expense_list__chronologically_sorted_expense_list():
    test = ExpenseServices()
    test._expenses_repository = [Expense(11, 257, "housekeeping"), Expense(2, 101, "transport"), Expense(7, 10, "food")]
    test.sort_the_expenses_in_chronological_order()
    expense_data = test.expenses_repository

    assert expense_data[0].expense_day == 2
    assert expense_data[0].expense_amount == 101
    assert expense_data[0].expense_type == 'transport'

    assert expense_data[1].expense_day == 7
    assert expense_data[1].expense_amount == 10
    assert expense_data[1].expense_type == 'food'

    assert expense_data[2].expense_day == 11
    assert expense_data[2].expense_amount == 257
    assert expense_data[2].expense_type == 'housekeeping'


def sort_the_chronological_order_expenses_in_ascending_order_of_amount__correct_expense_list__chronologically_and_amount_sorted_expense_list():
    test = ExpenseServices()
    test._expenses_repository = [Expense(11, 257, "housekeeping"), Expense(2, 101, "transport"), Expense(2, 75, "food")]
    test.sort_the_chronological_order_expenses_in_ascending_order_of_amount()
    expense_data = test.expenses_repository

    assert expense_data[0].expense_day == 2
    assert expense_data[0].expense_amount == 75
    assert expense_data[0].expense_type == 'food'

    assert expense_data[1].expense_day == 2
    assert expense_data[1].expense_amount == 101
    assert expense_data[1].expense_type == 'transport'

    assert expense_data[2].expense_day == 11
    assert expense_data[2].expense_amount == 257
    assert expense_data[2].expense_type == 'housekeeping'
