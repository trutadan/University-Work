import itertools
import numpy


def check_input_is_valid_number(input_string):
    """
    Validate the input string given by the user, in order to see if it is a number in the suitable range.
    :param input_string: the string given by the user.
    :return: the integer form of the input_string in case it is a number, else an exception will be raised,
    that means there are no operations to be done, so the application will stop.
    """

    # first check if the number is a non-zero natural number
    if input_string.isnumeric():
        input_number = int(input_string)

        # then check if it is lower than 1 or bigger than 4
        if input_number < 2 or input_number > 5:
            raise ValueError("The number's value should be an integer between 2 and 5!")

    else:
        raise ValueError("The given value must be a natural number(no extra spaces or any other characters)!")

    return input_number


def get_cartesian_product_tuples_of_0_and_1s(number_of_columns):
    """
    Create a list with all non-zero existing vectors in Z2^sequence_length.
    :return: a list with all non-zero existing vectors.
    :pre-condition: the sequence length should be a non-zero natural number.
    """

    # create the cartesian product list of the given length, which represents all the rows
    # with which you can form the matrices
    cartesian_product_list = [list(index) for index in itertools.product([0, 1], repeat=number_of_columns)]

    return cartesian_product_list


def check_reduced_row_echelon_form(given_matrix):
    """
    Given a matrix, check if it is in row echelon form, and then check again if it also checks the reduced property.
    :param given_matrix: a matrix(an array of lists).
    :return: True if the matrix is in the reduced echelon form.
    :pre-condition: given_matrix is a list of lists(a matrix).
    """

    previous_row_number_of_0 = 0
    column_index = 0

    # remember the index of the columns which have a leading 1
    leading_entry_column_index = []

    # get the numbers of 0s on the first line before the leading 1
    while column_index < len(given_matrix[0]):
        if given_matrix[0][column_index] == 0:
            previous_row_number_of_0 += 1
        else:
            leading_entry_column_index.append(column_index)
            break

        column_index += 1

    # compare the number of 0s from the first line with the others(the consecutive ones)
    row = 1

    while row < len(given_matrix):
        actual_row_numbers_of_0 = 0
        column_index = 0

        while column_index < len(given_matrix[row]):
            if given_matrix[row][column_index] == 0:
                actual_row_numbers_of_0 += 1
            else:
                if column_index not in leading_entry_column_index:
                    leading_entry_column_index.append(column_index)
                    break
                else:
                    return False
            column_index += 1

        if actual_row_numbers_of_0 <= previous_row_number_of_0:
            return False

        previous_row_number_of_0 = actual_row_numbers_of_0
        row += 1

    # check if there are more 1s on the same column where you can find a leading 1 element
    # if there are, it means the matrix is not in row reduced echelon form
    given_matrix = numpy.array(given_matrix)
    number_of_1s = numpy.count_nonzero(given_matrix == 1, axis=0)
    for column in leading_entry_column_index:
        if number_of_1s[column] > 1:
            return False

    return True


def get_number_of_reduced_echelon_form_matrices_and_their_format(all_possible_matrix_rows_format, number_of_rows,
                                                                 number_of_columns):
    """
    Given a tuple with all non-zero existing vectors in Z2^sequence_length and the dimension of the basis,
    check all the possible permutations of the vectors which can create a basis.
    :return: number of the bases found and their content.
    :pre-condition: all_non_zero_possible_vectors should be a tuple with all non-zero existing vectors that can
    be a part of the basis, basis_dimension should be a positive integer.
    """

    # store the bases(in the tuple format) found in a list
    matrices_found = list()

    # check for each possible matrix if it is in the reduced echelon form
    for matrix in itertools.permutations(all_possible_matrix_rows_format, number_of_rows):
        matrix = list(matrix)
        if check_reduced_row_echelon_form(matrix) and matrix not in matrices_found:
            matrix = tuple(tuple(i) for i in matrix)
            matrices_found.append(matrix)

    # add the zero matrix to the list, since it is in raw echelon form for any given dimension
    zero_matrix = [[0] * number_of_columns] * number_of_rows
    zero_matrix = tuple(tuple(i) for i in zero_matrix)

    if zero_matrix not in matrices_found:
        matrices_found.append(zero_matrix)

    # store the number of bases found
    number_of_matrices_found = len(matrices_found)

    return number_of_matrices_found, matrices_found


def run_algorithm():
    # get the input string from the first line of the file
    with open("input.txt") as file:
        input_from_file = file.readline()

    m_value, n_value = input_from_file.split()

    # open the output file in the 'write' mode, in order to clean the data that existed before the run
    file = open("output.txt", "w")

    # check if the input passed is valid
    try:
        number_of_rows = check_input_is_valid_number(m_value)
        number_of_columns = check_input_is_valid_number(n_value)
    except ValueError as error:
        file.write(str(error))
        return

    # get the values necessary for both sub-points
    all_possible_matrix_rows_format = get_cartesian_product_tuples_of_0_and_1s(number_of_columns)
    number_of_matrices_found, matrices_found = \
        get_number_of_reduced_echelon_form_matrices_and_their_format \
            (all_possible_matrix_rows_format, number_of_rows, number_of_columns)

    # open the output file again, but in the 'append' mode, to keep the data displayed earlier unmodified
    file = open("output.txt", "a")

    # print the corresponding output
    file.write(
        f"1. the number of matrices A from M{number_of_rows},{number_of_columns}(Z2) in reduced echelon form is {number_of_matrices_found}.\n")

    file.write(f"2. the matrices A from M{number_of_rows},{number_of_columns}(Z2) in reduced echelon form are: \n")

    # print the matrices in the reduced row echelon form found
    for matrix in matrices_found:
        for row in matrix:
            file.write(f"{row}\n")
        file.write(f"\n")


if __name__ == '__main__':
    run_algorithm()
