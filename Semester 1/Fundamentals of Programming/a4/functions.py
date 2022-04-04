import re
import math

"""
  Program functionalities module
"""


def create_complex_number(real, imaginary):
    """
    :description: create a complex number object, set by its real and imaginary parts.
    :param real: the real part of the complex number.
    :param imaginary: the imaginary part of the complex number.
    :return: a list with complex number parts.
    :precondition: real and imaginary are integer values
    """

    if real == 0 and imaginary == 0:
        return None

    return [real, imaginary]


def initialize_complex_numbers_list():
    """
    :description: create a few complex numbers in the application at startup.
    :return: list of created complex numbers.
    """

    return [create_complex_number(1, 1), create_complex_number(12, -2), create_complex_number(10, 2),
            create_complex_number(3, -3), create_complex_number(19, 0), create_complex_number(6, 5),
            create_complex_number(16, 0), create_complex_number(6, 8), create_complex_number(3, 0),
            create_complex_number(-1, -6), create_complex_number(8, 14), create_complex_number(1, 1)]


def initialize_complex_numbers_list_history(complex_numbers_list):
    """
    :description: create a history copy of initialize_complex_numbers_list.
    :param complex_numbers_list: a list of complex numbers.
    :return: a list of lists of complex numbers modification history.
    """

    complex_numbers_list_history = [complex_numbers_list]

    return complex_numbers_list_history


# We use 'setters' and 'getters'

def get_real_part(complex_number):
    """
    :description: get the real part of the given complex number.
    :param complex_number: list with the two parts of a complex number.
    :return: the real part of the complex number.
    :precondition: complex_number is a list with two elements(integers).
    """

    return complex_number[0]


def get_imaginary_part(complex_number):
    """
    :description: get the imaginary part of the given complex number.
    :param complex_number: list with the two parts of a complex number.
    :return: the imaginary part of the complex number.
    :precondition: complex_number is a list with two elements(integers).
    """

    return complex_number[1]


def get_imaginary_part_format(imaginary_part):
    """
    :description: in order to create a complex number as a string format,
    place no value in front of "i" in case the imaginary part is 1.
    :param imaginary_part: the imaginary part of a complex number.
    :return: empty string if imaginary part is 1 or -1, else the absolute value of imaginary part.
    :precondition: imaginary_part is an integer value.
    """

    return "" if abs(imaginary_part) == 1 else abs(imaginary_part)


def complex_number_format(real_part, imaginary_part):
    """
    :description: given the parts of a complex number, determine the appropriate complex number format in a string.
    :param real_part: the real part of a complex number.
    :param imaginary_part: the imaginary part of a complex number.
    :return: string complex number format based on the value of integers and their signs.
    :precondition: both real_part and imaginary_part are integers.
    """

    if real_part == 0:

        # the number doesn't exist
        if imaginary_part == 0:
            return None

        # the number has only the real part
        else:
            return f"{get_imaginary_part_format(imaginary_part)}i" if \
                imaginary_part > 0 else f"-{get_imaginary_part_format(imaginary_part)}i"

    else:

        # the number has only the imaginary part
        if imaginary_part == 0:
            return str(real_part)

        # the imaginary part is negative or positive
        else:
            return f"{real_part}-{get_imaginary_part_format(imaginary_part)}i" if \
                imaginary_part < 0 else f"{real_part}+{get_imaginary_part_format(imaginary_part)}i"


def check_if_a_string_has_numbers(input_string):
    """
    :description: check if a string has digits in its component.
    :param input_string: string entered by the user.
    :return: True if the string has digits, False if not.
    :precondition: input_string's type is a string.
    """

    return any(character.isdigit() for character in input_string)


def split_user_input_into_words(user_input_string):
    """
    :description: regular expression that splits the given string into substrings separated by white spaces.
    :param user_input_string: string entered by the user.
    :return: a list with all the substrings separated by white spaces in the given string.
    :precondition: user_input_string's type is a string.
    """

    return re.findall(r'\S+', user_input_string)


def split_complex_numbers_into_parts(complex_number_as_string):
    """
    :description: given a complex number(as a string) in the format 'a+bi', split it in
    a list with two elements, first being the real part and second the imaginary part of the complex number.
    :param complex_number_as_string: complex number as a string.
    :return: a list of elements containing the integer values of the real and imaginary parts of a complex number.
    :precondition: complex_number_as_string is a string in the format 'a+bi' or 'a+bj', where a and b are integer
    variables, and when they are missing, they will be replaced by 0.
    """

    complex_number_as_string = complex_number_as_string.replace('i', 'j')
    try:
        complex_number = complex(complex_number_as_string)
        return [int(complex_number.real), int(complex_number.imag)]
    except ValueError:
        return None


def check_if_complex_number_position_exists(complex_numbers_list, list_position):
    """
    :description: given a complex numbers list and a position,
    check if that position can represent an index in that list.
    :param complex_numbers_list: a list with complex numbers.
    :param list_position: the position in the list that must be checked if it's in range.
    :return: True if the list_position value is an integer,
    bigger than 0 and lower than complex_numbers_list's length, False if not.
    :precondition: complex_numbers_list is a list, list_position is an integer.
    """

    complex_numbers_counter = len(complex_numbers_list)

    if list_position.isnumeric():
        if 0 < int(list_position) <= complex_numbers_counter:
            return True

    return False


def delete_elements_in_list_between_two_positions(complex_numbers_list, start_position, end_position):
    """
    :description: delete the elements in a list between a start position index and an end position index.
    :param complex_numbers_list: a list.
    :param start_position: an integer from which the removing process starts.
    :param end_position: an integer which expresses the position where the removing process stops.
    :precondition: start_position and end_position are integers, smaller than the length of the
    list; at the same time, start_position must be smaller or equal to end_position.
    """

    del complex_numbers_list[start_position - 1:end_position]


def delete_element_in_given_list_position(complex_numbers_list, position_to_be_deleted):
    """
    :description: delete the elements in a list that holds the given position index.
    :param complex_numbers_list: a list.
    :param position_to_be_deleted: an integer that represents the index in the list.
    :precondition: position_to_be_deleted must be a valid index,
    bigger than 0 and smaller or equal to the length of the complex_numbers_list.
    """

    del complex_numbers_list[position_to_be_deleted - 1]


def replace_particular_value_in_a_list(complex_numbers_list, complex_number_to_be_replaced, substitute_complex_number):
    """
    :description: given a list of complex numbers and two complex numbers, replace all the instances of
    the first one with the value of the second one.
    :param complex_numbers_list: a list.
    :param complex_number_to_be_replaced: the complex number that has to be replaced.
    :param substitute_complex_number: the complex number that replaces the other one.
    :return: the complex numbers list after being modified.
    :precondition: complex_number_to_be_replaced and substitute_complex_number are lists that hold the
    imaginary and real part of complex numbers and whose values are integers.
    """

    complex_numbers_list = [substitute_complex_number if complex_number == complex_number_to_be_replaced
                            else complex_number for complex_number in complex_numbers_list]

    return complex_numbers_list


def get_complex_number_modulo(real_part, imaginary_part):
    """
    :description: given the values of the real and imaginary part of a complex number,
    return the modulo of that complex number.
    :param real_part: real part of a complex number.
    :param imaginary_part: imaginary part of a complex number.
    :return: modulo of the complex number.
    :precondition: real_part and imaginary_part must be integer values.
    """

    return math.sqrt(real_part ** 2 + imaginary_part ** 2)


def get_all_complex_numbers(complex_numbers_list):
    """
    :description: given a list of complex numbers, create and return a list with strings
    that hold the format of each complex number in the list.
    :param complex_numbers_list: a list of complex numbers.
    :return: a list with the suitable string format of complex numbers.
    :precondition: complex_numbers_list is a list.
    """

    complex_number_counter = 1
    complex_numbers_output = []

    for complex_number in complex_numbers_list:
        complex_number_real_part = get_real_part(complex_number)
        complex_number_imaginary_part = get_imaginary_part(complex_number)
        complex_number_value = complex_number_format(complex_number_real_part, complex_number_imaginary_part)

        # avoid the case both real and imaginary parts are 0
        if complex_number_value is not None:
            complex_numbers_output.append(f"z{complex_number_counter}={complex_number_value}")
            complex_number_counter += 1

    return complex_numbers_output


def get_real_numbers_between_two_given_positions(complex_numbers_list, starting_index, finish_index):
    """
    :description: given a list of complex numbers, create and return a list with strings
    that hold the format of each complex number in the list, between two given positions.
    :param complex_numbers_list: a list of complex numbers.
    :param starting_index: the position where the new created list should start.
    :param finish_index: the position where the new created list should stop.
    :return: a list with the suitable string format of complex numbers between given positions.
    :precondition: complex_numbers_list is a list; starting_index and finish_index are both integers,
    bigger than 0 and smaller or equal to the complex_numbers_list, and at the same time
    starting_index is smaller or equal to the finish_index
    """

    real_numbers_output = []

    while starting_index <= finish_index:
        complex_number_real_part = get_real_part(complex_numbers_list[starting_index - 1])
        complex_number_imaginary_part = get_imaginary_part(complex_numbers_list[starting_index - 1])
        complex_number_value = complex_number_format(complex_number_real_part, complex_number_imaginary_part)

        # avoid the case both real and imaginary parts are 0
        if complex_number_value is not None and int(complex_number_imaginary_part) == 0:
            real_numbers_output.append(f"z{starting_index}={complex_number_value}")

        starting_index += 1

    return real_numbers_output


def get_all_complex_numbers_having_given_modulo_property(complex_numbers_list, user_input_string):
    """
    :description: given an user input string, split the elements of the string, check if there exists
    a comparison symbol and a comparison number, and if so, create a list with the elements that fits
    the property between the comparison symbol and number; the new list is just being printed.
    :param complex_numbers_list: a list with complex numbers.
    :param user_input_string: a string entered by the user as input.
    :return: appropriate message if the format of the input string is not correct; appropriate message if there
    are no complex numbers that meet the given property; a list with the complex numbers that meet the
    given property.
    :precondition: complex_numbers_list must be a list, user_input_string must be a string
    in the suitable form mentioned in the menu.
    """

    split_string_elements = split_user_input_into_words(user_input_string)
    complex_numbers_output = []

    if len(split_string_elements) == 4:
        comparison_symbol = split_string_elements[2]
        comparison_number = split_string_elements[3]

        if comparison_symbol in "<=>" and comparison_number.isnumeric():
            complex_number_counter = 1

            comparison_number = int(comparison_number)

            for complex_number in complex_numbers_list:
                complex_number_real_part = get_real_part(complex_number)
                complex_number_imaginary_part = get_imaginary_part(complex_number)
                complex_number_value = complex_number_format(complex_number_real_part, complex_number_imaginary_part)
                complex_number_modulo = get_complex_number_modulo(
                    complex_number_real_part, complex_number_imaginary_part)

                # avoid the case both real and imaginary parts are 0
                if complex_number_value is not None:
                    if comparison_symbol == "<":
                        if complex_number_modulo < comparison_number:
                            complex_numbers_output.append(f"z{complex_number_counter}={complex_number_value}")
                    elif comparison_symbol == "=":
                        if complex_number_modulo == comparison_number:
                            complex_numbers_output.append(f"z{complex_number_counter}={complex_number_value}")
                    elif comparison_symbol == ">":
                        if complex_number_modulo > comparison_number:
                            complex_numbers_output.append(f"z{complex_number_counter}={complex_number_value}")
                    else:
                        return "Not a valid comparison symbol. Try again!"

                    complex_number_counter += 1

        else:
            return "Not a valid comparison symbol or number input. Try again!"

    else:
        return "Not a valid user input format. Try again!"

    return complex_numbers_output


def get_sum_of_complex_numbers_between_two_given_positions(complex_numbers_list, starting_index, finish_index):
    """
    :description: given 2 positions, calculate the sum of the complex numbers between those two positions.
    :param complex_numbers_list: a list with complex numbers.
    :param starting_index: the position from where the sum starts to be computed.
    :param finish_index: the position where the sum stops to be computed.
    :return: the sum of the complex numbers between the two positions.
    :precondition: complex_numbers_list is a list; starting_index and finish_index are both integers,
    bigger than 0 and smaller or equal to the complex_numbers_list, and at the same time
    starting_index is smaller or equal to the finish_index
    """

    real_part_sum = 0
    imaginary_part_sum = 0

    starting_index -= 1

    while starting_index < finish_index:
        complex_number = complex_numbers_list[starting_index]
        complex_number_real_part = get_real_part(complex_number)
        complex_number_imaginary_part = get_imaginary_part(complex_number)
        complex_number_value = complex_number_format(complex_number_real_part, complex_number_imaginary_part)

        # avoid the case both real and imaginary parts are 0
        if complex_number_value is not None:
            real_part_sum += complex_number_real_part
            imaginary_part_sum += complex_number_imaginary_part

        starting_index += 1

    return real_part_sum, imaginary_part_sum


def get_product_of_complex_numbers_between_two_given_positions(complex_numbers_list, starting_index, finish_index):
    """
    :description: given 2 positions, calculate the product of the complex numbers between those two positions.
    :param complex_numbers_list: a list with complex numbers.
    :param starting_index: the position from where the product starts to be computed.
    :param finish_index: the position where the product stops to be computed.
    :return: the product of the complex numbers between the two positions.
    :precondition: complex_numbers_list is a list; starting_index and finish_index are both integers,
    bigger than 0 and smaller or equal to the complex_numbers_list, and at the same time
    starting_index is smaller or equal to the finish_index
    """

    real_part_product = get_real_part(complex_numbers_list[starting_index - 1])
    imaginary_part_product = get_imaginary_part(complex_numbers_list[starting_index - 1])

    while starting_index < finish_index:
        complex_number = complex_numbers_list[starting_index]
        complex_number_real_part = get_real_part(complex_number)
        complex_number_imaginary_part = get_imaginary_part(complex_number)
        complex_number_value = complex_number_format(complex_number_real_part, complex_number_imaginary_part)

        # avoid the case both real and imaginary parts are 0
        if complex_number_value is not None:

            copy_of_real_part_product = real_part_product
            copy_of_imaginary_part_product = imaginary_part_product

            real_part_product = \
                copy_of_real_part_product * complex_number_real_part - copy_of_imaginary_part_product * \
                complex_number_imaginary_part
            imaginary_part_product = \
                copy_of_real_part_product * complex_number_imaginary_part + copy_of_imaginary_part_product * \
                complex_number_real_part

        starting_index += 1

    return real_part_product, imaginary_part_product


def filter_all_real_numbers_from_complex_numbers_list(complex_numbers_list):
    """
    :description: given a list of complex numbers, modify the list in order to obtain a new list
    consisting of all real numbers from the initial list.
    :param complex_numbers_list: a list with complex numbers.
    :return: a list with all the real numbers from the complex numbers list.
    :precondition: complex_numbers_list is a list.
    """

    filtered_real_numbers = []

    for complex_number in complex_numbers_list:
        complex_number_real_part = get_real_part(complex_number)
        complex_number_imaginary_part = get_imaginary_part(complex_number)
        complex_number_value = complex_number_format(complex_number_real_part, complex_number_imaginary_part)

        # avoid the case both real and imaginary parts are 0
        if complex_number_value is not None:
            if int(complex_number_imaginary_part) == 0:
                filtered_real_numbers.append(complex_number)

    return filtered_real_numbers


def filter_complex_numbers_having_given_modulo_property(complex_numbers_list, user_input_string):
    """
    :description: given an user input string, split the elements of the string, check if there exists
    a comparison symbol and a comparison number, and if so, create a new list with the elements that fits
    the property between the comparison symbol and number; the old list becomes the new list.
    :param complex_numbers_list: a list with complex numbers.
    :param user_input_string: a string entered by the user as input.
    :return: appropriate message if the format of the input string is not correct; appropriate message if there
    are no complex numbers that meet the given property; a list with the complex numbers that meet the
    given property.
    :precondition: complex_numbers_list must be a list, user_input_string must be a string
    in the suitable form mentioned in the menu.
    """

    split_string_elements = split_user_input_into_words(user_input_string)
    filtered_complex_numbers = []

    if len(split_string_elements) == 4:
        comparison_symbol = split_string_elements[2]
        comparison_number = split_string_elements[3]

        if comparison_symbol in "<=>" and comparison_number.isnumeric():

            comparison_number = int(comparison_number)

            for complex_number in complex_numbers_list:
                complex_number_real_part = get_real_part(complex_number)
                complex_number_imaginary_part = get_imaginary_part(complex_number)
                complex_number_value = complex_number_format(complex_number_real_part, complex_number_imaginary_part)
                complex_number_modulo = get_complex_number_modulo(
                    complex_number_real_part, complex_number_imaginary_part)

                # avoid the case both real and imaginary parts are 0
                if complex_number_value is not None:
                    if comparison_symbol == "<":
                        if complex_number_modulo < comparison_number:
                            filtered_complex_numbers.append(complex_number)
                    elif comparison_symbol == "=":
                        if complex_number_modulo == comparison_number:
                            filtered_complex_numbers.append(complex_number)
                    elif comparison_symbol == ">":
                        if complex_number_modulo > comparison_number:
                            filtered_complex_numbers.append(complex_number)
                    else:
                        return "Not a valid comparison symbol. Try again!"

        else:
            return "Not a valid comparison symbol or number input. Try again!"

    else:
        return "Not a valid user input format. Try again!"

    return filtered_complex_numbers


def undo_last_operation_done(complex_numbers_list_history):
    """
    :description: delete the last modification of the complex numbers list, if that exists.
    :param complex_numbers_list_history: a list of lists, consisting of the
    all complex numbers that have been modified during program execution.
    :return: a string with the suitable message, telling the user if the operation could be done.
    :precondition: complex_numbers_list_history is a list.
    """

    if len(complex_numbers_list_history) > 1:
        del complex_numbers_list_history[-1]
        return "The last operation performed was undone."

    else:
        return "There are no list modification operations to be undone."
