/**
 * @file linear_search.c
 * @author Ferdi Kanat
 * @date 2025/02/10
 * @brief Implementation of linear search algorithm
 *
 * This program implements a linear search algorithm to find a target number
 * in an array of integers. The search runs in O(n) time complexity.
 *
 * @note Assumes input array is valid and properly initialized
 *
 * @example
 * Input array: [1, 2, 3, 4, 5]
 * Search for: 5
 * Output: Found
 */

#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>

#define MAX_ARRAY_SIZE 100
#define MIN_ARRAY_SIZE 1

/* Function prototypes */
bool linear_search(const int array[], int size, int target);
bool validate_array_size(int size);

int main(void)
{
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);

    // Validate array size
    if (!validate_array_size(size))
    {
        printf("Error: Invalid array size\n");
        return 1;
    }

    // Get search target from user
    int target = get_int("Enter number to search: ");

    // Perform search and output result
    if (linear_search(array, size, target))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not found\n");
    }

    return 0;
}

/**
 * @brief Performs linear search on an array
 * @param array The array to search in
 * @param size Size of the array
 * @param target The value to search for
 * @return true if target is found, false otherwise
 */
bool linear_search(const int array[], int size, int target)
{
    if (array == NULL || size <= 0)
    {
        return false;
    }

    for (int i = 0; i < size; i++)
    {
        if (array[i] == target)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Validates if the array size is within acceptable bounds
 * @param size Size to validate
 * @return true if size is valid, false otherwise
 */
bool validate_array_size(int size)
{
    return (size >= MIN_ARRAY_SIZE && size <= MAX_ARRAY_SIZE);
}
