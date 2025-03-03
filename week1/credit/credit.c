/**
 * @file credit.c
 * @author Ferdi Kanat
 * @date 2025/02/07
 * @brief Calculates the validity of a credit card number
 * 
 * This program prompts the user for a credit card number and
 * determines whether it is a valid American Express, MasterCard,
 * or Visa card number.
 * 
 * @example
 * Input: Number: 378282246310005
 * Output: AMEX
 */
#include <stdio.h>
#include <cs50.h>

bool luhn_algorithm(long card_number);
void determine_card_type(long card_number);

int main(void)
{
    long card_number;
    do 
    {
        card_number = get_long("Number: ");
    } 
    while (card_number <= 0);
    
    if (luhn_algorithm(card_number))
    {
        determine_card_type(card_number);
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

// Luhn algoritması
bool luhn_algorithm(long card_number)
{
    int sum = 0;
    bool is_second = false;
    long temp = card_number;

    while (temp > 0)
    {
        int digit = temp % 10;

        if (is_second)
        {
            digit *= 2;
            sum += (digit > 9) ? (digit - 9) : digit;
        }
        else
        {
            sum += digit;
        }
        
        is_second = !is_second;
        temp /= 10;
    }

    return (sum % 10) == 0;
}

void determine_card_type(long card_number)
{
    // Kartın uzunluğunu hesapla
    long temp = card_number;
    int length = 0;
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }

    // İlk iki basamağı al
    temp = card_number;
    while (temp >= 100)
    {
        temp /= 10;
    }
    int first_two_digits = temp;
    int first_digit = first_two_digits / 10;

    // Kart tipini belirle
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && first_two_digits >= 51 && first_two_digits <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}