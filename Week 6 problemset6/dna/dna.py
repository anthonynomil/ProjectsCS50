import csv
import sys


def main():

    # DONE: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(4012)
    # DONE: Read database file into a variable
    data = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            data.append(row)

    # DONE: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        sequence = file.read()

    # DONE: Find longest match of each STR in DNA sequence
    STR = list(data[0].keys())[1:]
    STR_match = {}
    STR_len = len(STR)
    for i in range(STR_len):
        STR_match[STR[i]] = longest_match(sequence, STR[i])

    # DONE: Check database for matching profiles
    data_len = len(data)
    for i in range(data_len):
        counter = 0
        for j in range(STR_len):
            if int(STR_match[STR[j]]) == int(data[i][STR[j]]):
                counter += 1
            if counter == STR_len:
                print(data[i]["name"])
                return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break
            
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
