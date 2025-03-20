from cs50 import get_string
import sys

def main():
    # Check command line arguments
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    # Load banned words from file
    banned = set()
    try:
        with open(sys.argv[1]) as file:
            for line in file:
                banned.add(line.strip().lower())
    except FileNotFoundError:
        print("Could not load dictionary.")
        sys.exit(1)

    # Get message from user
    message = get_string("What message would you like to censor?\n")

    # Process each word in the message
    words = message.split()
    for i, word in enumerate(words):
        if word.lower() in banned:
            # Replace banned word with asterisks
            words[i] = '*' * len(word)

    # Print censored message
    print(' '.join(words))

if __name__ == "__main__":
    main()