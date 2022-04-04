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
        if input_number <= 0 or input_number >= 5:
            raise ValueError("The input should be a non-zero natural number.")

    else:
        raise ValueError("The number's value should be an integer "
                         "between one and four(no spaces or any other characters)!")

    return input_number


def get_cartesian_product_tuples_of_0_and_1s(sequence_length):
    """
    Create a list with all non-zero existing vectors in Z2^sequence_length, and then transform it
    into a tuple.
    :param sequence_length: the number of elements in each vector.
    :return: a tuple with all non-zero existing vectors.
    :pre-condition: the sequence length should be a non-zero natural number.
    """

    # create the cartesian product list of the given length, which represents all vectors from the Z2^sequence_length
    cartesian_product_list = [list(index) for index in itertools.product([0, 1], repeat=sequence_length)]

    # delete the zero vector from the list
    zero_vector = [0] * sequence_length
    cartesian_product_list.remove(zero_vector)

    # in order to be easier to print the bases, the vectors will be stored in tuples of tuples
    # because tuples already got the round brackets in their format
    cartesian_product_list = tuple(tuple(element) for element in cartesian_product_list)

    return cartesian_product_list


def get_number_of_bases_and_vectors_of_each_basis(all_non_zero_possible_vectors, basis_dimension):
    """
    Given a tuple with all non-zero existing vectors in Z2^sequence_length and the dimension of the basis,
    check all the possible permutations of the vectors which can create a basis.
    :param all_non_zero_possible_vectors:
    :param basis_dimension: the dimension of the basis.
    :return: number of the bases found and their content.
    :pre-condition: all_non_zero_possible_vectors should be a tuple with all non-zero existing vectors that can
    be a part of the basis, basis_dimension should be a positive integer.
    """

    # store the number of bases found
    number_of_bases = 0

    # store the bases(in the tuple format) found in a list
    bases = list()

    # check for each vector of given dimension if the determinant of the matrix
    # represented by the vectors is not equal to 0(working in Z2 => using modulo 2)
    for basis in itertools.permutations(all_non_zero_possible_vectors, basis_dimension):
        if numpy.linalg.det(basis) % 2 != 0:
            number_of_bases += 1
            bases.append(basis)

    return number_of_bases, bases


def run_algorithm():

    # get the input string from the first line of the file
    with open("input.txt") as file:
        input_from_file = file.readline()

    # open the output file in the 'write' mode, in order to clean the data that existed before the run
    file = open("output.txt", "w")

    # check if the input passed is valid
    try:
        input_number = check_input_is_valid_number(input_from_file)
    except ValueError as error:
        file.write(str(error))
        return

    # get the values necessary for both sub-points
    all_non_zero_possible_vectors = get_cartesian_product_tuples_of_0_and_1s(input_number)
    number_of_bases, bases = get_number_of_bases_and_vectors_of_each_basis(all_non_zero_possible_vectors, input_number)

    # open the output file again, but in the 'append' mode, to keep the data displayed earlier unmodified
    file = open("output.txt", "a")

    # print the corresponding output
    file.write(f"1. the number of bases of the vector space Z2^{input_number} over Z2 is {number_of_bases}.\n")

    file.write(f"2. the vectors of each such basis are: \n")

    if input_number == 1:
        file.write(f"((1))\n")

    else:
        for basis in bases:
            file.write(f"{basis}\n")


if __name__ == '__main__':
    run_algorithm()
