/**
 * @file selection_sort.c
 * @author Ferdi Kanat
 * @date 2025/02/10
 * @brief Sorts an array of integers using the selection sort algorithm
 * 
 * This program sorts an array of integers using the selection sort algorithm.
 * 
 * @example
 * Input: 5 2 4 6 1 3
 * Output: 1 2 3 4 5 6
 */

#include <stdio.h>

#define MAX_ARRAY_SIZE 100
#define MIN_ARRAY_SIZE 1

/* Function prototypes */
void selection_sort(int array[], int size);
void print_array(const int array[], int size);

int main()
{
    int array[] = {5,2,4,6,1,3};
    int size = sizeof(array) / sizeof(array[0]);

    // Sort the array
    selection_sort(array, size);

    // Print the sorted array
    print_array(array, size);

    return 0;
}


/**
 * @brief Sorts an array of integers using the selection sort algorithm
 * @param array The array to sort
 * @param size Size of the array
 */
void selection_sort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;

        // Find the index of the minimum element in the unsorted part of the array
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[min_index])
            {
                min_index = j;
            }
        }

        // Swap the minimum element with the first element of the unsorted part
        int temp = array[i];
        array[i] = array[min_index];
        array[min_index] = temp;
    }
}

/**
 * @brief Prints the elements of an array
 * @param array The array to print
 * @param size Size of the array
 */
void print_array(const int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}