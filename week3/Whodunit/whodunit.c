/** 
 * Whodunit Game
 * 
 * This is a simple game where players have to solve the mystery of who done it.
 * 
 * Functionality:
 * - Filter out red "noise" in a BMP image.
 * - Reveal a hidden clue to identify the murderer.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile.bmp outfile.bmp\n");
        return 1;
    }

    // Use const qualifiers for file names
    const char *infile = argv[1];
    const char *outfile = argv[2];

    // Open input file in binary mode
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open '%s'.\n", infile);
        return 2;
    }

    // Open output file in binary mode
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create '%s'.\n", outfile);
        return 3;
    }

    // Read headers from input file
    BITMAPFILEHEADER bf;
    if (fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr) != 1)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Error reading file header.\n");
        return 4;
    }
    BITMAPINFOHEADER bi;
    if (fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr) != 1)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Error reading info header.\n");
        return 5;
    }

    // Validate BMP format
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 6;
    }

    // Write headers to output file
    if (fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr) != 1 ||
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr) != 1)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Error writing headers to output file.\n");
        return 7;
    }

    // Calculate padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Process each scanline
    for (int row = 0, absHeight = abs(bi.biHeight); row < absHeight; row++)
    {
        // Process each pixel in the row
        for (int col = 0; col < bi.biWidth; col++)
        {
            RGBTRIPLE triple;
            if (fread(&triple, sizeof(RGBTRIPLE), 1, inptr) != 1)
            {
                fclose(inptr);
                fclose(outptr);
                fprintf(stderr, "Error reading pixel data.\n");
                return 8;
            }

            // Modify pixel based on color criteria
            if (triple.rgbtRed > 0xf0 && triple.rgbtGreen < 0x80 && triple.rgbtBlue < 0x80)
            {
                triple.rgbtRed = 0xff;
                triple.rgbtGreen = 0xff;
                triple.rgbtBlue = 0xff;
            }
            else
            {
                if (triple.rgbtRed < 0x80)
                    triple.rgbtRed = 0x00;
                if (triple.rgbtGreen < 0x80)
                    triple.rgbtGreen = 0x00;
                if (triple.rgbtBlue < 0x80)
                    triple.rgbtBlue = 0x00;
            }

            if (fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr) != 1)
            {
                fclose(inptr);
                fclose(outptr);
                fprintf(stderr, "Error writing pixel data.\n");
                return 9;
            }
        }

        // Skip over input file padding
        if (fseek(inptr, padding, SEEK_CUR) != 0)
        {
            fclose(inptr);
            fclose(outptr);
            fprintf(stderr, "Error skipping input padding.\n");
            return 10;
        }

        // Add output padding
        for (int k = 0; k < padding; k++)
        {
            if (fputc(0x00, outptr) == EOF)
            {
                fclose(inptr);
                fclose(outptr);
                fprintf(stderr, "Error writing output padding.\n");
                return 11;
            }
        }
    }

    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}