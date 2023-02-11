#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("What height should the pyramid be?\n");
    while (height <= 0 || height > 8)
    // height should be a positive number that's not higher than 8
    {
        height = get_int("What height should the pyramid be?\n");
    // looping to repeat the question if input is incorrect
    }
    for (int i = 0; i < height; i++)
    // first loop to make up the rows of the pyramid
    {
        for (int b = 1; b < height - i; b++)
    // second loop to make up the number of empty spaces
        {
            printf(" ");
    // printing empty space to allign the pyramid to the right
        }
        for (int a = 0; a <= i; a++)
    // third loop to make up the number of hashes/"#"
        {
            printf("#");
    //printing a hash on the same row for every loop in the cycle
        }
        printf("\n");
    // printing new row after the hash loop to separate the pyramid tiers
    }
}