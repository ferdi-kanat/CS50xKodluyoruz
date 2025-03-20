"""
Cash - A program that calculates the minimum number of coins required to give a user change.
CS50x Kodluyoruz Week 6 Problem
"""

from cs50 import get_float
from typing import List

# Coin denominations in cents (quarters, dimes, nickels, pennies)
DENOMINATIONS = [25, 10, 5, 1]


def main() -> None:
    """
    Main function that prompts for change amount and displays minimum coins needed.
    """
    # Get the amount of change owed from the user
    change_amount = get_change_amount()

    # Convert the amount to cents
    cents = round(change_amount * 100)

    # Calculate and print the minimum number of coins
    coin_count = calculate_min_coins(cents, DENOMINATIONS)
    print(coin_count)


def get_change_amount() -> float:
    """
    Prompts the user for a positive amount of change.

    Returns:
        float: The change amount in dollars
    """
    while True:
        try:
            change_owed = get_float("Change owed: ")
            if change_owed > 0:
                return change_owed
            print("Please enter a positive amount.")
        except ValueError:
            print("Please enter a valid numeric amount.")


def calculate_min_coins(amount: int, coin_denominations: List[int]) -> int:
    """
    Calculates the minimum number of coins needed for the given amount.

    Args:
        amount: The amount in cents
        coin_denominations: Available coin denominations in cents

    Returns:
        int: Minimum number of coins needed
    """
    coins = 0

    for coin in coin_denominations:
        coins += amount // coin
        amount %= coin

    return coins


if __name__ == "__main__":
    main()