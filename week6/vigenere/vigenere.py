import sys

def main():
    # Get key from command line argument
    if len(sys.argv) != 2:
        print("Usage: python vigenere.py key")
        sys.exit(1)

    key = sys.argv[1]
    if not key.isalpha():
        print("Key must contain only letters.")
        sys.exit(1)

    # Get plaintext from user
    plaintext = input("plaintext: ")

    # Print ciphertext
    print("ciphertext: ", end="")
    key_pos = 0

    # Iterate through each character in plaintext
    for c in plaintext:
        if c.isalpha():
            # Calculate shift based on key character
            shift = ord(key[key_pos % len(key)].upper()) - ord('A')

            # Handle uppercase
            if c.isupper():
                print(chr((ord(c) - ord('A') + shift) % 26 + ord('A')), end="")
            # Handle lowercase
            else:
                print(chr((ord(c) - ord('a') + shift) % 26 + ord('a')), end="")

            key_pos += 1
        else:
            # Print non-alphabetic characters as is
            print(c, end="")

    print()

if __name__ == "__main__":
    main()