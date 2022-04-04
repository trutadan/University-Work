#include <stdio.h>

void read_numbers(int, int*);
int get_maximum_number(int, int*);

int main()
{
    int counter;
    printf("Enter how many numbers you want to read: ");
    scanf("%d", &counter);
     
    int string_address[100];
    read_numbers(counter, string_address);

    int maximum; 
    maximum = get_maximum_number(counter, string_address); 
    
    char file_name[] = "max.txt";
    FILE *file_descriptor;
    file_descriptor = fopen(file_name, "w");

    int result; 
    result = fprintf(file_descriptor, "%x", maximum);
    if(result == 0)
        printf("error...");
    
    return 0;
}
