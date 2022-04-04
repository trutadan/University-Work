from functions import *

"""
  User interface module
"""


def add_complex_number_to_list(complex_numbers_list, user_input_string):

    split_string_elements = split_user_input_into_words(user_input_string)

    if len(split_string_elements) == 2:
        complex_number = split_string_elements[1]
        complex_number_parts = split_complex_numbers_into_parts(complex_number)

        if complex_number_parts is not None:
            complex_numbers_list.append(complex_number_parts)
            print("The given complex number has been successfully added!")

        else:
            print("Not a valid complex number format. Try again!")

    else:
        print("Not a valid user input format. Try again!")


def insert_complex_number_in_list_to_given_position(complex_numbers_list, user_input_string):

    split_string_elements = split_user_input_into_words(user_input_string)

    if len(split_string_elements) == 4:
        complex_number_to_be_added = split_string_elements[1]
        complex_number_parts = split_complex_numbers_into_parts(complex_number_to_be_added)

        position_to_be_modified = split_string_elements[3]

        if complex_number_parts is not None:

            if position_to_be_modified.isnumeric():
                complex_numbers_list.insert(int(position_to_be_modified) - 1, complex_number_parts)
                print("The given complex number has been successfully added to the position mentioned!")

            else:
                print("Not a valid position. Try again!")

        else:
            print("Not a valid complex number format. Try again!")

    else:
        print("Not a valid user input format. Try again!")


def remove_complex_number_from_position(complex_numbers_list, user_input_string):

    split_string_elements = split_user_input_into_words(user_input_string)

    if len(split_string_elements) == 2:
        number_position_to_be_deleted = split_string_elements[1]

        if check_if_complex_number_position_exists(complex_numbers_list, number_position_to_be_deleted):
            number_position_to_be_deleted = int(number_position_to_be_deleted)
            delete_element_in_given_list_position(complex_numbers_list, number_position_to_be_deleted)
            print("The complex number from the given position has been successfully deleted!")

        else:
            print("Not a valid position. Try again!")

    else:
        print("Not a valid user input format. Try again!")


def remove_complex_number_between_positions(complex_numbers_list, user_input_string):

    split_string_elements = split_user_input_into_words(user_input_string)

    if len(split_string_elements) == 4:
        start_position = split_string_elements[1]
        end_position = split_string_elements[3]

        if check_if_complex_number_position_exists(complex_numbers_list, start_position) and \
                check_if_complex_number_position_exists(complex_numbers_list, end_position):

            if start_position <= end_position:
                start_position = int(start_position)
                end_position = int(end_position)
                delete_elements_in_list_between_two_positions(complex_numbers_list, start_position, end_position)
                print(f"The complex numbers between positions {start_position} and {end_position} have been deleted!")

            else:
                print("The start position must be lower than the end position. Try again!")

        else:
            print("Not valid positions. Try again!")

    else:
        print("Not a valid user input format. Try again!")


def replace_all_instances_of_given_complex_number_with_other_given_complex_number(complex_numbers_list, input_string):

    split_string_elements = split_user_input_into_words(input_string)

    if len(split_string_elements) == 4:
        complex_number_to_be_replaced = split_string_elements[1]
        substitute_complex_number = split_string_elements[3]

        complex_number_to_be_replaced_parts = split_complex_numbers_into_parts(complex_number_to_be_replaced)
        substitute_complex_number_parts = split_complex_numbers_into_parts(substitute_complex_number)

        if complex_number_to_be_replaced_parts is not None and substitute_complex_number_parts is not None:
            complex_numbers_list = replace_particular_value_in_a_list(
                complex_numbers_list, complex_number_to_be_replaced_parts, substitute_complex_number_parts)
            print(f"All occurrences of number {complex_number_to_be_replaced} "
                  f"have been replaced with the number {substitute_complex_number}!")

        else:
            print("Not valid complex number format. Try again!")

    else:
        print("Not a valid user input format. Try again!")

    return complex_numbers_list


def list_all_complex_numbers(complex_numbers_list):

    complex_numbers_output = get_all_complex_numbers(complex_numbers_list)

    if complex_numbers_output:
        print("The numbers you are looking for are: ")
        for complex_number in complex_numbers_output:
            print(complex_number)

    else:
        print("There are no more numbers left. Add some!")


def list_real_numbers_between_two_given_positions(complex_numbers_list, user_input_string):

    split_string_elements = split_user_input_into_words(user_input_string)

    if len(split_string_elements) == 5:
        starting_index = split_string_elements[2]
        finish_index = split_string_elements[4]

        if check_if_complex_number_position_exists(complex_numbers_list, starting_index) \
                and check_if_complex_number_position_exists(complex_numbers_list, finish_index):
            real_numbers = get_real_numbers_between_two_given_positions(complex_numbers_list,
                                                                        int(starting_index), int(finish_index))
            if real_numbers:
                print("The real numbers you are looking for are: ")
                for real_number in real_numbers:
                    print(real_number)

            else:
                print("There are no real numbers in that interval. Try other indexes!")

        else:
            print("Not valid positions. Try again!")

    else:
        print("Not a valid user input format. Try again!")


def list_all_complex_numbers_having_given_modulo_property(complex_numbers_list, user_input_string):

    complex_numbers_having_given_modulo_property = get_all_complex_numbers_having_given_modulo_property\
        (complex_numbers_list, user_input_string)

    if type(complex_numbers_having_given_modulo_property) == str:
        print(complex_numbers_having_given_modulo_property)
    elif not complex_numbers_having_given_modulo_property:
        print("There are no complex numbers for the given modulo property. Try again!")
    else:
        for complex_number in complex_numbers_having_given_modulo_property:
            print(complex_number)


def list_sum_of_complex_numbers_between_two_given_positions(complex_numbers_list, user_input_string):

    split_string_elements = split_user_input_into_words(user_input_string)

    if len(split_string_elements) == 4:
        starting_index = split_string_elements[1]
        finish_index = split_string_elements[3]

        if check_if_complex_number_position_exists(complex_numbers_list, starting_index) \
                and check_if_complex_number_position_exists(complex_numbers_list, finish_index):
            real_part_sum, imaginary_part_sum = get_sum_of_complex_numbers_between_two_given_positions\
                (complex_numbers_list, int(starting_index), int(finish_index))
            sum_complex_number_format = complex_number_format(real_part_sum, imaginary_part_sum)
            print(f"The sum of complex numbers between positions {starting_index} and {finish_index} is:")
            if sum_complex_number_format is None:
                print("s=0")
            else:
                print(f"s={sum_complex_number_format}")

        else:
            print("Not valid positions. Try again!")

    else:
        print("Not a valid user input format. Try again!")


def list_product_of_complex_numbers_between_two_given_positions(complex_numbers_list, user_input_string):

    split_string_elements = split_user_input_into_words(user_input_string)

    if len(split_string_elements) == 4:
        starting_index = split_string_elements[1]
        finish_index = split_string_elements[3]

        if check_if_complex_number_position_exists(complex_numbers_list, starting_index) \
                and check_if_complex_number_position_exists(complex_numbers_list, finish_index):
            real_part_product, imaginary_part_product = get_product_of_complex_numbers_between_two_given_positions\
                (complex_numbers_list, int(starting_index), int(finish_index))
            product_complex_number_format = complex_number_format(real_part_product, imaginary_part_product)
            print(f"The sum of complex numbers between positions {starting_index} and {finish_index} is:")
            if product_complex_number_format is None:
                print("p=0")
            else:
                print(f"p={product_complex_number_format}")

        else:
            print("Not valid positions. Try again!")

    else:
        print("Not a valid user input format. Try again!")


def list_filtered_real_numbers_from_a_complex_numbers_list(complex_numbers_list):

    filtered_real_numbers = filter_all_real_numbers_from_complex_numbers_list(complex_numbers_list)

    print("The complex numbers list has been successfully modified.")

    return filtered_real_numbers


def list_filtered_complex_numbers_having_given_modulo_property(complex_numbers_list, user_input_string):

    filtered_complex_numbers = filter_complex_numbers_having_given_modulo_property\
        (complex_numbers_list, user_input_string)

    if type(filtered_complex_numbers) == str:
        print(filtered_complex_numbers)
        return None

    else:
        return filtered_complex_numbers


def check_filtered_complex_numbers_having_given_modulo_property(numbers_list, numbers_list_history, user_input_string):

    if list_filtered_complex_numbers_having_given_modulo_property(numbers_list, user_input_string) \
            is not None:

        print("The complex numbers list has been successfully modified.")
        complex_numbers_list = list_filtered_complex_numbers_having_given_modulo_property\
            (numbers_list, user_input_string)
        numbers_list_history.append(complex_numbers_list)
        numbers_list = complex_numbers_list

    return numbers_list, numbers_list_history


def undo_last_operation_done_and_print_message(complex_numbers_list_history):

    print(undo_last_operation_done(complex_numbers_list_history))


def show_start_interface_commands():
    print(">>> menu")
    print(">>> add <number>")
    print(">>> insert <number> at <position>")
    print(">>> remove <position>")
    print(">>> remove <start position> to <end position>")
    print(">>> replace <old number> with <new number>")
    print(">>> list")
    print(">>> list real <start position> to <end position>")
    print(">>> list modulo [ < | = | > ] <number>")
    print(">>> sum <start position> to <end position>")
    print(">>> product <start position> to <end position>")
    print(">>> filter real")
    print(">>> filter modulo [ < | = | > ] <number>")
    print(">>> undo")
