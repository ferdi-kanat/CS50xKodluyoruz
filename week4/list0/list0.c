/**
 * @file list0.c
 * @author Ferdi Kanat
 * @date 01/03/2025
 * 
 * This program reads numbers from the user until EOF and prints them in the order they were entered.
 */
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    // Memory for numbers
    node* numbers = NULL;

    // Prompt for numbers (until EOF)
    while (true)
    {
        // Prompt for number
        int number = get_int("number: ");
        
        // Check for EOF or error
        if (number == INT_MAX && (feof(stdin) || ferror(stdin)))
        {
            break;
        }

        // Allocate space for number
        node *n = malloc(sizeof(node));
        if (!n)
        {
            // Free previously allocated memory before exiting
            while (numbers != NULL)
            {
                node* tmp = numbers;
                numbers = numbers->next;
                free(tmp);
            }
            return 1;
        }
        
        // Add number to list
        n->number = number;
        n->next = NULL;
        if (numbers)
        {
            node* ptr;
            for (ptr = numbers; ptr->next != NULL; ptr = ptr->next);
            ptr->next = n;
        }
        else
        {
            numbers = n;
        }
    }
    
    // Print numbers
    for (node* ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // Free memory
    while (numbers != NULL)
    {
        node* tmp = numbers;
        numbers = numbers->next;
        free(tmp);
    }
    return 0;
}