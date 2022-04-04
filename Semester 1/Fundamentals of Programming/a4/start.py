from ui import *

"""
  Start the program by running this module
"""


def start_command_interface():

    show_start_interface_commands()

    complex_numbers_list = initialize_complex_numbers_list()
    complex_numbers_list_history = initialize_complex_numbers_list_history(initialize_complex_numbers_list())

    while True:
        user_command = input("prompt > ").lower()

        if 'add' in user_command:
            add_complex_number_to_list(complex_numbers_list, user_command)
            complex_numbers_list_history.append(complex_numbers_list)

        elif 'insert' in user_command and 'at' in user_command:
            insert_complex_number_in_list_to_given_position(complex_numbers_list, user_command)
            complex_numbers_list_history.append(complex_numbers_list)

        elif 'remove' in user_command:
            if 'to' not in user_command:
                remove_complex_number_from_position(complex_numbers_list, user_command)
            else:
                remove_complex_number_between_positions(complex_numbers_list, user_command)
            complex_numbers_list_history.append(complex_numbers_list)

        elif 'replace' in user_command:
            complex_numbers_list = replace_all_instances_of_given_complex_number_with_other_given_complex_number(
                complex_numbers_list, user_command)
            complex_numbers_list_history.append(complex_numbers_list)

        elif user_command == 'list':
            list_all_complex_numbers(complex_numbers_list)

        elif 'list' in user_command and 'real' in user_command:
            list_real_numbers_between_two_given_positions(complex_numbers_list, user_command)

        elif 'list' in user_command and 'modulo' in user_command:
            list_all_complex_numbers_having_given_modulo_property(complex_numbers_list, user_command)

        elif 'sum' in user_command and 'to' in user_command:
            list_sum_of_complex_numbers_between_two_given_positions(complex_numbers_list, user_command)

        elif 'product' in user_command and 'to' in user_command:
            list_product_of_complex_numbers_between_two_given_positions(complex_numbers_list, user_command)

        elif user_command == 'filter real':
            complex_numbers_list = list_filtered_real_numbers_from_a_complex_numbers_list(complex_numbers_list)
            complex_numbers_list_history.append(complex_numbers_list)

        elif 'filter' in user_command and 'modulo' in user_command:
            complex_numbers_list, complex_numbers_list_history = \
                check_filtered_complex_numbers_having_given_modulo_property\
                    (complex_numbers_list, complex_numbers_list_history, user_command)

        elif user_command == 'undo':
            undo_last_operation_done_and_print_message(complex_numbers_list_history)
            complex_numbers_list = complex_numbers_list_history[-1]

        elif user_command == 'menu':
            show_start_interface_commands()

        elif user_command == 'exit':
            return

        else:
            print("Command does not exist. Try another one!")


if __name__ == '__main__':
    start_command_interface()
