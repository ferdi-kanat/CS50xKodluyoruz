#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "bmp.h"

void free_memory(RGBTRIPLE **image, int height);

int main(int argc, char *argv[])
{
    // Check command line arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile.bmp outfile.bmp\n");
        return 1;
    }

    // Get the resize factor
    float f = atof(argv[1]);
    if (f <= 0.0 || f > 100.0)
    {
        fprintf(stderr, "Resize factor must be between 0.0 and 100.0.\n");
        return 1;
    }

    // Get the names of the input and output files
    char *infile = argv[2];
    char *outfile = argv[3];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Read file header
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read info header
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Check if the file is a BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Update headers for the new BMP file
    BITMAPFILEHEADER new_bf = bf;
    BITMAPINFOHEADER new_bi = bi;

    // Calculate new width and height
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    int newWidth = (int)(oldWidth * f);
    int newHeight = (int)(oldHeight * f);

    // Assign new values
    new_bi.biWidth = newWidth;
    new_bi.biHeight = newHeight;

    // Calculate padding
    int padding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Calculate new size
    new_bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + new_padding) * abs(newHeight);
    new_bf.bfSize = new_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Write new headers to the output file
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // For enlargement: copy each row to an array and write it f times
    if (f >= 1.0) // Enlargement or keeping the same size
    {
        // Process each row
        for (int i = 0; i < abs(oldHeight); i++)
        {
            // Repeat rows f times
            for (int v_repeat = 0; v_repeat < f; v_repeat++)
            {
                // Read each row and enlarge it f times
                for (int j = 0; j < oldWidth; j++)
                {
                    // Read pixel
                    RGBTRIPLE triple;
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                    // Write pixel f times
                    for (int h_repeat = 0; h_repeat < f; h_repeat++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                
                // Skip padding in the input file
                fseek(inptr, padding, SEEK_CUR);
                
                // Add padding to the output file
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }
                
                // Move the cursor back to read the same row again
                if (v_repeat < f - 1)
                {
                    fseek(inptr, -((oldWidth * sizeof(RGBTRIPLE)) + padding), SEEK_CUR);
                }
            }
        }
    }
    else // Reduction (f < 1.0)
    {
        // Read the input image into memory
        RGBTRIPLE **input_image = malloc(abs(oldHeight) * sizeof(RGBTRIPLE *));
        if (input_image == NULL)
        {
            fclose(inptr);
            fclose(outptr);
            fprintf(stderr, "Memory allocation failed.\n");
            return 5;
        }

        for (int i = 0; i < abs(oldHeight); i++)
        {
            input_image[i] = malloc(oldWidth * sizeof(RGBTRIPLE));
            if (input_image[i] == NULL)
            {
                free_memory(input_image, i);
                fclose(inptr);
                fclose(outptr);
                fprintf(stderr, "Memory allocation failed.\n");
                return 5;
            }
            
            // Read row
            for (int j = 0; j < oldWidth; j++)
            {
                fread(&input_image[i][j], sizeof(RGBTRIPLE), 1, inptr);
            }
            
            // Skip padding
            fseek(inptr, padding, SEEK_CUR);
        }
        
        // Create the reduced image
        for (int y = 0; y < abs(newHeight); y++)
        {
            for (int x = 0; x < newWidth; x++)
            {
                // Calculate the source coordinates for this pixel
                int src_x = (int)(x / f);
                int src_y = (int)(y / f);
                
                // Determine the boundaries of the source frame
                int x_start = (int)(x / f);
                int y_start = (int)(y / f);
                int x_end = (int)((x + 1) / f);
                int y_end = (int)((y + 1) / f);
                
                // Adjust boundaries
                if (x_end >= oldWidth) x_end = oldWidth - 1;
                if (y_end >= abs(oldHeight)) y_end = abs(oldHeight) - 1;
                
                // Calculate the average color
                int red_sum = 0, green_sum = 0, blue_sum = 0;
                int count = 0;
                
                for (int i = y_start; i <= y_end; i++)
                {
                    for (int j = x_start; j <= x_end; j++)
                    {
                        red_sum += input_image[i][j].rgbtRed;
                        green_sum += input_image[i][j].rgbtGreen;
                        blue_sum += input_image[i][j].rgbtBlue;
                        count++;
                    }
                }
                
                // Write the new pixel
                RGBTRIPLE out_pixel;
                out_pixel.rgbtRed = (BYTE)(red_sum / count);
                out_pixel.rgbtGreen = (BYTE)(green_sum / count);
                out_pixel.rgbtBlue = (BYTE)(blue_sum / count);
                
                fwrite(&out_pixel, sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // Add padding to the output file
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        
        // Free memory
        free_memory(input_image, abs(oldHeight));
    }

    // Close files
    fclose(inptr);
    fclose(outptr);
    
    return 0;
}

void free_memory(RGBTRIPLE **image, int height)
{
    for (int i = 0; i < height; i++)
    {
        free(image[i]);
    }
    free(image);
}