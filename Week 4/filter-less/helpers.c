#include "helpers.h"
#include <math.h>

int check_value(int);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int average =
                roundf((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            int sepiaRed =
                check_value(roundf(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                   .189 * image[i][j].rgbtBlue));
            int sepiaGreen =
                check_value(roundf(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue));
            int sepiaBlue =
                check_value(roundf(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                   .131 * image[i][j].rgbtBlue));

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels

            // Create a buffer for a single pixel
            RGBTRIPLE buffer = image[i][j];

            // Update pixel values
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Create buffers for average RGB pixel values
    int avrgRed;
    int avrgGreen;
    int avrgBlue;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner case
            if (j == 0 && i == 0)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                 4.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                                   4.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                  4.0);
            }
            // Top rigth corner case
            else if (j == width - 1 && i == 0)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                 4.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                                   4.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                                  4.0);
            }
            // Bottom left corner case
            else if (j == 0 && i == height - 1)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                  copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                 4.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                    copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                                   4.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                   copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                                  4.0);
            }
            // Bottom rigth corner case
            else if (j == width - 1 && i == height - 1)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                  copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) /
                                 4.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                    copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                                   4.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                   copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) /
                                  4.0);
            }

            // Left side cases
            else if (j == 0)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed +
                                  copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                 6.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                    copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                                   6.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                   copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                  6.0);
            }
            // Rigth side cases
            else if (j == width - 1)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed +
                                  copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                 6.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                    copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                                   6.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                   copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                                  6.0);
            }
            // Top side cases
            else if (i == 0)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                  copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                  copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) /
                                 6.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                    copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                    copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                                   6.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                   copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                   copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                                  6.0);
            }
            // Bottom side cases
            else if (i == height - 1)
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                  copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                  copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) /
                                 6.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                    copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                    copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                                   6.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                   copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                   copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                                  6.0);
            }
            // Normal cases
            else
            {
                avrgRed = roundf((copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                  copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                  copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                  copy[i][j + 1].rgbtRed) /
                                 9.0);
                avrgGreen = roundf((copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                                    copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                    copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                                    copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                                    copy[i][j + 1].rgbtGreen) /
                                   9.0);
                avrgBlue = roundf((copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                   copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                                   copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                                   copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                   copy[i][j + 1].rgbtBlue) /
                                  9.0);
            }

            // Update pixel values
            image[i][j].rgbtRed = avrgRed;
            image[i][j].rgbtGreen = avrgGreen;
            image[i][j].rgbtBlue = avrgBlue;
        }
    }
    return;
}

// Compare the value with 255 and return the smallest
int check_value(int value)
{
    if (value > 255)
    {
        return 255;
    }
    else
    {
        return value;
    }
}
