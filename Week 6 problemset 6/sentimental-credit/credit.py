from cs50 import get_string


def main():

    card = get_number()
    is_valid = validate_card(card)
    type_of_card(is_valid, card)


# This function gets the number from the user and keeps asking until a valid number is given
def get_number():
    while True:
        card = get_string("Number: ")
        if int(card) > 0:
            break
    return card

# Validate the card with the Luhn's Algorithm
def validate_card(card_number):

    # Transfer the string card_number in another list as integers create a full_sum to addition all numbers
    card_number_int = list(map(int, card_number))
    full_sum = 0
    len_card = len(card_number_int)

    # Check the card from the end 2 by 2 and multiply each number by 2 and remove 9 if the number is 10 or above then assign them  to the nb variable
    for i in range(len_card - 2, -1, -2):  # 15 -1 -2,
        nb = card_number_int[i] * 2
        if nb > 9:
            nb = nb - 9
        card_number_int[i] = nb

    # for every number in the card add it to the full_sum
    for i in range(len_card - 1, -1, -1):
        full_sum += card_number_int[i]

    # Check if it's a multiple of ten and that the card has between 13 and 16 numbers both of those numbers included
    if full_sum % 10 == 0 and (len(card_number) >= 13 and len(card_number) <= 16):
        return True
    else:
        return False

# Check which type of card it is by checking the 2 first numbers of the card
def type_of_card(is_valid, card_number):
    if is_valid == True:
        if int(card_number[0]) == 3 and (int(card_number[1]) == 4 or int(card_number[1]) == 7):
            print("AMEX")
        elif int(card_number[0]) == 5 and (1 <= int(card_number[1]) <= 5):
            print("MASTERCARD")
        elif int(card_number[0]) == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()
