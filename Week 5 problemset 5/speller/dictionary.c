// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Declare variables
unsigned int word_count;
unsigned int hash_value;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // DONE
    // Hash the word to get the hash value
    hash_value = hash(word);

    // Point the cursor to the first node
    node *cursor = table[hash_value];

    // Go through the linked list
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // DONE: Improve this hash function

    // Create a variable total to use later on
    unsigned long total = 0;

    // Create an int for the length of the word to optimize the for loop
    int word_len = strlen(word);

    // For each letter convert the letter to lowercase and add it to the total;
    for (int i = 0; i < word_len; ++i)
    {
        total += tolower(word[i]);
    }

    // Retun the total and get the remainder of total % N;
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // DONE

    // Open dictionary and verify that the file can be opened
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("%s cannot be opened\n", dictionary);
        return 1;
    }

    // Create a word variable to store the words
    char word[LENGTH + 1];

    // Scan the dictionary for words until there are no more words
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for the words and check if the memory is available
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the word into the node
        strcpy(n->word, word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        ++word_count;
    }

    // Close the file and return true
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // DONE
    // If the word count is superior to zero return the number of words
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Go through each bucket
    for (int i = 0; i < N; ++i)
    {
        // Set the cursor to each bucket location
        node *cursor = table[i];

        // If the cursor isn't NULL free the memory
        while (cursor != NULL)
        {
            // Create a temporary variable
            node *tmp = cursor;
            // Move cursor to next node
            cursor = cursor->next;
            // Free up temp
            free(tmp);
        }

        // If cursor is NULL return true
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }

    return false;
}
