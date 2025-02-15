/*
 * File: mario_advanced.c
 * Author: Ferdi Kanat
 * Date: 2025/02/07
 * Description: Builds a double half-pyramid (Mario-style) of a user-specified height.
 * Usage: Run the program and enter a height between 1 and 8 when prompted.
 * Example: 
 *     Height: 4
 *        #  #
 *       ##  ##
 *      ###  ###
 *     ####  ####
 */

#include <stdio.h>
#include <cs50.h>

// Constants
#define MIN_HEIGHT 1   // Minimum allowed height for the pyramid
#define MAX_HEIGHT 8   // Maximum allowed height for the pyramid
#define GAP_WIDTH 2    // Width of the gap between pyramids

// Function prototypes
static int get_valid_height(void);
static void print_pyramids(int height);
static void print_spaces(int count);
static void print_hashes(int count);

int main(void) 
{   
    printf("Welcome to Mario Pyramid Builder!\n\n");
    int height = get_valid_height();
    print_pyramids(height);
    return 0;
}

/**
 * Gets a valid pyramid height from the user.
 * @return Integer between MIN_HEIGHT and MAX_HEIGHT inclusive
 * @note The function will keep prompting the user until a valid height is entered.
 * @note The function uses get_int() from the CS50 library.
 */
static int get_valid_height(void)
{
    int height;
    do {
        height = get_int("Height (between %d and %d): ", MIN_HEIGHT, MAX_HEIGHT);
        if (height < MIN_HEIGHT || height > MAX_HEIGHT)
        {
            printf("Invalid input. Please enter a value between %d and %d.\n", MIN_HEIGHT, MAX_HEIGHT);
        }
    } while (height < MIN_HEIGHT || height > MAX_HEIGHT);
    return height;
}

/**
 * Prints the complete double pyramid structure
 * @param height The height of the pyramids
 */
static void print_pyramids(int height)
{
    for (int row = 0; row < height; row++)
    {
        int spaces = height - row - 1;
        int hashes = row + 1;
        
        print_spaces(spaces);
        print_hashes(hashes);
        print_spaces(GAP_WIDTH);
        print_hashes(hashes);
        printf("\n");
    }
}

/**
 * Prints the specified number of spaces to the console.
 * @param count The number of spaces to print. Must be a non-negative integer.
 */
static void print_spaces(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf(" ");
    }
}

/**
 * Prints the specified number of hash symbols
 * @param count Number of hash symbols to print (assumed non-negative)
 */
static void print_hashes(int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("#");
    }
}