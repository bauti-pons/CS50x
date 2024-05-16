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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Create Gx and Gy kernel arrays
    int Gx_kernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1},
    };
    int Gy_kernel[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1},
    };

    // Create buffers for Gx and Gy RGB pixel values
    int red_Gx;
    int green_Gx;
    int blue_Gx;
    int red_Gy;
    int green_Gy;
    int blue_Gy;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner case
            if (j == 0 && i == 0)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                Gx_kernel[1][0] * 0 + Gx_kernel[2][0] * 0 +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gx_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                  Gx_kernel[1][0] * 0 + Gx_kernel[2][0] * 0 +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gx_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                 Gx_kernel[1][0] * 0 + Gx_kernel[2][0] * 0 +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gx_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                Gy_kernel[1][0] * 0 + Gy_kernel[2][0] * 0 +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gy_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                  Gy_kernel[1][0] * 0 + Gy_kernel[2][0] * 0 +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gy_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                 Gy_kernel[1][0] * 0 + Gy_kernel[2][0] * 0 +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gy_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);
            }
            // Top rigth corner case
            else if (j == width - 1 && i == 0)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                Gx_kernel[1][2] * 0 + Gx_kernel[2][2] * 0 +
                                Gx_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtRed +
                                Gx_kernel[2][1] * copy[i + 1][j].rgbtRed);
                green_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                  Gx_kernel[1][2] * 0 + Gx_kernel[2][2] * 0 +
                                  Gx_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen +
                                  Gx_kernel[2][1] * copy[i + 1][j].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                 Gx_kernel[1][2] * 0 + Gx_kernel[2][2] * 0 +
                                 Gx_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue +
                                 Gx_kernel[2][1] * copy[i + 1][j].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                Gy_kernel[1][2] * 0 + Gy_kernel[2][2] * 0 +
                                Gy_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtRed +
                                Gy_kernel[2][1] * copy[i + 1][j].rgbtRed);
                green_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                  Gy_kernel[1][2] * 0 + Gy_kernel[2][2] * 0 +
                                  Gy_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen +
                                  Gy_kernel[2][1] * copy[i + 1][j].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                 Gy_kernel[1][2] * 0 + Gy_kernel[2][2] * 0 +
                                 Gy_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue +
                                 Gy_kernel[2][1] * copy[i + 1][j].rgbtBlue);
            }
            // Bottom left corner case
            else if (j == 0 && i == height - 1)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                Gx_kernel[0][0] * 0 + Gx_kernel[1][0] * 0 +
                                Gx_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[1][2] * copy[i][j + 1].rgbtRed);
                green_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                  Gx_kernel[0][0] * 0 + Gx_kernel[1][0] * 0 +
                                  Gx_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[1][2] * copy[i][j + 1].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                 Gx_kernel[0][0] * 0 + Gx_kernel[1][0] * 0 +
                                 Gx_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[1][2] * copy[i][j + 1].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                Gy_kernel[0][0] * 0 + Gy_kernel[1][0] * 0 +
                                Gy_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[1][2] * copy[i][j + 1].rgbtRed);
                green_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                  Gy_kernel[0][0] * 0 + Gy_kernel[1][0] * 0 +
                                  Gy_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[1][2] * copy[i][j + 1].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                 Gy_kernel[0][0] * 0 + Gy_kernel[1][0] * 0 +
                                 Gy_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[1][2] * copy[i][j + 1].rgbtBlue);
            }
            // Bottom rigth corner case
            else if (j == width - 1 && i == height - 1)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                Gx_kernel[0][2] * 0 + Gx_kernel[1][2] * 0 +
                                Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gx_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gx_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed);
                green_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                  Gx_kernel[0][2] * 0 + Gx_kernel[1][2] * 0 +
                                  Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gx_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gx_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                 Gx_kernel[0][2] * 0 + Gx_kernel[1][2] * 0 +
                                 Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gx_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gx_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                Gy_kernel[0][2] * 0 + Gy_kernel[1][2] * 0 +
                                Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gy_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gy_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed);
                green_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                  Gy_kernel[0][2] * 0 + Gy_kernel[1][2] * 0 +
                                  Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gy_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gy_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                 Gy_kernel[0][2] * 0 + Gy_kernel[1][2] * 0 +
                                 Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gy_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gy_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue);
            }
            // Left side cases
            else if (j == 0)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[1][0] * 0 + Gx_kernel[2][0] * 0 +
                                Gx_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gx_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[1][0] * 0 + Gx_kernel[2][0] * 0 +
                                  Gx_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gx_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[1][0] * 0 + Gx_kernel[2][0] * 0 +
                                 Gx_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gx_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[1][0] * 0 + Gy_kernel[2][0] * 0 +
                                Gy_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gy_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[1][0] * 0 + Gy_kernel[2][0] * 0 +
                                  Gy_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gy_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[1][0] * 0 + Gy_kernel[2][0] * 0 +
                                 Gy_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gy_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);
            }
            // Rigth side cases
            else if (j == width - 1)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[0][2] * 0 + Gx_kernel[1][2] * 0 + Gx_kernel[2][2] * 0 +
                                Gx_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gx_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtRed);
                green_Gx = roundf(Gx_kernel[0][2] * 0 + Gx_kernel[1][2] * 0 + Gx_kernel[2][2] * 0 +
                                  Gx_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gx_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[0][2] * 0 + Gx_kernel[1][2] * 0 + Gx_kernel[2][2] * 0 +
                                 Gx_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gx_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[0][2] * 0 + Gy_kernel[1][2] * 0 + Gy_kernel[2][2] * 0 +
                                Gy_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gy_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtRed);
                green_Gy = roundf(Gy_kernel[0][2] * 0 + Gy_kernel[1][2] * 0 + Gy_kernel[2][2] * 0 +
                                  Gy_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gy_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[0][2] * 0 + Gy_kernel[1][2] * 0 + Gy_kernel[2][2] * 0 +
                                 Gy_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gy_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue);
            }
            // Top side cases
            else if (i == 0)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                Gx_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtRed +
                                Gx_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                  Gx_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen +
                                  Gx_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[0][0] * 0 + Gx_kernel[0][1] * 0 + Gx_kernel[0][2] * 0 +
                                 Gx_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue +
                                 Gx_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                Gy_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtRed +
                                Gy_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                  Gy_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen +
                                  Gy_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[0][0] * 0 + Gy_kernel[0][1] * 0 + Gy_kernel[0][2] * 0 +
                                 Gy_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue +
                                 Gy_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);
            }
            // Bottom side cases
            else if (i == height - 1)
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gx_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gx_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[1][2] * copy[i][j + 1].rgbtRed);
                green_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                  Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gx_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gx_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[1][2] * copy[i][j + 1].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[2][0] * 0 + Gx_kernel[2][1] * 0 + Gx_kernel[2][2] * 0 +
                                 Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gx_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gx_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[1][2] * copy[i][j + 1].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gy_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gy_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[1][2] * copy[i][j + 1].rgbtRed);
                green_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                  Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gy_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gy_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[1][2] * copy[i][j + 1].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[2][0] * 0 + Gy_kernel[2][1] * 0 + Gy_kernel[2][2] * 0 +
                                 Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gy_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gy_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[1][2] * copy[i][j + 1].rgbtBlue);
            }
            // Normal cases
            else
            {
                // Compute Gx
                red_Gx = roundf(Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gx_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gx_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gx_kernel[1][1] * copy[i][j].rgbtRed +
                                Gx_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtRed +
                                Gx_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gx = roundf(Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gx_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gx_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gx_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gx_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen +
                                  Gx_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gx = roundf(Gx_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gx_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gx_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gx_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gx_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gx_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gx_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue +
                                 Gx_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gx_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);

                // Compute Gy
                red_Gy = roundf(Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtRed +
                                Gy_kernel[0][1] * copy[i - 1][j].rgbtRed +
                                Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtRed +
                                Gy_kernel[1][0] * copy[i][j - 1].rgbtRed +
                                Gy_kernel[1][1] * copy[i][j].rgbtRed +
                                Gy_kernel[1][2] * copy[i][j + 1].rgbtRed +
                                Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtRed +
                                Gy_kernel[2][1] * copy[i + 1][j].rgbtRed +
                                Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtRed);
                green_Gy = roundf(Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtGreen +
                                  Gy_kernel[0][1] * copy[i - 1][j].rgbtGreen +
                                  Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtGreen +
                                  Gy_kernel[1][0] * copy[i][j - 1].rgbtGreen +
                                  Gy_kernel[1][1] * copy[i][j].rgbtGreen +
                                  Gy_kernel[1][2] * copy[i][j + 1].rgbtGreen +
                                  Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtGreen +
                                  Gy_kernel[2][1] * copy[i + 1][j].rgbtGreen +
                                  Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtGreen);
                blue_Gy = roundf(Gy_kernel[0][0] * copy[i - 1][j - 1].rgbtBlue +
                                 Gy_kernel[0][1] * copy[i - 1][j].rgbtBlue +
                                 Gy_kernel[0][2] * copy[i - 1][j + 1].rgbtBlue +
                                 Gy_kernel[1][0] * copy[i][j - 1].rgbtBlue +
                                 Gy_kernel[1][1] * copy[i][j].rgbtBlue +
                                 Gy_kernel[1][2] * copy[i][j + 1].rgbtBlue +
                                 Gy_kernel[2][0] * copy[i + 1][j - 1].rgbtBlue +
                                 Gy_kernel[2][1] * copy[i + 1][j].rgbtBlue +
                                 Gy_kernel[2][2] * copy[i + 1][j + 1].rgbtBlue);
            }

            // Update pixel values
            image[i][j].rgbtRed = check_value(roundf(sqrt(pow(red_Gx, 2) + pow(red_Gy, 2))));
            image[i][j].rgbtGreen = check_value(roundf(sqrt(pow(green_Gx, 2) + pow(green_Gy, 2))));
            image[i][j].rgbtBlue = check_value(roundf(sqrt(pow(blue_Gx, 2) + pow(blue_Gy, 2))));
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
