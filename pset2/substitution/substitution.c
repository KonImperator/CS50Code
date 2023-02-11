#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
bool check_alphabet(string input);
bool check_duplicates(string input);
// declaring functions to be used in main
int main(int argc, string argv[])
{
    if (argc < 2)
    // checking if there is no input of arguments
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    bool checkDuplicates = check_duplicates(argv[1]);
    bool checkLetter = check_alphabet(argv[1]);
    // calling functions and saving result in bool variable
    if (argc > 2)
    // checking if argument count exceeds 2
    {
        printf("Maximum arguments can't exceed 1.\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    // checking if length if argument is 26
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (checkDuplicates)
    // checking if there are duplicate letters
    {
        printf("Key must contain only unique characters.\n");
        return 1;
    }
    else if (!checkLetter)
    // checking if there are non-alphabetic characters
    {
        printf("Key must contain only alphabetic characters.\n");
        return 1;
    }
    string inputText = get_string("plaintext: ");
    // getting input from user
    printf("ciphertext: ");
    for (int i = 0, len = strlen(inputText); i < len; i++)
    // substracting ascii value of A/a from current character and using the result as the index to use from the input arg string
    {
        if (isupper(inputText[i]))
        {
            char character = argv[1][(inputText[i] - 'A')];
            printf("%c", toupper(character));
        }
        else if (islower(inputText[i]))
        {
            char character = argv[1][(inputText[i] - 'a')];
            printf("%c", tolower(character));
        }
        else
        {
           char character = inputText[i];
           printf("%c", character);
        }
    }
    printf("\n");
}
bool check_alphabet(string input)
{
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        if (!isalpha(input[i]))
        {
            return false;
        }
    }
    return true;
}
bool check_duplicates(string input)
{
    for (int i = 0, len = strlen(input); i < len; i++)
    // checking if there are no duplicates using tolower to remove case sensitivity
    {
        char currentChar = tolower(input[i]);
        for (int j = i + 1; j < len; j++)
        {
            char nextChar = tolower(input[j]);
            if (currentChar == nextChar)
            {
                return true;
            }
        }
    }
    return false;
}