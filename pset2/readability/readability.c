#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
// function prototypes so that main function can call the fucntions queued separately below main
int main(void)
{
    string input = get_string("Text: ");
    float letterCount = count_letters(input);
    float wordCount = count_words(input);
    float sentenceCount = count_sentences(input);
    // numbers type is float, since if it's int, it doesn't calculate properly. Dumb language

    double L = (letterCount / wordCount) * 100;
    double S = (sentenceCount / wordCount) * 100;
    // double for funzies
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    // int since it's rounded to the closest number without a decimal point
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
// function for calculating number of letters
{
    int letterCount = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        // checks if the current element is from the alphabet
        {
            letterCount++;
        }
    }
    return letterCount;
}
int count_words(string text)
// function for calculating number of words
{
    int wordCount = 1;
    // starting with the first word since there's no space before it
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        // checks if the current element is a space
        {
            wordCount++;
        }
    }
    return wordCount;
}
int count_sentences(string text)
// function for calculating number of sentences
{
    int sentenceCount = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        // separating sentences by these three symbols for now, I know it's not correct
        {
            sentenceCount++;
        }
    }
    return sentenceCount;
}