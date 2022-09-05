from cs50 import get_string


def main():
    text = get_text()
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    index = get_index(letters, words, sentences)
    check_grade(index)

# Get the text to check from the user
def get_text():
    while True:
        text = get_string("Text: ")
        if len(text) > 0:
            break
    return text

# Count each letters from the text if they're alpha numeric
def count_letters(text):
    letters = 0
    for c in text:
        if (c.isalnum()):
            letters += 1
    return letters

# Count words by counting each spaces, start from 1 to count the last word
def count_words(text):
    words = 1
    for c in text:
        if c == ' ':
            words += 1
    return words

# Count sentences by counting punctuations that end sentences
def count_sentences(text):
    sentences = 0
    sentence_end = {'.', '!', '?'}
    for c in text:
        if c in sentence_end:
            sentences += 1
    return sentences

# Use the data we got from other functions to calculate the Coleman-Liau index
def get_index(letters, words, sentences):
    l = (letters / words) * 100
    s = (sentences / words) * 100
    index = 0.0588 * l - 0.296 * s - 15.8
    return index


# Check in which grade the text belong to
def check_grade(index):
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


main()