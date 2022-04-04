# NOTE: I certainly could refactor 13 and 14 more because they are too long and don't respect
# the single-responsibility principle at all, but I'm too exhausted to find another solve that can
# allow me to do that. This applies to the problem 2 as well, but I hope the rest of them are
# good enough. I enjoyed doing them so I decided to solve them all.


# a function that keeps asking the user for input until a number is passed
def handle_user_input(message):
    # input message is not a number
    valid = False

    # initialize the user input
    user_input = ""

    # input message is still not a number
    while not valid:
        try:
            user_input = int(input(message))
            valid = True
        except ValueError:
            print("Not a valid input. Try again!")

    return user_input


# 1. Generate the first prime number larger than a given natural number n.


def check_prime_number(number):
    """Check if the number passed is prime."""

    is_prime = True

    if number >= 2:
        # go through each number from 2 to user's number - 1 and check if it divides the user's number
        for i in range(2, number):
            if (number % i) == 0:

                # if a value that divides the number is found, set flag to True
                is_prime = False

                # stop the loop
                break
    # if the number is smaller than 2, it is not prime
    else:
        is_prime = False

    return is_prime


def next_prime_input():
    """Ask the user to enter a natural number."""

    input_message = "Insert a natural number and I will generate the" \
                    " first prime number larger than the one you give me: "

    return handle_user_input(input_message)


def find_next_prime_number(user_number):
    """Find the first prime number larger than the given one."""

    # get the first number after the given one
    prime_number = user_number + 1

    # the next prime number wasn't found
    not_found = True

    while not_found:
        # check if the actual number is prime or not
        if check_prime_number(prime_number):

            # return the number and stop the process
            return prime_number

        prime_number += 1


def generate_next_prime_number():
    """Generate the first prime number larger than a given natural number."""

    user_number = next_prime_input()

    return f"The first prime number larger than {user_number} is {find_next_prime_number(user_number)}."


# 2. Given natural number n, determine the prime numbers p1 and p2
# such that n = p1 + p2 (check the Goldbach hypothesis).


def prime_pairs_input():
    """Ask the user to enter a natural number."""

    input_message = "Enter an even integer, greater than 4: "

    return handle_user_input(input_message)


def prime_numbers_pairs():
    """Given a natural number, determine the prime numbers p1 and p2 such that n = p1 + p2."""

    user_number = prime_pairs_input()

    pairs = []

    if user_number > 4:
        # the Goldbach hypothesis applies for even numbers(bigger than 4)
        if not user_number % 2:
            p1 = 3
            p2 = user_number - 3

            while p1 <= p2:
                # both pair's terms must be prime
                if check_prime_number(p1) and check_prime_number(p2):
                    pairs.append(f"{user_number} = {p1} + {p2}")
                # the pairs can be formed only with odd numbers(number 2 is the single even prime number)
                p1 += 2
                p2 -= 2

        else:
            # if a number is odd, one of the pair's term must be 2
            if check_prime_number(user_number-2):
                pairs.append(f"{user_number}  = 2 + {user_number - 2}")

    return pairs


def prime_numbers_pairs_output():
    """Print the prime numbers pairs if they exist, if not a specific message should be displayed."""

    pairs = prime_numbers_pairs()

    if len(pairs):
        print("Pairs found:")
        for pair in pairs:
            print(pair)

    else:
        print("No pairs found.")


# 3. For a given natural number n find the minimal natural number m formed with the same digits. (e.g. n=3658, m=3568).


def get_number_digits(number):
    """Given a number, create an array with its digits."""

    digits = []

    while number > 0:
        digits.append(number % 10)
        number //= 10

    return digits


def create_number_from_digits(digits):
    """Given a digits array, create a number with them, placing the digits in the same order as they are in array."""

    number = 0

    for digit in digits:
        number = number * 10 + digit

    return number


def find_minimal_number():
    """For a given natural number, find the minimal natural number formed with the same digits."""

    input_message = "Insert a natural number and I will find the smallest natural number written with the same digits: "
    user_number = handle_user_input(input_message)

    # get all the digits contained by the number
    number_digits = get_number_digits(user_number)

    # ascending order
    number_digits.sort()

    return f"Minimal natural number that you are looking for: {create_number_from_digits(number_digits)}."


# 4. For a given natural number n find the largest natural number written with the same digits. (e.g. n=3658, m=8653).


def largest_number_input():
    """Ask the user to enter a natural number."""

    input_message = "Insert a natural number and I will find the largest natural number written with the same digits: "

    return handle_user_input(input_message)


def find_largest_number():
    """For a given natural number, find the largest natural number written with the same digits."""

    user_number = largest_number_input()

    # get all the digits contained by the number
    number_digits = get_number_digits(user_number)

    # descending order
    number_digits.sort(reverse=True)

    return f"Largest natural number which you are looking for: {create_number_from_digits(number_digits)}."


# 5. Generate the largest prime number smaller than a given natural number n.
# If such a number does not exist, a message should be displayed.


def previous_prime_input():
    """Ask the user to enter a natural number."""

    input_message = "Insert a natural number and I will generate the largest " \
                    "prime number smaller than the one you give me: "

    return handle_user_input(input_message)


def get_previous_prime_number(input_number):
    """Check if there is any largest prime number smaller than a given natural number."""

    # the next number smaller than the given one
    prime_number = input_number - 1

    # check each number lower than the given one until a prime one is found
    while prime_number > 1:
        if check_prime_number(prime_number):
            return f"The largest prime number smaller than {input_number} is {prime_number}."
        prime_number -= 1

    return "Unlucky, such a number does not exist. Try another value."


def determine_previous_prime_number():
    """Generate the largest prime number smaller than a given natural number or the replacement message."""

    input_number = previous_prime_input()

    return get_previous_prime_number(input_number)


if __name__ == '__main__':
    # first problem
    print(generate_next_prime_number())
    # # second problem
    # prime_numbers_pairs_output()
    # # third problem
    # print(find_minimal_number())
    # # fourth problem
    # print(find_largest_number())
    # # fifth problem
    # print(determine_previous_prime_number())
