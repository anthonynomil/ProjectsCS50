#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Get the text and assign it to the variable text as a string
    string text = get_string("Text: ");

    // Get the length of the string, avoiding to put it in the loop for opti
    int tlength = strlen(text);

    float letter = 0;
    float sentence = 0;
    float word = 1;
    for (int i = 0; i < tlength; ++i)
    {
        if (isalnum(text[i]))
        {
            ++letter;
        }
        if (isspace(text[i]))
        {
            ++word;
        }
        if ((isalpha(text[i - 1]) || (ispunct(text[i + 1]))) && (text[i] == '.' || text[i] == '!' || text[i] == '?'))
        {
            ++sentence;
        }
    }

    float l = (letter / word) * 100;
    float s = (sentence / word) * 100;

    float index = 0.0588 * l - 0.296 * s - 15.8;
    int rindex = round(index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", rindex);
        //printf("Grade %f\n", index);
    }

    //printf("Letters: %f\n", letter);
    //printf("Sentences: %f\n", sentence);
    //printf("Words: %f\n", word);
}