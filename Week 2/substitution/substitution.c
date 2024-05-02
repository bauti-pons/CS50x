#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_key(string);
string encrypt_message(string, string, char *);

int main(int argc, string argv[])
{
    // Check if exactly one command-line argument is provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate the encryption key provided by the user
    int check = check_key(argv[1]);
    if (check == 1)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (check == 2)
    {
        printf("Key contains an invalid character.\n");
        return 1;
    }
    else if (check == 3)
    {
        printf("Key contains a repeated character.\n");
        return 1;
    }

    string key = argv[1];
    string plaintext = get_string("plaintext:  "); // Get plaintext from the user
    int length = strlen(plaintext);
    char ciphertext[length + 1];                 // Create buffer for ciphertext
    encrypt_message(plaintext, key, ciphertext); // Encrypt the message using the validated key
    printf("ciphertext: %s\n", ciphertext);      // Output the ciphertext
    return 0;
}

// Validates the substitution key for proper length and character uniqueness
int check_key(string k)
{
    int l = strlen(k);
    if (l != 26)
        return 1; // Key length must be exactly 26 characters

    for (int i = 0; i < l; i++)
    {
        if (isalpha(k[i]) == 0) // Check if the character is not alphabetical
            return 2;

        // Check for repeated characters in the key
        int count = 0;
        for (int j = 0; j < l; j++)
        {
            if (tolower(k[i]) == tolower(k[j]) && i != j)
            {
                count++;
            }
        }
        if (count > 0)
            return 3; // Return error if there are repeated characters
    }

    return 0; // Return 0 if the key is valid
}

// Encrypts the plaintext using the provided key
string encrypt_message(string txt, string ky, char *message)
{

    int l = strlen(txt);
    for (int i = 0; i < l; i++)
    {
        char chrt = (char) txt[i];

        // Encrypt uppercase letters
        if (chrt >= 65 && chrt <= 90)
        {
            int index = chrt - 65;
            message[i] = toupper(ky[index]); // Map to the corresponding key character
        }
        // Encrypt lowercase letters
        else if (chrt >= 97 && chrt <= 122)
        {
            int index = chrt - 97;
            message[i] = tolower(ky[index]); // Map to the corresponding key character
        }
        else
        {
            message[i] = txt[i]; // Non-alphabet characters are copied as is
        }
    }
    message[l] = '\0'; // Null-terminate the ciphertext

    return message; // Return the encrypted message
}
