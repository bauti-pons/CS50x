#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Prompt the user for a credit card number.
    string number;
    do
    {
        number = get_string("Number: ");
    }
    while (10 > strlen(number) || strlen(number) > 16); // Only accepts input of 10 to 16 characters.

    int sum = 0;

    if (strlen(number) % 2 == 0) // Check if the number of digits in the card number is even.
    {
        for (int i = 0; i < strlen(number); i += 2)
        {
            char n_char = number[i];  // Convert digit to char.
            int n_int = n_char - '0'; // Convert char to int.
            n_int *= 2;

            if (n_int > 9)
            {
                int n_1 = 1;
                int n_2 = n_int - 10;
                sum = sum + n_1 + n_2;
            }
            else
            {
                sum += n_int;
            }
        }
    }
    else
    {
        for (int i = 1; i < strlen(number); i += 2)
        {
            char n_char = number[i];  // Convert digit to char.
            int n_int = n_char - '0'; // Convert char to int.
            n_int *= 2;
            if (n_int > 9)
            {
                int n_1 = 1;
                int n_2 = n_int - 10;
                sum = sum + n_1 + n_2;
            }
            else
            {
                sum += n_int;
            }
        }
    }

    int total_sum = sum;

    if (strlen(number) % 2 == 0) // Check if the number of digits in the card number is even.
    {
        for (int i = 1; i < strlen(number); i += 2)
        {
            char n_char = number[i];  // Convert digit to char.
            int n_int = n_char - '0'; // Convert char to int.
            total_sum += n_int;
        }
    }
    else
    {
        for (int i = 0; i < strlen(number); i += 2)
        {
            char n_char = number[i];  // Convert digit to char.
            int n_int = n_char - '0'; // Convert char to int.
            total_sum += n_int;
        }
    }

    if (total_sum % 10 == 0)
    {
        char c_first = number[0];      // Convert digit to char.
        int i_first = c_first - '0';   // Convert char to int.
        char c_second = number[1];     // Convert digit to char.
        int i_second = c_second - '0'; // Convert char to int.

        if (i_first == 4 && (strlen(number) == 13 || strlen(number) == 16))
        {
            printf("VISA\n");
        }
        else if (i_first == 3 && (i_second == 4 || i_second == 7) && strlen(number) == 15)
        {
            printf("AMEX\n");
        }
        else if (i_first == 5 && (i_second > 0 && i_second < 6) && strlen(number) == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
