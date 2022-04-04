from functions import *

"""
    unit tests for non-ui functions
"""


def test_initialize_complex_numbers_list_history():
    assert initialize_complex_numbers_list_history([]) == [[]]
    assert initialize_complex_numbers_list_history([[1, 2], [3, 4]]) == [[[1, 2], [3, 4]]]
    assert initialize_complex_numbers_list_history([[0, 3], [-8, 5], [12, 3]]) == [[[0, 3], [-8, 5], [12, 3]]]


def test_create_complex_number():
    assert create_complex_number(0, 1) == [0, 1]
    assert create_complex_number(0, 0) is None
    assert create_complex_number(-5, 0) == [-5, 0]
    assert create_complex_number(-2, -7) == [-2, -7]
    assert create_complex_number(178, 39) == [178, 39]


def test_get_real_part():
    assert get_real_part([1, 4]) == 1
    assert get_real_part([0, 0]) == 0
    assert get_real_part([-4, 8]) == -4


def test_get_imaginary_part():
    assert get_imaginary_part([-1, 4]) == 4
    assert get_imaginary_part([0, 0]) == 0
    assert get_imaginary_part([4, -8]) == -8


def test_get_imaginary_part_format():
    assert get_imaginary_part_format(1) == ""
    assert get_imaginary_part_format(-1) == ""
    assert get_imaginary_part_format(5) == 5
    assert get_imaginary_part_format(0) == 0
    assert get_imaginary_part_format(-11) == 11


def test_complex_number_format():
    assert complex_number_format(0, 5) == "5i"
    assert complex_number_format(0, -3) == "-3i"
    assert complex_number_format(0, 1) == "i"
    assert complex_number_format(2, 3) == "2+3i"
    assert complex_number_format(4, -7) == "4-7i"
    assert complex_number_format(8, 0) == "8"
    assert complex_number_format(0, 0) is None


def test_check_if_a_string_has_numbers():
    assert check_if_a_string_has_numbers("hello") is False
    assert check_if_a_string_has_numbers("age 11") is True
    assert check_if_a_string_has_numbers("L33T") is True
    assert check_if_a_string_has_numbers("number one") is False
    assert check_if_a_string_has_numbers("") is False


def test_split_user_input_into_words():
    assert split_user_input_into_words("hello,   user") == ["hello,", "user"]
    assert split_user_input_into_words("testing_function") == ["testing_function"]
    assert split_user_input_into_words("") == []
    assert split_user_input_into_words("a     b c     d   e") == ["a", "b", "c", "d", "e"]


def test_split_complex_numbers_into_parts():
    assert split_complex_numbers_into_parts("7+8i") == [7, 8]
    assert split_complex_numbers_into_parts("4 +   8i") is None
    assert split_complex_numbers_into_parts("-2-4j") == [-2, -4]
    assert split_complex_numbers_into_parts("1+i") == [1, 1]
    assert split_complex_numbers_into_parts("i") == [0, 1]
    assert split_complex_numbers_into_parts("+4i") == [0, 4]
    assert split_complex_numbers_into_parts("    2i") == [0, 2]


def test_check_if_complex_number_position_exists():
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "3") is True
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "7") is False
    assert check_if_complex_number_position_exists([], "1") is False
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "position") is False
    assert check_if_complex_number_position_exists([[1, 3], [-2, -3], [0, 7], [1, 4]], "a5b") is False


def test_replace_particular_value_in_a_list():
    assert replace_particular_value_in_a_list([[2, -3], [4, 7], [2, -3]], [2, -3], [1, 2]) == [[1, 2], [4, 7], [1, 2]]
    assert replace_particular_value_in_a_list([[2, -3], [4, 7], [2, -3]], [2, 5], [1, 2]) == [[2, -3], [4, 7], [2, -3]]
    assert replace_particular_value_in_a_list([], [2, 5], [1, 3]) == []


def test_get_complex_number_modulo():
    assert get_complex_number_modulo(3, 4) == 5
    assert get_complex_number_modulo(12, 15) == 19.209372712298546
    assert get_complex_number_modulo(0, 0) == 0
    assert get_complex_number_modulo(2, 7) == 7.280109889280518


def test_undo_last_operation_done():
    assert undo_last_operation_done([]) == "There are no list modification operations to be undone."
    assert undo_last_operation_done([[[1, 2], [-1, 6]]]) == "There are no list modification operations to be undone."
    assert undo_last_operation_done([[[1, 2], [-1, 6]], [[2, -3], [4, 7], [2, -3]]]) == \
           "The last operation performed was undone."
    assert undo_last_operation_done([[[1, 2], [-1, 6]], [[1, 2], [-1, 6]]]) == \
           "The complex numbers list didn't change after the last operation."


def run_unit_testing_functions():
    test_initialize_complex_numbers_list_history()
    test_create_complex_number()
    test_get_real_part()
    test_get_imaginary_part()
    test_get_imaginary_part_format()
    test_complex_number_format()
    test_check_if_a_string_has_numbers()
    test_split_user_input_into_words()
    test_split_complex_numbers_into_parts()
    test_check_if_complex_number_position_exists()
    test_replace_particular_value_in_a_list()
    test_get_complex_number_modulo()
    test_undo_last_operation_done()


if __name__ == '__main__':
    run_unit_testing_functions()
