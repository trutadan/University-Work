from p1 import handle_user_input, get_number_digits, check_prime_number


# 6. Determine a calendar date (as year, month, day) starting from two integer numbers representing
# the year and the day number inside that year (e.g. day number 32 is February 1st).
# Take into account leap years. Do not use Python's inbuilt date/time functions.


def get_ordinal_number(number):
    """Given a number, determine the right suffix to make it an ordinal number."""

    ordinal_suffixes = {1: 'st', 2: 'nd', 3: 'rd'}

    # the numbers between 10 and 20 don't follow the normal counting scheme
    if 10 <= number % 100 <= 20:
        suffix = 'th'
    else:

        # the second parameter('th') is a default case
        suffix = ordinal_suffixes.get(number % 10, 'th')

    return str(number) + suffix


def check_leap_year(year):
    """Given a year, check if it is a leap year or not."""

    # leap year
    if not year % 4:
        return 1

    return 0


def get_date_format(year, day):
    """Given the number of days belonging to a year, determine the month and the day specific to the days number."""

    calendar_dictionary = {
        1: ['January', 31],
        2: ['February', 28],
        3: ['March', 31],
        4: ['April', 30],
        5: ['May', 31],
        6: ['June', 30],
        7: ['July', 31],
        8: ['August', 31],
        9: ['September', 30],
        10: ['October', 31],
        11: ['November', 30],
        12: ['December', 31]
    }

    # check and correct data in case of a leap year
    calendar_dictionary[2][1] += check_leap_year(year)

    aux_day = 0
    month_counter = 1

    # starting with January, add each month's days until the user's number is reached
    while aux_day < day:
        aux_day += calendar_dictionary[month_counter][1]
        month_counter += 1

    month_counter -= 1
    aux_day -= calendar_dictionary[month_counter][1]

    return f"{year} {calendar_dictionary[month_counter][0]} {get_ordinal_number(day - aux_day)}"


def get_year_input():
    """Ask the user to enter a natural number representing a year."""

    year_message = "Enter the year: "

    return handle_user_input(year_message)


def get_day_input():
    """Ask the user to enter a natural number representing a day inside a year(0 < number < 357)."""

    day_message = "Enter the day number: "

    return handle_user_input(day_message)


def determine_calendar_date():
    """Determine a calendar date, starting from two integer numbers
     representing the year and the day number inside that year."""

    print("I need a year and a day number inside that year, and I will determine the calendar date.")

    year_input = get_year_input()
    day_input = get_day_input()

    return f"The calendar date: {get_date_format(year_input, day_input)}."


# 7. Determine the twin prime numbers p1 and p2 immediately larger than the given non-null natural number n.
# Two prime numbers p and q are called twin if q - p = 2.


def twin_prime_input():
    """Ask the user to enter a natural, non-null number."""

    message = "Enter a non-null natural number and I will determine the first twin prime numbers pair larger " \
              "than the given one: "

    return handle_user_input(message)


def get_twin_prime_pair(user_number):
    """Checks all immediately larger pairs of numbers(q - p = 2) than the given one for a twin prime pair."""

    # the twin pair can't be formed with two even prime numbers
    first_prime = user_number + 1 + user_number % 2

    while True:
        second_prime = first_prime + 2
        if check_prime_number(first_prime) and check_prime_number(second_prime):
            break

        # we go through all odd numbers until we can find a pair
        first_prime += 2

    return first_prime, second_prime


def determine_twin_prime_numbers():
    """Given a non-null natural number, determine the twin prime numbers immediately larger than the given one."""

    user_number = twin_prime_input()

    twin_pair = get_twin_prime_pair(user_number)

    return f"The first twin prime pair is p1 = {twin_pair[0]} and p2 = {twin_pair[1]}."


# 8. Find the smallest number m from the Fibonacci sequence, defined by f[0]=f[1]=1, f[n]=f[n-1] + f[n-2], for n > 2,
# larger than the given natural number n. (e.g. for n = 6, m = 8).


def fibonacci_sequence_input():
    """Ask the user to enter a natural number."""

    message = "Enter a natural number and I will determine the smallest number from the Fibonacci sequence," \
              "larger than the given one: "

    return handle_user_input(message)


def get_fibonacci_number(number):
    """Keep building a fibonacci sequence until obtaining a term that is larger than a given one."""

    # initialize first 2 fibonacci terms
    fibonacci_terms = [0, 1]

    actual_term = 1

    # keep building Fibonacci sequence until the smallest larger number than the passed one is found
    while actual_term <= number:
        actual_term = fibonacci_terms[-1] + fibonacci_terms[-2]
        fibonacci_terms.append(actual_term)

    return actual_term


def determine_fibonacci_sequence():
    """Given a natural number, find the smallest number from the Fibonacci sequence larger than the given one."""

    user_number = fibonacci_sequence_input()

    return f"The number you are looking for is {get_fibonacci_number(user_number)}."


# 9. Consider a given natural number n. Determine the product p of all the proper factors of n.


def factors_product_input():
    """Ask the user to enter a natural number."""

    message = "Enter a natural number and I will determine the product of all the proper factors of that number: "

    return handle_user_input(message)


def get_factors_product(user_number):
    """Calculate the product of all the proper factors of a number."""

    product = 1

    for number in range(1, user_number):
        product *= number

    return product


def determine_proper_factors_product():
    """Given a natural number, determine the product of all the proper factors of that number."""

    user_number = factors_product_input()

    product = get_factors_product(user_number)

    return f"The product is {product}."


# 10. The palindrome of a number is the number obtained by reversing the order of its digits
# (e.g. the palindrome of 237 is 732). For a given natural number n, determine its palindrome.


def reverse_string_number(number):
    """String reverse function used for numbers."""

    string = str(number)

    return string[::-1]


def palindrome_number_input():
    """Ask the user to enter a natural number."""

    message = "Enter a natural number and I will determine its palindrome: "

    return handle_user_input(message)


def determine_palindrome_number():
    """For a given natural number, determine its palindrome."""

    user_input = palindrome_number_input()

    return f"{user_input}'s palindrome is {reverse_string_number(user_input)}."


# 11. The numbers n1 and n2 have the property P if their writing in base 10 uses the
# same digits (e.g. 2113 and 323121). Determine whether two given natural numbers have property P.


def p_first_number_input():
    """Ask the user to enter the first natural number for checking the property P."""

    message_1 = "Enter the first number: "

    return handle_user_input(message_1)


def p_second_number_input():
    """Ask the user to enter the second natural number for checking the property P."""

    message_2 = "Enter the second number: "

    return handle_user_input(message_2)


def get_number_digits_set(number):
    """Given a natural number, the function gets a list with the number's digits,
    then transform it into a set to remove duplicates."""

    return set(get_number_digits(number))


def check_same_digits(number_1, number_2):
    """Check if 2 numbers are made up of the same digits."""

    digits_number_1 = get_number_digits_set(number_1)
    digits_number_2 = get_number_digits_set(number_2)

    return digits_number_1 == digits_number_2


def check_property_p():
    """Given two numbers, check if they have the property P(their writing in base 10 uses same digits)."""

    print("I will check if two given natural numbers have property P.")

    number_1 = p_first_number_input()
    number_2 = p_second_number_input()

    if check_same_digits(number_1, number_2):
        return f"Number '{number_1}' and number '{number_2}' have the property P!"

    return f"Number '{number_1}' and number '{number_2}' don't have the property P!"


if __name__ == '__main__':
    # 6th problem
    print(determine_calendar_date())
    # # 7th problem
    # print(determine_twin_prime_numbers())
    # # 8th problem
    # print(determine_fibonacci_sequence())
    # # 9th problem
    # print(determine_proper_factors_product())
    # # 10th problem
    # print(determine_palindrome_number())
    # # 11th problem
    # print(check_property_p())
