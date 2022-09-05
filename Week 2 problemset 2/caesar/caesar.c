#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    // Exit the program if more than the command and the key is entered
    if (argc != 2)
    {
        printf("Usage : ./caesar key");
        return 1;
    }

    // Verify each character to see if it's a digit or not
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Please write a digit\n");
            return 1;
        }
    }

    // Get the string from the user, create the array ciphertext, convert the key to an integer and print ciphertext :
    string ptext = get_string("Plain text: ");
    int key = atoi(argv[1]);
    int l = strlen(ptext);
    char ctext[l];
    printf("ciphertext: ");

    // Create a loop to add the key to each character and leave the character as is if it's not an alphabetical ( Reducing by 65 for uppercase letters and 97 for the lower case letters to get a temporary alphabetical index) print the result
    for (int i = 0; i < l; i++)
    {
        if (isalpha(ptext[i]))
        {
            if (isupper(ptext[i]))
            {
                ctext[i] = ((((ptext[i]) - 65) + key) % 26) + 65;
            }
            else if (islower(ptext[i]))
            {
                ctext[i] = ((((ptext[i]) - 97) + key) % 26) + 97;
            }
            printf("%c", ctext[i]);
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
}