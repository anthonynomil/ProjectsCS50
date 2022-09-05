from cs50 import get_int

def main():
    # While height not between 0 and 9 (so 1 to 8) ask the height
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    # While i inferior to the height add height - i number of spaces then i number of blocs then two spaces then repeat the first two inversed
    i = 1
    while i <= height:
        space(height - i)
        bloc(i)
        space(2)
        bloc(i)
        print()
        i += 1

# Create a function bloc to write # * n
def bloc(n):
    print("#" * n, end="")

# Create a function space to write a space * n
def space(n):
    print(" " * n, end="")

main()
