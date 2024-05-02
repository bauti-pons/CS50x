#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string);
int count_words(string);
int count_sentcs(string);
float get_Coleman_Liau_index(int, int, int);
void print_grade_level(float);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentcs = count_sentcs(text);

    // Compute the Coleman-Liau index
    float index = get_Coleman_Liau_index(letters, words, sentcs);

    // Print the grade level
    print_grade_level(index);
}

int count_letters(string t)
{
    int count = 0;
    for (int i = 0, l = strlen(t); i < l; i++)
    {
        if (isalpha(t[i]) != 0)
        {
            count++;
        }
    }

    return count;
}

int count_words(string t)
{
    int count = 1;
    for (int i = 0, l = strlen(t); i < l; i++)
    {
        if (isspace(t[i]) != 0)
        {
            count++;
        }
    }

    return count;
}

int count_sentcs(string t)
{
    int count = 0;
    for (int i = 0, l = strlen(t); i < l; i++)
    {
        if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            count++;
        }
    }

    return count;
}

float get_Coleman_Liau_index(l, w, s)
{
    float L = (float) l / (float) w * 100;
    float S = (float) s / (float) w * 100;
    float ind = round(0.0588 * L - 0.296 * S - 15.8);

    return ind;
}

void print_grade_level(float i)
{
    if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (i >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) i);
    }
}
