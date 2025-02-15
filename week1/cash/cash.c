/**
 * @file cash.c
 * @author Ferdi Kanat
 * @date 2025/02/07
 * @brief Calculates the minimum number of coins needed for change
 *
 * This program prompts the user for a cash amount and calculates
 * the minimum number of coins (quarters, dimes, nickels, pennies)
 * needed to make that change.
 *
 * @example
 * Input: Change owed: 0.41
 * Output: 4
 */
#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Constants
#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1
#define NUM_DENOMINATIONS 4

// Function prototypes
static float get_valid_cash(void);
static void calculate_change(float cash);

int main(void)
{
    printf("Welcome to Cash Change Calculator!\n\n");
    float cash = get_valid_cash();
    calculate_change(cash);
    return 0;
}

/**
 * Gets a valid cash amount from the user.
 * @return Float value greater than 0
 * @note The function will keep prompting the user until a valid cash amount is entered.
 * @note The function uses get_float() from the CS50 library.
 */
static float get_valid_cash(void)
{   
    float cash;
    do {
        cash = get_float("Change owed: ");
    } while (cash <= 0);
    return cash;
}

/**
 * Calculates the change owed to the customer.
 * @param cash The cash amount entered by the user
 */
static void calculate_change(float cash)
{
    int cents = round(cash * 100);
    int coin_count = 0;
    int denominations[] = {QUARTER, DIME, NICKEL, PENNY};
    for (int i = 0; i < NUM_DENOMINATIONS; i++)
    {
        coin_count += cents / denominations[i];
        cents %= denominations[i];
    }
    printf("%d\n", coin_count); // Added newline for clean output
}