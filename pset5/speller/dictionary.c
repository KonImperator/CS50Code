// Implements a dictionary's functionality
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

// Word counter
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    unsigned int value = 0;
    //Initializing return value
    unsigned int key_len = strlen(word);
    //Initializing word length
    for (int i = 0; i < key_len; i++)
    {
        value = value + 37 * tolower(word[i]);
        //Iterating over the word's chars adding 37 * char ascii value to initial value
    }
    value = value % N;
    //Getting final value by modding with number of buckets (N)
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char new_word[LENGTH + 1];
    // Initialize new word
    FILE *dict = fopen(dictionary, "r");
    // Open dictionary file for reading
    if (dict == NULL)
    {
        printf("Loading dictionary failed.");
        return false;
    }

    while (fscanf(dict, "%s", new_word) != EOF)
    // Start reading strings until end of file
    {

        node *new_node = malloc(sizeof(node));
        // Allocate memory to new node
        if (new_node == NULL)
        {
            printf("Not enough memory.");
            return false;
        }
        unsigned int index = hash(new_word);
        // Hashing new word to get index to place it in on the hash table
        strcpy(new_node->word, new_word);
        // Copying word over to the new node
        if (table[index] == NULL)
        {
            new_node->next = NULL;
            table[index] = new_node;
        }
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
        word_count++;
    }

    fclose(dict);
    return true;
    // TODO
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    // TODO
    return true;
}
