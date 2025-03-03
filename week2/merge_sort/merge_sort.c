/**
 * @file merge_sort.c
 * @author Ferdi Kanat
 * @date 2025/02/11
 *
 * @brief Sorts an array of integers using the merge sort algorithm.
 *
 * This program demonstrates the merge sort algorithm to order an array of
 * integers. It validates the array size before proceeding with sorting.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 100
#define MIN_ARRAY_SIZE 1

/* Function prototypes */
void merge_sort(int array[], int left, int right);
void merge(int array[], int left, int middle, int right);
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

    // Sort the array using merge sort
    merge_sort(array, 0, size - 1);

    // Print the sorted array
    printf("Sorted array:\n");
    print_array(array, size);

    return 0;
}

/**
 * @brief Sorts an array of integers using the merge sort algorithm.
 * @param array The array to be sorted.
 * @param left The leftmost index of the array.
 * @param right The rightmost index of the array.
 */
void merge_sort(int array[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        // Sort the left half
        merge_sort(array, left, middle);

        // Sort the right half
        merge_sort(array, middle + 1, right);

        // Merge the sorted halves
        merge(array, left, middle, right);
    }
}

/**
 * @brief Merges two sorted subarrays into one sorted array.
 * @param array The array to be merged.
 * @param left The leftmost index of the array.
 * @param middle The middle index of the array.
 * @param right The rightmost index of the array.
 */
void merge(int array[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    int left_array[n1], right_array[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
    {
        left_array[i] = array[left + i];
    }

    for (j = 0; j < n2; j++)
    {
        right_array[j] = array[middle + 1 + j];
    }

    // Merge the temporary arrays back into the original array
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (left_array[i] <= right_array[j])
        {
            array[k] = left_array[i];
            i++;
        }
        else
        {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left_array if any
    while (i < n1)
    {
        array[k] = left_array[i];
        i++;
        k++;
    }

    // Copy remaining elements of right_array if any
    while (j < n2)
    {
        array[k] = right_array[j];
        j++;
        k++;
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