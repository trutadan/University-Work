from p1 import handle_user_input, check_prime_number


# 12. Determine the age of a person, in number of days. Take into account leap years, as well as the date of birth
# and current date (year, month, day). Do not use Python's inbuilt date/time functions.


def get_current_date():
    """Ask the user for the current date, expressed in numbers(year, month, day)."""

    current_year = handle_user_input("Enter the current year: ")
    current_month = handle_user_input("Enter the current month(number): ")
    current_day = handle_user_input("Enter the current day(number): ")

    return current_year, current_month, current_day


def get_birth_date():
    """Ask the user for the birth of date, expressed in numbers(year, month, day)."""

    birth_year = handle_user_input("Enter the birth year: ")
    birth_month = handle_user_input("Enter the birth month(number): ")
    birth_day = handle_user_input("Enter the birth day(number): ")

    return birth_year, birth_month, birth_day


def calc_years_between(birth_date, current_date):
    """Determine how many years, in number of days, taking leap years into account, the user has lived,
    excepting the birth year and the current year."""

    years_number = 0
    aux_year = birth_date[0] + 1

    while aux_year < current_date[0]:
        if aux_year % 4:
            years_number += 365

        # leap year
        else:
            years_number += 366
        aux_year += 1

    return years_number


def calc_days_remaining_after(current_date):
    """Determine the days the user has lived in the current year."""

    # each position represents the number of days for each month
    month_days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    aux_month = 1

    # number of days lived in the current month
    days_number = current_date[2]

    while aux_month < current_date[1]:
        days_number += month_days[aux_month - 1]
        aux_month += 1

    return days_number


def calc_days_remaining_before(birth_date):
    """Determine the days between the day in which the user has been born and the beginning of the next year."""

    # each position represents the number of days for each month
    month_days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    aux_month = 12

    # number of days lived in the month of birth
    days_number = month_days[birth_date[1] - 1] - birth_date[2]

    while aux_month > birth_date[1]:
        days_number += month_days[aux_month - 1]
        aux_month -= 1

    return days_number


def age_in_days_number():
    """Determine the age of a person, in number of days, given the date of birth and current date."""
    print("With your date of birth and current date and I will determine your age, in number of days.")

    print("First, I will need your date of birth.")
    birth_date = get_birth_date()

    print("Second, I will need the current date.")
    current_date = get_current_date()

    number_of_days = calc_years_between(birth_date, current_date) + \
                     calc_days_remaining_before(birth_date) + \
                     calc_days_remaining_after(current_date)

    return f"You have lived {number_of_days} days. Many happy returns!"


# 13. Determine the n-th element of the sequence 1,2,3,2,5,2,3,7,2,3,2,5,... obtained
# from the sequence of natural numbers by replacing composed numbers
# with their prime divisors, without memorizing the elements of the sequence.


def nth_element_input():
    """Ask the user to enter a natural number."""

    message = "Enter a natural number and I will determine the n-th element of " \
              "the sequence obtained by replacing composed numbers with their prime divisors: "

    return handle_user_input(message)


def get_nth_element():
    """Given a natural number n, determine the n-th element of the sequence obtained from the sequence
    of natural numbers by replacing composed numbers with their prime divisors"""

    user_number = nth_element_input()

    # the second element of the sequence
    aux_number = 2

    user_number -= 1

    # if the user's input is the number 1
    divisor = 1

    while user_number:
        divisor = 2

        actual_number = aux_number

        while actual_number != 1:

            # count the number of divisors for each numbers
            if not actual_number % divisor:
                while not actual_number % divisor:
                    actual_number //= divisor

                user_number -= 1

                # stop when it reaches the n-th element
                if user_number == 0:
                    return f"The n-th element of the sequence is: {divisor}."

            divisor += 1

        aux_number += 1

    return f"The n-th element of the sequence is: {divisor}."


# 14. Determine the n-th element of the sequence 1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,... obtained from
# the sequence of natural numbers by replacing composed numbers with their prime divisors,
# each divisor d being written d times, without memorizing the elements of the sequence.


def dup_nth_element_input():
    """Ask the user to enter a natural number."""

    message = "Enter a natural number and I will determine the n-th element of the sequence obtained by replacing " \
              "composed numbers with their prime divisors, \neach divisor d being written d times: "

    return handle_user_input(message)


def get_composed_nth_element():
    """Given a natural number n, determine the n-th element of the sequence obtained from the sequence of
    natural numbers by replacing composed numbers with their prime divisors, each divisor d being written d times."""

    user_number = dup_nth_element_input()

    if 1 <= user_number <= 3:
        return f"The n-th element of the sequence is: {user_number}."

    else:
        # the second element of the sequence
        aux_number = 4

        user_number -= 3

        while user_number:

            # as seen in the example, the prime numbers appear only once in the sequence
            if check_prime_number(aux_number):
                user_number -= 1
                if user_number == 0:
                    return f"The n-th element of the sequence is: {aux_number}."

            else:
                divisor = 2

                actual_number = aux_number

                while actual_number != 1:

                    # count the number of divisors for each numbers
                    if not actual_number % divisor:
                        while not actual_number % divisor:
                            actual_number //= divisor

                        # the divisor d is counted d times
                        for i in range(1, divisor+1):
                            user_number -= 1

                            # stop when it reaches the n-th element
                            if user_number == 0:
                                return f"The n-th element of the sequence is: {divisor}."

                    divisor += 1

            aux_number += 1


# 15. Generate the largest perfect number smaller than a given natural number n.
# If such a number does not exist, a message should be displayed. A number is perfect if it is equal
# to the sum of its divisors, except itself. (e.g. 6 is a perfect number, as 6=1+2+3).


def check_perfect_number(number):
    """Check if a number is perfect(it is equal to the sum of its divisors)."""

    divisors_sum = 1
    divisor = 2

    while divisor * divisor <= number:
        if number % divisor == 0:
            divisors_sum = divisors_sum + divisor + number/divisor
        divisor += 1

    return number == divisors_sum


def perfect_number_input():
    """Ask the user to enter a natural number."""

    message = 'Enter a natural number and I will display the largest perfect number smaller than the given one: '

    return handle_user_input(message)


def get_perfect_number(user_number):
    """Search the largest perfect number smaller than the value passed in 'user_number' parameter."""

    # 6 is the smallest perfect number
    while user_number >= 6:
        if check_perfect_number(user_number):
            return f"The largest perfect number you are looking for is {user_number}."
        user_number -= 1

    # if return didn't pass earlier, then no perfect number was found
    return "Sorry! There is no such number."


def generate_perfect_number():
    """Given a natural number, determine the largest perfect number smaller than the given one."""

    input_number = perfect_number_input()

    user_number = input_number - 1

    return get_perfect_number(user_number)


if __name__ == '__main__':
    # 12th problem
    print(age_in_days_number())
    # # 13th problem
    # print(get_nth_element())
    # # 14th problem
    # print(get_composed_nth_element())
    # # 15th problem
    # print(generate_perfect_number())
