#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Exit the program if more than the command and the key is entered
    if (argc != 2)
    {
        printf("Usage : ./substitution key\n");
        return 1;
    }

    // Put the code in a string
    string scode = argv[1];
    // Put the code in an array as char
    char code[26];
    // Create a variable for the alphabetical index that we'll use later on
    int aindex;

    // Verify each character to see if they are letters and if there are 26 characters
    int argvlen = strlen(argv[1]);
    int duo = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (isdigit(argv[1][i]))
        {
            printf("Please write letters\n");
            return 1;
        }
        if (argvlen < 26 || argvlen > 26)
        {
            printf("Please enter 26 characters\n");
            return 1;
        }
    }


    // Assign the code string to each char in the array and check if it's a lowercase and convert it to uppercase
    for (int i = 0; i < 26; ++i)
    {
        code[i] = scode[i];
        if (islower(code[i]))
        {
            code[i] -= 32;
        }
    }

    //Create a second array to avoid duplicate checks on the same letter and check for duplicates
    char checker[26];
    int checkerlength = 0;
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            if (code[i] == checker[j])
            {
                printf("You done goofed\n");
                return 1;
            }
        }
        checker[checkerlength++] = code[i];
    }

    // Ask for the sentence to cipher and assign it to ptext
    string ptext = get_string("Text: ");
    // Get the length of the ptext plain text variable
    int ptextlen = strlen(ptext);

    //Start ciphering each letters and check if they're upper and lower case, else just print back the
    printf("ciphertext: ");
    for (int i = 0; i < ptextlen; ++i)
    {
        if (isalpha(ptext[i]))
        {
            if (isupper(ptext[i]))
            {
                aindex = ptext[i] - 65;
                printf("%c", code[aindex]);
            }
            else if (islower(ptext[i]))
            {
                aindex = ptext[i] - 97;
                printf("%c", code[aindex] + 32);
            }
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
}