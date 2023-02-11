#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
bool only_digits(string input);
char rotate_chars(char character, int rotations);
int main(int argc, string argv[])
{
    if (argc != 2)
        // Make sure program was run with just one command-line argument
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    bool checkDigits = only_digits(argv[1]);
    // Make sure every character in argv[1] is a digit
    if (!checkDigits)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int rotations = atoi(argv[1]);
    // Convert argv[1] from a `string` to an `int`
    string plaintext = get_string("plaintext: ");
    // Prompt user for plaintext
    printf("ciphertext: ");
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char character = rotate_chars(plaintext[i], rotations);
        printf("%c", character);
        // For each character in the plaintext rotate the character if it's a letter
    }
    printf("\n");
    // Print a new line for whatever fucking reason stupid ass checks for fucks sake this took me hours
}
bool only_digits(string input)
{
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        if (input[i] < 48 || input[i] > 57)
        {
            return false;
        }
    }
    return true;
}
char rotate_chars(char character, int rotations)
{
    if (isalpha(character))
    {
        if (isupper(character))
        {
            char result = (character - 65 + rotations) % 26 + 65;
            // Example with D and 2 rotations. 68 - 65 + 2 = 5; 5 % 26 = 5 + 65 = 70 == F
            return result;
        }
        else
        {
            char result = (character - 97 + rotations) % 26 + 97;
            return result;
        }
    }
    else
    {
        char result = character;
        return result;
    }
}