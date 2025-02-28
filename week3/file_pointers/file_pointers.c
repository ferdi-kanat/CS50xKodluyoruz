/**
 * @file file_pointers.c
 * @author Ferdi Kanat
 * @date 2025/02/11
 * @brief This program demonstrates the use of file pointers in C.
 * functions used: fopen, fclose, fgetc, fputc, feof, fprintf, fscanf, fseek, ftell, rewind
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *file = fopen("test.txt", "w+");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file 'test.txt'\n");
        return EXIT_FAILURE;
    }

    // write to file
    fprintf(file, "Hello World\n");
    fprintf(file, "CS50x Kodluyoruz\n");

    // rewind file pointer to beginning
    rewind(file);

    // read file content character by character
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        putchar(c);
    }

    // move file pointer to end and add a character
    fseek(file, 0, SEEK_END);
    if (fputc('*', file) == EOF)
    {
        fprintf(stderr, "Error writing to file 'test.txt'\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    int position = ftell(file);
    if (position == -1)
    {
        fprintf(stderr, "Error getting file position\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    printf("\nPosition: %d\n", position);

    // create a new file, write and read an integer
    FILE *numFile = fopen("numbers.txt", "w+");
    if (numFile == NULL)
    {
        fprintf(stderr, "Error opening file 'numbers.txt'\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    int num = 42;
    fprintf(numFile, "%d", num);
    rewind(numFile);

    int readNum;
    if (fscanf(numFile, "%d", &readNum) != 1)
    {
        fprintf(stderr, "Error reading number from 'numbers.txt'\n");
        fclose(file);
        fclose(numFile);
        return EXIT_FAILURE;
    }
    printf("Number: %d\n", readNum);

    // close files
    fclose(file);
    fclose(numFile);
    
    return EXIT_SUCCESS;
}