#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512
#define FILENAME_SIZE 8

int main(int argc, char *argv[])
{
    // Check command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s image\n", argv[0]);
        return 1;
    }

    // Get the input file name
    char *infile = argv[1];

    // Open the input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Allocate memory for buffer
    BYTE buffer[BLOCK_SIZE];

    // JPEG file counter
    int file_count = 0;

    // Output file pointer
    FILE *outptr = NULL;

    // Allocate memory for JPEG file name
    char filename[FILENAME_SIZE];

    // Read blocks
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Check for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a new JPEG file is found, close the previous file
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Create a new file name for the new JPEG file
            sprintf(filename, "%03i.jpg", file_count);
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                fclose(inptr);
                return 3;
            }
            file_count++;
        }

        // Write to the JPEG file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }

    // Close the last file
    if (outptr != NULL)
    {
        fclose(outptr);
    }

    // Close the input file
    fclose(inptr);

    return 0;
}