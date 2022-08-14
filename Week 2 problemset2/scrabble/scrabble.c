#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // DONE Print the winner or a draw depending on the scores
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    //create for the for loop
    int n = strlen(word);
    int score = 0;
    //create l to find at which place in the array we need to take the points
    int l = 0;
    // DONE
    for (int i = 0; i < n; ++i)
    {
        //If it's a lowercase remove -97 from the ASCII to get our alphabetical index from 0 to 27 if it's uppercase remove -65 per the Ascii else it's not a letter and won't add any points
        if (islower(word[i]))
        {
            l = word[i] - 97;
            score += POINTS[l];
        }
        else if (isupper(word[i]))
        {
            l = word[i] - 65;
            score += POINTS[l];
        }
        else {}
    }
    return score;
}
