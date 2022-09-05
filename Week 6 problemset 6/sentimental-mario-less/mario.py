from cs50 import get_int

# While height not between 0 and 9 (so 1 to 8) ask the height
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# While i <= height then print the spaces before the bloc, print the bloc * i, add 1 to i, print \n
i = 1
while i <= height:
    print(" " * (height - i), end="")
    print("#" * i, end="")
    i += 1
    print()
