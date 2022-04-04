import re
import math

"""
  non-UI functions below
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


def test_create_complex_number():
    assert create_complex_number(0, 1) == [0, 1]
    assert create_complex_number(0, 0) is None
    assert create_complex_number(-5, 0) == [-5, 0]
    assert create_complex_number(-2, -7) == [-2, -7]
    assert create_complex_number(178, 39) == [178, 39]


test_create_complex_number()


def initialize_complex_numbers_list():
    """
    :description: create a few complex numbers in the application at startup.
    :return: list of created complex numbers.
    """

    return [create_complex_number(1, 1), create_complex_number(12, -2), create_complex_number(10, 2),
            create_complex_number(3, -3), create_complex_number(19, 0), create_complex_number(6, 5),
            create_complex_number(16, 0), create_complex_number(6, 8), create_complex_number(3, 0),
            create_complex_number(-1, -6), create_complex_number(8, 14), create_complex_number(1, 1)]


# We use 'setters' and 'getters'

def get_real_part(complex_number):
    """
    :description: get the real part of the given complex number.
    :param complex_number: list with the two parts of a complex number.
    :return: the real part of the complex number.
    :precondition: complex_number is a list with two elements(integers).
    """

    return complex_number[0]


def test_get_real_part():
    assert get_real_part([1, 4]) == 1
    assert get_real_part([0, 0]) == 0
    assert get_real_part([-4, 8]) == -4


test_get_real_part()


def get_imaginary_part(complex_number):
    """
    :description: get the imaginary part of the given complex number.
    :param complex_number: list with the two parts of a complex number.
    :return: the imaginary part of the complex number.
    :precondition: complex_number is a list with two elements(integers).
    """

    return complex_number[1]


def test_get_imaginary_part():
    assert get_imaginary_part([-1, 4]) == 4
    assert get_imaginary_part([0, 0]) == 0
    assert get_imaginary_part([4, -8]) == -8


test_get_imaginary_part()


def get_imaginary_part_format(imaginary_part):
    """
    :description: in order to create a complex number as a string format,
    place no value in front of "i" in case the imaginary part is 1.
    :param imaginary_part: the imaginary part of a complex number.
    :return: empty string if imaginary part is 1 or -1, else the absolute value of imaginary part.
    :precondition: imaginary_part is an integer value.
    """

    return "" if abs(imaginary_part) == 1 else abs(imaginary_part)


def test_get_imaginary_part_format():
    assert get_imaginary_part_format(1) == ""
    assert get_imaginary_part_format(-1) == ""
    assert get_imaginary_part_format(5) == 5
    assert get_imaginary_part_format(0) == 0
    assert get_imaginary_part_format(-11) == 11


test_get_imaginary_part_format()


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
            return f"{get_imaginary_part_format(imaginary_part)}i" if\
                imaginary_part > 0 else f"-{get_imaginary_part_format(imaginary_part)}i"

    else:

        # the number has only the imaginary part
        if imaginary_part == 0:
            return str(real_part)

        # the imaginary part is negative or positive
        else:
            return f"{real_part}-{get_imaginary_part_format(imaginary_part)}i" if \
                imaginary_part < 0 else f"{real_part}+{get_imaginary_part_format(imaginary_part)}i"


def test_complex_number_format():
    assert complex_number_format(0, 5) == "5i"
    assert complex_number_format(0, -3) == "-3i"
    assert complex_number_format(0, 1) == "i"
    assert complex_number_format(2, 3) == "2+3i"
    assert complex_number_format(4, -7) == "4-7i"
    assert complex_number_format(8, 0) == "8"
    assert complex_number_format(0, 0) is None


test_complex_number_format()


def check_if_a_string_has_numbers(input_string):
    """
    :description: check if a string has digits in its component.
    :param input_string: string entered by the user.
    :return: True if the string has digits, False if not.
    :precondition: input_string's type is a string.
    """

    return any(character.isdigit() for character in input_string)


def test_check_if_a_string_has_numbers():
    assert check_if_a_string_has_numbers("hello") is False
    assert check_if_a_string_has_numbers("age 11") is True
    assert check_if_a_string_has_numbers("L33T") is True
    assert check_if_a_string_has_numbers("number one") is False
    assert check_if_a_string_has_numbers("") is False


test_check_if_a_string_has_numbers()


def split_user_input_into_words(user_input_string):
    """
    :description: regular expression that splits the given string into substrings separated by white spaces.
    :param user_input_string: string entered by the user.
    :return: a list with all the substrings separated by white spaces in the given string.
    :precondition: user_input_string's type is a string.
    """

    return re.findall(r'\S+', user_input_string)


def test_split_user_input_into_words():
    assert split_user_input_into_words("hello,   user") == ["hello,", "user"]
    assert split_user_input_into_words("testing_function") == ["testing_function"]
    assert split_user_input_into_words("") == []
    assert split_user_input_into_words("a     b c     d   e") == ["a", "b", "c", "d", "e"]


test_split_user_input_into_words()


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


def test_split_complex_numbers_into_parts():
    assert split_complex_numbers_into_parts("7+8i") == [7, 8]
    assert split_complex_numbers_into_parts("4 +   8i") is None
    assert split_complex_numbers_into_parts("-2-4j") == [-2, -4]
    assert split_complex_numbers_into_parts("1+i") == [1, 1]
    assert split_complex_numbers_into_parts("i") == [0, 1]
    assert split_complex_numbers_into_parts("+4i") == [0, 4]
    assert split_complex_numbers_into_parts("    2i") == [0, 2]


test_split_complex_numbers_into_parts()


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


def test_check_if_complex_number_position_exists():
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "3") is True
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "7") is False
    assert check_if_complex_number_position_exists([], "1") is False
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "position") is False
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "a5b") is False


test_check_if_complex_number_position_exists()


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


def test_replace_particular_value_in_a_list():
    assert replace_particular_value_in_a_list([[2, -3], [4, 7], [2, -3]], [2, -3], [1, 2]) == [[1, 2], [4, 7], [1, 2]]
    assert replace_particular_value_in_a_list([[2, -3], [4, 7], [2, -3]], [2, 5], [1, 2]) == [[2, -3], [4, 7], [2, -3]]
    assert replace_particular_value_in_a_list([], [2, 5], [1, 3]) == []


test_replace_particular_value_in_a_list()


def get_complex_number_modulo(real_part, imaginary_part):
    """
    :description: given the values of the real and imaginary part of a complex number,
    return the modulo of that complex number.
    :param real_part: real part of a complex number.
    :param imaginary_part: imaginary part of a complex number.
    :return: modulo of the complex number.
    :precondition: real_part and imaginary_part must be integer values.
    """

    return math.sqrt(real_part**2 + imaginary_part**2)


def test_get_complex_number_modulo():
    assert get_complex_number_modulo(3, 4) == 5
    assert get_complex_number_modulo(12, 15) == 19.209372712298546
    assert get_complex_number_modulo(0, 0) == 0
    assert get_complex_number_modulo(2, 7) == 7.280109889280518


test_get_complex_number_modulo()


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
    the property between the comparison symbol and number.
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


"""
  command-driven UI below
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
        print("The complex numbers you are looking for are: ")
        for complex_number in complex_numbers_output:
            print(complex_number)

    else:
        print("There are no more complex numbers left. Add some!")


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


def start_command_interface():

    show_start_interface_commands()

    complex_numbers_list = initialize_complex_numbers_list()

    while True:
        user_command = input("prompt > ").lower()

        if 'add' in user_command:
            add_complex_number_to_list(complex_numbers_list, user_command)

        elif 'insert' in user_command and 'at' in user_command:
            insert_complex_number_in_list_to_given_position(complex_numbers_list, user_command)

        elif 'remove' in user_command:
            if 'to' not in user_command:
                remove_complex_number_from_position(complex_numbers_list, user_command)
            else:
                remove_complex_number_between_positions(complex_numbers_list, user_command)

        elif 'replace' in user_command:
            complex_numbers_list = replace_all_instances_of_given_complex_number_with_other_given_complex_number(
                complex_numbers_list, user_command)

        elif user_command == 'list':
            list_all_complex_numbers(complex_numbers_list)

        elif 'list' in user_command and 'real' in user_command:
            list_real_numbers_between_two_given_positions(complex_numbers_list, user_command)

        elif 'modulo' in user_command:
            list_all_complex_numbers_having_given_modulo_property(complex_numbers_list, user_command)

        elif user_command == 'menu':
            show_start_interface_commands()

        elif user_command == 'exit':
            return

        else:
            print("Command does not exist. Try another one!")


if __name__ == '__main__':
    start_command_interface()
