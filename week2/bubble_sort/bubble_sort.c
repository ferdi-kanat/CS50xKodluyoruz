/**
 * @file bubble_sort.c
 * @author Ferdi Kanat
 * @date 2025/02/10
 * @brief Sorts an array of integers using the bubble sort algorithm.
 *
 * This program demonstrates the bubble sort algorithm to order an array of 
 * integers. It validates the array size before proceeding with sorting.
 */
#include <stdio.h>

#define MAX_ARRAY_SIZE 100
#define MIN_ARRAY_SIZE 1

/* Function prototypes */
void bubble_sort(int array[], int size);
void print_array(const int array[], int size);

int main(void)
{
    int array[] = {5, 2, 4, 6, 1, 3};
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

    // Sort the array using bubble sort
    bubble_sort(array, size);

    // Print the sorted array
    printf("Sorted array:\n");
    print_array(array, size);

    return 0;
}

/**
 * @brief Sorts an array of integers using the bubble sort algorithm.
 * @param array The array to be sorted.
 * @param size The size of the array.
 */
void bubble_sort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++) 
    {
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (array[j] > array[j + 1]) 
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
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