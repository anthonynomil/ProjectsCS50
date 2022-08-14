#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Define the number chosen by the user and forces the user to choose a number between 1 and 8
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);

    //define rows
    int r;
    //define spaces
    int s;
    //define blocks
    int b;

    for (r = 1; r <= n; r++)
    {
        //You remove the number of rows to the general number to get the spaces
        s = n - r;
        // You remove the number of spaces to the general number to get the blocks
        b = n - s;

        //This print the spaces on the left obstacle
        for (int x = 0; x < s; x++)
        {
            printf(" ");
        }
        //This print the blocks on the left obstacle
        for (int y = 0; y < b; y++)
        {
            printf("#");
        }
        //The two spaces between the two obstacles
        printf(" ");
        printf(" ");
        //This print the blocks on the right obstacles no need for the spaces for this side
        for (int y = 0; y < b; y++)
        {
            printf("#");
        }
        //Return to the line
        printf("\n");
    }
}