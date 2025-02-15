//Description: Builds a half-pyramid (Mario-style) of a user-specified height.
// Usage: Run the program and enter a height between 1 and 8 when prompted.
// Prompts user for pyramid height (between MIN_HEIGHT and MAX_HEIGHT) 
// and prints a right-aligned pyramid. CS50 library is used for input.
#include <stdio.h>
#include <cs50.h>

// Constants
#define MIN_HEIGHT 1   // Minimum allowed height for the pyramid
#define MAX_HEIGHT 8   // Maximum allowed height for the pyramid

// Function prototype
void print_pyramid(const int height);

/**
 * Program to print a pyramid pattern
 * Prompts user for height between 1-8 and validates input
 * @return 0 on success, 1 on error
 */
int main(void)
{
    // Get height between MIN_HEIGHT and MAX_HEIGHT
    int height;
    do
    {
        height = get_int("Height (1-8): ");
        if (height < MIN_HEIGHT || height > MAX_HEIGHT)
        {
            printf("Error: Invalid height. Enter a value between %d and %d.\n", MIN_HEIGHT, MAX_HEIGHT);
        }
    }
    while (height < MIN_HEIGHT || height > MAX_HEIGHT);

    // Print the pyramid
    print_pyramid(height);

    return 0;
}

/**
 * Prints a right-aligned pyramid of specified height
 * @param height The height of the pyramid (1-8)
 */
void print_pyramid(const int height)
{
    for (int i = 0; i < height; i++)
    {
        // Print spaces
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        // Print hashes
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        // Move to the next line
        printf("\n");
    }
}