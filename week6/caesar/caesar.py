# caesar task from cs50

import sys
from cs50 import get_string

def main():
    # Check if the correct number of command-line arguments is provided
    if len(sys.argv) != 2:
        print("Usage: python caesar.py key")
        sys.exit(1)

    # Get the key and ensure it is a positive integer
    try:
        key = int(sys.argv[1])
        if key < 0:
            raise ValueError
    except ValueError:
        print("Key must be a positive integer.")
        sys.exit(1)

    # Get the plaintext
    plaintext = get_string("plaintext: ")

    # Initialize the ciphertext
    ciphertext = ""

    # Iterate through the plaintext
    for char in plaintext:
        # Check if the character is an uppercase letter
        if char.isupper():
            # Calculate the new character
            new_char = chr((ord(char) - 65 + key) % 26 + 65)
            ciphertext += new_char
        # Check if the character is a lowercase letter
        elif char.islower():
            # Calculate the new character
            new_char = chr((ord(char) - 97 + key) % 26 + 97)
            ciphertext += new_char
        else:
            # If it's not a letter, just add it to the ciphertext
            ciphertext += char

    # Print the ciphertext
    print("ciphertext:", ciphertext)

if __name__ == "__main__":
    main()
