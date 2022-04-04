#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void print_menu();

int* dynamic_vector_allocation(int* starting_pointer, int* number_of_elements);

void read_vector_elements(int* starting_pointer, int number_of_elements);

void read_vector_from_console_and_display_it();

void display_vector_dynamically_allocated(int* starting_pointer, int number_of_elements);

void dynamic_vector_deallocation(int* starting_pointer);

int check_relatively_prime_numbers(int first_number, int second_number);

int get_number_from_user();

void display_numbers_relatively_prime_numbers_smaller_than_given_one(int number);

void run_first_laboratory_statement();

void display_longest_contiguous_subsequence_with_maximum_sum(int* vector_pointer, int vector_length);

void run_second_laboratory_statement();

void display_prime_numbers_and_their_exponent_from_a_number_decomposition(int number);

void run_third_laboratory_statement();

int main() {
    char command;
    int valid_input = 1;

    // as long as the user doesn't press the key 'd', the program keeps running
    while (valid_input)
    {

        print_menu();
        printf("Enter the type of the command: ");
        scanf(" %c", &command);

        switch(command){
        
        case 'a':
            read_vector_from_console_and_display_it();
            break;

        case 'b':
            run_first_laboratory_statement();
            break;

        case 'c':
            run_second_laboratory_statement();
            break;

        case 'd':
            run_third_laboratory_statement();
            break;

        case 'e':
            printf("Exit the program...\n\n");
            valid_input = 0;
            break;

        default:
            printf("Unexpected input. Choose between 'a', 'b', 'c' and 'd'.\n\n");
            break;
        }
        
    }
    return 0;
}

void print_menu() {
    // print the menu in a nice format
    printf("[a] Read a vector of numbers from the console.\n");
    printf("[b] Determine all the numbers smaller than a given natural and non-null number n and that are relatively prime to n.\n");
    printf("[c] Given a vector of numbers, find the longest contiguous subsequence with the maximum sum.\n");
    printf("[d] Print the exponent of a prime number from the decomposition in prime factors of a given number n. \n");
    printf("[e] Exit.\n\n");
}

int* dynamic_vector_allocation(int* starting_pointer, int* number_of_elements){
    // get the number of elements of the vector from the user
    printf("Enter the number of elements of the vector: ");
    scanf("%d", number_of_elements);

    // allocate dynamic memory to store a vector of given length (dynamically)
    starting_pointer = (int*)malloc(*number_of_elements * sizeof(int));

    // if the starting pointer was initialized with NULL, something went wrong
    if (!starting_pointer)
    {
        printf("Allocation error!");
        return 0;
    }

    return starting_pointer;
}

void read_vector_elements(int* starting_pointer, int number_of_elements){
    // get the numbers to be introduced in the vector from the user
    printf("Enter the elements of the new created vector:\n");

    for (int iterator = 0; iterator < number_of_elements; iterator++)
        scanf("%d", &starting_pointer[iterator]);
}

void display_vector_dynamically_allocated(int* starting_pointer, int number_of_elements) {
    // display the elements of the vector
    printf("The elements of the vector are: ");
    for (int index = 0; index < number_of_elements; index++)
        printf("%d ", starting_pointer[index]);
    printf("\n\n");
}

void dynamic_vector_deallocation(int* starting_pointer) {
    // deallocates the memory previously allocated, if it was allocated
    if (starting_pointer != NULL)
        free(starting_pointer);
}

void read_vector_from_console_and_display_it() {
    int* vector_starting_pointer = NULL, number_of_elements;
    // allocate the space given by the user, for the vector
    vector_starting_pointer = dynamic_vector_allocation(vector_starting_pointer, &number_of_elements);
    
    // read the elements of the vector
    read_vector_elements(vector_starting_pointer, number_of_elements);

    // display the elements of the vector given by the user
    display_vector_dynamically_allocated(vector_starting_pointer, number_of_elements);

    dynamic_vector_deallocation(vector_starting_pointer);
}

int check_relatively_prime_numbers(int first_number, int second_number) {
    // compute the greatest common divisor of the numbers provided
    while (first_number != second_number) {
        if (first_number > second_number)
            first_number -= second_number;

        else if (first_number < second_number)
            second_number -= first_number;
    }

    // if the greatest common divisor is 1, then the numbers are relatively prime
    if (first_number == 1)
        return 1;

    // else, the numbers are not
    return 0;
}

int get_number_from_user() {
    // get the number you want to find the relatively prime numbers for
    int number;
    printf("Enter the number you want to compile: ");
    scanf("%d", &number);

    return number;
}

void display_numbers_relatively_prime_numbers_smaller_than_given_one(int number) {
    // validate the input
    if (number < 2) {
        printf("The number must be positive and greater than 1!\n\n");
        return;
    }

    // print the numbers found
    printf("The numbers lower than %d that are relatively prime to it are: ", number);
    for (int index = 1; index < number; index++)
        if (check_relatively_prime_numbers(index, number))
            printf("%d ", index);

    printf("\n\n");
}

void run_first_laboratory_statement() {
    int given_number = get_number_from_user();
    display_numbers_relatively_prime_numbers_smaller_than_given_one(given_number);
}

void display_longest_contiguous_subsequence_with_maximum_sum(int *vector_pointer, int vector_length) {
    int maximum_sum_until_now = INT_MIN;
    int maximum_sum_in_this_point = 0;

    // we iterate once through the vector, time complexity is linear
    for (int index = 0; index < vector_length; index++) {
        maximum_sum_in_this_point += vector_pointer[index];

        if (maximum_sum_in_this_point < vector_pointer[index])
            maximum_sum_in_this_point = vector_pointer[index];

        if (maximum_sum_until_now < maximum_sum_in_this_point)
            maximum_sum_until_now = maximum_sum_in_this_point;
    }

    // print the response in a nice format
    printf("The longest contiguous subsequence with the maximum sum has the sum value %d.\n", maximum_sum_until_now);
}

void run_second_laboratory_statement() {
    int* vector_starting_pointer = NULL, number_of_elements;
    
    // allocate the space given by the user, for the vector
    vector_starting_pointer = dynamic_vector_allocation(vector_starting_pointer, &number_of_elements);

    // read the elements of the vector
    read_vector_elements(vector_starting_pointer, number_of_elements);

    display_longest_contiguous_subsequence_with_maximum_sum(vector_starting_pointer, number_of_elements);

    dynamic_vector_deallocation(vector_starting_pointer);
}

void display_prime_numbers_and_their_exponent_from_a_number_decomposition(int number){
    if (number < 2) {
        printf("The number must be positive and greater than 1!\n\n");
        return;
    }

    int divisor = 2;

    printf("The prime divisors of the given number and their exponent are:\n");
    while (number != 1){
        if (number % divisor == 0){
            int exponent = 0;
            while (number % divisor == 0){
                number = number / divisor;
                exponent++;
            }
            printf("divisor = %d; exponent = %d\n", divisor, exponent);
        }
        divisor++;
    }
    printf("\n");
}

void run_third_laboratory_statement(){
    int given_number = get_number_from_user();
    display_prime_numbers_and_their_exponent_from_a_number_decomposition(given_number);
}
