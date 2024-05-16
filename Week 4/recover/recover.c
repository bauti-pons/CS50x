#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open memory card.\n");
        return 1;
    }

    BYTE buffer[512];  // Create a buffer for a block of data
    char filename[10]; // Allocate enough space for the filename and null terminator
    FILE *img = NULL;  // Initialize the image file pointer to NULL
    int count = 0;     // Initialize count to 0

    // Read through the card file
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous image file if it exists
            if (img != NULL)
                fclose(img);

            // Create a new filename
            sprintf(filename, "%03i.jpg", count);
            count++;

            // Open a new image file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(card);
                return 1;
            }
        }

        // If an image file is open, write to it
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
        fclose(img);

    fclose(card);

    return 0;
}
