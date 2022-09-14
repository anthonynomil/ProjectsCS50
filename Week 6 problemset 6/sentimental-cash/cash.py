# TODO
from cs50 import get_float


def main():
    cents = get_cents()
    print(f"{calculate_coins(cents)}")

# Get the number of cents from the user
def get_cents():
    while True:
        cents = get_float("How much: ")
        if cents > 0:
            break
    return cents

# Calculate by removing each type of coin one at a time and return the amount of the coins.
def calculate_coins(n):
    coins = 0
    remaining = int(n * 100)
    while remaining >= 25:
        remaining -= 25
        coins += 1
    while remaining >= 10:
        remaining -= 10
        coins += 1
    while remaining >= 5:
        remaining -= 5
        coins += 1
    while remaining >= 1:
        remaining -= 1
        coins += 1
    return coins


main()
