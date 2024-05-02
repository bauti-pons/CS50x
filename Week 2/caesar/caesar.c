#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string only_digits(string);
char rotate(char, int);

int main(int argc, string argv[])
{
    // Check if exactly one command-line argument is provided
    if (argc != 2)
    {
        printf("Please, enter one command-line argument\n");
        return 1;
    }

    // Validate that the provided argument is entirely numeric
    if (strcmp(only_digits(argv[1]), "false") == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert the string argument to an integer to use as the cipher key
    int key = atoi(argv[1]);

    // Prompt the user for the plaintext input
    string plaintext = get_string("plaintext:  ");
    int l = strlen(plaintext); // Get the length of the plaintext
    char ciphertext[l + 1];    // Create a character array to store the ciphertext

    // Encrypt each character of the plaintext
    for (int i = 0; i < l; i++)
    {
        char ascii = (char) plaintext[i];
        ciphertext[i] = rotate(ascii, key); // Rotate the character by the given key
    }
    ciphertext[l] = '\0'; // Null-terminate the ciphertext string

    // Output the ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

// Function to check if a string consists only of digits
string only_digits(string s)
{
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        // Check if each character is not a digit
        if (!isdigit(s[i]))
        {
            return "false"; // Return "false" if any non-digit is found
        }
    }
    return "true"; // Return "true" if all characters are digits
}

// Function to rotate a character by 'n' positions in the alphabet
char rotate(char ch, int n)
{
    // Rotate uppercase letters
    if (ch >= 65 && ch <= 90)
    {
        for (int i = 0; i < n; i++)
        {
            if (ch != 90)
            {
                ch += 1;
            }
            else
            {
                ch = 65;
            }
        }
        return ch;
    }
    // Rotate lowercase letters
    else if (ch >= 97 && ch <= 122)
    {
        for (int i = 0; i < n; i++)
        {
            if (ch != 122)
            {
                ch += 1;
            }
            else
            {
                ch = 97;
            }
        }
        return ch;
    }
    // Return the character unchanged if it's not alphabetic
    else
    {
        return ch;
    }
}
