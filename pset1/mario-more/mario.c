#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("What height should the pyramid have?\n");
    while (height < 1 || height > 8)
    {
        height = get_int("What height should the pyramid have?\n");
    }
    for (int rows = 1; rows <= height; rows++)
    // main loop for the rows of the pyramid. The col loops are guided from this one
    {
        for (int spaces = height - rows; spaces > 0; spaces--)
        {
            printf(" ");
        }
        // loop for making the empty spaces before the pyramid. Going from the value of height to 0
        for (int leftCols = 0; leftCols < rows; leftCols++)
        {
            printf("#");
        }
        // loop for the left side of the pyramid. Adding dashes after the empty spaces have all been generated for the row
        printf(" ");
        printf(" ");
        // adding empty spaces after the dash/es on the row for the middle of the pyramid
        for (int rightCols = 0; rightCols < rows; rightCols++)
        {
            printf("#");
        }
        // loop for the right side of the pyramid. Same as the loop before it
        printf("\n");
        // starting the next row for the pyramid
    }
}