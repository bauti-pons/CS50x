#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Prompt the user for two words
    string word_1 = get_string("Player 1: ");
    string word_2 = get_string("Player 2: ");

    // Compute the score of each word
    char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int points[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int total_1 = 0;
    int total_2 = 0;

    for (int i = 0, w = strlen(word_1); i < w; i++)
    {
        for (int j = 0, l = strlen(letters); j < l; j++)
        {
            int let = toupper(word_1[i]);
            if (let == (int) letters[j] && let >= 65 && let <= 90)
            {
                total_1 += points[j];
            }
        }
    }

    for (int i = 0, w = strlen(word_2); i < w; i++)
    {
        for (int j = 0, l = strlen(letters); j < l; j++)
        {
            int let = toupper(word_2[i]);
            if (let == (int) letters[j] && let >= 65 && let <= 90)
            {
                total_2 += points[j];
            }
        }
    }

    // Print the winner
    if (total_1 > total_2)
    {
        printf("Player 1 wins!\n");
    }
    else if (total_1 < total_2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
