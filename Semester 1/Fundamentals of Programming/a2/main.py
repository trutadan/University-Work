#
# Write the implementation for A2 in this file
#


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values


# 9. Consecutive number pairs have equal sum. (e.g. 1+3i, 1-i, 1+3i, 1-i)

def make_consecutive_two_complex_numbers_pair(complex_numbers_list, starting_pairs_index):
    """Given a list of complex numbers,
    create sequences starting from the given index, by adding 2 consecutive pairs."""

    complex_numbers_pairs = []

    while starting_pairs_index + 1 < len(complex_numbers_list):
        complex_numbers_pairs.append([complex_numbers_list[starting_pairs_index][0] +
                                      complex_numbers_list[starting_pairs_index + 1][0],
                                      complex_numbers_list[starting_pairs_index][1] +
                                      complex_numbers_list[starting_pairs_index + 1][1]])
        starting_pairs_index += 2

    return complex_numbers_pairs


def get_longest_equal_elements_sequence(complex_numbers_pairs):
    """Given list as sum of pairs of consecutive complex numbers, obtain the longest sequence for which all
    elements of the sequence are the same."""

    longest_equal_elements_sequence_length = 1
    longest_equal_elements_sequence_finish_index = 1

    # go through all sequences, from the first to the last
    current_sequence_length = 1
    current_sequence_starting_index = 1

    while current_sequence_starting_index < len(complex_numbers_pairs):
        if complex_numbers_pairs[current_sequence_starting_index] == \
                complex_numbers_pairs[current_sequence_starting_index - 1]:
            current_sequence_length += 1
        else:
            if current_sequence_length > longest_equal_elements_sequence_length:
                longest_equal_elements_sequence_length = current_sequence_length
                longest_equal_elements_sequence_finish_index = current_sequence_starting_index
            current_sequence_length = 1

        current_sequence_starting_index += 1

    # if no such sequence was found, return (1, 0)
    return longest_equal_elements_sequence_length, longest_equal_elements_sequence_finish_index - 1


# we can form 2 types of consecutive sum sequences, forming them by starting from index 0 or index 1,
# so we need both of them

def get_longest_consecutive_equal_pairs_starting_position_zero(complex_numbers_list):

    pairs_starting_from_position_zero = make_consecutive_two_complex_numbers_pair(complex_numbers_list, 0)

    if get_longest_equal_elements_sequence(pairs_starting_from_position_zero) == (1, 0):
        return 1, 0
    else:
        longest_sequence_length, longest_sequence_finish_index = \
            get_longest_equal_elements_sequence(pairs_starting_from_position_zero)

        longest_sequence_finish_index = (longest_sequence_finish_index + 1) * 2 - 1
        longest_sequence_start_index = (longest_sequence_finish_index - longest_sequence_length) * 2 + 1

        return longest_sequence_start_index, longest_sequence_finish_index


def get_longest_consecutive_equal_pairs_starting_position_one(complex_numbers_list):

    pairs_starting_from_position_one = make_consecutive_two_complex_numbers_pair(complex_numbers_list, 1)

    if get_longest_equal_elements_sequence(pairs_starting_from_position_one) == (1, 0):
        return 1, 0
    else:
        longest_sequence_length, longest_sequence_finish_index = \
            get_longest_equal_elements_sequence(pairs_starting_from_position_one)

        longest_sequence_finish_index = (longest_sequence_finish_index + 1) * 2
        longest_sequence_start_index = longest_sequence_finish_index - 2 * longest_sequence_length + 1

        return longest_sequence_start_index, longest_sequence_finish_index


def compare_equal_pairs_from_both_cases(complex_numbers_list):
    """Compare both of the cases mentioned before and choose the longest sequence, if that exists."""

    pairs_from_one_start_index, pairs_from_one_finish_index = \
        get_longest_consecutive_equal_pairs_starting_position_one(complex_numbers_list)

    pairs_from_zero_start_index, pairs_from_zero_finish_index = \
        get_longest_consecutive_equal_pairs_starting_position_zero(complex_numbers_list)

    if pairs_from_one_finish_index == 0 and pairs_from_zero_finish_index == 0:
        return None
    if pairs_from_one_finish_index-pairs_from_one_start_index > \
            pairs_from_zero_finish_index - pairs_from_zero_start_index:
        return pairs_from_one_start_index, pairs_from_one_finish_index
    else:
        return pairs_from_zero_start_index, pairs_from_zero_finish_index


# 10. Sum of its elements is 10+10i

def split_complex_numbers_into_parts(complex_numbers_list):
    """Split the complex numbers into an array containing the real part of the numbers and
    another one containing the imaginary part of the complex numbers."""

    real_part_numbers = [real_part[0] for real_part in complex_numbers_list]
    imaginary_part_numbers = [imaginary_part[1] for imaginary_part in complex_numbers_list]

    return real_part_numbers, imaginary_part_numbers


def find_longest_sequence_for_given_sum(complex_numbers_list, given_sum):
    """Find all the sequences which have the sum of the elements equal to a given sum."""

    # list with the tuples containing starting and finish index of all sequences
    # for whose elements form the given sum
    sequences_found = []

    # sequences can start_program from the first element to the last but one
    sequence_starting_index = 0

    while sequence_starting_index < len(complex_numbers_list) - 1:
        sequence_finish_index = sequence_starting_index + 1
        sum_of_actual_sequence_elements = complex_numbers_list[sequence_starting_index]

        while sequence_finish_index < len(complex_numbers_list):
            sum_of_actual_sequence_elements += complex_numbers_list[sequence_finish_index]

            if sum_of_actual_sequence_elements == given_sum:
                sequences_found.append((sequence_starting_index, sequence_finish_index))

            sequence_finish_index += 1

        sequence_starting_index += 1

    return sequences_found


def find_common_sequences(complex_numbers_list):
    """Given two arrays with tuples check if there are any common tuples."""

    common_real_imaginary_sum_sequences = []
    real_part_numbers, imaginary_part_numbers = split_complex_numbers_into_parts(complex_numbers_list)

    real_part_sequences = find_longest_sequence_for_given_sum(real_part_numbers, 10)
    imaginary_part_sequences = find_longest_sequence_for_given_sum(imaginary_part_numbers, 10)

    for real_part_sequence in real_part_sequences:
        if real_part_sequence in imaginary_part_sequences:
            common_real_imaginary_sum_sequences.append(real_part_sequence)

    return common_real_imaginary_sum_sequences


def get_longest_real_imaginary_common_sequence(complex_numbers_list):

    common_real_imaginary_sum_sequences = find_common_sequences(complex_numbers_list)

    if not common_real_imaginary_sum_sequences:
        return None

    else:
        longest_sequence_length = common_real_imaginary_sum_sequences[0][1] - common_real_imaginary_sum_sequences[0][0]
        longest_sequence = common_real_imaginary_sum_sequences[0]

        for common_real_imaginary_sum_sequence in common_real_imaginary_sum_sequences:
            if common_real_imaginary_sum_sequence[1] - common_real_imaginary_sum_sequence[0] > longest_sequence_length:
                longest_sequence_length = common_real_imaginary_sum_sequence[1] - common_real_imaginary_sum_sequence[0]
                longest_sequence = common_real_imaginary_sum_sequence

        return longest_sequence


def initialize_complex_numbers_list():
    """
    Create a few test complex numbers.
    :return: List of created complex numbers.
    """
    return [create_complex_number(1, 1), create_complex_number(12, -2), create_complex_number(10, 2),
            create_complex_number(3, -3), create_complex_number(19, 3), create_complex_number(6, 5),
            create_complex_number(16, -5), create_complex_number(5, 8), create_complex_number(3, 2),
            create_complex_number(-1, -6), create_complex_number(8, 14)]


def create_complex_number(real, imaginary):
    """
    Function to create a complex number object.
    :param real - the real part of the complex number.
    :param imaginary - the imaginary part of the complex number.
    :return The complex number.
    """
    if real == 0 and imaginary == 0:
        return None

    return [real, imaginary]


# We use 'setters' and 'getters'

def get_real_part(complex_number):
    """Get the real part of a complex number."""

    return complex_number[0]


def get_imaginary_part(complex_number):
    """Get the imaginary part of a complex number."""

    return complex_number[1]


def add_complex_number(complex_numbers_list, complex_number):
    """
    Add a new complex number to the list.
    :param complex_numbers_list: The list of already existing complex numbers.
    :param complex_number: The new complex number.
    """
    complex_numbers_list.append(complex_number)


# UI section
# (write all functions that have input or print statements here).
# Ideally, this section should not contain any calculations relevant to program functionalities


def handle_user_input(message):
    """Keep asking the user for an integer-type input."""

    # input message is not a number
    valid_input = False

    # initialize the user input
    user_input = ""

    # input message is still not a number
    while not valid_input:
        try:
            user_input = int(input(message))
            valid_input = True
        except ValueError:
            print("Not a valid input. Try again!")

    return user_input


def delete_complex_number_ui(complex_numbers_list):
    """Delete a complex number from the list by the index passed."""

    show_all_complex_numbers(complex_numbers_list, 1)

    input_message = "Which complex number would you like to delete? Enter the index of the number. "

    index = handle_user_input(input_message)

    if index < 1 or index > len(complex_numbers_list):
        print("Invalid index.")
    else:
        complex_numbers_list.pop(index - 1)
        print("Complex number successfully deleted.")


def get_real_part_input():
    """Ask the user to enter a number."""

    real_part_input = "Enter the real part of the complex number= "

    return handle_user_input(real_part_input)


def get_imaginary_part_input():
    """Ask the user to enter a number."""

    imaginary_part_input = "Enter the imaginary part of the complex number= "

    return handle_user_input(imaginary_part_input)


def add_complex_number_ui(complex_number_list):
    """Get the real and imaginary part from the user input and add the corresponding complex number to the list."""

    real_part = get_real_part_input()

    imaginary_part = get_imaginary_part_input()

    # create the complex number with the given real and imaginary part
    complex_number = create_complex_number(real_part, imaginary_part)

    if complex_number is None:

        # if both real and imaginary parts are 0
        print('Invalid complex number.')

    else:

        # if the complex number is valid add it to the list
        add_complex_number(complex_number_list, complex_number)
        print("Complex number added successfully!")


def complex_number_format(real_part, imaginary_part):
    """Given the parts of a complex number, determine the appropriate number format in a string."""

    if real_part == 0:

        # the number doesn't exist
        if imaginary_part == 0:
            return None

        # the number has only the real part
        else:
            return f"{imaginary_part}i"

    else:

        # the number has only the imaginary part
        if imaginary_part == 0:
            return real_part

        # the imaginary part is negative
        elif imaginary_part < 0:
            return f"{real_part} - {abs(imaginary_part)}i"

        # the imaginary part is positive
        else:
            return f"{real_part} + {imaginary_part}i"


def show_all_complex_numbers(complex_numbers, starting_index):
    """Generate all the complex numbers from the created list."""

    complex_numbers_starting_index = starting_index

    for complex_number in complex_numbers:
        complex_number_value = complex_number_format(get_real_part(complex_number), get_imaginary_part(complex_number))

        # avoid the case both real and imaginary parts are 0
        if complex_number_value is not None:
            print(f"z{complex_numbers_starting_index} = {complex_number_value}")
            complex_numbers_starting_index += 1


def print_longest_sequence_of_sum_10(complex_numbers_list):
    """Print longest sequence for which sum of its elements is 10+10i."""

    longest_real_imaginary_common_sequence_indexes = get_longest_real_imaginary_common_sequence(complex_numbers_list)

    # such sequence does not exist
    if longest_real_imaginary_common_sequence_indexes is None:
        print("It does not exist the longest sequence for which sum of its elements is 10 + 10i. "
              "Try again after adding some new complex numbers.")
    else:
        longest_real_imaginary_common_sequence = complex_numbers_list[longest_real_imaginary_common_sequence_indexes[0]:
                                                                      longest_real_imaginary_common_sequence_indexes[1]
                                                                      + 1]

        # print the sequence with the suitable z counter numbers
        print("The longest sequence for which sum of its elements is 10 + 10i:")
        show_all_complex_numbers(longest_real_imaginary_common_sequence,
                                 longest_real_imaginary_common_sequence_indexes[0] + 1)


def print_consecutive_number_pairs_have_equal_sum(complex_numbers_list):
    """Print longest sequence for which consecutive number pairs have equal sum."""

    pairs_indexes = compare_equal_pairs_from_both_cases(complex_numbers_list)

    # such sequence does not exist
    if pairs_indexes is None:
        print("There are no such pairs. Try again after adding some new complex numbers.")
    else:
        complex_numbers = complex_numbers_list[pairs_indexes[0]:pairs_indexes[1] + 1]

        # print the sequence with the suitable z counter numbers
        print("The longest sequence for which consecutive number pairs have equal sum:")
        show_all_complex_numbers(complex_numbers, pairs_indexes[0] + 1)


def print_user_menu():
    print("1. Add a complex number.")
    print("2. Delete a complex number.")
    print("3. Show all complex numbers.")
    print("4. Show the longest sequence for which consecutive number pairs have equal sum.")
    print("5. Show the longest sequence for which sum of its elements is 10 + 10i.")
    print("6. Exit the program.")


def start_program():

    complex_numbers_list = initialize_complex_numbers_list()

    while True:
        print_user_menu()

        option = input("User option: ")
        if option == '1':
            add_complex_number_ui(complex_numbers_list)
        elif option == '2':
            delete_complex_number_ui(complex_numbers_list)
        elif option == '3':
            show_all_complex_numbers(complex_numbers_list, 1)
        elif option == '4':
            print_consecutive_number_pairs_have_equal_sum(complex_numbers_list)
        elif option == '5':
            print_longest_sequence_of_sum_10(complex_numbers_list)
        elif option == '6':
            return
        else:
            print("Option does not exist. Try again!")


if __name__ == '__main__':
    start_program()
