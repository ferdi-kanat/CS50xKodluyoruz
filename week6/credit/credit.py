# credit task cs50

# import libraries
from cs50 import get_string

# function to check the length of the card number
def check_length(card_number):
    # check if the card number is between 13 and 16 digits
    if len(card_number) < 13 or len(card_number) > 16:
        return False
    return True

# function to check the prefix of the card number
def check_prefix(card_number):
    # check if the card number starts with 4, 5, 6, or 37
    if card_number[0] == '4' or card_number[0] == '5' or card_number[0] == '6':
        return True
    elif card_number[0] == '3' and card_number[1] == '7':
        return True
    return False

# function to check the Luhn algorithm
def check_luhn(card_number):
    # convert the card number to a list of integers
    card_number = [int(i) for i in card_number]
    # reverse the card number
    card_number.reverse()
    # double every second digit
    for i in range(1, len(card_number), 2):
        card_number[i] = card_number[i] * 2
        # if the digit is greater than 9, subtract 9
        if card_number[i] > 9:
            card_number[i] = card_number[i] - 9
    # sum all the digits
    total = sum(card_number)
    # check if the total is divisible by 10
    if total % 10 == 0:
        return True
    return False
# function to check the card type
def check_card_type(card_number):
    # check if the card number starts with 4
    if card_number[0] == '4':
        return "VISA"
    # check if the card number starts with 5
    elif card_number[0] == '5':
        return "MASTERCARD"
    # check if the card number starts with 6
    elif card_number[0] == '6':
        return "DISCOVER"
    # check if the card number starts with 37
    elif card_number[0] == '3' and card_number[1] == '7':
        return "AMEX"
    return None

# main function
def main():
    # get the card number from the user
    card_number = get_string("Number: ")
    # check if the card number is valid
    if check_length(card_number) and check_prefix(card_number) and check_luhn(card_number):
        # check the card type
        card_type = check_card_type(card_number)
        if card_type:
            print(card_type)
        else:
            print("INVALID")
    else:
        print("INVALID")

# call the main function
if __name__ == "__main__":
    main()