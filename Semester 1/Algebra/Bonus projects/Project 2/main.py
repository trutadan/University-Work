import itertools
import os


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
        if input_number < 1 or input_number > 4:
            raise ValueError("The input should be a non-zero natural number.")

    else:
        raise ValueError("The number's value should be an integer "
                         "between one and four(no spaces or any other characters)!")

    return input_number


def get_cartesian_product_list_with_set_elements(number_of_set_elements):
    """
    Get a list of all possible cartesian product lists of the given length.
    :param number_of_set_elements: the length of the lists.
    :return: the list of all lists obtained as a cartesian product of a list of elements.
    """

    set_elements = list(range(0, number_of_set_elements))

    return [list(index) for index in itertools.product(set_elements, repeat=number_of_set_elements)]


def create_set_elements(number_of_set_elements):
    """
    Transform the set in the format {0, 1, 2, ..., n} to the one in the wanted format {a1, a2, ..., an}.
    :param number_of_set_elements: number of the elements in the set.
    :return: a string with the modified set.
    """

    # the elements of the set are going to be created as a string, to be easier to print
    set_elements = ""

    for element in list(range(0, number_of_set_elements)):
        set_elements += f"a{element + 1}, "
    # for the last element of the set, an additional string(", ") will be added, so delete it
    set_elements = set_elements[:-2]

    return set_elements


def is_table_associative(given_table):
    """
    Check if a table of operations is associative by using matrices. It is checking the well-known property
    on a set like {0, 1, 2, ..., n}, for the sake of simplicity,
    but this set can be also represented as {a1, a2, ..., an}.
    :param given_table: the table to check the associativity for.
    :return: True if the table is associative, False if not.
    """

    for i in range(0, len(given_table)):
        for j in range(0, len(given_table)):
            for k in range(0, len(given_table)):
                if given_table[given_table[i][j]][k] != given_table[i][given_table[j][k]]:
                    return False
    return True


# I am using this function because, in the algorithm, I first write the matrices, and only then, after I count them
# all, I know how many they are and can print this information. This function displays
def prepend_line_in_file_text(file_name, line):
    """
    Insert given string as a new line at the beginning of a file.
    :param file_name: the file of the name in which to prepend.
    :param line: the text that is to prepend.
    """

    # define name of temporary dummy file
    dummy_file = file_name + '.bak'

    # open original file in read mode and dummy file in write mode
    with open(file_name, 'r') as read_obj, open(dummy_file, 'w') as write_obj:
        # write given line to the dummy file
        write_obj.write(line + '\n')

        # read lines from original file one by one and append them to the dummy file
        for line in read_obj:
            write_obj.write(line)

    # remove original file
    os.remove(file_name)

    # rename dummy file as the original file
    os.rename(dummy_file, file_name)


def display_associative_table_operations_and_counter():
    # get the input string from the first line of the file
    with open("input.txt") as file:
        input_from_file = file.readline()
        file.close()

    # open the output file in the 'write' mode, in order to clean the data that existed before the run
    file = open("output.txt", "w")

    # check if the input passed is valid
    try:
        number_of_set_elements = check_input_is_valid_number(input_from_file)
    except ValueError as error:
        file.write(str(error))
        return

    file.close()

    # open the output file again, but in the 'append' mode, to keep the data displayed earlier unmodified
    file = open("output.txt", "a")

    # get all possible lists containing the elements of the set(as cartesian product)
    cartesian_product_list_with_set_elements = get_cartesian_product_list_with_set_elements(number_of_set_elements)

    # count the number of associative tables found
    number_of_associative_operations = 0

    # create a set of elements displayed as string, in order to handle the output
    set_elements = create_set_elements(number_of_set_elements)

    # print the corresponding output
    file.write("2. the operation tables of the associative operations on A = "
               "{" + set_elements + "} are given by the matrices: \n")

    # take each generated table, check if it is associative and write the elements of the table
    for table in itertools.product(cartesian_product_list_with_set_elements, repeat=number_of_set_elements):
        if is_table_associative(table):
            for line in table:
                for element in line:
                    file.write(f"a{str(element + 1)} ")
                file.write("\n")
            file.write("\n")
            number_of_associative_operations += 1

    file.close()

    # print the number of associative tables at the beginning of the file, before
    # all tables have been printed, in order to satisfy the project requirement
    prepend_line_in_file_text('output.txt', "1. the number of associative operations on a set A = {"
                              + set_elements + "}" + f" is {number_of_associative_operations}. \n")


if __name__ == '__main__':
    display_associative_table_operations_and_counter()
