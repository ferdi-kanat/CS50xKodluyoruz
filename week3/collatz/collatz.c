/**
 * @file collatz.c
 * @author Ferdi Kanat
 * @date 2025/02/20
 * @brief This program calculates the collatz conjecture for a given number.
 * 
 * The program takes a number from the user and calculates the collatz conjecture for that number.
 * The collatz conjecture is a conjecture in mathematics that states that for any positive integer n, the sequence defined by:
 * n -> n/2 (if n is even)
 * n -> 3n + 1 (if n is odd)
 * will eventually reach 1.
 * 
 */
#include <stdio.h>

void collatz(int n);

int main(void) {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) { 
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (number < 1) { 
        fprintf(stderr, "Please enter a positive integer.\n");
        return 1;
    }
    collatz(number);
    return 0;
}

/**
 * @brief This function calculates the collatz conjecture for a given number.
 * 
 * This function takes a number as an argument and calculates the collatz conjecture for that number.
 * The function prints the numbers in the sequence to the screen.
 * 
 * @param number The number to calculate the collatz conjecture for.
 */
void collatz(int number) {
    printf("%d ", number);
    if (number == 1) {
        return;
    } 
    else if (number % 2 == 0) 
    {
        collatz(number / 2);
    } 
    else 
    {
        collatz(3 * number + 1);
    }
}