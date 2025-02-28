#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure correct usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile.bmp outfile.bmp\n");
        return 1;
    }

    // Parse and validate resize factor
    int n = atoi(argv[1]);
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "Resize factor must be between 1 and 100.\n");
        return 1;
    }

    // File names (input and output)
    char *infile = argv[2];
    char *outfile = argv[3];

    // Open input file in binary mode
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s for reading.\n", infile);
        return 2;
    }

    // Open output file in binary mode
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s for writing.\n", outfile);
        return 3;
    }

    // Read input file headers
    BITMAPFILEHEADER bf;
    if (fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr) != 1)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Error reading BITMAPFILEHEADER.\n");
        return 4;
    }

    BITMAPINFOHEADER bi;
    if (fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr) != 1)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Error reading BITMAPINFOHEADER.\n");
        return 5;
    }

    // Validate BMP format
    if (bf.bfType != 0x4D42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 6;
    }

    // Prepare new headers for resized BMP
    BITMAPFILEHEADER new_bf = bf;
    BITMAPINFOHEADER new_bi = bi;

    new_bi.biWidth *= n;
    new_bi.biHeight *= n;

    // Calculate paddings
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Update image size and file size in headers
    new_bi.biSizeImage = ((sizeof(RGBTRIPLE) * new_bi.biWidth) + new_padding) * abs(new_bi.biHeight);
    new_bf.bfSize = new_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Write new headers to output file
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Process each scanline of the input file
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over each pixel in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Temporary variable to store pixel
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Write pixel n times for horizontal scaling
            for (int k = 0; k < n; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // Skip over input scanline padding
        fseek(inptr, padding, SEEK_CUR);

        // Write padding for resized image
        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
        }

        // Repeat scanline n-1 times for vertical scaling
        for (int l = 1; l < n; l++)
        {
            // Move file pointer back to the beginning of scanline
            fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);

            // Process each pixel again for vertical scaling
            for (int j = 0; j < bi.biWidth; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Advance past input scanline padding
            fseek(inptr, padding, SEEK_CUR);
            // Write new scanline padding
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // Close files
    fclose(inptr);
    fclose(outptr);

    return 0;
}