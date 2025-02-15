/**
 * @file insertion_sort.c
 * @author Ferdi Kanat
 * @date 2025/02/11
 * @brief Sorts an array of integers using the insertion sort algorithm
 * 
 * This program sorts an array of integers using the insertion sort algorithm.
 * 
 * @example
 * Input: 5 2 4 6 1 3
 * Output: 1 2 3 4 5 6
 */

#include <stdio.h>

#define MAX_ARRAY_SIZE 100
#define MIN_ARRAY_SIZE 1

/* Function prototypes */
void insertion_sort(int array[], int size);
void print_array(const int array[], int size);

int main(void)
{
    int array[] = {5,2,4,6,1,3};
    int size = sizeof(array) / sizeof(array[0]);

    // Validate array size
    if (size < MIN_ARRAY_SIZE || size > MAX_ARRAY_SIZE) 
    {
        fprintf(stderr, "Error: Array size must be between %d and %d.\n", MIN_ARRAY_SIZE, MAX_ARRAY_SIZE);
        return 1;
    }

    // Print the original array
    printf("Original array:\n");
    print_array(array, size);

    // Sort the array
    insertion_sort(array, size);

    // Print the sorted array
    printf("Sorted array:\n");
    print_array(array, size);
}

/**
 * @brief Sorts an array of integers using the insertion sort algorithm.
 * @param array The array to be sorted.
 * @param size The size of the array.
 */
void insertion_sort(int array[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

/**
 * @brief Prints the elements of an array.
 * @param array The array to be printed.
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