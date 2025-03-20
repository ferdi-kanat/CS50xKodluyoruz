# hello python task
# This is a simple Python program that prints "hello, {name}" to the console.
# It prompts the user for their name and uses string formatting to create a personalized greeting.
# The program also includes a function to print the greeting, demonstrating the use of functions in Python.

# Function to print the greeting
def print_greeting(name):
    """
    This function takes a name as an argument and prints a greeting message.
    :param name: str
    """
    print(f"hello, {name}")

# Main function to run the program
def main():
    """
    Main function to run the hello python program.
    """
    # Prompt the user for their name
    name = input("What is your name? ")

    # Call the print_greeting function with the user's name
    print_greeting(name)

# Entry point of the program
if __name__ == "__main__":
    main()
