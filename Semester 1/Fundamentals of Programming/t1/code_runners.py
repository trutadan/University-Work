import random
import time

"""
Implement the solution here. 
You may add other source files.
Make sure you commit & push the source code before the end of the test.

Solutions using user-defined classes will not be graded.
"""


"""
    non-ui functionalities
"""

# we use getter


def get_nth_digit_from_a_string_number(number, digit_position):
    return number[digit_position]


def generate_four_digit_random_secret_number_as_string():
    """
    Generate a valid four-digit random secret number, as a string.
    :return: the secret number.
    :post-condition: the generated number must be a string consisting of 4 distinct digits.
    """

    # compute the generated number as a string
    generated_number = ""

    # make a list with all digits between 0 and 9
    number_digits = list(range(10))

    # get the first digit which should be a random integer between 1 and 9
    first_digit_from_number = random.randint(1, 9)

    # delete the selected digit from the list and append it to the string
    number_digits.remove(first_digit_from_number)
    generated_number += str(first_digit_from_number)

    # for each of the 3 more digits we need to find
    for steps in range(3):
        # get a random digit from the remaining digits list
        distinct_number_digit = random.choice(number_digits)

        # delete the selected digit from the list and append it to the string
        number_digits.remove(distinct_number_digit)
        generated_number += str(distinct_number_digit)

    return generated_number


def get_computer_report_for_user_input_number(input_number, computer_generated_number):
    codes = []
    runners = []
    input_number_digits = []
    computer_generated_number_digits = []

    for digit_position in range(4):

        digit_from_input_number = get_nth_digit_from_a_string_number(input_number, digit_position)
        input_number_digits.append(digit_from_input_number)

        digit_from_generated_number = get_nth_digit_from_a_string_number(computer_generated_number, digit_position)
        computer_generated_number_digits.append(digit_from_generated_number)

        if digit_from_input_number == digit_from_generated_number:
            codes.append(digit_from_generated_number)

    for digit in input_number_digits:
        if digit in computer_generated_number_digits and digit not in codes:
            runners.append(digit)

    return codes, runners


def check_if_60_seconds_passed(starting_time):
    end_time = time.time()
    time_elapsed = (end_time - starting_time)

    if time_elapsed > 60:
        return False

    return True


"""
    ui functionalities + start menu
"""


def check_if_an_input_number_is_valid(input_number):
    # check if a number has the length of 4 and all characters are digits
    if len(input_number) == 4 and input_number.isdigit():

        # check if the first one is not the 0 digit
        if get_nth_digit_from_a_string_number(input_number, 0) == '0':
            return False

        # check if the digits of the number are distinct
        digits_set = set(input_number)
        if len(digits_set) == 4:
            return True

    return False


def start_game():

    print("Welcome to Code runners game! You have 60 seconds to win this!")
    start_time = time.time()

    computer_generated_number = generate_four_digit_random_secret_number_as_string()

    while check_if_60_seconds_passed(start_time):

        user_input_number = input("Please enter your four distinct digits number: ")

        if check_if_60_seconds_passed(start_time) is False:
            break

        else:
            if user_input_number == '8086':
                print(f"The computer revealed the number it selected: {computer_generated_number}.")

            elif check_if_an_input_number_is_valid(user_input_number):
                codes, runners = get_computer_report_for_user_input_number(user_input_number, computer_generated_number)
                if len(codes) == 4:
                    print("Congratulations, you won the game!")
                    return
                else:
                    print(f"{user_input_number} -> {len(codes)} codes and {len(runners)} runners.")
                    if len(codes) > 0:
                        print(f"{codes} are codes")
                    if len(runners) > 0:
                        print(f"{runners} are runners")

                    print("Try with another number, if you still have time.")
            else:
                print("The input is incorrect. Thank you for playing the game!")
                return

    print("You ran out of time! 60 seconds passed...")


if __name__ == '__main__':
    start_game()
