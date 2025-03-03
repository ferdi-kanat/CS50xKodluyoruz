/**
 * @file binary_search.c
 * @author Ferdi Kanat
 * @date 2025/02/11
 * 
 * @brief Searches for a value in a sorted array using the binary search algorithm.
 * 
 * This program demonstrates the binary search algorithm to find a value in a
 * sorted array of integers. It validates the array size before proceeding with
 * the search.
 * 
 * The binary search algorithm works by repeatedly dividing the search interval
 * in half. If the value of the search key is less than the item in the middle
 * of the interval, the search continues in the lower half. If the value of the
 * search key is greater, it continues in the upper half. This process continues
 * until the value is found or the interval is empty.
 * 
 * The binary search algorithm has a time complexity of O(log n).
 * 
 * @example
 * $ ./binary_search
 * Original array:
 * 1 2 3 4 5 6
 * 
 * Enter the value to search: 4
 * Value found at index 3.
 */

#include <stdio.h>

#define MAX_ARRAY_SIZE 100
#define MIN_ARRAY_SIZE 1

/* Function prototypes */
int binary_search(const int array[], int size, int value);
void print_array(const int array[], int size);

int main(void)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(array) / sizeof(array[0]);
    int value, index;

    // Validate array size
    if (size < MIN_ARRAY_SIZE || size > MAX_ARRAY_SIZE)
    {
        fprintf(stderr, "Error: Array size must be between %d and %d.\n", MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
        return 1;
    }

    // Print the original array
    printf("Original array:\n");
    print_array(array, size);

    // Get the value to search
    printf("\nEnter the value to search: ");
    scanf("%d", &value);

    // Search for the value in the array
    index = binary_search(array, size, value);

    if (index != -1)
    {
        printf("Value found at index %d.\n", index);
    }
    else
    {
        printf("Value not found.\n");
    }

    return 0;
}


/**
 * @brief Searches for a value in a sorted array using the binary search algorithm.
 * @param array The sorted array to search.
 * @param size The size of the array.
 * @param value The value to search for.
 * @return The index of the value if found, -1 otherwise.
 */
int binary_search(const int array[], int size, int value)
{
    int left = 0;
    int right = size - 1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (array[mid] == value)
        {
            return mid;
        }
        else if (array[mid] < value)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

/**
 * @brief Prints the elements of an array.
 * @param array The array to print.
 * @param size The size of the array.
 */
void print_array(const int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}