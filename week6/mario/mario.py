# mario task

def main():
    attempts = 0
    max_attempts = 3
    while attempts < max_attempts:
        try:
            # input for the height of the pyramid
            height = int(input("Height: "))
            if 1 <= height <= 8:
                break
        except ValueError:
            pass

    # loop for the height of the pyramid
    for i in range(1, height + 1):
        print(" " * (height - i) + "#" * i)

if __name__ == "__main__":
    main()