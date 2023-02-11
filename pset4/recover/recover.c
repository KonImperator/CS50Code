#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    // Only 1 input element allowed
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open file for reading
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    // If impossible to open, stop running
    {
        printf("File cannot be opened for reading.");
        return 1;
    }
    // Declaring variables
    int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    int counter = 0;

    // Initializing empty file to write to
    FILE *image;

    // Freeing up space for the name of the files we'll be writing to
    char *file_name = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(char), BLOCK_SIZE, card) == BLOCK_SIZE)
    // Read 512 bytes into a buffer
    // Repeat until the end of the file
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        // If start of new JPEG
        {
            if (counter > 0)
            // If it's not the first JPEG, close the previous file
            {
                fclose(image);
            }
            // Initialize the new file and start writing to it
            sprintf(file_name, "%03i.jpg", counter);
            image = fopen(file_name, "w");
            fwrite(&buffer, 1, BLOCK_SIZE, image);
            counter++;
        }
        else if (counter > 0)
        // Else if it's a continuation from previous JPEG
        {
            fwrite(&buffer, 1, BLOCK_SIZE, image);
        }
        else
        // Else if it's not a JPEG, continue
        {
            continue;
        }
    }
    fclose(card);
    fclose(image);
    free(file_name);
    return 0;
    // Close any remaining files
}