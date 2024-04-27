#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    int spaces = height - 1;
    for (int i = 1; i <= height; i++)
    {
        while (spaces > 0)
        {
            printf(" ");
            spaces--;
        }

        for (int j = i; j > 0; j--)
        {
            printf("#");
        }

        printf("  ");

        for (int j = i; j > 0; j--)
        {
            printf("#");
        }

        printf("\n");

        spaces = height - i - 1;
    }
}
