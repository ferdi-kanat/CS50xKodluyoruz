# mario advanced task
'''Height: 5
    # #
   ## ##
  ### ###
 #### ####
##### #####'''

def mario_advanced(height):
    attempts = 0
    max_attempts = 3

    # check if height is between 1 and 8
    while attempts < max_attempts:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                break
            else:
                print("Please enter a number between 1 and 8.")
        except ValueError:
            print("Please enter a valid number.")
        attempts += 1
    else:
        print("Too many invalid attempts. Exiting program.")
        return

    # print the pyramid
    for i in range(height):
        # print spaces
        for j in range(height - i - 1):
            print(" ", end="")
        # print left pyramid
        for j in range(i + 1):
            print("#", end="")
        # print gap
        print("  ", end="")
        # print right pyramid
        for j in range(i + 1):
            print("#", end="")
        # print new line
        print()

if __name__ == "__main__":
    # get height from user
    mario_advanced(0)